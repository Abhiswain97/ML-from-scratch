from functools import reduce
from operator import concat
from collections import Counter
from typing import Dict, List, Optional, Tuple, Union
import math
from sklearn.feature_extraction.text import TfidfVectorizer  # type: ignore
from scipy.sparse import csr_matrix  # type: ignore
from sklearn.preprocessing import normalize  # type: ignore


class Tfidf:
    def __init__(self, corpus: List[str]):
        self.corpus: List[str] = corpus
        self.word_list: List[List[str]] = list(
            map(lambda x: x.split(), self.corpus)  # type: ignore
        )
        # type: ignore  # https://github.com/python/mypy/issues/4673)
        self.flattened_word_list: List[str] = reduce(
            concat, self.word_list, [])

    def _word_frequency(self, document: List[str] = None) -> Counter:
        """
        Calculates the word frequency.
        If document=None, then it creates a Counter dict of all the words in the corpus
        else it just gives count in the current sentence(document)

        args:
            document: str -> an individual document(sentence) of the corpus

        returns:
            collections.Counter
        """
        return (
            Counter(document)
            if document is not None
            else Counter(self.flattened_word_list)
        )

    def unique_words(self) -> List[str]:
        return list(sorted(self._word_frequency(document=None).keys()))

    def _count(self, unique: bool = True) -> int:
        return (
            len(self.unique_words()) if unique else sum(
                self._word_frequency().values())
        )

    def compute_tf(self, word: str, document: List[str] = None) -> float:
        count = self._word_frequency(document=document)

        return count[word] / sum(count.values())

    def compute_idf(self) -> Dict[str, float]:
        idf_dict = {}

        N = len(self.word_list)

        for word in self.flattened_word_list:
            count = 0
            for document in self.word_list:
                if word in document:
                    count += 1

            idf_dict[word] = 1 + math.log((N + 1) / (count + 1))
        return idf_dict

    def compute_tfidf(self):
        """
        Computes the tfidf for the corpus

        returns:
            a csr matrix of tfidf values
        """

        idf = self.compute_idf()

        tfidf = {}
        tfidf_vec = [[0] * self._count(unique=True)
                     for _ in range(len(self.word_list))]

        rows, columns, values = [], [], []

        for i, words in enumerate(self.word_list):
            for j, word in enumerate(self.unique_words()):
                value = self.compute_tf(word=word, document=words) * idf[word]
                tfidf[word, i] = value
                tfidf_vec[i][j] = value  # type: ignore

                if value != float(0):
                    rows.append(i)
                    columns.append(j)
                    values.append(value)

        return normalize(
            csr_matrix(
                (values, (rows, columns)),
                shape=(len(self.word_list), self._count(unique=True)),
            )
        )

    def transform(self) -> List[List[float]]:
        tfidf_dict_tuple, tfidf_vec = self.compute_tfidf()

        tfidf = []

        for i, words in enumerate(self.word_list):
            t = []
            for word in words:
                t.append(tfidf_dict_tuple[word, i])
            tfidf.append(t)

        return tfidf


if __name__ == "__main__":
    corpus = [
        "this is the first document mostly",
        "this document is the second document",
        "and this is the third one",
        "is this the first document here",
    ]

    corpus1 = """
    This probabilistic interpretation in turn takes the same form as that of self-information. However, applying such information-theoretic notions to problems in information retrieval leads to problems when trying to define the appropriate event spaces for the required probability distributions: not only documents need to be taken into account, but also queries and terms.
    """

    tfidf = Tfidf(corpus=corpus1)

    print(tfidf._count(unique=True))
    print(tfidf.compute_tfidf())

#     print("=" * 50)

    # tfidf_sklearn = TfidfVectorizer()
    # X = tfidf_sklearn.fit_transform(corpus)
    # print(X)
