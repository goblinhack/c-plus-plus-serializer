#include <list>
#include <vector>
#include <map>

#define DEBUG_C_PLUS_PLUS_SERIALIZER
#include "c_plus_plus_serializer.h"

static void save_simple (const std::string filename)
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

static void load_simple (const std::string filename)
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

static void save_map_key_string_value_string (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    std::map< std::string, std::string > m;

    m.insert(std::make_pair(std::string("key1"), std::string("value1")));
    m.insert(std::make_pair(std::string("key2"), std::string("value2")));
    m.insert(std::make_pair(std::string("key3"), std::string("value3")));
    m.insert(std::make_pair(std::string("key4"), std::string("value4")));

    out << bits(m);
}

static void load_map_key_string_value_string (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    std::map< std::string, std::string > m;

    in >> bits(m);

    std::cout << "m = " << m.size() << " list-elems { " << std::endl;
    for (auto i : m) {
        std::cout << "    [" << i.first << "] = " << i.second << std::endl;
    }
    std::cout << "}" << std::endl;
}

static void save_map_key_string_value_list_of_strings (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    std::map< std::string, std::list<std::string> > m;

    std::initializer_list<std::string> L1 = {"list-elem1", "list-elem2"};
    std::list<std::string> l1(L1);
    std::initializer_list<std::string> L2 = {"list-elem3", "list-elem4"};
    std::list<std::string> l2(L2);

    m.insert(std::make_pair(std::string("key1"), l1));
    m.insert(std::make_pair(std::string("key2"), l2));

    out << bits(m);
}

static void load_map_key_string_value_list_of_strings (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    std::map< std::string, std::list<std::string> > m;

    in >> bits(m);

    std::cout << "m = " << m.size() << " list-elems { " << std::endl;
    for (auto i : m) {
        std::cout << "    [" << i.first << "] = [ ";
        for (auto j : i.second) {
            std::cout << j << ", ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "}" << std::endl;
}

int main (int argc, char *argv[])
{
    save_simple(std::string("simple.bin"));
    load_simple(std::string("simple.bin"));

    save_map_key_string_value_string(std::string("map.bin"));
    load_map_key_string_value_string(std::string("map.bin"));

    save_map_key_string_value_list_of_strings(std::string("map_of_string_to_list_of_strings.bin"));
    load_map_key_string_value_list_of_strings(std::string("map_of_string_to_list_of_strings.bin"));

    return (0);
}
