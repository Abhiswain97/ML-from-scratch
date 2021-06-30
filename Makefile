PYTHON := C:\Users\abhi0\anaconda3\python
MYPY := C:\Users\abhi0\anaconda3\envs\abhishek\Scripts\mypy
BLACK := C:\Users\abhi0\anaconda3\envs\abhishek\Scripts\black

CC := g++
FLAGS := -o

.PHONY = format run 

all: format type_check run

format:
	@echo Formatting ${FNAME} with black...
	${BLACK} ${FNAME}
	@echo.

type_check:
	@echo Checking for type issues....
	${MYPY} ${FNAME}
	@echo.

run:
	@echo Running ${FNAME}!
	@echo.
	${PYTHON} ${FNAME}

compile: 
	${CC} ${FNAME} 

run_cpp: 
	${CC} ${FNAME}

create_dll:
	g++ -fPIC --shared -o tests\app.dll Cpp\NLP\feature_extraction\src\BOW.cpp Cpp\NLP\feature_extraction\src\Tfidf.cpp Cpp\Metrics\src\Metrics.cpp Cpp\Data\src\Splitter.cpp

link:
	${CC} -L.\tests -lapp -o tests\main tests\main.cpp


