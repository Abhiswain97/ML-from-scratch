# ML-from-scratch

Implementation of machine learning algorithms from scratch.

There two implementations:
- implementation according to textbook formulae
- implementation to replicate sklearn output (In the *sklearn* folder)

## Contents

- NLP
    - Feature extraction 
        - [Bag of words](https://github.com/Abhiswain97/ML-from-scratch/blob/master/NLP/feature_extraction/BOW.py) 
        - [TFIDF](https://github.com/Abhiswain97/ML-from-scratch/blob/master/NLP/feature_extraction/Tfidf.py) or [TFIDF-sklearn](https://github.com/Abhiswain97/ML-from-scratch/blob/master/sklearn/NLP/feature_extraction/Tfidf.py) 

## How to run

### Locally

- Clone the repo: `git clone https://github.com/Abhiswain97/ML-from-scratch.git`

- Install requirements: `pip install -r requirements.txt`

- Do, `streamlit run app.py`

### Using Docker

- Clone the repo: 
    ```
    git clone https://github.com/Abhiswain97/ML-from-scratch.git
    cd ML-from-scratch
    ```

- Do, `docker build -f DockerFile -t my-app .`

- Run it, `docker run -p 8501:8501 -t my-app`

- Now just open a browser, it's available on http://localhost:8501/