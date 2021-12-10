#include "c_plus_plus_serializer.h"
#include "hexdump.h"
#include <array>
#include <limits>
#include <list>
#include <map>
#include <vector>

static void save_raw_memory(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  auto elems = 128;
  auto a     = new char[ elems ];
  for (auto i = 0; i < elems; i++) {
    a[ i ] = i;
  }

  out << bits(a);
}

static void load_raw_memory(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  auto elems = 128;
  auto a     = new char[ elems ];
  in >> bits(a);

  hexdump(a, elems);
  std::cout << std::endl;
}

void raw_memory_example(void)
{
  std::cout << "raw_memory_example" << std::endl;
  std::cout << "==================" << std::endl;
  save_raw_memory(std::string("raw_memory_example.bin"));
  load_raw_memory(std::string("raw_memory_example.bin"));
}
