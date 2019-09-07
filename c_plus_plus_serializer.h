#ifndef C_PLUS_PLUS_SERIALIZER
#define C_PLUS_PLUS_SERIALIZER
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

template<typename TYPE> struct Bits { TYPE t; };

template<typename TYPE>
static inline Bits<TYPE&> bits(TYPE &t)
{
    return Bits<TYPE&>{t};
}

template<typename TYPE>
static inline Bits<const TYPE&> bits(const TYPE& t)
{
    return Bits<const TYPE&>{t};
}

////////////////////////////////////////////////////////////////////////////
// Read/write POD types
////////////////////////////////////////////////////////////////////////////
template<typename TYPE>
static inline std::istream& operator>>(std::istream& s, Bits<TYPE&> b)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read " << sizeof(TYPE) << " bytes" << std::endl;
#endif
    return s.read((char*)(&b.t), sizeof(TYPE));
}

template<typename TYPE>
static inline std::ostream& operator<<(std::ostream &s, Bits<TYPE&> const b)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write " << sizeof(TYPE) << " bytes" << std::endl;
#endif
    // reinterpret_cast is for pointer conversion
    // static_cast is for compatible pointer conversion
    return s.write(reinterpret_cast<const char*>(&(b.t)), sizeof(TYPE));
}

////////////////////////////////////////////////////////////////////////////
// Read/write std::string
////////////////////////////////////////////////////////////////////////////
static inline std::istream& operator>>(std::istream& in, Bits<std::string &> v)
{
    size_t sz = 0;
    in >> bits(sz);
    if (in && sz) {
        std::vector<char> tmp(sz);
        in.read(tmp.data(), sz);
        v.t.assign(tmp.data(), sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "read '" << v.t << "'" << std::endl;
#endif
    }

    return in;
}

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const std::string &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write const '" << v.t << "'" << std::endl;
#endif
    size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

static inline
std::ostream& operator<<(std::ostream &out, Bits<std::string &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write '" << v.t << "'" << std::endl;
#endif
    size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

////////////////////////////////////////////////////////////////////////////
// Read/write simple container
////////////////////////////////////////////////////////////////////////////
template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<C<T> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write container<string> " << v.t.size() << " elems" << std::endl;
#endif
    size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const C<T> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write container<const T> " << v.t.size() << " elems" << std::endl;
#endif
    size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::istream& operator>>(std::istream &in, Bits<C<T> &> v)
{
    size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read container<T> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        while (sz--) {
            T s;
            in >> bits(s);
            v.t.push_back(s);
        }
    }

    return in;
}

////////////////////////////////////////////////////////////////////////////
// Read/write map
////////////////////////////////////////////////////////////////////////////
template <class K, class V>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<std::map<K,V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write map<K,V> " << m.t.size() << " elems" << std::endl;
#endif
    size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <class K, class V>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<std::map<K,const V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write map<K,const V> " << m.t.size() << " elems" << std::endl;
#endif
    size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <class K, class V>
static inline std::istream& operator>>(std::istream &in, 
                                       Bits<std::map<K,V> &> m)
{
    size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read map<K,V> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        while (sz--) {
            K k;
            V v;
            in >> bits(k) >> bits(v);
            m.t.insert(std::make_pair(k, v));
        }
    }

    return in;
}
#endif /* C_PLUS_PLUS_SERIALIZER */
