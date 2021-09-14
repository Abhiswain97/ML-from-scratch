from scikit_learn.NLP.feature_extraction.Tfidf import Tfidf
from NLP.feature_extraction.BOW import BagOfWords
from NLP.text_processing.cleaner import clean_corpus
import streamlit as st
import pandas as pd
import base64

opt = st.selectbox(
    "Classifier or Extractor ?",
    ("Classifier", "Feature extractor"),
    help="Select whether to classify or extract features"
)

if opt == "Classifier":
    st.markdown("<h1 style='text-align: center;'>Classifier</h1>",
                unsafe_allow_html=True)
    st.write("<center>Currently only KNN is available</center>",
             unsafe_allow_html=True)

else:
    st.markdown("<h1 style='text-align: center;'>Text feature extractor</h1>",
                unsafe_allow_html=True)

    text = """
    PythonAnywhere makes it easy to create and run Python programs in the cloud. 
    You can write your programs in a web-based editor or just run a console session from any modern web browser. 
    There's storage space on our servers, and you can preserve your session state and access it from anywhere, 
    with no need to pay for, or configure, your own server. 
    Start work on your work desktop, 
    then later pick up from where you left off by accessing exactly the same session from your laptop."
    """

    option = st.selectbox(
        "Select feature extractor",
        ("TFIDF", "Bag of Words"),
        help="Select type of text feature extractor out of TFIDF or Bag of words"
    )

    if option == "Bag of Words":
        type_ = st.selectbox(
            "Select type of Bag of words",
            ("Binary", "Non binary"),
            help="Select type of Bag of words"
        )

    corpus = st.text_area('Enter paragraph', text,
                          help='Enter your paragraph here')

    if st.button(f"Make {option} Features"):
        if not corpus:
            st.write("Enter some text!")
        else:
            cleaned_corpus = clean_corpus(corpus=corpus)

            if option == "TFIDF":

                tfidf = Tfidf(cleaned_corpus)

                unq = tfidf.unique_words()

                vec = tfidf.compute_tfidf().toarray()

            else:

                bow = BagOfWords(
                    cleaned_corpus, binary=True if type_ == "Binary" else False)

                vec = bow.fit()

                unq = bow.unique_words()

            df = pd.DataFrame(vec, columns=unq)

            st.dataframe(data=df)

            csv = df.to_csv(index=False)

            # From: https://discuss.streamlit.io/t/how-to-add-a-download-excel-csv-function-to-a-button/4474
            b64 = base64.b64encode(csv.encode()).decode()
            linko = f'<center><a href="data:file/csv;base64,{b64}" download="myfilename.csv">Download as CSV file</a></center>'
            st.markdown(linko, unsafe_allow_html=True)
