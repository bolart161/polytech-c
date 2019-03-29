#include "tasks.hpp"
#include "factorials.hpp"

void secondTask()
{
  Container factorial;
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
  std::reverse_iterator<Container::Iterator> rbegin(factorial.end());
  std::reverse_iterator<Container::Iterator> rend(factorial.begin());
  std::copy(rbegin, rend, std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
}
