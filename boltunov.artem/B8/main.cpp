#include <iostream>
#include "task1.hpp"
#include "task2.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Wrong number of parameters;";
    return 1;
  }

  std::string taskNumber(argv[1]);
  try {
    if (taskNumber == "1") {
      task1();
    } else if (taskNumber == "2") {
      task2();
    } else {
      std::cerr << "Wrong task number;";
      return 1;
    }
  } catch (const std::exception & e) {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
