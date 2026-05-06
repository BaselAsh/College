import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.compose import ColumnTransformer
from sklearn.ensemble import RandomForestRegressor
from sklearn.impute import SimpleImputer
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import OneHotEncoder, StandardScaler


def main():
    # ---------------------------------------------------------
    # 1. Dataset Selection & Loading
    # ---------------------------------------------------------
    plt.style.use("dark_background")
    df = pd.read_csv("student_performance.csv")

    # ---------------------------------------------------------
    # 2. Exploratory Data Analysis (EDA)
    # ---------------------------------------------------------
    # Plot A: Target Variable Distribution
    plt.figure(figsize=(8, 6))
    # bins=20: Divides the data into 20 bars to show frequency.
    # kde=True: Plots a Kernel Density Estimate (a smooth curve over the bars).
    sns.histplot(df["final_score"], bins=20, kde=True, color="skyblue")
    plt.title("Distribution of Final Scores")
    plt.show()

    # Plot B: Study Hours vs Final Score
    plt.figure(figsize=(8, 6))
    # hue="passed": Colors points based on whether they passed, helping identify clusters.
    plt.scatterplot(x="study_hours_per_week", y="final_score", hue="passed", data=df)
    plt.title("Study Hours vs Final Score")
    plt.show()

    # Plot C: Correlation Heatmap
    plt.figure(figsize=(8, 6))
    num_cols = df.select_dtypes(include=["int64", "float64"]).columns
    # annot=True: Displays the raw correlation number in each cell.
    # cmap="coolwarm": A diverging color map (red for positive, blue for negative correlation).
    sns.heatmap(df[num_cols].corr(), annot=True, cmap="coolwarm", fmt=".2f")
    plt.title("Correlation Heatmap")
    plt.show()

    # ---------------------------------------------------------
    # 3. Data Cleaning & 4. Feature Engineering
    # ---------------------------------------------------------
    # Dropping 'student_id' because it's a random unique ID with no predictive value.
    # Dropping 'passed' because it's calculated from 'final_score' (target leakage).
    X = df.drop(columns=["student_id", "final_score", "passed"])
    y = df["final_score"]

    numeric_features = [
        "age",
        "study_hours_per_week",
        "attendance_rate",
        "previous_score",
    ]
    categorical_features = [
        "gender",
        "parent_education",
        "internet_access",
        "extracurricular",
    ]

    # --- Numeric Transformation ---
    numeric_transformer = Pipeline(
        steps=[
            # strategy="median": Fills missing values with the middle value.
            # Better than 'mean' if you have outliers in your student data.
            ("imputer", SimpleImputer(strategy="median")),
            # StandardScaler: Rescales data so mean=0 and variance=1.
            # Crucial so 'attendance_rate' (0-100) doesn't overpower 'age' (18-22).
            ("scaler", StandardScaler()),
        ]
    )

    # --- Categorical Transformation ---
    categorical_transformer = Pipeline(
        steps=[
            # fill_value="Unknown": Instead of guessing, we create a new category for missing text.
            ("imputer", SimpleImputer(strategy="constant", fill_value="Unknown")),
            # handle_unknown="ignore": If the test set has a category not seen in training,
            # it will just set all zeros instead of crashing the script.
            ("onehot", OneHotEncoder(handle_unknown="ignore")),
        ]
    )

    # Combine transformers. remainder='passthrough' could be added if we had other columns.
    preprocessor = ColumnTransformer(
        transformers=[
            ("num", numeric_transformer, numeric_features),
            ("cat", categorical_transformer, categorical_features),
        ]
    )

    # ---------------------------------------------------------
    # 5. Machine Learning Model
    # ---------------------------------------------------------
    model = Pipeline(
        steps=[
            ("preprocessor", preprocessor),
            # n_estimators=100: The number of trees in the forest. More is usually better but slower.
            # random_state=42: A seed for the random number generator so you get the same results every run.
            ("regressor", RandomForestRegressor(n_estimators=100, random_state=42)),
        ]
    )

    # test_size=0.2: Reserves 20% of the data for testing, 80% for training.
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    # fit(): The "learning" phase where the model maps features to the target score.
    model.fit(X_train, y_train)

    # ---------------------------------------------------------
    # 6. Model Evaluation
    # ---------------------------------------------------------
    y_pred = model.predict(X_test)
    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(
        mse
    )  # RMSE tells you how many "score points" your model is off on average.
    r2 = r2_score(
        y_test, y_pred
    )  # 1.0 is perfect; 0.0 is as bad as guessing the average.

    print(f"\nRMSE: {rmse:.2f} | R2: {r2:.2f}")

    # ---------------------------------------------------------
    # 7. Insights (Feature Importance)
    # ---------------------------------------------------------
    rf_model = model.named_steps["regressor"]
    # get_feature_names_out: Maps the binary 0/1 columns back to their original names.
    cat_features_encoded = (
        model.named_steps["preprocessor"]
        .named_transformers_["cat"]
        .named_steps["onehot"]
        .get_feature_names_out(categorical_features)
    )
    all_features = numeric_features + list(cat_features_encoded)

    feature_importance_df = pd.DataFrame(
        {"Feature": all_features, "Importance": rf_model.feature_importances_}
    )
    feature_importance_df = feature_importance_df.sort_values(
        by="Importance", ascending=False
    )

    plt.figure(figsize=(10, 6))
    sns.barplot(x="Importance", y="Feature", data=feature_importance_df.head(10))
    plt.title("Top 10 Drivers of Student Performance")
    plt.show()


if __name__ == "__main__":
    main()
