Simple C++ 11 header-only serializer
====================================

A very minimal C++11 header only serializer. No sanity checking is performed
on the data when it is read back in, so make sure your serializer and 
deserializers match perfectly.

The data is saved in raw binary format, hence this is only loadable on the
same architecture that it is saved in.

To serialize:

<pre>
#include "c_plus_plus_serializer.h"

static void save (std::ofstream f)
{
    int a = 5, b = -1, c = 123456;
    std::string d("hello");
    std::initializer_list<std::string> data = {"there", "you"};
    std::vector<std::string> e(data);

    f << bits(a) << bits(b) << bits(c) << bits(d) << bits(e);
}
</pre>

To deserialize:

<pre>
static void load (std::ifstream f)
{
    int a, b, c;
    std::string d;
    std::vector<std::string> e;

    f >> bits(a) >> bits(b) >> bits(c) >> bits(d) >> bits(e);
}
</pre>

Saving a map:

<pre>
static void save_map (std::ofstream f)
{
    std::map< std::string, std::string > m;
    m.insert(std::make_pair(std::string("key1"), std::string("value1")));
    m.insert(std::make_pair(std::string("key2"), std::string("value2")));
    m.insert(std::make_pair(std::string("key3"), std::string("value3")));
    m.insert(std::make_pair(std::string("key4"), std::string("value4")));
    out << bits(m);
}
</pre>

Loading a map:

<pre>
static void load_map (std::ifstream f)
{
    std::map< std::string, std::string > m;
    in >> bits(m);
}
</pre>

Saving and loading a slightly more complex map:

<pre>
static void save_map (std::ofstream f)
{
    std::map< std::string, std::list<std::string> > m;

    std::initializer_list<std::string> L1 = {"list-elem1", "list-elem2"};
    std::list<std::string> l1(L1);
    std::initializer_list<std::string> L2 = {"list-elem3", "list-elem4"};
    std::list<std::string> l2(L2);

    m.insert(std::make_pair(std::string("key1"), l1));
    m.insert(std::make_pair(std::string("key2"), l2));

    out << bits(m);
}

static void load_map (std::ifstream f)
{
    std::map< std::string, std::list<std::string> > m;

    in >> bits(m);
}
</pre>

Custom classes are easy to add also:

<pre>
class Custom {
public:
    int a;
    std::string b;
    std::vector<std::string> c;

    friend std::ostream& operator<<(std::ostream &out, 
                                    Bits<class Custom & > my)
    {
        out << bits(my.t.a) << bits(my.t.b) << bits(my.t.c);
        return (out);
    }

    friend std::istream& operator>>(std::istream &in, 
                                    Bits<class Custom &> my)
    {
        in >> bits(my.t.a) >> bits(my.t.b) >> bits(my.t.c);
        return (in);
    }
};
</pre>

And a more complex example. A map of custom classes:

<pre>
class Custom {
public:
    int a;
    std::string b;
    std::vector<std::string> c;

    friend std::ostream& operator<<(std::ostream &out, 
                                    Bits<class Custom & > my)
    {
        out << bits(my.t.a) << bits(my.t.b) << bits(my.t.c);
        return (out);
    }

    friend std::istream& operator>>(std::istream &in, 
                                    Bits<class Custom &> my)
    {
        in >> bits(my.t.a) >> bits(my.t.b) >> bits(my.t.c);
        return (in);
    }

    friend std::ostream& operator<<(std::ostream &out, 
                                    class Custom &my)
    {
        out << "a:" << my.a << " b:" << my.b;

        out << " c:[" << my.c.size() << " elems]:";
        for (auto v : my.c) {
            out << v << " ";
        }
        out << std::endl;

        return (out);
    }
};

static void save_map_key_string_value_custom (const std::string filename)
{
    std::cout << "save to " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary );

    std::map< std::string, class Custom > m;

    auto c1 = Custom();
    c1.a = 1;
    c1.b = "hello";
    std::initializer_list<std::string> L1 = {"vec-elem1", "vec-elem2"};
    std::vector<std::string> l1(L1);
    c1.c = l1;

    auto c2 = Custom();
    c2.a = 2;
    c2.b = "there";
    std::initializer_list<std::string> L2 = {"vec-elem3", "vec-elem4"};
    std::vector<std::string> l2(L2);
    c2.c = l2;

    m.insert(std::make_pair(std::string("key1"), c1));
    m.insert(std::make_pair(std::string("key2"), c2));

    out << bits(m);
}

static void load_map_key_string_value_custom (const std::string filename)
{
    std::cout << "read from " << filename << std::endl;
    std::ifstream in(filename);

    std::map< std::string, class Custom > m;

    in >> bits(m);
    std::cout << std::endl;

    std::cout << "m = " << m.size() << " list-elems { " << std::endl;
    for (auto i : m) {
        std::cout << "    [" << i.first << "] = " << i.second;
    }
    std::cout << "}" << std::endl;
}

void map_custom_class_example (void)
{
    std::cout << "map key string, value class" << std::endl;
    std::cout << "============================" << std::endl;
    save_map_key_string_value_custom(std::string("map_of_custom_class.bin"));
    load_map_key_string_value_custom(std::string("map_of_custom_class.bin"));
    std::cout << std::endl;
}
</pre>

And corresponding output from the above:

<pre>
map key string, value class
============================
save to map_of_custom_class.bin
read from map_of_custom_class.bin

m = 2 list-elems {
    [key1] = a:1 b:hello c:[2 elems]:vec-elem1 vec-elem2
    [key2] = a:2 b:there c:[2 elems]:vec-elem3 vec-elem4
}
</pre>

To build:

<pre>
sh ./RUNME
</pre>

Or, if that fails, manual build:

<pre>
c++ -std=c++11 -Werror -O2 -Wall -c -o .o/main.o main.cpp
c++ .o/main.o   -o c_plus_plus_serializer
</pre>

To test:

<pre>
./c_plus_plus_serializer
</pre>

Recompile with DEBUG_C_PLUS_PLUS_SERIALIZER to debug.
