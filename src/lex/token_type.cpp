#include <lex/token_type.hpp>

namespace lex {

#define AST_NODE_LIST(code) \
  code(NUMBER)              \
  code(STRING)              \
  code(IDENTIFIER)          \
  code(TRUE)                \
  code(FALSE)               \
  code(PLUS)                \
  code(MINUS)               \
  code(MUL)                 \
  code(DIV)                 \
  code(ASSIGN)              \
  code(EQUALS)              \
  code(NOT_EQ)              \
  code(LT)                  \
  code(GT)                  \
  code(LEFT_PAREN)          \
  code(RIGHT_PAREN)         \
  code(LEFT_CBRACE)         \
  code(RIGHT_CBRACE)        \
  code(NOT)                 \
  code(FUN)                 \
  code(COMMA)               \
  code(VAR)                 \
  code(FOR)                 \
  code(TY_INT)              \
  code(TY_BOOL)             \
  code(TY_CHAR)             \
  code(TY_UNIT)             \
  code(TY_STRING)           \
  code(IF)                  \
  code(THEN)                \
  code(ELSE)                \
  code(COLON)               \
  code(SEMICOLUMN)          \
  code(RETURN)              \
  code(YIELD)               \
  code(TOKEN_EOF)           \
  code(STAR)                \
  code(ARROW)               \
  code(BLETERNs)

////////////////////////////////////////////////////////////////

#define DEFINE_TYPE_STRING(type) \
  case TokenType::type:          \
    return #type;

////////////////////////////////////////////////////////////////

const char* FormatTokenType(TokenType type) {
  switch (type) {
    AST_NODE_LIST(DEFINE_TYPE_STRING)
    default:
      break;
  }
  std::abort();
}

#undef DEFINE_TYPE_STRING

////////////////////////////////////////////////////////////////

}  // namespace lex
