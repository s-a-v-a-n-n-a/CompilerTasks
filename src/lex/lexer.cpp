#include <lex/lexer.hpp>

namespace lex {

Lexer::Lexer(std::istream& source) : scanner_{source}, expect_next_{true} {
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetNextToken() {
  SkipWhitespace();

  SkipComments();

  if (auto op = MatchOperators()) {
    return *op;
  }

  if (auto lit = MatchLiterals()) {
    return *lit;
  }

  if (auto word = MatchWords()) {
    return *word;
  }

  FMT_ASSERT(false, "Could not match any token\n");
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetPreviousToken() {
  return prev_;
}

////////////////////////////////////////////////////////////////////

void Lexer::Advance() {
  prev_ = peek_;

  if (expect_next_) {
    peek_ = GetNextToken();
    expect_next_ = false;
  } else {
    expect_next_ = true;
  }
}

////////////////////////////////////////////////////////////////////

bool Lexer::Matches(lex::TokenType tokenType) {
  if (Peek().type_ != tokenType) {
    std::cout << int(Peek().type_) << " " << int(tokenType) << "\n";
    return false;
  }

  Advance();

  return true;
}

////////////////////////////////////////////////////////////////////

Token Lexer::Peek() {
  if (expect_next_) {
    Advance();
  }

  return peek_;
}

////////////////////////////////////////////////////////////////////

bool IsWhitespace(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void Lexer::SkipWhitespace() {
  while (IsWhitespace(scanner_.getCurrentSymbol())) {
    scanner_.shift(1);
  }
}

////////////////////////////////////////////////////////////////////

void Lexer::SkipComments() {
  while (scanner_.getCurrentSymbol() == '#') {
    scanner_.skipRestLine();
    SkipWhitespace();
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchOperators() {
  auto matchResult = MatchOperator();
  if (matchResult.has_value()) {
    // std::cout << "HERE " << scanner_.getCurrentState() << "\n";
    scanner_.shift(1);
    
    return Token(
      table_.LookupWord(matchResult.value()),
      matchResult.value(),
      std::nullopt,
      scanner_.getCurrentState(),
      matchResult.value().size()
    );
  }

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<std::string> Lexer::MatchOperator() { // std::optional<TokenType>
  std::string result = "";
  
  char currentSymbol = scanner_.getCurrentSymbol();
  // std::cout << "cur symb = " << currentSymbol << ", " << int(currentSymbol) << "\n";
  switch (currentSymbol) {
    case '=':
      if (expectNextSymbol('=')) {
        scanner_.shift(1);

        return "==";
      } else {
        return result + currentSymbol;
      }
      break;
    case '!':
      if (expectNextSymbol('=')) {
        scanner_.shift(1);
        
        return "!="; // TokenType::NOT_EQ;
      } else {
        return result + currentSymbol; // TokenType::NOT;
      }
      break;
    case '<':
      return result + currentSymbol; // TokenType::LT;
    case '>':
      return result + currentSymbol; // TokenType::GT;
    case '+':
      return result + currentSymbol; // TokenType::PLUS;
    case '-':
      return result + currentSymbol; // TokenType::MINUS;
    case '*':
      return result + currentSymbol; // TokenType::STAR;
    case '/':
      return result + currentSymbol; // TokenType::DIV;
    case '(':
      return result + currentSymbol; // TokenType::LEFT_PAREN;
    case ')':
      return result + currentSymbol; // TokenType::RIGHT_PAREN;
    case '[':
      return result + currentSymbol; // TokenType::LEFT_BRACE;
    case ']':
      return result + currentSymbol; // TokenType::RIGHT_BRACE;
    case '{':
      return result + currentSymbol; // TokenType::LEFT_CBRACE;
    case '}':
      return result + currentSymbol; // TokenType::RIGHT_CBRACE;
    case ',':
      return result + currentSymbol; // TokenType::COMMA;
    case ':':
      return result + currentSymbol; // TokenType::COLON;
    case ';':
      return result + currentSymbol; // TokenType::SEMICOLUMN;
    case EOF:
      return "EOF";
    default:
      return std::nullopt;
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchLiterals() {
  auto numericLiteral = MatchNumericLiteral();
  if (numericLiteral.has_value()) {
    return numericLiteral;
  }

  auto charLiteral = MatchCharLiteral();
  if (charLiteral.has_value()) {
    return charLiteral;
  }

  auto stringLiteral = MatchStringLiteral();
  if (stringLiteral.has_value()) {
    return stringLiteral;
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchNumericLiteral() {
  double number = 0.0;
  ssize_t digitsAmount = 0;

  char currentSymbol = scanner_.getCurrentSymbol();
  // std::cout << "NUMBER HERE " << currentSymbol << "\n";

  while (isdigit(currentSymbol)) {
    number = number * 10 + currentSymbol - '0';

    scanner_.shift(1);
    currentSymbol = scanner_.getCurrentSymbol();

    ++digitsAmount;
  }

  // error, if dot is first
  if (expectSymbol('.')) {
    // scanner_.shift(1);

    // currentSymbol = scanner_.getCurrentSymbol();
    // ssize_t digitsAfterDotAmount = 1;
    
    // // error if dot is last
    // while (isdigit(currentSymbol)) {
    //   double currentAdding = (double)(currentSymbol - '0');

    //   for (int i = 0; i < digitsAfterDotAmount; ++i) {
    //     currentAdding /= 10;
    //   }

    //   number += currentAdding;

    //   scanner_.shift(1);

    //   currentSymbol = scanner_.getCurrentSymbol();
    //   ++digitsAfterDotAmount;
    // }
    std::string fraction = "0.";
    ssize_t digitsAfterDotAmount = 0;
    while (isdigit(currentSymbol)) {
      fraction += std::string(currentSymbol);

      scanner_.shift(1);

      currentSymbol = scanner_.getCurrentSymbol();
      ++digitsAfterDotAmount;
    }

    if (digitsAfterDotAmount > 0) {
      number += strtod(fraction);
    } // else error

    if (digitsAmount > 0) {
      return Token(
        TokenType::NUMBER,
        "",
        number,
        scanner_.getCurrentState(),
        digitsAmount + digitsAfterDotAmount + 1
      );
    } 
  }

  if (digitsAmount > 0) {
    return Token(
      TokenType::NUMBER,
      "",
      number,
      scanner_.getCurrentState(),
      digitsAmount
    );
  }

  // maybe distinct integers and doubles ?????????????????

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchCharLiteral() {
  std::string matchResult = "";
  
  if (!expectSymbol('\'')) {
    return std::nullopt;
  }

  matchResult.push_back('\'');
  scanner_.shift(1);

  if (!expectNextSymbol('\'')) {
    matchResult.push_back('\'');
    scanner_.shift(1);

  } else {
    matchResult.push_back(scanner_.getCurrentSymbol());
    scanner_.shift(1);

    if (expectSymbol('\'')) {
      matchResult.push_back('\'');
      scanner_.shift(1);
    } else {
      return std::nullopt;
    }
  }

  return Token(
    TokenType::TY_CHAR,
    "",
    matchResult,
    scanner_.getCurrentState(),
    matchResult.size()
  );
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchStringLiteral() {
  std::string matchResult = "";
  
  // std::cout << "TRYING TO READ STRING\n";
  
  if (!expectSymbol('\"')) {
    return std::nullopt;
  }

  // std::cout << "First SYMBOL OF STRING FOUND\n";

  matchResult.push_back('\"');
  scanner_.shift(1);

  char currentSymbol = scanner_.getCurrentSymbol();
  while (currentSymbol != '\"' && !scanner_.atEnd()) {
    matchResult.push_back(currentSymbol);
    scanner_.shift(1);

    currentSymbol = scanner_.getCurrentSymbol();
  }

  if (scanner_.atEnd()) {
    return std::nullopt; // React to error
  }

  matchResult.push_back('\"');
  scanner_.shift(1);

  return Token(
    TokenType::STRING,
    "",
    matchResult,
    scanner_.getCurrentState(),
    matchResult.size()
  );
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchWords() {
  std::string matchResult = "";
  
  char currentSymbol = scanner_.getCurrentSymbol();
  while (isalnum(currentSymbol) || currentSymbol == '_') {
    matchResult.push_back(currentSymbol);
    scanner_.shift(1);

    currentSymbol = scanner_.getCurrentSymbol();
  }

  if (matchResult.size() == 0) {
    return std::nullopt; // React that it is an error
  }

  if (table_.LookupWord(matchResult) == TokenType::IDENTIFIER) {
    return Token(
      TokenType::IDENTIFIER,
      "",
      matchResult,
      scanner_.getCurrentState(),
      matchResult.size()
    );
  }

  return Token(
    table_.LookupWord(matchResult),
    matchResult,
    "",
    scanner_.getCurrentState(),
    matchResult.size()
  );
}

////////////////////////////////////////////////////////////////////

bool Lexer::expectNextSymbol(char symbol) {
  if (scanner_.getNextSymbol() == symbol) {
    return true;
  }

  return false;
}

bool Lexer::expectSymbol(char symbol) {
  if (scanner_.getCurrentSymbol() == symbol) {
    return true;
  }

  return false;
}

}  // namespace lex
