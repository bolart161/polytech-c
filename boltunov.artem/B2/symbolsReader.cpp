#include "symbolsReader.hpp"

void SymbolsReader::readNum(std::string& tmpStr, char &currentChar) const
{
  size_t counter = 1;
  char decimalPoint = std::use_facet<std::numpunct<char>>(std::cin.getloc()).decimal_point();

  while (std::cin.get(currentChar)) {

    if (!isDigit(currentChar)) {

      if ((tmpStr == "-") || (tmpStr == "+")) {
        throw std::invalid_argument("Wrong input data;");
      }

      if (isSpace(currentChar)) {
        skipWs(currentChar);
      } else if (currentChar == decimalPoint) {
        if (tmpStr.find(decimalPoint) == tmpStr.npos) {
          ++counter;
          tmpStr.push_back(currentChar);
          continue;
        }
      }

      if (isPunctuation(currentChar)) {
        if (tmpStr.back() == decimalPoint) {
          throw std::invalid_argument("Wrong input data;");
        }

        switch (currentChar) {
          case '+':
            break;
          case ',':
            tmpStr.push_back(currentChar);
            std::cin.get(currentChar);
            skipWs(currentChar);
            if (currentChar != '-') {
              break;
            }
          case '-':
          {
            char nextChar = std::cin.peek();
            if (nextChar == '-') {
              readDash(tmpStr, currentChar);
              return;
            } else {
              break;
            }
          }
          default:
            tmpStr.push_back(currentChar);
            return;
        }
      }
      std::cin.unget();
      return;
    }

    if (++counter > 20) {
      throw std::invalid_argument("Reached the maximum length of the number;");
    }
    tmpStr.push_back(currentChar);
  }
  if ((tmpStr == "-") || (tmpStr == "+")) {
    throw std::invalid_argument("Wrong input data;");
  }
}

void SymbolsReader::readWord(std::string& tmpStr, char &currentChar) const
{
  size_t counter = 1;

  while (std::cin.get(currentChar)) {

    if (!isLetter(currentChar)) {

      if (currentChar == '-') {
        if (tmpStr.back() == '-') {
          readDash(tmpStr, currentChar);
          return;
        } else {
          ++counter;
          tmpStr.push_back(currentChar);
          continue;
        }
      }

      if (isSpace(currentChar)) {
        skipWs(currentChar);
        if (currentChar == '-') {
          readDash(tmpStr, currentChar);
          return;
        }
      }

      if (isPunctuation(currentChar)) {
        tmpStr.push_back(currentChar);
        if (currentChar == ',') {
          std::cin.get(currentChar);
          skipWs(currentChar);
          if (currentChar == '-') {
            readDash(tmpStr, currentChar);
            return;
          }
        } else {
          return;
        }
      }

      std::cin.unget();
      return;
    }

    if (++counter > 20) {
      throw std::invalid_argument("Reached the maximum length of the word;");
    }
    tmpStr.push_back(currentChar);
  }
}

void SymbolsReader::readDash(std::string &tmpStr, char &currentChar) const
{
  std::string dash(1, '-');
  dash.reserve(4);

  if (tmpStr.back() == '-') {
    dash.push_back('-');
  }

  for (int i = 0; (i < 2) && (std::cin); ++i) {
    std::cin.get(currentChar);
    dash.push_back(currentChar);
  }

  if (dash.back() != '-') {
    std::cin.unget();
    dash.pop_back();
  }

  if (dash == "---") {
    if (tmpStr.back() == '-') {
      tmpStr.back() = ' ';
      tmpStr.append("---");
      return;
    } else {
      tmpStr.append(" ---");
      return;
    }
  } else if (dash == "----") {
    tmpStr.append(" ---");
    return;
  }
  throw std::invalid_argument("Invalid dash;");
}

void SymbolsReader::skipWs(char &currentChar) const
{
  while (isSpace(currentChar) && !(std::cin.eof())) {
    std::cin.get(currentChar);
  }
}
