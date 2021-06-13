import string
from typing import List


def clean_corpus(corpus) -> List[str]:
    """
    Cleans the corpus. Cleans each sentence by removing punctuation,
    digits and strips whitespaces.

    args:
        corpus: List[str] -> The corpus

    returns:
        sen_list: List[str] -> Cleaned corpus
    """
    corpus = corpus.split('.')

    sen_list = []
    for sentence in corpus:
        sentence = sentence.translate(str.maketrans(
            "", "", string.punctuation)).translate(str.maketrans("", "", string.digits))

        sentence = sentence.strip()

        sen_list.append(sentence)

    sen_list = list(filter(lambda x: x != '', sen_list))

    return sen_list
