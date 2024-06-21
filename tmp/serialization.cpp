#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/assign.hpp>

// 定义枚举类型
enum class Color
{
    Red,
    Green,
    Blue
};

// 自定义数据类型
struct Address
{
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
    Color       color;

    // Boost.Serialization 的序列化函数
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_NVP(street);
        ar& BOOST_SERIALIZATION_NVP(city);
        ar& BOOST_SERIALIZATION_NVP(state);
        ar& BOOST_SERIALIZATION_NVP(zip);
        ar& BOOST_SERIALIZATION_NVP(color);
    }
};

// 定义 Boost.Bimap 用于双向查找
typedef boost::bimap<boost::bimaps::unordered_set_of<std::string>, boost::bimaps::unordered_set_of<Color>> ColorBimap;
ColorBimap color_map = boost::assign::list_of<ColorBimap::relation>("Red", Color::Red)("Green", Color::Green)("Blue", Color::Blue);

// 重载输出流运算符（用于序列化）
std::ostream& operator<<(std::ostream& os, const Color& color)
{
    os << color_map.right.at(color);
    return os;
}

// 重载输入流运算符（用于反序列化）
std::istream& operator>>(std::istream& is, Color& color)
{
    std::string str;
    is >> str;
    color = color_map.left.at(str);
    return is;
}

// 包含各种类型的数据类
class Person
{
public:
    std::string                name;
    int                        age;
    double                     height;
    Address                    address;
    std::vector<std::string>   hobbies;
    std::map<std::string, int> scores;

    // Boost.Serialization 的序列化函数
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_NVP(name);
        ar& BOOST_SERIALIZATION_NVP(age);
        ar& BOOST_SERIALIZATION_NVP(height);
        ar& BOOST_SERIALIZATION_NVP(address);
        ar& BOOST_SERIALIZATION_NVP(hobbies);
        ar& BOOST_SERIALIZATION_NVP(scores);
    }
};

int main()
{
    // 创建一个 Person 对象并设置数据
    Person p1;
    p1.name = "John Doe";
    p1.age = 30;
    p1.height = 175.5;
    p1.address = {"123 Main St", "Anytown", "CA", "12345"};
    p1.hobbies = {"Reading", "Hiking", "Cooking"};
    p1.scores = {
        {"Math",    90},
        {"English", 85},
        {"History", 88}
    };

    // 将对象序列化到不同格式的文件
    {
        // 文本格式序列化
        std::ofstream                 ofs_text("person_data.txt");
        boost::archive::text_oarchive oa_text(ofs_text);
        oa_text << BOOST_SERIALIZATION_NVP(p1);
        ofs_text.close();
        std::cout << "Text serialization complete.\n";
    }

    {
        // 二进制格式序列化
        std::ofstream                   ofs_binary("person_data.bin", std::ios::binary);
        boost::archive::binary_oarchive oa_binary(ofs_binary);
        oa_binary << BOOST_SERIALIZATION_NVP(p1);
        ofs_binary.close();
        std::cout << "Binary serialization complete.\n";
    }

    {
        // XML格式序列化
        std::ofstream                ofs_xml("person_data.xml");
        boost::archive::xml_oarchive oa_xml(ofs_xml);
        // const unsigned int version_to_serialize = 610;
        const std::string sdk_version = "6.1.0";
        oa_xml << BOOST_SERIALIZATION_NVP(sdk_version);
        oa_xml << BOOST_SERIALIZATION_NVP(p1);
        ofs_xml.close();
        std::cout << "XML serialization complete.\n";
    }

    return 0;
}
