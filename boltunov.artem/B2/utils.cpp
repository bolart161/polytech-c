#include "utils.hpp"

bool isLetter(const char& ch)
{
  return std::isalpha(ch, std::cin.getloc());
}

bool isPunctuation(const char& ch)
{
  return std::ispunct(ch, std::cin.getloc());
}

bool isDigit(const char& ch)
{
  return std::isdigit(ch, std::cin.getloc());
}

bool isSpace(const char& ch)
{
  return std::isspace(ch, std::cin.getloc());
}
