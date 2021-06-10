from functools import reduce
from operator import concat
from collections import Counter
from typing import Dict, List, Optional, Tuple
import math
import pprint


class Tfidf:
    def __init__(self, corpus: List[str]):
        self.corpus: List[str] = corpus
        self.word_list: List[List[str]] = list(
            map(lambda x: x.split(), self.corpus))
        self.flattened_word_list: List[str] = reduce(concat, self.word_list)

    def _word_frequency(self, document: List[str] = None) -> Counter:
        """
        Calculates the word frequency.
        If document=None, then it creates a Counter dict of all the words in the corpus
        else it just gives count in the current sentence(document)

        returns:
            collections.Counter
        """
        return (
            Counter(document)
            if document is not None
            else Counter(self.flattened_word_list)
        )

    def unique_words(self) -> List[str]:
        return list(self._word_frequency(document=None).keys())

    def _total_count(self, unique: bool = True) -> int:
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

            idf_dict[word] = math.log(N / count)

        return idf_dict

    def compute_tfidf(self) -> Dict[Tuple[(str, int)], float]:

        idf = self.compute_idf()

        tfidf = {}

        for i, words in enumerate(self.word_list):
            for j, word in enumerate(self.unique_words()):
                tfidf[word, i] = round(
                    self.compute_tf(word=word, document=words) * idf[word], 2
                )

        return tfidf

    def transform(self):
        tfidf_dict_tuple = self.compute_tfidf()

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

    tfidf = Tfidf(corpus=corpus)

    print(tfidf.transform())
