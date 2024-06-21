#include <pybind11/pybind11.h>
#include "mylibrary.h"
// bindings.cpp
namespace py = pybind11;

// 适配器类，用于处理纯虚函数的绑定
class PyShape : public Shape
{
public:
    using Shape::Shape;    // 继承构造函数

    // 覆盖纯虚函数，并在需要时调用 Python 实现
    std::string name() const override
    {
        PYBIND11_OVERRIDE_PURE(std::string,    // 返回类型
                               Shape,          // 父类
                               name            // 函数名
        );
    }

    double area() const override
    {
        PYBIND11_OVERRIDE_PURE(double,    // 返回类型
                               Shape,     // 父类
                               area       // 函数名
        );
    }
};

PYBIND11_MODULE(example, m)
{
    py::class_<Shape, PyShape>(m, "Shape")
        .def(py::init<>())    // 默认构造函数
        .def("name", &Shape::name)
        .def("area", &Shape::area);
}
