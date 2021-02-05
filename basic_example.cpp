#include "c_plus_plus_serializer.h"
#include <limits>

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
    wchar_t g = L'💩';
    std::wstring h(L"wide string 💩");
    std::pair<int, std::string> p(42, "life");

    std::cout << std::endl;
    std::cout << "write:" <<  std::endl;
    std::cout << "  a: char                     " << a << std::endl;
    std::cout << "  b: unsigned short           " << b << std::endl;
    std::cout << "  c: int                      " << c << std::endl;
    std::cout << "  d: float                    " << d << std::endl;
    std::cout << "  e: double                   " << e << std::endl;
    std::cout << "  f: std::string              " << f << std::endl;
    std::wcout << "  g: wchar_t                  " << g << std::endl;
    std::wcout << "  h: std::wstring             " << h << std::endl;
    std::cout << "  p: std::pair                " << p.first << " " << p.second << std::endl;

    std::cout << std::endl;

    out << bits(a) << bits(b) << bits(c) << bits(d);
    out << bits(e) << bits(f) << bits(g) << bits(h);
    out << bits(p);
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
    wchar_t g;
    std::wstring h;
    std::pair<int, std::string> p;

    in >> bits(a) >> bits(b) >> bits(c) >> bits(d);
    in >> bits(e) >> bits(f) >> bits(g) >> bits(h);
    in >> bits(p);

    std::cout << std::endl;
    std::cout << "read:" <<  std::endl;
    std::cout << "  a: char                     " << a << std::endl;
    std::cout << "  b: unsigned short           " << b << std::endl;
    std::cout << "  c: int                      " << c << std::endl;
    std::cout << "  d: float                    " << d << std::endl;
    std::cout << "  e: double                   " << e << std::endl;
    std::cout << "  f: std::string              " << f << std::endl;
    std::wcout << "  g: wchar_t                  " << g << std::endl;
    std::wcout << "  h: std::wstring             " << h << std::endl;
    std::cout << "  p: std::pair                " << p.first << " " << p.second << std::endl;
    std::cout << std::endl;
}

void basic_example (void)
{
    //
    // Need this to get the poop emoji printed! :)
    //
    std::locale loc("");
    std::ios_base::sync_with_stdio(false);
    std::wcout.imbue(loc);

    std::cout << "basic_example" << std::endl;
    std::cout << "=============" << std::endl;
    save_simple(std::string("basic_example.bin"));
    load_simple(std::string("basic_example.bin"));
}
