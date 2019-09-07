#include <list>
#include <vector>
#include <array>
#include <map>
#include <limits>
#include "c_plus_plus_serializer.h"

static void save_simple (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    char a = 42;
    unsigned short b = 65535;
    int c = 123456;
    float d = std::numeric_limits<float>::max();
    double e = std::numeric_limits<double>::max();
    std::string f("hello");

    out << bits(a) << bits(b) << bits(c) << bits(d);
    out << bits(e) << bits(f);
}

static void load_simple (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    char a;
    unsigned short b;
    int c;
    float d;
    double e;
    std::string f;

    in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
    in >> bits(e) >> bits(f);

    std::cout << std::endl;
    std::cout << "a: char                     " << a << std::endl;
    std::cout << "b: unsigned short           " << b << std::endl;
    std::cout << "c: int                      " << c << std::endl;
    std::cout << "d: float                    " << d << std::endl;
    std::cout << "e: double                   " << e << std::endl;
    std::cout << "f: std::string              " << f << std::endl;
    std::cout << std::endl;
}

void basic_example (void)
{
    std::cout << "basic_example" << std::endl;
    std::cout << "=============" << std::endl;
    save_simple(std::string("basic_example.bin"));
    load_simple(std::string("basic_example.bin"));
}
