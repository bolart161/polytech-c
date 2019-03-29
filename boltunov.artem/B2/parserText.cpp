#include "parserText.hpp"

ParserText::ParserText(const SymbolsReader& symbolsReader, const size_t& buffSize):
    buffer_(),
    currentChar_(' '),
    bufferMaxSize_(buffSize),
    symbolsReader_(symbolsReader)
{
  buffer_.reserve(buffSize);
}

void ParserText::printText() const
{
  if (!buffer_.empty()) {
    std::cout << buffer_ <<"\n";
  }
}

void ParserText::parse()
{
  std::string tmpStr;
  tmpStr.reserve(26);

  while (std::cin.get(currentChar_)) {

    token_t token = getToken(currentChar_);

    switch (token.type) {
      case token_t::WHITESPACE:
      {
        continue;
      }
      case token_t::NUMBER:
      {
        tmpStr.push_back(currentChar_);
        symbolsReader_.readNum(tmpStr, currentChar_);
        break;
      }
      case token_t::WORD:
      {
        tmpStr.push_back(currentChar_);
        symbolsReader_.readWord(tmpStr, currentChar_);
        break;
      }
      case token_t::PUNCTUATION:
      {
        throw std::invalid_argument("Wrong punctuation;");
      }
    }

    if (bufferMaxSize_ - buffer_.size() <= tmpStr.size()) {
      std::cout << buffer_ << "\n";
      buffer_.clear();
    } else if ((buffer_.size() + tmpStr.size() < bufferMaxSize_ + 1) && !(buffer_.empty())) {
      buffer_.push_back(' ');
    }

    buffer_ += tmpStr;
    tmpStr.clear();
  }
}

token_t ParserText::getToken(char ch) {
  if (isSpace(ch)) {
    return token_t{token_t::WHITESPACE};
  } else if (isDigit(ch) || ch == '+' || ch == '-') {
    return token_t{token_t::NUMBER};
  } else if (isLetter(ch)) {
    return token_t{token_t::WORD};
  } else if (isPunctuation(ch)) {
    return token_t{token_t::PUNCTUATION};
  } else {
    return token_t{};
  }
}
