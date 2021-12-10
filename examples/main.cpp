
int main(int argc, char *argv[])
{
  extern void basic_example(void);
  basic_example();

  extern void container_example(void);
  container_example();

  extern void raw_memory_example(void);
  raw_memory_example();

  extern void map_example(void);
  map_example();

  extern void unordered_map_example(void);
  unordered_map_example();

  extern void map_string_to_list_of_strings_example(void);
  map_string_to_list_of_strings_example();

  extern void custom_class_example(void);
  custom_class_example();

  extern void template_class_example(void);
  template_class_example();

  extern void map_custom_class_example(void);
  map_custom_class_example();

  extern void custom_bitset_class_example();
  custom_bitset_class_example();

  extern void zipper_container_example();
  zipper_container_example();

  return (0);
}
