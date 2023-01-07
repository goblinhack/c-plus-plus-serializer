#include "c_plus_plus_serializer.h"
#include <deque>
#include <list>
#include <vector>

static void save_deque_key_string_value_string(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::ofstream out(filename, std::ios::binary);

  std::deque< std::string > m;

  m.push_front(std::string("key1"));
  m.push_front(std::string("key2"));
  m.push_back(std::string("key3"));
  m.push_back(std::string("key4"));

  out << bits(m);
}

static void load_deque_key_string_value_string(const std::string filename)
{
  std::cout << "read from " << filename << std::endl;
  std::ifstream in(filename);

  std::deque< std::string > m;

  in >> bits(m);
  std::cout << std::endl;

  std::cout << "m = " << m.size() << " list-elems { " << std::endl;
  for (auto i : m) {
    std::cout << "    [" << i << "] " << std::endl;
  }
  std::cout << "}" << std::endl;
  std::cout << std::endl;
}

void deque_example(void)
{
  std::cout << "deque key string, value string" << std::endl;
  std::cout << "============================" << std::endl;
  save_deque_key_string_value_string(std::string("deque_of_strings.bin"));
  load_deque_key_string_value_string(std::string("deque_of_strings.bin"));
}
