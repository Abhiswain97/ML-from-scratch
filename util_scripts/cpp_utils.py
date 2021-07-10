import os
import subprocess
import sys
from typing import List


def find_all_cpp() -> List[str]:
    cpp_files = []
    for file in os.listdir("Cpp\\src"):
        cpp_files.append(os.path.abspath(os.path.join("Cpp\\src", file)))
    return cpp_files


def create_dll(compiler):
    command = "{} -fPIC --shared -o Cpp\\examples\\app.dll".format(
        "clang++" if compiler == "clang" else "g++"
    )

    files = find_all_cpp()

    for file in files:
        command += str(" " + file)

    subprocess.run(command, shell=True)


def format_all_cpp_hpp():

    hpp_files = [os.path.join(os.path.abspath("Cpp\\include"), file)
                 for file in os.listdir(os.path.abspath("Cpp\\include"))]
    cpp_files = [os.path.join(os.path.abspath("Cpp\\src"), file)
                 for file in os.listdir(os.path.abspath("Cpp\\src"))]

    command = "clang-format -i -style=google"

    for f1, f2 in zip(cpp_files, hpp_files):
        command += str(" " + f1 + " " + f2)

    subprocess.run(command, shell=True)


if __name__ == "__main__":
    cpp_files = find_all_cpp()

    format_all_cpp_hpp()
    # create_dll(compiler="clang++")
