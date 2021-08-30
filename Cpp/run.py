from ctypes import *
import subprocess

lib = cdll.LoadLibrary(
    "C:\\Users\\abhi0\\Desktop\\ML-from-scratch\\Cpp\\MLCpp.lib")


print(lib)
