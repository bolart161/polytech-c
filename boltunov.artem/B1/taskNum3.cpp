#include <vector>
#include <iostream>
#include <iterator>
#include "tasks.hpp"

int taskNum3()
{
  std::vector<int> vector = {};
  int i = -1;
  size_t multiples3 = 0;

  while (std::cin && !(std::cin>>i).eof()) {
    if (std::cin.fail() || std::cin.bad()) {
      std::cerr << "Error reading file";
      return 1;
    }
    if (i == 0) {
      break;
    }
    if (i % 3 == 0) {
      multiples3++;
    }
    vector.push_back(i);
  }

  if (vector.empty()) {
    return 0;
  }

  if (i != 0) {
    std::cerr << "Missing zero";
    return 1;
  }

  if (vector.back() == 1) {
    auto iter = vector.begin();
    while (iter != vector.end()) {
      if (*iter % 2 == 0) {
        iter = vector.erase(iter);
      } else {
        iter++;
      }
    }
  }

  if (vector.back() == 2) {
    vector.reserve(vector.size() + multiples3 * 3);
    auto iter = vector.begin();
    while (iter != vector.end()) {
      if (*iter % 3 == 0) {
        iter = vector.insert(iter + 1, 3, 1);
        iter += 2;
      }
      iter++;
    }
  }

  printCollection(vector.begin(), vector.end());
  return 0;
}
