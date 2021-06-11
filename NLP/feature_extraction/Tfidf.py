from functools import reduce
from operator import concat
from collections import Counter
from typing import Dict, List, Optional, Tuple, Union
import math
import pprint


class Tfidf:
    def __init__(self, corpus: Union[List[str], str]):
        self.corpus: Union[List[str], str] = corpus.split(".") if not isinstance(
            corpus, list
        ) else self.corpus
        self.word_list: List[List[str]] = list(
            map(lambda x: x.split(), self.corpus)  # type: ignore
        )
        self.flattened_word_list: List[str] = reduce(
            concat, self.word_list  # type: ignore  # https://github.com/python/mypy/issues/4673
        )

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
        return list(self._word_frequency(document=None).keys())

    def _total_count(self, unique: bool = True) -> int:
        return (
            len(self.unique_words()) if unique else sum(self._word_frequency().values())
        )

    def compute_tf(
        self, word: str, document: List[str] = None, smoothing: bool = True
    ) -> float:
        count = self._word_frequency(document=document)
        if smoothing:
            return (count[word] + 1) / (sum(count.values()) + 1)
        else:
            return (count[word]) / (sum(count.values()))

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

    def compute_tfidf(
        self, rounding_factor: int = 2
    ) -> Tuple[Dict[Tuple[str, int], float], List[List[int]]]:
        """
        args:
            rounding_factor: int -> How much to round the tfidf values

        returns:
            tfidf: Dict -> A dictionary of tuples as keys and tfidf values as values.
                           Each tuple contains: (word, it's document index) 
            tfidf_vec: List[List[float]] -> The TFIDF vector

        """

        idf = self.compute_idf()

        tfidf = {}
        tfidf_vec = [
            [0] * self._total_count(unique=True) for _ in range(len(self.word_list))
        ]

        for i, words in enumerate(self.word_list):
            for j, word in enumerate(self.unique_words()):
                value = round(
                    self.compute_tf(word=word, document=words) * idf[word],
                    rounding_factor,
                )
                tfidf[word, i] = value
                tfidf_vec[i][j] = value  # type: ignore

        return tfidf, tfidf_vec

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

    corpus2 = """
    TF-IDF (term frequency-inverse document frequency) was invented for document search and information retrieval.
    It works by increasing proportionally to the number of times a word appears in a document,
    but is offset by the number of documents that contain the word.
    So, words that are common in every document, such as this,
    what, and if, rank low even though they may appear many times,
    since they don’t mean much to that document in particular.
    """

    corpus3 = """
    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
    Etiam semper purus ut nisi eleifend dignissim in nec risus.
    Quisque eget viverra quam. Ut dapibus est in odio feugiat volutpat.
    Vestibulum sit amet nisl risus. Phasellus consequat mollis est.
    Donec dui ante, luctus a quam vel, ullamcorper bibendum mi.
    Quisque semper ex vitae neque lobortis, vel lacinia ligula finibus.
    Vivamus lacinia sem id sodales molestie.
    Maecenas convallis magna ac suscipit tincidunt. Nulla fermentum dictum mauris nec aliquam.
    """

    tfidf = Tfidf(corpus=corpus3)

    print(tfidf.compute_tfidf())
    # pprint.pprint(tfidf.transform())
