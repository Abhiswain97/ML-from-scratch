from collections import Counter
from typing import List, Optional, Tuple
from functools import reduce
from operator import concat
import pprint


class BagOfWords:
    def __init__(self, corpus: List[str], binary=False):
        self.corpus: List[str] = corpus
        self.word_list: List[List[str]] = list(
            map(lambda x: x.split(), self.corpus))
        self.binary = binary

    def unique_words(self) -> List[str]:
        return sorted(list(
            Counter(
                reduce(
                    concat, self.word_list  # type: ignore
                )
            ).keys()
        ))

    def fit(self) -> List[List[int]]:
        unique_words = self.unique_words()

        bow_vector = []

        for sentence in self.word_list:
            sen_word_count = {}
            for word in unique_words:
                if self.binary:
                    sen_word_count[word] = 1 if word in sentence else 0
                else:
                    sen_word_count[word] = sentence.count(word)

            bow_vector.append(list(sen_word_count.values()))

        return bow_vector


if __name__ == "__main__":
    corpus = [
        "this is the first document mostly",
        "this document is the second document",
        "and this is the third one",
        "is this the first document here",
    ]

    bow = BagOfWords(corpus, binary=False)

    # sens = list(map(lambda x: Counter(x), list(
    #     map(lambda x: x.split(), corpus))))

    # pprint.pprint(sens)
