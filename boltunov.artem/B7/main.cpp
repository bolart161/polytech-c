#include "functor.hpp"

int main()
{
  Functor func;
  std::for_each(std::istream_iterator<int> (std::cin), std::istream_iterator<int> (), std::ref(func));

  if (!std::cin.eof()) {
    std::cerr << "Invalid input";
    return 1;
  }

  func.print();
  return 0;
}
