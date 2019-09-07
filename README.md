Simple C++ 11 header-only serializer
====================================

A very minimal C++11 header only serializer. No sanity checking is performed
on the data when it is read back in, so make sure your serializer and 
deserializers match perfectly.

The data is saved in raw binary format, hence this is only loadable on the
same architecture that it is saved in.

To serialize basic POD types is fairly easy:

<pre>
    #include "c_plus_plus_serializer.h"

    static void serialize (std::ofstream out)
    {
	char a = 42;
	unsigned short b = 65535;
	int c = 123456;
	float d = std::numeric_limits<float>::max();
	double e = std::numeric_limits<double>::max();
        std::string f("hello");

	out << bits(a) << bits(b) << bits(c) << bits(d);
        out << bits(e) << bits(f);
    }
</pre>

To deserialize:

<pre>
    static void load (std::ifstream in)
    {
	char a;
	unsigned short b;
	int c;
	float d;
	double e;
	std::string f;

	in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
        in >> bits(e) >> bits(f);
    }
</pre>

For containers:

<pre>
    #include "c_plus_plus_serializer.h"

    static void serialize (std::ofstream out)
    {
        std::initializer_list<std::string> d1 = {"vec-elem1", "vec-elem2"};
	std::vector<std::string> a(d1);

	std::initializer_list<std::string> d2 = {"list-elem1", "list-elem2"};
	std::list<std::string> b(d2);

	std::array<std::string, 2> c = {"arr-elem1", "arr-elem2"};

	std::array<std::array<char, 2>, 3> d;
	d[0][0] = '0'; d[0][1] = '1';
	d[1][0] = '2'; d[1][1] = '3';
	d[2][0] = '4'; d[2][1] = '5';

	out << bits(a) << bits(b) << bits(c) << bits(d);
    }

    static void load (std::ifstream in)
    {
        std::string f;
	std::vector<std::string> a;
	std::list<std::string> b;
	std::array<std::string, 2> c;
	std::array<std::array<char, 2>, 3> d;

	in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
    }
</pre>

Maps:

<pre>
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
</pre>

Map of lists example:

<pre>
    static void serialize (std::ofstream out)
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

    static void deserialize (std::ifstream in)
    {
        std::map< std::string, std::list<std::string> > m;

        in >> bits(m);
    }
</pre>

Custom class example:

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

    static void serialize (...)
    {
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
</pre>

Bitfields example, C style and C++ style:

<pre>
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
</pre>

To build:

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

To debug, uncomment this line in Makefile.base, then recompile:

<pre>
    #EXTRA_CFLAGS+=-DDEBUG_C_PLUS_PLUS_SERIALIZER
</pre>
