#include "c_plus_plus_serializer.h"
#include "hexdump.h"
#include "quicklz.h"
#include <array>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <vector>

static std::vector< char > read_binary_file(const std::string filename)
{
  // binary mode is only for switching off newline translation
  std::ifstream file(filename, std::ios::binary);
  file.unsetf(std::ios::skipws);

  std::streampos file_size;
  file.seekg(0, std::ios::end);
  file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector< char > vec(file_size);
  vec.insert(vec.begin(), std::istream_iterator< char >(file), std::istream_iterator< char >());
  return (vec);
}

static void save_zipper_container(const std::string filename)
{
  std::cout << "save to " << filename << std::endl;
  std::stringstream out(std::ios::in | std::ios::out | std::ios::binary);

  std::initializer_list< std::string > d1 = {"vec-elem1", "vec-elem2"};
  std::vector< std::string >           a(d1);

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

  //
  // Get the pre compress buffer
  //
  std::string tmp = out.str();
  out.seekg(0, std::ios::end);
  int srclen = out.tellg();
  out.seekg(0, std::ios::beg);

  std::cout << "before compression ";
  hexdump(tmp.c_str(), srclen);

  //
  // Compress
  //
  qlz_state_compress *state_compress = (qlz_state_compress *) new char[ sizeof(qlz_state_compress) ];

  //
  // http://www.quicklz.com/manual.html
  //
  // The destination buffer must be at least size + 400 bytes large because
  // incompressible data may increase in size.
  //
  auto dst    = new char[ srclen + 400 /* qlz header */ ];
  auto dstlen = qlz_compress(tmp.c_str(), dst, srclen, state_compress);

  //
  // Dump the post compress buffer
  //
  std::cout << "after compression ";
  hexdump(dst, dstlen);

  //
  // Save the post compress buffer
  //
  auto ofile = fopen(filename.c_str(), "wb");
  fwrite(dst, dstlen, 1, ofile);
  fclose(ofile);
  delete[] dst;
  delete state_compress;
}

static void load_zipper_container(const std::string filename)
{
  //
  // Read to a vector and then copy to a C buffer for qlz to use
  //
  auto vec = read_binary_file(filename);

#ifdef MAKE_COPY
  auto src = (char *) new char[ vec.size() ];
  std::copy(vec.begin(), vec.end(), src);
#else
  //
  // Avoid copying, a bit hacky, but should work
  //
  auto src = vec.data();
#endif

  //
  // Decompress
  //
  auto                  dstlen           = qlz_size_decompressed(src);
  auto                  dst              = new char[ dstlen ];
  qlz_state_decompress *state_decompress = (qlz_state_decompress *) new char[ sizeof(qlz_state_decompress) ];
  auto                  newlen           = qlz_decompress(src, dst, state_decompress);

  std::cout << "decompressed as ";
  hexdump(dst, newlen);

  std::string        s((const char *) dst, (size_t) newlen);
  std::istringstream in(s);

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

  delete state_decompress;
#ifdef MAKE_COPY
  delete[] src;
#endif
  delete[] dst;
}

void zipper_container_example(void)
{
  std::cout << "zipper_container_example" << std::endl;
  std::cout << "========================" << std::endl;
  save_zipper_container(std::string("zipper_container_example.bin"));
  load_zipper_container(std::string("zipper_container_example.bin"));
}
