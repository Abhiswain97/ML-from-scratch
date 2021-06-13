from streamlit.elements.utils import clean_text
from scikit_learn.NLP.feature_extraction.Tfidf import Tfidf
from NLP.feature_extraction.BOW import BagOfWords
from NLP.text_processing.cleaner import clean_corpus
import streamlit as st
import pandas as pd
import base64

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

corpus = st.text_area('Enter paragraph', '',
                      help='Enter your paragraph here')

if not corpus:
    st.write("Enter some text!")
else:
    cleaned_corpus = clean_corpus(corpus=corpus)

    if option == "TFIDF":

        tfidf = Tfidf(cleaned_corpus)

        unq = tfidf.unique_words()

        vec = tfidf.compute_tfidf().toarray()

    else:

        bow = BagOfWords(cleaned_corpus)

        vec = bow.make_BoW(binary=True if type_ == "Binary" else False)

        unq = bow.unique_words()

    df = pd.DataFrame(vec, columns=unq)

    st.dataframe(data=df)

    csv = df.to_csv(index=False)

# From: https://discuss.streamlit.io/t/how-to-add-a-download-excel-csv-function-to-a-button/4474
b64 = base64.b64encode(csv.encode()).decode()
linko = f'<center><a href="data:file/csv;base64,{b64}" download="myfilename.csv">Download as CSV file</a></center>'
st.markdown(linko, unsafe_allow_html=True)
