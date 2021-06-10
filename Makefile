PYTHON = C:\Users\abhi0\anaconda3\python
MYPY = C:\Users\abhi0\anaconda3\envs\abhishek\Scripts\mypy
BLACK = C:\Users\abhi0\anaconda3\envs\abhishek\Scripts\black

.PHONY = format run 

all: format type_check run

format:
	@echo Formatting the source file with black...
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