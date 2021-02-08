Simple C++ 11 header-only serializer
====================================

Have you ever wanted a really minimal header-only C++11 serializer? Of course 
you have! Having tried some other implementations I found them too hard to
maintain and grok when they inevitably failed to compile under the latest
g++ version. Hopefully this one is simple enough to avoid such issues. All you 
need to do is add

<pre>
#include "c_plus_plus_serializer.h" 
</pre>

in your project for any files that need to do serialization.

The data is saved in raw binary format, hence this is only loadable on the
same architecture that it was saved in.

Credits
=======

This work was based on some of the ideas in [this link](https://stackoverflow.com/questions/1559254/are-there-binary-memory-streams-in-c), specifically,
those by Samuel Powell: 

Tested types
============

- POD types (char, wchar_t, int, float, double etc...)
- std::string, std::wstring
- std::vector
- std::list
- std::array (multidimensional works too)
- std::map
- std::unordered_map
- custom class
- nested types e.g. std::map< std::string, std::list>
- std::pair

POD serialization
=================

```C++
    #include "c_plus_plus_serializer.h"

    static void serialize (std::ofstream out)
    {
        char           a = 42;
        unsigned short b = 65535;
        int            c = 123456;
        float          d = std::numeric_limits<float>::max();
        double         e = std::numeric_limits<double>::max();
        std::string    f("hello");
        wchar_t        g = L'💩';
        std::wstring   h(L"wide string 💩");

        out << bits(a) << bits(b) << bits(c) << bits(d);
        out << bits(e) << bits(f) << bits(g) << bits(h);
    }

    static void deserialize (std::ifstream in)
    {
        char           a;
        unsigned short b;
        int            c;
        float          d;
        double         e;
        std::string    f;
        wchar_t        g;
        std::wstring   h;

        in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
        in >> bits(e) >> bits(f) >> bits(g) >> bits(h);
    }
```

Container serialization
=======================

```C++
    #include "c_plus_plus_serializer.h"

    static void serialize (std::ofstream out)
    {
        std::initializer_list< std::string > d1 = {"vec-elem1", "vec-elem2"};
        std::vector< std::string > a(d1);

        std::initializer_list< std::string > d2 = {"list-elem1", "list-elem2"};
        std::list< std::string > b(d2);

        std::array< std::string, 2> c = {"arr-elem1", "arr-elem2"};

        //
        // 2d array
        //
        std::array< std::array<char, 2>, 3> d;
        d[0][0] = '0'; d[0][1] = '1';
        d[1][0] = '2'; d[1][1] = '3';
        d[2][0] = '4'; d[2][1] = '5';

        //
        // 3d array
        //
        std::array< std::array< std::array<char, 2>, 3>, 4> ddd;
        ddd[0][0][0] = 'a'; ddd[0][0][1] = 'b';
        ddd[0][1][0] = 'c'; ddd[0][1][1] = 'd';
        ddd[0][2][0] = 'e'; ddd[0][2][1] = 'f';
        ddd[1][0][0] = 'g'; ddd[1][0][1] = 'h';
        ddd[1][1][0] = 'i'; ddd[1][1][1] = 'j';
        ddd[1][2][0] = 'k'; ddd[1][2][1] = 'l';
        ddd[2][0][0] = 'm'; ddd[2][0][1] = 'n';
        ddd[2][1][0] = 'o'; ddd[2][1][1] = 'p';
        ddd[2][2][0] = 'q'; ddd[2][2][1] = 'r';
        ddd[3][0][0] = 's'; ddd[3][0][1] = 't';
        ddd[3][1][0] = 'u'; ddd[3][1][1] = 'v';
        ddd[3][2][0] = 'w'; ddd[3][2][1] = 'x';

        out << bits(a) << bits(b) << bits(c) << bits(dd) << bits(ddd);
    }

    static void deserialize (std::ifstream in)
    {
        std::string f;
        std::vector< std::string > a;
        std::list< std::string > b;
        std::array< std::string, 2> c;
        std::array< std::array<char, 2>, 3> d;
        std::array< std::array< std::array<char, 2>, 3>, 4> ddd;

        in >> bits(a) >> bits(b) >> bits(c) >> bits(dd) >> bits(ddd);
    }
```

Map serialization
=================

```C++
    static void serialize (std::ofstream out)
    {
        std::map< std::string, std::string > m;
        m.insert(std::make_pair(std::string("key1"), std::string("value1")));
        m.insert(std::make_pair(std::string("key2"), std::string("value2")));
        m.insert(std::make_pair(std::string("key3"), std::string("value3")));
        m.insert(std::make_pair(std::string("key4"), std::string("value4")));
        out << bits(m);
    }

    static void deserialize (std::ifstream in)
    {
        std::map< std::string, std::string > m;
        in >> bits(m);
    }
```

Unordered map serialization
===========================

```C++
    static void serialize (std::ofstream out)
    {
        std::unordered_map< std::string, std::string > m;
        m.insert(std::make_pair(std::string("key1"), std::string("value1")));
        m.insert(std::make_pair(std::string("key2"), std::string("value2")));
        m.insert(std::make_pair(std::string("key3"), std::string("value3")));
        m.insert(std::make_pair(std::string("key4"), std::string("value4")));
        out << bits(m);
    }

    static void deserialize (std::ifstream in)
    {
        std::unordered_map< std::string, std::string > m;
        in >> bits(m);
    }
```

std::map< std::string, std::list > example
========================================

```C++
    static void serialize (std::ofstream out)
    {
        std::map< std::string, std::list< std::string > > m;

        std::initializer_list< std::string > L1 = {"list-elem1", "list-elem2"};
        std::list< std::string > l1(L1);
        std::initializer_list< std::string > L2 = {"list-elem3", "list-elem4"};
        std::list< std::string > l2(L2);

        m.insert(std::make_pair(std::string("key1"), l1));
        m.insert(std::make_pair(std::string("key2"), l2));

        out << bits(m);
    }

    static void deserialize (std::ifstream in)
    {
        std::map< std::string, std::list< std::string > > m;

        in >> bits(m);
    }
```

User defined class serialization
================================

```C++
    class Custom {
    public:
        int a;
        std::string b;
        std::vector< std::string > c;

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
```

Serializing a custom template class
===================================

```C++
    template<class T > class MyPoint
    {
    public:
        T x {};
        T y {};

        MyPoint (void) : x(0), y(0) {};

        MyPoint (T x, T y) : x(x), y(y) { }

        friend std::ostream& operator<<(std::ostream &out,
                                        Bits<const MyPoint & > const my)
        {
            out << bits(my.t.x) << bits(my.t.y);
            return (out);
        }

        friend std::istream& operator>>(std::istream &in, Bits<MyPoint &> my)
        {
            in >> bits(my.t.x) >> bits(my.t.y);
            return (in);
        }

        friend std::ostream& operator << (std::ostream &out, const MyPoint &my)
        {
            out << "(" << my.x << ", " << my.y << ")";
            return (out);
        }
    };

    typedef MyPoint<int > IntPoint;
    typedef MyPoint<float > FloatPoint;
    typedef MyPoint<double > DoublePoint;

    static void serialize (std::ofstream out)
    {
        out << bits(IntPoint(1, 2));
        out << bits(FloatPoint(1.1, 2.2));
        out << bits(DoublePoint(3.3, 4.4));
    }

    static void deserialize (std::ifstream in)
    {
        IntPoint a;
        FloatPoint b;
        DoublePoint c;

        in >> bits(a);
        in >> bits(b);
        in >> bits(c);
    }
```

User defined class serialization (more complex one, a map of classes)
=====================================================================

```C++
    class Custom {
    public:
        int a;
        std::string b;
        std::vector< std::string > c;

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

    static void serialize (...)
    {
        std::map< std::string, class Custom > m;

        auto c1 = Custom();
        c1.a = 1;
        c1.b = "hello";
        std::initializer_list< std::string > L1 = {"vec-elem1", "vec-elem2"};
        std::vector< std::string > l1(L1);
        c1.c = l1;

        auto c2 = Custom();
        c2.a = 2;
        c2.b = "there";
        std::initializer_list< std::string > L2 = {"vec-elem3", "vec-elem4"};
        std::vector< std::string > l2(L2);
        c2.c = l2;

        m.insert(std::make_pair(std::string("key1"), c1));
        m.insert(std::make_pair(std::string("key2"), c2));

        out << bits(m);
    }

    static void deserialize (...)
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
```

Bitfield serialization (C and C++ style)
========================================

```C++
    class BitsetClass {
    public:
        std::bitset<1> a;
        std::bitset<2> b;
        std::bitset<3> c;

        unsigned int d:1; // need c++20 for default initializers for bitfields
        unsigned int e:2;
        unsigned int f:3;
        BitsetClass(void) { d = 0; e = 0; f = 0; }

        friend std::ostream& operator<<(std::ostream &out,
                                        Bits<const class BitsetClass & > const my)
        {
            out << bits(my.t.a);
            out << bits(my.t.b);
            out << bits(my.t.c);

            std::bitset<6> s(my.t.d | my.t.e << 1 | my.t.f << 3);
            out << bits(s);

            return (out);
        }

        friend std::istream& operator>>(std::istream &in,
                                        Bits<class BitsetClass &> my)
        {
            std::bitset<1> a;
            in >> bits(a);
            my.t.a = a;

            in >> bits(my.t.b);
            in >> bits(my.t.c);
            std::bitset<6> s;
            in >> bits(s);

            unsigned long raw_bits = static_cast<unsigned long>(s.to_ulong());
            my.t.d = raw_bits & 0b000001;
            my.t.e = (raw_bits & 0b000110) >> 1;
            my.t.f = (raw_bits & 0b111000) >> 3;

            return (in);
        }
    };
```

Raw memory
==========
```C++
    #include "hexdump.h"

    auto elems = 128;

    static void serialize (std::ofstream out)
    {
        auto a = new char[elems];
        for (auto i = 0; i < elems; i++) {
            a[i] = i;
        }
        out << bits(a);
    }

    static void deserialize (std::ifstream in)
    {
        auto a = new char[elems];
        in >> bits(a);

        hexdump(a, elems);
    }
```

Output:

```C++
    128 bytes:
    0000 00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f |................|
    0010 10 11 12 13 14 15 16 17  18 19 1a 1b 1c 1d 1e 1f |................|
    0020 20 21 22 23 24 25 26 27  28 29 2a 2b 2c 2d 2e 2f | !"#$%&'()*+,-./|
    0030 30 31 32 33 34 35 36 37  38 39 3a 3b 3c 3d 3e 3f |0123456789:;<=>?|
    0040 40 41 42 43 44 45 46 47  48 49 4a 4b 4c 4d 4e 4f |@ABCDEFGHIJKLMNO|
    0050 50 51 52 53 54 55 56 57  58 59 5a 5b 5c 5d 5e 5f |PQRSTUVWXYZ[\]^_|
    0060 60 61 62 63 64 65 66 67  68 69 6a 6b 6c 6d 6e 6f |`abcdefghijklmno|
    0070 70 71 72 73 74 75 76 77  78 79 7a 7b 7c 7d 7e 7f |pqrstuvwxyz{|}~.|
```

Compression
===========

For compression, look at the following which uses [quicklz](http://www.quicklz.com/download.html)

<pre>
    zipped_container_example.cpp
</pre>

Building
========

Do

<pre>
    sh ./RUNME
</pre>

Or, if that fails, manual build:

<pre>
    c++ -std=c++11 -Werror -O2 -Wall -c -o .o/main.o main.cpp
    c++ .o/main.o -o c_plus_plus_serializer
</pre>

To test:

<pre>
    ./c_plus_plus_serializer
</pre>

To debug, uncomment this line in Makefile.base, and then rerun RUNME:

<pre>
    #EXTRA_CFLAGS+=-DDEBUG_C_PLUS_PLUS_SERIALIZER
</pre>

To use 64-bit size_t when saving vectors, uncomment in Makefile.base and then
rerun RUNME:

<pre>
    #EXTRA_CFLAGS+=-DUSE_SIZE_T
</pre>

Note, no sanity checking is performed on the data when it is read back in, so
make sure your serializer and deserializers match perfectly.
