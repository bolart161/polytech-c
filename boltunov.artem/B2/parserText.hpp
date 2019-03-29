#ifndef PARSERTEXT_HPP
#define PARSERTEXT_HPP

#include <iostream>
#include <string>

#include "utils.hpp"
#include "symbolsReader.hpp"
#include "token.hpp"

class ParserText{
public:
  explicit ParserText(const SymbolsReader& symbolsReader, const size_t& buffSize = 40);
  void printText() const;
  void parse();
  token_t getToken(char ch);

private:
  std::string buffer_;
  char currentChar_;
  size_t bufferMaxSize_;
  SymbolsReader symbolsReader_;
};

#endif //PARSERTEXT_HPP
