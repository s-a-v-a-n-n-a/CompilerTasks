#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseExpression() {
  auto blockExprerssion = ParseBlockExpression();
  if (blockExprerssion) {
    return blockExprerssion;
  }
  
  return ParseComparison();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseKeywordExpresssion() {
  if (auto return_statement = ParseReturnStatement()) {
    return return_statement;
  }

  if (auto yield_statement = ParseYieldStatement()) {
    return yield_statement;
  }

  if (auto if_expr = ParseIfExpression()) {
    return if_expr;
  }

  if (auto match_expr = ParseMatchExpression()) {
    return match_expr;
  }

  if (auto new_expr = ParseNewExpression()) {
    return new_expr;
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseDeref() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseAddressof() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseIfExpression() {
  if (!Matches(lex::TokenType::IF)) {
    return nullptr;
  }

  auto ifToken = lexer_.GetPreviousToken();
  auto condition = ParseExpression();

  if (!condition) {
    throw parse::errors::ParseTrueBlockError{ifToken.getLocation().Format()};
  }

  Consume(lex::TokenType::THEN);

  auto thenToken = lexer_.GetPreviousToken();
  auto thenBranch = ParseExpression();

  if (!thenBranch) {
    throw parse::errors::ParseTrueBlockError{ifToken.getLocation().Format()};
  }

  Expression *elseBranch = nullptr;
  
  if (Matches(lex::TokenType::ELSE)) {
    elseBranch = ParseExpression();
  }

  return new IfExpression(ifToken, condition, thenToken, thenBranch, elseBranch);
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseMatchExpression() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseNewExpression() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBlockExpression() {
  if (!Matches(lex::TokenType::LEFT_CBRACE)) {
    return nullptr;
  }

  auto location_token = lexer_.GetPreviousToken();

  std::vector<Statement*> body;
  Expression *lastExpression = nullptr;

  while (!Matches(lex::TokenType::BLETERN)) {
    auto declaration = ParseDeclaration();
    if (declaration) {
      body.push_back(declaration);
    } else {
      auto statement = ParseStatement();
      if (statement) {
        body.push_back(statement);
      }
    }
  }

  Expression *result = ParseExpression();

  return new BlockExpression(location_token, std::move(body), result);
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseComparison() {
  auto leftExpression = ParseBinary();
  
  auto comparisonToken = lexer_.Peek();

  if (MatchesComparisonSign(comparisonToken.getType()) 
  || Matches(lex::TokenType::EQUALS) 
  || Matches(lex::TokenType::NOT_EQ)) {
    auto rightExpression = ParseBinary();
    return new ComparisonExpression(leftExpression, rightExpression, comparisonToken);
  }

  return leftExpression;
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseBinary() {
  auto leftExpression = ParseUnary();

  auto arithmetic = lexer_.Peek();
  if (Matches(lex::TokenType::PLUS)
  || Matches(lex::TokenType::MINUS)
  || Matches(lex::TokenType::MUL)
  || Matches(lex::TokenType::DIV)) {
    auto rightExpression = ParseUnary();

    return new BinaryExpression(leftExpression, rightExpression, arithmetic);
  }

  return leftExpression;
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseUnary() {
  auto token = lexer_.Peek();

  if (Matches(lex::TokenType::MINUS) || Matches(lex::TokenType::NOT)) {
    auto expression = ParseUnary();
    
    return new UnaryExpression(expression, token);
  }

  return ParsePostfixExpressions();
}

///////////////////////////////////////////////////////////////////

// Assume lex::TokenType::ARROW has already been parsed
Expression* Parser::ParseIndirectFieldAccess(Expression* expr) {
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseFieldAccess(Expression* expr) {
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseIndexingExpression(Expression* expr) {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseFnCallExpression(Expression* expr, lex::Token id) {
  // Consume(lex::TokenType::LEFT_PAREN);

  if (Matches(lex::TokenType::RIGHT_PAREN)) {
    return new FnCallExpression(id, expr, {});
  }

  auto args = ParseCSV();

  Consume(lex::TokenType::RIGHT_PAREN);
  return new FnCallExpression(id, expr, std::move(args));
}

////////////////////////////////////////////////////////////////////

auto Parser::ParseCSV() -> std::vector<Expression*> {
  auto expression = ParseExpression();
  std::vector<Expression*> parameters = std::vector<Expression*>();

  while(expression && Matches(lex::TokenType::COMMA)) {
    parameters.push_back(expression);

    expression = ParseExpression();
  }

  return parameters;
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseFnCallUnnamed(Expression* expr) {
  std::abort();
}

////////////////////////////////////////////////////////////////////

// !!!!!!!!!! Not understandable
Expression* Parser::ParsePostfixExpressions() {
  auto primary = ParsePrimary();

  while (Matches(lex::TokenType::LEFT_BRACE)) {
    auto brace = lexer_.GetPreviousToken();

    auto parameter = ParseExpression();

    std::vector<Expression*> arguments = std::vector<Expression*>();
    while (parameter) {
      arguments.push_back(parameter);
      parameter = ParseExpression();
    }

    primary = new FnCallExpression(
      primary,
      arguments
    );

    Consume(lex::TokenType::RIGHT_BRACE);
  }

  return primary;
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParsePrimary() {
  // Try parsing grouping first

  if (Matches(lex::TokenType::LEFT_BRACE)) {
    auto expression = ParseExpression();
    Consume(lex::TokenType::RIGHT_BRACE);

    return expression;
  }

  // Then keyword expressions

  auto keywordExpression = ParseKeywordExpresssion();
  if (keywordExpression) {
    return keywordExpression;
  }

  // Then all the base cases: IDENT, INT, TRUE, FALSE, ETC...

  auto token = lexer_.Peek();
  switch (token.getType()) {
    case lex::TokenType::IDENTIFIER:
    case lex::TokenType::STRING:
    case lex::TokenType::NUMBER:
    case lex::TokenType::TRUE:
    case lex::TokenType::FALSE:
      lexer_.Advance();
      return new LiteralExpression(token);
    default:
      throw parse::errors::ParsePrimaryError(token.location.Format());
  }

  FMT_ASSERT(false, "Unreachable!");
}

////////////////////////////////////////////////////////////////////

// var t = {.field = 3, .bar = true,};
Expression* Parser::ParseCompoundInitializer(lex::Token curly) {
  std::abort();
}

// Short-hand notation: .<Tag> <Expr>
// e.g: `.some 5` which is the same as `{ .some = 5 }`
Expression* Parser::ParseSignleFieldCompound() {
  std::abort();
}

////////////////////////////////////////////////////////////////////

Expression* Parser::ParseReturnStatement() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Expression* Parser::ParseYieldStatement() {
  std::abort();
}

///////////////////////////////////////////////////////////////////
