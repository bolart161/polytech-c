#include <vector>
#include <forward_list>
#include <iostream>
#include <string.h>
#include "tasks.hpp"
#include "accessBehavior.hpp"


int taskNum1(const char *direction)
{
  if (strcmp(direction, "ascending") != 0 && strcmp(direction, "descending") != 0) {
    std::cerr << "Error sorting direction is wrong";
    return 1;
  }

  using VectorCollection = std::vector<int>;
  using ListCollection = std::forward_list<int>;

  VectorCollection vectorAt = {};
  int i = -1;
  while (std::cin && !(std::cin>>i).eof()) {
    if (std::cin.fail() || std::cin.bad()) {
      std::cerr << "Error reading file";
      return 1;
    }
    vectorAt.push_back(i);
  }

  VectorCollection vectorBracket(vectorAt.begin(), vectorAt.end());
  ListCollection listIter(vectorAt.begin(), vectorAt.end());

  sortCollection<VectorCollection, AtAccess>(vectorAt, direction);
  sortCollection<VectorCollection, BracketAccess>(vectorBracket, direction);
  sortCollection<ListCollection, IterAccess>(listIter, direction);

  printCollection(vectorAt.begin(), vectorAt.end());
  printCollection(vectorBracket.begin(), vectorBracket.end());
  printCollection(listIter.begin(), listIter.end());

  return 0;
}
