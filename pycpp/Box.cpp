#include "Box.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Info& info)
{
    os << "Info: a = " << info.a << ", b = " << info.b << ", c = " << info.c << "; ";
    return os;
}

int Box::func1(int a, float b, char* c)
{
    std::cout << "func1: " << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    a += 1;
    b += 2.0;
    int d = p_->func1back(a, b, c + 1);
    std::cout << "after func1back: d = " << d << std::endl;
    return 0;
}

Info Box::func2(Info a, const Info& b)
{
    std::cout << "fun2: " << "a = " << a << ", b = " << b << std::endl;
    Info copyb = b;
    Info ret = p_->func2back(copyb, a);
    std::cout << "after func2back: ret = " << ret << std::endl;
    return a;
}

std::string& Box::func3(std::vector<Info> a)
{
    std::cout << "fun3: " << "a.size() = " << a.size() << std::endl;
    std::string ret = p_->func3back(a);
    std::string retref("ret_of_func3");
    std::cout << "after func3back: ret = " << ret << std::endl;
    return retref;
}