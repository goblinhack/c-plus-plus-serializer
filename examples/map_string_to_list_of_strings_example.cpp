#include "c_plus_plus_serializer.h"
#include <list>
#include <map>
#include <vector>

static void save_map_key_string_value_list_of_strings(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::map< std::string, std::list< std::string > > m;

  std::initializer_list< std::string > L1 = {"list-elem1", "list-elem2"};
  std::list< std::string >             l1(L1);
  std::initializer_list< std::string > L2 = {"list-elem3", "list-elem4"};
  std::list< std::string >             l2(L2);

  m.insert(std::make_pair(std::string("key1"), l1));
  m.insert(std::make_pair(std::string("key2"), l2));

  out << bits(m);
}

static void load_map_key_string_value_list_of_strings(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::map< std::string, std::list< std::string > > m;

  in >> bits(m);
  std::cout << std::endl;

  std::cout << "m = " << m.size() << " list-elems { " << std::endl;
  for (auto i : m) {
    std::cout << "    [" << i.first << "] = [ ";
    for (auto j : i.second) {
      std::cout << j << ", ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "}" << std::endl;
  std::cout << std::endl;
}

void map_string_to_list_of_strings_example(void)
{
  std::cout << "map key string, value list of strings" << std::endl;
  std::cout << "=====================================" << std::endl;
  save_map_key_string_value_list_of_strings(std::string("map_of_string_to_list_of_strings.bin"));
  load_map_key_string_value_list_of_strings(std::string("map_of_string_to_list_of_strings.bin"));
}
