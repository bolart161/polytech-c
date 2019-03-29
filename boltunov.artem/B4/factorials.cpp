#include "factorials.hpp"

Container::Iterator Container::begin()
{
  return Container::Iterator{};
}

Container::Iterator Container::end()
{
  Container::Iterator iter{};
  std::advance(iter, 10);
  return iter;
}

Container::Iterator::Iterator() :
  n_(1),
  factor_(1)
{}

size_t & Container::Iterator::operator * ()
{
  return factor_;
}

size_t * Container::Iterator::operator -> ()
{
  return &factor_;
}

Container::Iterator & Container::Iterator::operator ++ ()
{
  factor_ *= ++n_;
  return *this;
}

Container::Iterator Container::Iterator::operator ++ (int)
{
  Container::Iterator oldIter = *this;
  factor_ *= ++n_;
  return oldIter;
}

Container::Iterator & Container::Iterator::operator -- ()
{
  factor_ /= n_--;
  return *this;
}

Container::Iterator Container::Iterator::operator -- (int)
{
  Container::Iterator oldIter = *this;
  factor_ /= n_--;
  return oldIter;
}

bool Container::Iterator::operator == (const Container::Iterator & rhs) const
{
  return n_ == rhs.n_;
}

bool Container::Iterator::operator != (const Container::Iterator & rhs) const
{
  return n_ != rhs.n_;
}
