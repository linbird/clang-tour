# test.py

import sys
sys.path.append('./build')

import mylibrary

from IHelperSinkImpl import IHelperSinkImpl

# 创建 IHelperSink 实例
sink = IHelperSinkImpl()

# 创建 Box 实例
box = mylibrary.Box(sink)

# 测试 func1
box.func1(1, 2.0, b"hello")

# 测试 func2
info1 = mylibrary.Info()
info1.a = 1
info1.b = 2.0
info1.c = b"info1"

info2 = mylibrary.Info()
info2.a = 3
info2.b = 4.0
info2.c = b"info2"

box.func2(info1, info2)

# 测试 func3
info_list = [info1, info2]
box.func3(info_list)
