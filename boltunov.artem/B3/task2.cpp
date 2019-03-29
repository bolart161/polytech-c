#include "tasks.hpp"
#include <list>
#include <stdexcept>
#include <iostream>


template <typename T>
void print(T beginIter, T endIter, int size, std::ostream & out)
{
  if (size == 1) {
    out << *beginIter << std::endl;
    return;
  }
  endIter--;
  while (size != 0) {
    if (size > 1) {
      out << *beginIter << ' ' << *endIter;
      if (size / 2 != 1) {
        out << ' ';
      }
      beginIter++;
      endIter--;
      size-=2;
    } else {
      out << ' ' << *beginIter;
      size-=1;
    }
  }
  out << std::endl;
}

void task2(std::istream & input, std::ostream & out)
{
  const size_t maxSize = 20;
  const int minVal = 1;
  const int maxVal = 20;
  std::list<int> list;

  int value;
  while(input >> value) {
    if((value < minVal) || (value > maxVal)) {
      throw std::out_of_range("Incorrect data.");
    }
    list.push_back(value);
  }

  if (!input.eof() || (list.size() > maxSize)) {
    throw std::invalid_argument("Incorrect input.");
  }

  if (list.empty()) {
    return;
  }

  print(list.begin(), list.end(), list.size(), out);
}
