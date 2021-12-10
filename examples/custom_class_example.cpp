#include "c_plus_plus_serializer.h"
#include <list>
#include <map>
#include <vector>

class Custom
{
public:
  int                        a;
  std::string                b;
  std::vector< std::string > c;

  friend std::ostream &operator<<(std::ostream &out, Bits< const class Custom & > const my)
  {
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write custom class" << std::endl;
#endif
    out << bits(my.t.a) << bits(my.t.b) << bits(my.t.c);
    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< class Custom & > my)
  {
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read custom class" << std::endl;
#endif
    in >> bits(my.t.a) >> bits(my.t.b) >> bits(my.t.c);
    return (in);
  }

  friend std::ostream &operator<<(std::ostream &out, class Custom &my)
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

static void save(const std::string filename, const class Custom &c)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  out << bits(c);
}

static void load(const std::string filename, class Custom &c)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  in >> bits(c);
}

static void save_custom_class_example(void)
{
  auto c = Custom();

  c.a = 1;
  c.b = "hello";

  std::initializer_list< std::string > L1 = {"vec-elem1", "vec-elem2"};
  std::vector< std::string >           l1(L1);
  c.c = l1;

  save(std::string("custom_class.bin"), c);
}

static void load_custom_class_example(void)
{
  auto c = Custom();

  load(std::string("custom_class.bin"), c);
  std::cout << std::endl;
  std::cout << c;
  std::cout << std::endl;
}

void custom_class_example(void)
{
  std::cout << "custom_class_example" << std::endl;
  std::cout << "====================" << std::endl;
  save_custom_class_example();
  load_custom_class_example();
}
