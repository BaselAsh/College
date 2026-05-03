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
    # Ensure 'student_performance.csv' is in the same directory
    plt.style.use("dark_background")
    df = pd.read_csv("student_performance.csv")

    print("--- Dataset Overview ---")
    print(f"Shape: {df.shape}")
    print(df.info())

    # ---------------------------------------------------------
    # 2. Exploratory Data Analysis (EDA)
    # ---------------------------------------------------------
    print("\n--- Summary Statistics ---")
    print(df.describe(include="all"))

    print("\n--- Missing Values ---")
    print(df.isnull().sum())

    # Generate EDA Visualizations
    plt.figure(figsize=(15, 5))

    # Plot A: Target Variable Distribution
    plt.subplot(1, 3, 1)
    sns.histplot(df["final_score"], bins=20, kde=True, color="skyblue")
    plt.title("Distribution of Final Scores")
    plt.xlabel("Final Score")

    # Plot B: Study Hours vs Final Score
    plt.subplot(1, 3, 2)
    sns.scatterplot(x="study_hours_per_week", y="final_score", hue="passed", data=df)
    plt.title("Study Hours vs Final Score")

    # Plot C: Correlation Heatmap
    plt.subplot(1, 3, 3)
    num_cols = df.select_dtypes(include=["int64", "float64"]).columns
    sns.heatmap(df[num_cols].corr(), annot=True, cmap="coolwarm", fmt=".2f")
    plt.title("Correlation Heatmap")

    plt.tight_layout()
    plt.show()  # Save these plots for your PowerPoint

    # ---------------------------------------------------------
    # 3. Data Cleaning & 4. Feature Engineering
    # ---------------------------------------------------------
    # Separate target and features
    # Drop 'student_id' (irrelevant) and 'passed' (target leakage)
    X = df.drop(columns=["student_id", "final_score", "passed"])
    y = df["final_score"]

    # Define feature types
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

    # Preprocessing pipelines
    numeric_transformer = Pipeline(
        steps=[
            ("imputer", SimpleImputer(strategy="median")),  # Handle any missing numbers
            ("scaler", StandardScaler()),  # Feature Scaling
        ]
    )

    categorical_transformer = Pipeline(
        steps=[
            (
                "imputer",
                SimpleImputer(strategy="constant", fill_value="Unknown"),
            ),  # Fill missing categories
            (
                "onehot",
                OneHotEncoder(handle_unknown="ignore"),
            ),  # Encode text to numbers
        ]
    )

    # Combine preprocessing steps
    preprocessor = ColumnTransformer(
        transformers=[
            ("num", numeric_transformer, numeric_features),
            ("cat", categorical_transformer, categorical_features),
        ]
    )

    # ---------------------------------------------------------
    # 5. Machine Learning Model
    # ---------------------------------------------------------
    # Create full modeling pipeline
    model = Pipeline(
        steps=[
            ("preprocessor", preprocessor),
            ("regressor", RandomForestRegressor(n_estimators=100, random_state=42)),
        ]
    )

    # Split Data (80% Training, 20% Testing)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42
    )

    # Train the Model
    model.fit(X_train, y_train)

    # ---------------------------------------------------------
    # 6. Model Evaluation
    # ---------------------------------------------------------
    y_pred = model.predict(X_test)
    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(mse)
    r2 = r2_score(y_test, y_pred)

    print("\n--- Model Evaluation ---")
    print(f"Mean Squared Error (MSE): {mse:.2f}")
    print(f"Root Mean Squared Error (RMSE): {rmse:.2f}")
    print(f"R-squared (R2): {r2:.2f}")

    # ---------------------------------------------------------
    # 7. Insights (Feature Importance)
    # ---------------------------------------------------------
    # Extract feature names after encoding
    rf_model = model.named_steps["regressor"]
    cat_features_encoded = (
        model.named_steps["preprocessor"]
        .named_transformers_["cat"]
        .named_steps["onehot"]
        .get_feature_names_out(categorical_features)
    )
    all_features = numeric_features + list(cat_features_encoded)

    # Map importances
    feature_importance_df = pd.DataFrame(
        {"Feature": all_features, "Importance": rf_model.feature_importances_}
    )
    feature_importance_df = feature_importance_df.sort_values(
        by="Importance", ascending=False
    )

    # Plot Feature Importances
    plt.figure(figsize=(10, 6))
    sns.barplot(x="Importance", y="Feature", data=feature_importance_df.head(10))
    plt.title("Top 10 Drivers of Student Performance")
    plt.tight_layout()
    plt.show()  # Save this plot for your PowerPoint


if __name__ == "__main__":
    main()
