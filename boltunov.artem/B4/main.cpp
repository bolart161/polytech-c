#include <iostream>
#include <stdexcept>
#include <string>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid number of parameters";
    return 1;
  }

  std::string taskNum(argv[1]);
  try {
    if (taskNum == "1") {
      firstTask(std::cin, std::cout);
    }  else if (taskNum == "2") {
      secondTask();
    } else {
      std::cerr << "Wrong task;";
      return 1;
    }
  } catch (const std::exception & e) {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
