#include <list>
#include <vector>
#include <array>
#include <map>
#include <limits>
#include "c_plus_plus_serializer.h"

static void save_container (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    std::initializer_list<std::string> d1 = {"vec-elem1", "vec-elem2"};
    std::vector<std::string> a(d1);

    std::initializer_list<std::string> d2 = {"list-elem1", "list-elem2"};
    std::list<std::string> b(d2);

    std::array<std::string, 2> c = {"arr-elem1", "arr-elem2"};

    std::array<std::array<char, 2>, 3> d;
    d[0][0] = '0';
    d[0][1] = '1';
    d[1][0] = '2';
    d[1][1] = '3';
    d[2][0] = '4';
    d[2][1] = '5';

    out << bits(a) << bits(b) << bits(c) << bits(d);
}

static void load_container (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    std::vector<std::string> a;
    std::list<std::string> b;
    std::array<std::string, 2> c;
    std::array<std::array<char, 2>, 3> d;

    in >> bits(a) >> bits(b) >> bits(c) >> bits(d);

    std::cout << std::endl;
    std::cout << "a: std::vector<std::string> " << a.size() << " elems: ";
    for (auto elem : a) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "b: std::list<std::string>   " << b.size() << " elems: ";
    for (auto elem : b) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "c: std::array<std::string>  " << c.size() << " elems: ";
    for (auto elem : c) {
        std::cout << "[" << elem << "] ";
    }
    std::cout << std::endl;

    std::cout << "d: std::array<std::array<char, 2>, 3> :" << std::endl;
    for (auto x = 0; x < 3; x++) {
        for (auto y = 0; y < 2; y++) {
            std::cout << "  d[" << x << "][" << y << "] = " << d[x][y] << std::endl;
        }
    }
    std::cout << std::endl;
}

void container_example (void)
{
    std::cout << "container_example" << std::endl;
    std::cout << "=============" << std::endl;
    save_container(std::string("container_example.bin"));
    load_container(std::string("container_example.bin"));
}
