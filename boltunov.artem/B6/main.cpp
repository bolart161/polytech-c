#include "task1.hpp"
#include "task2.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Wrong patameters count";
    return 1;
  }

  std::string taskNum(argv[1]);
  try {
    if (taskNum == "1") {
      task1();
    } else if (taskNum == "2") {
      task2();
    } else {
      std::cerr << "Wrong task number";
      return 1;
    }
  } catch (const std::exception & e) {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
