#include <vector>
#include <ctime>
#include <iostream>
#include <string.h>
#include <math.h>
#include "tasks.hpp"
#include "accessBehavior.hpp"

void fillRandom(double *array, int size)
{
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    array[i] = (rand() % 11) * 0.2 - 1;
  }
}

int taskNum4(const char *direction, const char *num)
{
  if (strcmp(direction, "ascending") != 0 && strcmp(direction, "descending") != 0) {
    std::cerr << "Error: sorting direction is wrong";
    return 1;
  }

  using Collection = std::vector<double>;

  const size_t numElements = atoi(num);
  if (numElements <= 0) {
    std::cerr << "Invalid args of length";
    return 1;
  }

  //Before sorting
  Collection vector(numElements);
  fillRandom(vector.data(), numElements);
  printCollection(vector.begin(), vector.end());

  sortCollection<Collection, AtAccess>(vector, direction);
  //After sorting
  printCollection(vector.begin(), vector.end());

  return 0;
}
