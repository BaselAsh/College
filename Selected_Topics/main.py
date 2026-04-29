import re

import pandas as pd
from sklearn.feature_extraction.text import ENGLISH_STOP_WORDS

STOP_WORDS = set(ENGLISH_STOP_WORDS)
sw = set(ENGLISH_STOP_WORDS)
sw.add("hate")


def clean_text(text, stop_words):
    text = text.lower()
    text = re.sub(r"[^\w\s]", "", text)
    words = text.split()
    words = [word for word in words if word not in stop_words]

    return " ".join(words)


def main():
    data = {
        "review": [
            "I hate this this thing",
            "I love this product",
            "This is the worst experience",
            "Absolutely fantastic service",
            "I hate it",
            "Not bad, could be better",
            "Very happy with the quality",
        ],
        "sentiment": [0, 1, 0, 1, 0, 1, 1],
    }
    df = pd.DataFrame(data)
    df["review_length"] = df["review"].apply(lambda x: len(x))
    df["word_count"] = df["review"].apply(lambda x: x.count(" ") + 1)
    df["clean_review"] = df["review"].apply(lambda x: clean_text(x, STOP_WORDS))
    df["clean_review_no_hate"] = df["review"].apply(lambda x: clean_text(x, sw))
    print(df)


if __name__ == "__main__":
    main()
