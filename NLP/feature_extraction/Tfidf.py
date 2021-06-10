from functools import reduce
from operator import concat
from collections import Counter
from typing import List
import math

from sklearn.feature_extraction.text import TfidfVectorizer


class Tfidf:
    def __init__(self, corpus: List[str]):
        self.corpus: List[str] = corpus
        self.word_list: List[List[str]] = list(map(lambda x: x.split(), self.corpus))
        self.flattened_word_list: List[str] = reduce(concat, self.word_list)

    def _word_frequency(self, document: str = None) -> Counter:
        """
        Calculates the word frequency.
        If document=None, then it creates a Counter dict of all the words in the corpus
        else it just gives count in the current sentence(document)

        returns:
            collections.Counter
        """
        return (
            Counter(sorted(document))
            if document is not None
            else Counter(sorted(self.flattened_word_list))
        )

    def unique_words(self) -> List[str]:
        return list(self._word_frequency(document=None).keys())

    def _total_count(self, unique: bool = True) -> int:
        return (
            len(self.unique_words()) if unique else sum(self._word_frequency().values())
        )

    def compute_tf(self):
        tf_dict = {}
        for words in self.word_list:
            count = self._word_frequency(document=words)
            for word in words:
                tf_dict[word] = count[word] / sum(count.values())

        return tf_dict

    def compute_idf(self):
        idf_dict = {}

        N = self._total_count(unique=False)

        for word in self.flattened_word_list:
            count = 0
            for document in self.corpus:
                if word in document:
                    count += 1

            idf_dict[word] = math.log(N / (count + 1))

        return idf_dict

    def compute_tfidf(self):

        tf = self.compute_tf()
        idf = self.compute_idf()

        tfidf = [
            [0] * self._total_count(unique=True) for _ in range(len(self.word_list))
        ]

        for i, words in enumerate(self.word_list):
            for j, word in enumerate(self.unique_words()):
                tfidf[i][j] = tf[word] * idf[word]

        return tfidf


if __name__ == "__main__":
    corpus = [
        "this is the first document mostly",
        "this document is the second document",
        "and this is the third one",
        "is this the first document here",
    ]

    tfidf_sklearn = TfidfVectorizer()

    print(tfidf_sklearn.fit_transform(corpus))

    tfidf = Tfidf(corpus=corpus)

    print(tfidf.compute_tfidf()[0])
