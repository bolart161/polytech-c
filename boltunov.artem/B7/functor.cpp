#include "functor.hpp"

Functor::Functor ():
  max_ (std::numeric_limits<int>::min()),
  min_ (std::numeric_limits<int>::max()),
  count_ (0),
  sum_ (0),
  positive_ (0),
  negative_ (0),
  sumOdd_ (0),
  sumEven_ (0),
  first_ (0),
  last_ (0)
{}

void Functor::operator()(int newNum)
{
  if (newNum > max_) {
    max_ = newNum;
  }

  if (newNum < min_) {
    min_ = newNum;
  }

  if (newNum > 0) {
    positive_++;
  }

  if (newNum < 0) {
    negative_++;
  }

  if (count_ == 0) {
    first_ = newNum;
  }

  last_ = newNum;
  sum_ += newNum;
  count_++;

  if (newNum % 2 != 0) {
    sumOdd_+= newNum;
  } else {
    sumEven_+=newNum;
  }
}

void Functor::print()
{
  if (count_ == 0) {
    std::cout << "No Data" << std::endl;
    return;
  }
  std::cout.precision(1);
  double mean = sum_ / count_;
  std::cout << "Max: " << max_ << std::endl;
  std::cout << "Min: " << min_ << std::endl;
  std::cout << "Mean: " << std::fixed << mean << std::endl;
  std::cout << "Positive: " << positive_ << std::endl;
  std::cout << "Negative: " << negative_ << std::endl;
  std::cout << "Odd Sum: " << sumOdd_ << std::endl;
  std::cout << "Even Sum: " << sumEven_ << std::endl;

  (first_ != last_) ? (std::cout << "First/Last Equal: no" << std::endl) : (std::cout << "First/Last Equal: yes" << std::endl);
}
