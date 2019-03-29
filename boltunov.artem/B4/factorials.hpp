#ifndef FACTORIALS_HPP
#define FACTORIALS_HPP

#include <iterator>

class Container
{
public:
  class Iterator;
  Iterator begin();
  Iterator end();
};

class Container::Iterator :
  public std::iterator<std::bidirectional_iterator_tag, size_t, size_t, size_t*, size_t>
{
public:
  Iterator();
  size_t & operator * ();
  size_t * operator -> ();
  Iterator & operator ++ ();
  Iterator operator ++ (int);
  Iterator & operator -- ();
  Iterator operator -- (int);
  bool operator == (const Iterator & rhs) const;
  bool operator != (const Iterator & rhs) const;

private:
  size_t n_;
  size_t factor_;
};
#endif
