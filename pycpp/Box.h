#include "IHelper.hpp"

class Box : public IHelper
{
public:
    Box(IHelperSink* p) : p_(p) {}

    int          func1(int a, float b, char* c) override;
    Info         func2(Info a, const Info& b) override;
    std::string& func3(std::vector<Info> a) override;

private:
    IHelperSink* p_;
};
