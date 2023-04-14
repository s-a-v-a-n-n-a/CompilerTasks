#include <parse/parser.hpp>
#include <parse/parse_error.hpp>

///////////////////////////////////////////////////////////////////

FunDeclaration* Parser::ParseFunDeclarationStandalone() {
  std::abort();
}

///////////////////////////////////////////////////////////////////

Declaration* Parser::ParseDeclaration() {
  if (auto var_declaration = ParseVarDeclStatement()) {
    return var_declaration;
  }

  if (auto fun_declaration = ParseFunDeclStatement()) {
    return fun_declaration;
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////

FunDeclaration* Parser::ParseFunDeclStatement() {
  if (!Matches(lex::TokenType::FUN)) {
    return nullptr;
  }

  auto name = lexer_.Peek();
  Consume(lex::TokenType::LEFT_CBRACE);
  auto args = ParseFormals();
  Consume(lex::TokenType::RIGHT_CBRACE);

  Consume(lex::TokenType::ASSIGN);
  Expression* body = ParseExpression();
  Consume(lex::TokenType::SEMICOLUMN);

  return new FunDeclaration(name, std::move(args), body);
}

///////////////////////////////////////////////////////////////////

auto Parser::ParseFormals() -> std::vector<lex::Token> {
  auto parameter = lexer_.Peek();
  std::vector<lex::Token> parameters = std::vector<lex::Token>();

  while (parameter.getType() == lex::TokenType::IDENTIFIER) {
    parameters.push_back(parameter);

    if (!Matches(lex::TokenType::COMMA)) {
      break;
    }

    parameter = lexer_.Peek();
  }

  return parameters;
}

///////////////////////////////////////////////////////////////////

VarDeclaration* Parser::ParseVarDeclStatement() {
  if (!Matches(lex::TokenType::VAR)) {
    return nullptr;
  }
  
  Consume(lex::TokenType::IDENTIFIER);
  auto name = lexer_.GetPreviousToken();
  Consume(lex::TokenType::ASSIGN);

  auto assign = lexer_.GetPreviousToken();

  auto expression = ParseExpression();

  if (!expression) {
    throw new parse::errors::ParseNonLvalueError(assign.getLocation().Format());
  }

  Consume(lex::TokenType::SEMICOLUMN);

  return new VarDeclaration(name, expression);
}

///////////////////////////////////////////////////////////////////
