#include "c_plus_plus_serializer.h"
#include <list>
#include <unordered_map>
#include <vector>

static void save_unordered_map_key_string_value_string(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::unordered_map< std::string, std::string > m;

  m.insert(std::make_pair(std::string("key1"), std::string("value1")));
  m.insert(std::make_pair(std::string("key2"), std::string("value2")));
  m.insert(std::make_pair(std::string("key3"), std::string("value3")));
  m.insert(std::make_pair(std::string("key4"), std::string("value4")));

  out << bits(m);
}

static void load_unordered_map_key_string_value_string(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::unordered_map< std::string, std::string > m;

  in >> bits(m);
  std::cout << std::endl;

  std::cout << "m = " << m.size() << " list-elems { " << std::endl;
  for (auto i : m) {
    std::cout << "    [" << i.first << "] = " << i.second << std::endl;
  }
  std::cout << "}" << std::endl;
  std::cout << std::endl;
}

void unordered_map_example(void)
{
  std::cout << "unordered_map key string, value string" << std::endl;
  std::cout << "======================================" << std::endl;
  save_unordered_map_key_string_value_string(std::string("unordered_map_of_strings.bin"));
  load_unordered_map_key_string_value_string(std::string("unordered_map_of_strings.bin"));
}
