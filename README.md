Simple c++ serializer
=====================

A very minimal C++14 header only serializer. No sanity checking is performed
on the data when it is read back in, so make sure your serializer and 
deserializers match perfectly. Example usege:

saving:

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

loading:

<pre>
static void save (std::ifstream f)
{
    int a, b, c;
    std::string d;
    std::vector<std::string> e;

    f >> bits(a) >> bits(b) >> bits(c) >> bits(d) >> bits(e);
}
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
a 5
b -1
c 123456
d hello
e 2 vec-elems: [vec-elem1] [vec-elem2]
f 2 list-elems: [list-elem1] [list-elem2]
</pre>

Recompile with DEBUG_C_PLUS_PLUS_SERIALIZER to debug.
