#include "c_plus_plus_serializer.h"
#include <list>
#include <set>
#include <vector>

static void save_set_key_string_value_string(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::set< std::string > m;

  m.insert(std::string("key1"));
  m.insert(std::string("key2"));
  m.insert(std::string("key3"));
  m.insert(std::string("key4"));

  out << bits(m);
}

static void load_set_key_string_value_string(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::set< std::string > m;

  in >> bits(m);
  std::cout << std::endl;

  std::cout << "m = " << m.size() << " list-elems { " << std::endl;
  for (auto i : m) {
    std::cout << "    [" << i << "] " << std::endl;
  }
  std::cout << "}" << std::endl;
  std::cout << std::endl;
}

void set_example(void)
{
  std::cout << "set key string, value string" << std::endl;
  std::cout << "============================" << std::endl;
  save_set_key_string_value_string(std::string("set_of_strings.bin"));
  load_set_key_string_value_string(std::string("set_of_strings.bin"));
}
