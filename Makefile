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
	${PYTHON} util_scripts\cpp_utils.py ${COMP}

link:
	${CC} -LCpp\lib -lapp -o Cpp\bin\main Cpp\examples\main.cpp

run_example:
	Cpp\bin\main.exe Cpp\examples\features.txt Cpp\examples\labels.txt

make_docs:
	doxygen

