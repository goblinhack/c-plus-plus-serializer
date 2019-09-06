#include <list>
#include <vector>

#define DEBUG_C_PLUS_PLUS_SERIALIZER
#include "c_plus_plus_serializer.h"

static void save (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    int a = 5, b = -1, c = 123456;

    std::string d("hello");

    std::initializer_list<std::string> d1 = {"vec-elem1", "vec-elem2"};
    std::vector<std::string> e(d1);

    std::initializer_list<std::string> d2 = {"list-elem1", "list-elem2"};
    std::list<std::string> f(d2);

    out << bits(a) << bits(b) << bits(c) << bits(d) << bits(e) << bits(f);
}

static void load (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    int a, b, c;
    std::string d;
    std::vector<std::string> e;
    std::list<std::string> f;

    in >> bits(a) >> bits(b) >> bits(c) >> bits(d) >> bits(e) >> bits(f);

    std::cout << "a " << a << std::endl;
    std::cout << "b " << b << std::endl;
    std::cout << "c " << c << std::endl;
    std::cout << "d " << d << std::endl;
    std::cout << "e " << e.size() << " vec-elems: ";

    for (auto i : e) {
        std::cout << "[" << i << "] ";
    }
    std::cout << std::endl;

    std::cout << "f " << f.size() << " list-elems: ";
    for (auto i : f) {
        std::cout << "[" << i << "] ";
    }
    std::cout << std::endl;
}

int main (int argc, char *argv[])
{
    save(std::string("data.bin"));
    load(std::string("data.bin"));
    return (0);
}
