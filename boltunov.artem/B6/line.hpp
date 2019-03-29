#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include <algorithm>

class Line : public std::string
{
  friend std::istream & operator>>(std::istream & in, Line & line);
};

std::istream & operator>>(std::istream & in, Line & line);

#endif //LINE_HPP
