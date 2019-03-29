#ifndef TASK2_HPP
#define TASK2_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <list>
#include <memory>
#include <sstream>
#include "shape.hpp"
#include "figures.hpp"

void task2();
Point readPoint(std::istringstream & iss, const size_t & lineWidth);
std::shared_ptr<Shape> createShape(const std::string & figureName, const Point & point);
bool hasData(const std::string & line);
std::string readShapeName(std::istringstream & iss);

template <typename TIterator>
void printList(TIterator begin, TIterator end, const std::string & header)
{
  std::cout << header << ":\n";
  std::for_each(begin, end, std::bind(&Shape::draw, std::placeholders::_1, std::ref(std::cout)));
}

#endif //TASK2_HPP
