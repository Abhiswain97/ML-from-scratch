import string
from typing import List
import re


def clean_corpus(corpus) -> List[str]:
    """
    Cleans the corpus. Cleans each sentence by removing punctuation,
    digits and strips whitespaces.

    args:
        corpus: List[str] -> The corpus

    returns:
        sen_list: List[str] -> Cleaned corpus
    """

    corpus = re.sub(re.compile('<.*?>'), '', corpus)
    corpus = corpus.split('.')

    sen_list = []
    for sentence in corpus:
        sentence = sentence.translate(
            str.maketrans("", "", string.punctuation))

        sentence = sentence.translate(str.maketrans("", "", string.digits))

        sentence = sentence.replace(",", "")

        sentence = sentence.replace("n\'t", " not")
        sentence = sentence.strip()

        sen_list.append(sentence)

    sen_list = list(filter(lambda x: x != '', sen_list))

    return sen_list


if __name__ == "__main__":
    corpus = """
    Far far away, behind the word mountains, far from the countries Vokalia and Consonantia, there live the blind texts. Separated they live in Bookmarksgrove right at the coast of the Semantics, a large language ocean. A small river named Duden flows by their place and supplies it with the necessary regelialia. It is a paradisematic country, in which roasted parts of sentences fly into your mouth. Even the all-powerful Pointing has no control about the blind texts it is an almost unorthographic life One day however a small line of blind text by the name of Lorem Ipsum decided to leave for the far World of Grammar. The Big Oxmox advised her not to do so, because there were thousands of bad Commas, wild Question Marks and devious Semikoli, but the Little Blind Text didn’t listen. She packed her seven versalia, put her initial into the belt and made herself on the way. When she reached the first hills of the Italic Mountains, she had a last view back on the skyline of her hometown Bookmarksgrove, the headline of Alphabet Village and the subline of her own road, the Line Lane. Pityful a rethoric question ran over her cheek, then
    """

    print(clean_corpus(corpus))
