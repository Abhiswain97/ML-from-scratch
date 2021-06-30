# ML-from-scratch

Implementation of machine learning algorithms from scratch.

There two implementations:
- implementation according to textbook formulae
- implementation to replicate sklearn output (In the *sklearn* folder)

## Web-app

Currently available app: *Text feature extractor* 

It's now deployed -> [Check it out!](https://textfeaturextractor.herokuapp.com/)

<p align="center">
  <img src="txt_ext.gif">
</p>

## Contents

- Data
  - [random_splitter](https://github.com/Abhiswain97/ML-from-scratch/blob/master/Cpp/Data/src/Splitter.cpp) 
  
- NLP
  - Python
    - Feature extraction 
      - [Bag of words](https://github.com/Abhiswain97/ML-from-scratch/blob/master/NLP/feature_extraction/BOW.py) 
      - [TFIDF](https://github.com/Abhiswain97/ML-from-scratch/blob/master/NLP/feature_extraction/Tfidf.py) or [TFIDF-sklearn](https://github.com/Abhiswain97/ML-from-scratch/blob/master/sklearn/NLP/feature_extraction/Tfidf.py)
  - C++
    - Feature extraction
      - [Bag of Words](https://github.com/Abhiswain97/ML-from-scratch/blob/master/Cpp/NLP/feature_extraction/src/BOW.cpp)
      - [TFIDF](https://github.com/Abhiswain97/ML-from-scratch/blob/master/Cpp/NLP/feature_extraction/src/Tfidf.cpp) 


## Running the app

Clone the repo:
```
git clone https://github.com/Abhiswain97/ML-from-scratch.git
cd ML-from-scratch
```

### Locally

- Install requirements: `pip install -r requirements.txt`

- Do, `streamlit run app.py`

### Using Docker

- Do, `docker build -f Dockerfiles\Docker-streamlit -t my-app .`

- Run it, `docker run -p 8501:8501 -t my-app`

- Now just open a browser, it's available on http://localhost:8501/

> Note: Incase you're running the app with docker, simply closing the broswer doesn't stop the app. It's still running. You need to stop the docker container. For that open powershell or git bash and do, `docker kill <container-id>` (You can get the container ID by running `docker container ls`). Then do `docker container prune`. 

## Documentation for Cpp examples

- Install doxygen

- Clone the repo: 
  ```
  git clone https://github.com/Abhiswain97/ML-from-scratch.git
  cd ML-from-scratch
  ```
- In Doxyfile set:
  ```
  OUTPUT_DIRECTORY = C:\....\Desktop\ML-from-scratch\Cpp\docs
  INPUT = C:\....\Desktop\ML-from-scratch\Cpp
  ```
- Do, `doxygen`

- Now, navigate to `C:\....\Desktop\ML-from-scratch\Cpp\docs\html` and run the `index.html` file.

## Running the Cpp examples

### Requirements

- A C++ compiler like g++ or clang++

### Steps

- You need two files: a `.txt` file containing the corpus and another containing the labels

#### With default settings

- You can simply run my `main.cpp` by doing `tests\main.exe tests\features.txt tests\labels.txt`

#### With custom settings

- I have provided the `.dll` file in the tests folder. You can create your custom `.cpp` file. You need to include 4 header files namely: `BOW.h`, `Tfidf.h`, `Metrics.h`, `Splitter.h` (Use `main.cpp` as a reference)

- Next create the executable by: `g++ -L. -lapp -o main <your-custom-cpp-file>`
  > Remember the `app.dll` file should be in the same directory as your custom cpp file.

- This will create `main.exe`. Now run it by: `main.exe <path-to-corpus-file> <path-to-labels-file>`


