#include "c_plus_plus_serializer.h"
#include <list>
#include <map>
#include <vector>

template < class T > class MyPoint
{
public:
  T x {};
  T y {};

  MyPoint(void) : x(0), y(0) {};

  MyPoint(T x, T y) : x(x), y(y) {}

  friend std::ostream &operator<<(std::ostream &out, Bits< const MyPoint & > const my)
  {
    out << bits(my.t.x) << bits(my.t.y);
    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< MyPoint & > my)
  {
    in >> bits(my.t.x) >> bits(my.t.y);
    return (in);
  }

  friend std::ostream &operator<<(std::ostream &out, const MyPoint &my)
  {
    out << "(" << my.x << ", " << my.y << ")";
    return (out);
  }
};

typedef MyPoint< int >    IntPoint;
typedef MyPoint< float >  FloatPoint;
typedef MyPoint< double > DoublePoint;

static void save_template_class_example(void)
{
  auto filename = ("template_class.bin");
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  out << bits(IntPoint(1, 2));
  out << bits(FloatPoint(1.1, 2.2));
  out << bits(DoublePoint(3.3, 4.4));
}

static void load_template_class_example(void)
{
  auto filename = ("template_class.bin");
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  IntPoint    a;
  FloatPoint  b;
  DoublePoint c;

  in >> bits(a);
  in >> bits(b);
  in >> bits(c);

  std::cout << std::endl;
  std::cout << "IntPoint: " << a << std::endl;
  std::cout << "FloatPoint: " << b << std::endl;
  std::cout << "DoublePoint: " << c << std::endl;
  std::cout << std::endl;
}

void template_class_example(void)
{
  std::cout << "template_class_example" << std::endl;
  std::cout << "======================" << std::endl;
  save_template_class_example();
  load_template_class_example();
}
