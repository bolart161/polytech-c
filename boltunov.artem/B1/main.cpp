#include "tasks.hpp"

int main(int argc, char *argv[])
{
  if (argc == 1) {
    std::cerr << "Incorrect count args";
    return 1;
  }

  int code = 0;
  const int numOfTask = atoi(argv[1]);

  switch (numOfTask) {
  case 1:{
    if (argc < 3) {
      std::cerr << "Incorrect args";
      return 1;
    }
    code = taskNum1(argv[2]);
    break;
  }
  case 2:{
    if (argc < 3) {
      std::cerr << "Incorrect args";
      return 1;
    }
    code = taskNum2(argv[2]);
    break;
  }
  case 3:{
    code = taskNum3();
    break;
  }
  case 4:{
    if (argc < 4) {
      std::cerr << "Incorrect args";
      return 1;
    }
    code = taskNum4(argv[2], argv[3]);
    break;
  }
  default:
    std::cerr << "Incorrect args";
    return 1;
  }

  return code;

}
