import os
import subprocess
import sys
from typing import List


def find_all_cpp() -> List[str]:
    cpp_files = []
    for dirpath, _, filenames in os.walk("Cpp"):
        for f in filenames:
            cpp_files.append(os.path.abspath(os.path.join(dirpath, f))) if f.endswith(
                ".cpp"
            ) else None

    return cpp_files


def create_dll(compiler) -> None:
    command = "{} -fPIC --shared -o tests\\app.dll".format(
        "clang++" if compiler == "clang" else "g++"
    )

    files = find_all_cpp()

    for file in files:
        command += str(" " + file)

    subprocess.run(command, shell=True)


def format_all_cpp_hpp():
    files = []
    for dirpath, _, filenames in os.walk("Cpp"):
        for f in filenames:
            files.append(os.path.abspath(os.path.join(dirpath, f))) if (f.endswith(
                ".cpp"
            ) or f.endswith(".h")) else None

    command = "clang-format -i -style=google"

    for file in files:
        command += str(" " + file)

    subprocess.run(command, shell=True)


if __name__ == "__main__":
    cpp_files = find_all_cpp()

    format_all_cpp_hpp()
    create_dll(compiler="clang++")
