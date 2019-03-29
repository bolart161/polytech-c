#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iterator>
#include <functional>

class Functor
{
public:
  Functor();
  void operator ()(int newNum);
  void print();
private:
  int max_;
  int min_;
  double count_;
  double sum_;
  int positive_;
  int negative_;
  long int sumOdd_;
  long int sumEven_;
  int first_;
  int last_;
};

#endif //FUNCTOR_HPP
