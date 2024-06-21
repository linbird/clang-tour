import sys
sys.path.append('./build')

import inspect

import mylibrary as example  # 导入通过 pybind11 生成的 Python 模块

from IHelperSinkImpl import IHelperSinkImpl

import json
import importlib

# 创建 IHelperSink 实例
sink = IHelperSinkImpl()

# 创建 Box 实例
box = example.Box(sink)

class Address:
    def __init__(self, city, street, number):
        self.city = city
        self.street = street
        self.number = number

class Person:
    def __init__(self, name, age, address, phones):
        self.name = name
        self.age = age
        self.address = address
        self.phones = phones

# 定义一个反射调用函数
def call_method(obj, method_name, *args, **kwargs):
    method = getattr(obj, method_name)
    return method(*args, **kwargs)

def serialize(obj):
    if isinstance(obj, (int, float, str, bool, type(None))):
        return obj
    elif isinstance(obj, (list, tuple)):
        return [serialize(item) for item in obj]
    elif isinstance(obj, dict):
        return {key: serialize(value) for key, value in obj.items()}
    elif hasattr(obj, '__dict__'):
        obj_dict = {key: serialize(value) for key, value in obj.__dict__.items()}
        obj_dict['__class__'] = obj.__class__.__name__
        return obj_dict
    else:
        raise TypeError(f"Type {type(obj)} not serializable")

def serialize(obj):
    """递归地将 Python 对象序列化为 JSON 可表示的类型。"""
    if isinstance(obj, (int, float, str, bool, type(None))):
        return obj
    elif isinstance(obj, (list, tuple)):
        return [serialize(item) for item in obj]
    elif isinstance(obj, dict):
        return {key: serialize(value) for key, value in obj.items()}
    # # 检查是否是 C++ 类实例
    # elif hasattr(obj, '__cppclass__'): 
    #     obj_dict = obj.__dict__.copy()  # 使用 __dict__ 获取所有属性
    #     obj_dict['__cppclass__'] = obj.__class__.__name__  # 保存类名
    #     return obj_dict
    elif hasattr(obj, '__dict__'):
        obj_dict = {key: serialize(value) for key, value in obj.__dict__.items()}
        obj_dict['__class__'] = obj.__class__.__name__
        return obj_dict
    else:
        # 记录错误信息，而不是直接抛出异常
        print(f"Warning: Type {type(obj)} not serializable, skipping...")
        return None  # 或者返回其他默认值
    
def deserialize(data):
    if isinstance(data, dict):
        if '__class__' in data:
            class_name = data.pop('__class__')
            module_name = __name__
            cls = getattr(importlib.import_module(module_name), class_name)
            obj = cls.__new__(cls)
            for key, value in data.items():
                setattr(obj, key, deserialize(value))
            return obj
        else:
            return {key: deserialize(value) for key, value in data.items()}
    elif isinstance(data, list):
        return [deserialize(item) for item in data]
    else:
        return data

def add_repr_to_class(cls):
    def generate_repr(self):
        # 获取实例的所有属性名
        members = inspect.getmembers(self, lambda member: not inspect.isroutine(member))
        # 构建属性值的字符串表示
        attr_strings = [f"{name}={value}" for name, value in members if not name.startswith('__')]
        return f"{cls.__name__}({', '.join(attr_strings)})"

    cls.__repr__ = generate_repr
    return cls

# 使用反射调用 Box 类的方法
try:
    result = call_method(box, 'func1', 10, 3.5, "test")
    print(f"Result of func1: {result}\n")
except Exception as e:
    print(f"Error calling func1: {e}\n")

try:
    info1 = example.Info(1, 2.0, b"info1")
    info2 = example.Info(3, 4.0, b"info2")
    result = call_method(box, 'func2', info1, info2)
    print(f"Result of func2: {result}\n")
except Exception as e:
    print(f"Error calling func2: {e}\n")

try:
    infos = [example.Info(1, 2.0, b"info1"), example.Info(3, 4.0, b"info2")]
    result = call_method(box, 'func3', infos)
    print(f"Result of func3: {result}\n")
except Exception as e:
    print(f"Error calling func3: {e}\n")

try:
    address = Address("New York", "5th Avenue", 123)
    person = Person("John", 30, address, ["123-456-7890", "098-765-4321"])

    # 序列化
    json_data = json.dumps(serialize(person), indent=2)
    print(json_data)

    # 在反序列化时动态创建对象
    deserialized_person = deserialize(json.loads(json_data))

    print(deserialized_person)
    print(deserialized_person.name)
    print(deserialized_person.age)
    print(deserialized_person.address.city)
    print(deserialized_person.address.street)
    print(deserialized_person.address.number)
    print(deserialized_person.phones)
    print()

except Exception as e:
    print(f"Error calling func1: {e}\n")

try:

    example.Info = add_repr_to_class(example.Info)

    info2 = example.Info(3, 4.0, b"info2")

    print(info2)

    # 序列化 Info 对象
    # serialized_info = serialize(info2)

    # # 转换为 JSON 格式
    # json_data = json.dumps(serialized_info)

    # print(json_data)
    # for attr_name in dir(info2):
    #     if not attr_name.startswith("__"):  # 排除私有属性
    #         attr_value = getattr(info2, attr_name)
    #         print(f"{attr_name} = {attr_value}")

    # json_data = json.dumps(info2.__dict__)
    # print(json_data)
    # print(info2)
    # json_data = json.dumps(serialize(info2))
    # print(json_data)
except Exception as e:
    print(f"Error calling func2: {e}\n")
