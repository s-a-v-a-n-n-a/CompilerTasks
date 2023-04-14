#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

/*
<statement> ::= <expression-statement>
              | <assignment-statement>

<expression-statement> ::= <expression> ;

<assignment-statement> ::= <unary-expression> = <expression>
*/

///////////////////////////////////////////////////////////////////

Statement* Parser::ParseStatement() {
  Statement* exprStatement = ParseExprStatement();

  if (exprStatement) {
    return exprStatement;
  } else {
    AssignmentStatement* assignment = ParseAssignmentStmt();

    if (assignment) {
      return assignment;
    }
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////

Statement* Parser::ParseExprStatement() {
  Expression* expression = ParseExpression();

  // after all expressions goes ';'
  Consume(lex::TokenType::SEMICOLUMN);

  return new ExprStatement(expression);
}

AssignmentStatement* Parser::ParseAssignmentStmt() { // LvalueExpression* target
  Expression* expression = ParseExpression();

  Consume(lex::TokenType::ASSIGN);

  auto leftPart = expression->as<LvalueExpression>();
  if (leftPart) {
    auto assignment = new lex::Token(lexer_.GetPreviousToken());
    auto rightPart = ParseExpression();

    return new AssignmentStatement(leftPart, rightPart, assignment);
  }

  throw parse::errors::ParseNonLvalueError{FormatLocation()};
}