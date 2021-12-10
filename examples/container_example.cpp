#include "c_plus_plus_serializer.h"
#include <array>
#include <limits>
#include <list>
#include <map>
#include <vector>

static void save_container(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::initializer_list< std::string > d1 = {
      "vec-elem1",
      "vec-elem2"
      "vec-elem3, I may not have gone where I intended to go, but I think I have ended up where I needed to be.",
  };
  std::vector< std::string > a(d1);

  std::initializer_list< std::string > d2 = {"list-elem1", "list-elem2"};
  std::list< std::string >             b(d2);

  std::array< std::string, 2 > c = {"arr-elem1", "arr-elem2"};

  //
  // 2d array
  //
  std::array< std::array< char, 2 >, 3 > dd;
  dd[ 0 ][ 0 ] = '0';
  dd[ 0 ][ 1 ] = '1';
  dd[ 1 ][ 0 ] = '2';
  dd[ 1 ][ 1 ] = '3';
  dd[ 2 ][ 0 ] = '4';
  dd[ 2 ][ 1 ] = '5';

  //
  // 3d array
  //
  std::array< std::array< std::array< char, 2 >, 3 >, 4 > ddd;
  ddd[ 0 ][ 0 ][ 0 ] = 'a';
  ddd[ 0 ][ 0 ][ 1 ] = 'b';
  ddd[ 0 ][ 1 ][ 0 ] = 'c';
  ddd[ 0 ][ 1 ][ 1 ] = 'd';
  ddd[ 0 ][ 2 ][ 0 ] = 'e';
  ddd[ 0 ][ 2 ][ 1 ] = 'f';
  ddd[ 1 ][ 0 ][ 0 ] = 'g';
  ddd[ 1 ][ 0 ][ 1 ] = 'h';
  ddd[ 1 ][ 1 ][ 0 ] = 'i';
  ddd[ 1 ][ 1 ][ 1 ] = 'j';
  ddd[ 1 ][ 2 ][ 0 ] = 'k';
  ddd[ 1 ][ 2 ][ 1 ] = 'l';
  ddd[ 2 ][ 0 ][ 0 ] = 'm';
  ddd[ 2 ][ 0 ][ 1 ] = 'n';
  ddd[ 2 ][ 1 ][ 0 ] = 'o';
  ddd[ 2 ][ 1 ][ 1 ] = 'p';
  ddd[ 2 ][ 2 ][ 0 ] = 'q';
  ddd[ 2 ][ 2 ][ 1 ] = 'r';
  ddd[ 3 ][ 0 ][ 0 ] = 's';
  ddd[ 3 ][ 0 ][ 1 ] = 't';
  ddd[ 3 ][ 1 ][ 0 ] = 'u';
  ddd[ 3 ][ 1 ][ 1 ] = 'v';
  ddd[ 3 ][ 2 ][ 0 ] = 'w';
  ddd[ 3 ][ 2 ][ 1 ] = 'x';

  out << bits(a) << bits(b) << bits(c) << bits(dd) << bits(ddd);
}

static void load_container(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::vector< std::string >                              a;
  std::list< std::string >                                b;
  std::array< std::string, 2 >                            c;
  std::array< std::array< char, 2 >, 3 >                  dd;
  std::array< std::array< std::array< char, 2 >, 3 >, 4 > ddd;

  in >> bits(a) >> bits(b) >> bits(c) >> bits(dd) >> bits(ddd);

  std::cout << std::endl;
  std::cout << "a: std::vector<std::string> " << a.size() << " elems: ";
  for (auto elem : a) {
    std::cout << "[" << elem << "] ";
  }
  std::cout << std::endl;

  std::cout << "b: std::list<std::string>   " << b.size() << " elems: ";
  for (auto elem : b) {
    std::cout << "[" << elem << "] ";
  }
  std::cout << std::endl;

  std::cout << "c: std::array<std::string>  " << c.size() << " elems: ";
  for (auto elem : c) {
    std::cout << "[" << elem << "] ";
  }
  std::cout << std::endl;

  std::cout << "2d: std::array<std::array<char, 2>, 3> :" << std::endl;
  for (auto x = 0; x < 3; x++) {
    for (auto y = 0; y < 2; y++) {
      std::cout << "  2d[" << x << "][" << y << "] = " << dd[ x ][ y ] << std::endl;
    }
  }
  std::cout << std::endl;

  std::cout << "3d: std::array<std::array<std::array<char, 2>, 3>, 4> :" << std::endl;
  for (auto x = 0; x < 4; x++) {
    for (auto y = 0; y < 3; y++) {
      for (auto z = 0; z < 2; z++) {
        std::cout << "  3d[" << x << "][" << y << "][" << z << "] = " << ddd[ x ][ y ][ z ] << std::endl;
      }
    }
  }
  std::cout << std::endl;
}

void container_example(void)
{
  std::cout << "container_example" << std::endl;
  std::cout << "=================" << std::endl;
  save_container(std::string("container_example.bin"));
  load_container(std::string("container_example.bin"));
}
