#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include "QueueWithPriority.hpp"


void add(std::stringstream & istream, QueueWithPriority<std::string> & queue, std::ostream & ostream);
void get(QueueWithPriority<std::string> & queue, std::ostream & ostream);
void accelerate(QueueWithPriority<std::string> & queue);

#endif
