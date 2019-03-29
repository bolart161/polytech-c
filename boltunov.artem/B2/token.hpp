#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

struct token_t
{
  enum token_type
  {
    WORD,
    NUMBER,
    PUNCTUATION,
    WHITESPACE
  };

  token_type type;
};

#endif // TOKEN_HPP
