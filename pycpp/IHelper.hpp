#include <vector>
#include <string>

#ifndef _IHELPER_HPP_
#define _IHELPER_HPP_

// Info struct to be used in the test
struct Info
{
    int         a;
    float       b;
    std::string c;    // 使用 std::string 替代 char*


    Info(int _a, float _b, std::string _c) : a(_a), b(_b), c(_c) {};

    Info() {};
};

class IHelper
{
public:
    IHelper() = default;
    virtual ~IHelper() = default;
    virtual int          func1(int a, float b, char* c) = 0;
    virtual Info         func2(Info a, const Info& b) = 0;
    virtual std::string& func3(std::vector<Info> a) = 0;
};

class IHelperSink
{
public:
    IHelperSink() = default;
    virtual ~IHelperSink() = default;
    virtual int          func1back(int a, float b, char* c) = 0;
    virtual Info         func2back(Info a, const Info& b) = 0;
    virtual std::string& func3back(std::vector<Info> a) = 0;
};

#endif