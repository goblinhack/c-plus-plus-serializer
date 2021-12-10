#include "c_plus_plus_serializer.h"
#include <bitset>

class BitsetClass
{
public:
  std::bitset< 1 > a;
  std::bitset< 2 > b;
  std::bitset< 3 > c;

  unsigned int d : 1;
  unsigned int e : 2;
  unsigned int f : 3;

  BitsetClass(void)
  {
    d = 0;
    e = 0;
    f = 0;
  }

  friend std::ostream &operator<<(std::ostream &out, Bits< const class BitsetClass & > const my)
  {
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write custom bitset class" << std::endl;
#endif
    out << bits(my.t.a);
    out << bits(my.t.b);
    out << bits(my.t.c);

    std::bitset< 6 > s(my.t.d | my.t.e << 1 | my.t.f << 3);
    out << bits(s);

    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< class BitsetClass & > my)
  {
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read custom bitset class" << std::endl;
#endif
    std::bitset< 1 > a;
    in >> bits(a);
    my.t.a = a;

    in >> bits(my.t.b);
    in >> bits(my.t.c);
    std::bitset< 6 > s;
    in >> bits(s);

    unsigned long raw_bits = static_cast< unsigned long >(s.to_ulong());
    my.t.d                 = raw_bits & 0b000001;
    my.t.e                 = (raw_bits & 0b000110) >> 1;
    my.t.f                 = (raw_bits & 0b111000) >> 3;

    return (in);
  }

  friend std::ostream &operator<<(std::ostream &out, const class BitsetClass &my)
  {
    out << "a(1bit):" << my.a << std::endl;
    out << "b(2bit):" << my.b << std::endl;
    out << "c(3bit):" << my.c << std::endl;
    out << "d(1bit):" << std::bitset< 1 >(my.d) << std::endl;
    out << "e(2bit):" << std::bitset< 2 >(my.e) << std::endl;
    out << "f(3bit):" << std::bitset< 3 >(my.f) << std::endl;

    return (out);
  }
};

static void save(const std::string filename, const class BitsetClass &c)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  out << bits(c);
}

static void load(const std::string filename, class BitsetClass &c)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  in >> bits(c);
}

static void save_custom_bitset_class_example(void)
{
  auto c = BitsetClass();

  c.a = 1;
  c.b = 3;
  c.c = 7;
  c.d = 1;
  c.e = 3;
  c.f = 7;

  save(std::string("custom_bitset_class.bin"), c);
}

static void load_custom_bitset_class_example(void)
{
  auto c = BitsetClass();

  load(std::string("custom_bitset_class.bin"), c);
  std::cout << std::endl;
  std::cout << c;
  std::cout << std::endl;
}

void custom_bitset_class_example(void)
{
  std::cout << "custom_bitset_class_example" << std::endl;
  std::cout << "===========================" << std::endl;
  save_custom_bitset_class_example();
  load_custom_bitset_class_example();
}
