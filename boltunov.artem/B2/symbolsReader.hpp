#ifndef SYMBOLSREADER_HPP
#define SYMBOLSREADER_HPP

#include <iostream>
#include <string>

#include "utils.hpp"

class SymbolsReader{
public:
  void readNum(std::string &tmpString, char &currentChar) const;
  void readWord(std::string &tmpString, char &currentChar) const;
  void readDash(std::string &tmpString, char &currentChar) const;
  void skipWs(char &currentChar) const;
};

#endif //SYMBOLSREADER_HPP
