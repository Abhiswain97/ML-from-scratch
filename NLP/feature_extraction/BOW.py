from collections import Counter
from typing import List
from functools import reduce
from operator import concat


class BagOfWords:
    def __init__(self, corpus: List[str]):
        self.corpus: List[str] = corpus
        self.word_list: List[List[str]] = list(
            map(lambda x: x.split(), self.corpus))
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
            len(self.unique_words()) if unique else sum(
                self._word_frequency().values())
        )

    def make_BoW(self, binary=False):
        bow_vec = [
            [0] * self._total_count(unique=True) for _ in range(len(self.corpus))
        ]

        for i, sen in enumerate(self.word_list):
            count_dict = self._word_frequency(document=sen)
            for j, word in enumerate(sen):
                if binary:
                    bow_vec[i][j] = 1 if word in count_dict.keys() else 0
                    continue
                else:
                    bow_vec[i][j] = count_dict[word]

        return bow_vec


if __name__ == "__main__":
    corpus = [
        "this is the first document mostly",
        "this document is the second document",
        "and this is the third one",
        "is this the first document here",
        "My name is Abhishek",
    ]

    bow = BagOfWords(corpus)

    print(bow._word_frequency())
    print(bow._total_count(unique=True))
    print(bow.flattened_word_list)
    print(bow.unique_words())
    print(bow.make_BoW(binary=True))
