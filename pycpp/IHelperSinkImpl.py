# IHelperSinkImpl.py

import sys
sys.path.append('./build')

import mylibrary

class IHelperSinkImpl(mylibrary.IHelperSink):
    def func1back(self, a, b, c):
        print(f"func1back called with a={a}, b={b}, c={c}")
        return a + 1

    def func2back(self, a, b):
        print(f"func2back called with a={a}, b={b}")
        return a

    def func3back(self, a):
        print(f"func3back called with a={a}")
        return "func3back_result"
