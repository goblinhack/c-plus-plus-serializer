Simple c++ serializer
=====================

A very minimal C++11 header only serializer. No sanity checking is performed
on the data when it is read back in, so make sure your serializer and 
deserializers match perfectly. Example usege:

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
#include "c_plus_plus_serializer.h"

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
#include "c_plus_plus_serializer.h"

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
#include "c_plus_plus_serializer.h"

static void load_map (std::ifstream f)
{
    std::map< std::string, std::string > m;
    in >> bits(m);
}
</pre>

Saving and loading a slightly more complex map:

<pre>
#include "c_plus_plus_serializer.h"

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
#include "c_plus_plus_serializer.h"
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

To build:

<pre>
sh ./RUNME
c++ -std=c++2a -Werror -g -ggdb3 -O2 -Wall -fmessage-length=0 -fdiagnostics-print-source-range-info -fdiagnostics-show-category=id -fdiagnostics-parseable-fixits -Wno-trigraphs -Wmissing-prototypes -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value -Wno-sign-conversion -c -o .o/main.o main.cpp
c++ .o/main.o   -o c_plus_plus_serializer
</pre>

To test:

<pre>
./c_plus_plus_serializer
</pre>

Recompile with DEBUG_C_PLUS_PLUS_SERIALIZER to debug.
