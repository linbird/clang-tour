// shape.h
#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape
{
public:
    virtual ~Shape() = default;

    virtual std::string name() const = 0;    // 纯虚函数
    virtual double      area() const = 0;    // 纯虚函数
};

#endif    // SHAPE_H
