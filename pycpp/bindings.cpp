// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/pickle.h>
#include "IHelper.hpp"
#include "Box.h"
#include <sstream>

namespace py = pybind11;

class PyIHelper : public IHelper
{
public:
    using IHelper::IHelper;

    int func1(int a, float b, char* c) override { PYBIND11_OVERRIDE_PURE(int, IHelper, func1, a, b, c); }

    Info func2(Info a, const Info& b) override { PYBIND11_OVERRIDE_PURE(Info, IHelper, func2, a, b); }

    std::string& func3(std::vector<Info> a) override { PYBIND11_OVERRIDE_PURE(std::string&, IHelper, func3, a); }
};

class PyIHelperSink : public IHelperSink
{
public:
    using IHelperSink::IHelperSink;

    int func1back(int a, float b, char* c) override { PYBIND11_OVERRIDE_PURE(int, IHelperSink, func1back, a, b, c); }

    Info func2back(Info a, const Info& b) override { PYBIND11_OVERRIDE_PURE(Info, IHelperSink, func2back, a, b); }

    std::string& func3back(std::vector<Info> a) override { PYBIND11_OVERRIDE_PURE(std::string&, IHelperSink, func3back, a); }
};

PYBIND11_MODULE(mylibrary, m)
{
    py::class_<Info>(m, "Info")
        .def(py::init<>())
        .def(py::init<int, float, std::string>())
        .def_readwrite("a", &Info::a)
        .def_readwrite("b", &Info::b)
        .def_readwrite("c", &Info::c);


    py::class_<IHelper, PyIHelper>(m, "IHelper")
        .def(py::init<>())
        .def("func1", &IHelper::func1)
        .def("func2", &IHelper::func2)
        .def("func3", &IHelper::func3);

    py::class_<IHelperSink, PyIHelperSink>(m, "IHelperSink")
        .def(py::init<>())
        .def("func1back", &IHelperSink::func1back)
        .def("func2back", &IHelperSink::func2back)
        .def("func3back", &IHelperSink::func3back);

    py::class_<Box, IHelper>(m, "Box").def(py::init<IHelperSink*>()).def("func1", &Box::func1).def("func2", &Box::func2).def("func3", &Box::func3);
}
