from streamlit.elements.utils import clean_text
from scikit_learn.NLP.feature_extraction.Tfidf import Tfidf
from NLP.feature_extraction.BOW import BagOfWords
from NLP.text_processing.cleaner import clean_corpus
import streamlit as st
import pandas as pd

st.markdown("<h1 style='text-align: center;'>Text feature extractor</h1>",
            unsafe_allow_html=True)

option = st.selectbox(
    "Select feature extractor",
    ("TFIDF", "Bag of Words"),
)

if option == "Bag of Words":
    type_ = st.selectbox(
        "Select type of Bag of words",
        ("Binary", "Non binary"),
    )

corpus = st.text_input('Enter paragraph', '',
                       help='Enter your paragraph here')

if not corpus:
    st.write("Enter some text!")
else:
    cleaned_corpus = clean_corpus(corpus=corpus)

    if option == "TFIDF":

        tfidf = Tfidf(cleaned_corpus)

        unq = tfidf.unique_words()

        vec = tfidf.compute_tfidf().toarray()

        df = pd.DataFrame(vec, columns=unq)

    else:

        bow = BagOfWords(cleaned_corpus)

        vec = bow.make_BoW(binary=True if type_ == "Binary" else False)

        unq = bow.unique_words()

        df = pd.DataFrame(vec, columns=unq)

    st.dataframe(data=df)
