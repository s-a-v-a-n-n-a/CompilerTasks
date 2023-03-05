#pragma once

#include <cstdlib>

namespace lex {

//////////////////////////////////////////////////////////////////////

enum class TokenType {
  NUMBER,
  STRING,
  IDENTIFIER,

  TY_INT,
  TY_BOOL,
  TY_CHAR,
  TY_UNIT,
  TY_STRING,

  TRUE,
  FALSE,

  PLUS,
  MINUS,
  MUL,
  DIV,

  ASSIGN,
  EQUALS,
  NOT_EQ,
  NOT,
  LT,
  GT,

  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_CBRACE,
  RIGHT_CBRACE,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  COLON,
  SEMICOLUMN,

  FUN,
  VAR,

  FOR,
  IF,
  THEN,
  ELSE,

  YIELD,
  RETURN,

  TOKEN_EOF,

  STAR,
  ARROW,

  BLETERN,

  NONE
};

// extern const std::string TOKEN_NAMES[];

////////////////////////////////////////////////////////////////

const char* FormatTokenType(TokenType type);

////////////////////////////////////////////////////////////////

}  // namespace lex
