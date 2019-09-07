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

    std::initializer_list<std::string> d1 = {"vec-elem1", "vec-elem2"};
    std::vector<std::string> g(d1);

    std::initializer_list<std::string> d2 = {"list-elem1", "list-elem2"};
    std::list<std::string> h(d2);

    std::array<std::string, 2> i = {"arr-elem1", "arr-elem2"};

    std::array<std::array<char, 2>, 3> j;
    j[0][0] = '0';
    j[0][1] = '1';
    j[1][0] = '2';
    j[1][1] = '3';
    j[2][0] = '4';
    j[2][1] = '5';

    out << bits(a) << bits(b) << bits(c) << bits(d);
    out << bits(e) << bits(f) << bits(g) << bits(h);
    out << bits(i) << bits(j);
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
    std::vector<std::string> g;
    std::list<std::string> h;
    std::array<std::string, 2> i;
    std::array<std::array<char, 2>, 3> j;

    in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
    in >> bits(e) >> bits(f) >> bits(g) >> bits(h);
    in >> bits(i) >> bits(j);

    std::cout << std::endl;

    std::cout << "a: char                     " << a << std::endl;
    std::cout << "b: unsigned short           " << b << std::endl;
    std::cout << "c: int                      " << c << std::endl;
    std::cout << "d: float                    " << d << std::endl;
    std::cout << "e: double                   " << e << std::endl;
    std::cout << "f: std::string              " << f << std::endl;

    std::cout << "g: std::vector<std::string> " << g.size() << " elems: ";
    for (auto elem : g) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "h: std::list<std::string>   " << h.size() << " elems: ";
    for (auto elem : h) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "i: std::array<std::string>  " << i.size() << " elems: ";
    for (auto elem : i) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "j: std::array<std::array<char, 2>, 3> :" << std::endl;
    for (auto x = 0; x < 3; x++) {
        for (auto y = 0; y < 2; y++) {
            std::cout << "  j[" << x << "][" << y << "] = " << j[x][y] << std::endl;
        }
    }
    std::cout << std::endl;
}

void basic_example (void)
{
    std::cout << "basic_example" << std::endl;
    std::cout << "=============" << std::endl;
    save_simple(std::string("simple.bin"));
    load_simple(std::string("simple.bin"));
    std::cout << std::endl;
}
