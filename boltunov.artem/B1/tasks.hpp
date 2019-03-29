#ifndef TASKS_HPP
#define TASKS_HPP

#include <iostream>
#include <memory>
#include <string.h>
#include "accessBehavior.hpp"

template <typename TCollection, template <typename> class TAccess>
void sortCollection(TCollection &collection, const char *direction)
{
  std::shared_ptr<AccessBehavior<TCollection>> access = std::make_shared<TAccess<TCollection>>();

  for (auto i = collection.begin(); i != collection.end(); i = std::next(i)) {
    auto currentItem = i;
    for (auto j = std::next(i); j != collection.end(); j = std::next(j)) {
      if (strcmp(direction, "ascending") ? *access -> getElement(collection, j) > *access -> getElement(collection, currentItem):
          *access -> getElement(collection, j) < *access -> getElement(collection, currentItem)) {
        currentItem = j;
      }
    }
    if (currentItem != i) {
      std::swap(*access->getElement(collection, i), *access->getElement(collection, currentItem));
    }
  }
};

template <typename TIterator>
void printCollection(TIterator begin, TIterator end)
{
  for (auto i = begin; i != end; i = std::next(i)) {
    std::cout << *i << " ";
  }
  std::cout << "\n";
};

int taskNum1(const char *direction);
int taskNum2(const char *fileName);
int taskNum3();
int taskNum4(const char *direction, const char *num);

#endif
