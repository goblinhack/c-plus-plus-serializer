#include "c_plus_plus_serializer.h"
#include <list>
#include <map>
#include <vector>

static void save_map_key_string_value_string(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::map< std::string, std::string > m;

  m.insert(std::make_pair(std::string("key1"), std::string("value1")));
  m.insert(std::make_pair(std::string("key2"), std::string("value2")));
  m.insert(std::make_pair(std::string("key3"), std::string("value3")));
  m.insert(std::make_pair(std::string("key4"), std::string("value4")));

  out << bits(m);
}

static void load_map_key_string_value_string(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::map< std::string, std::string > m;

  in >> bits(m);
  std::cout << std::endl;

  std::cout << "m = " << m.size() << " list-elems { " << std::endl;
  for (auto i : m) {
    std::cout << "    [" << i.first << "] = " << i.second << std::endl;
  }
  std::cout << "}" << std::endl;
  std::cout << std::endl;
}

void map_example(void)
{
  std::cout << "map key string, value string" << std::endl;
  std::cout << "============================" << std::endl;
  save_map_key_string_value_string(std::string("map_of_strings.bin"));
  load_map_key_string_value_string(std::string("map_of_strings.bin"));
}
