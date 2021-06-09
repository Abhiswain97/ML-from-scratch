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

    def _word_frequency(self) -> Counter:
        """
        Calculates the word frequency

        returns:
            collections.Counter
        """
        return Counter(sorted(self.flattened_word_list))

    def unique_words(self) -> List[str]:
        return list(
            map(
                lambda x: x[0],
                list(
                    filter(
                        lambda values: values[1] == 1, self._word_frequency(
                        ).items()
                    )
                ),
            )
        )

    def _total_count(self, unique: bool = True) -> int:
        return (
            len(self.unique_words()) if unique else sum(
                self._word_frequency().values())
        )


if __name__ == "__main__":
    corpus = [
        "this is the first document mostly",
        "this document is the second document",
        "and this is the third one",
        "is this the first document here",
    ]

    bow = BagOfWords(corpus)

    print(bow._word_frequency())
    print(bow._total_count(unique=False))
    print(bow.flattened_word_list)
    print(bow.unique_words())
