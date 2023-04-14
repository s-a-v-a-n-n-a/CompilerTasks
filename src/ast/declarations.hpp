#pragma once

#include <ast/statements.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Declaration : public Statement {
 public:
  virtual void Accept(Visitor* /*visitor*/) {}

  virtual std::string GetName() = 0;
};

//////////////////////////////////////////////////////////////////////

// Объявление переменной
class VarDeclaration : public Declaration {
 public:
  VarDeclaration(lex::Token name, Expression* lvalue)
      : name_(name), lvalue_(lvalue) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarDeclaration(this);
  }

  virtual lex::Location GetLocation() override {
    return lvalue_->GetLocation();
  }

  std::string GetName() override {
    return name_.getName();
  }
  
  lex::Token name_;
  Expression* lvalue_;

  ast::scope::Context *layer_ = nullptr;
};

//////////////////////////////////////////////////////////////////////

// Объявление функции
class FunDeclaration : public Declaration {
  public:
  FunDeclaration(lex::Token name, std::vector<lex::Token> parameters, Expression* body)
      : name_(name), parameters_(std::move(parameters)), body_(body) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitFunDeclaration(this);
  }

  virtual lex::Location GetLocation() override {
    return name_.getLocation();
  }

  std::string GetName() override {
    return name_.getName();
  }

  lex::Token name_;
  std::vector<lex::Token> parameters_;
  Expression* body_;

  ast::scope::Context* layer_ = nullptr;
};

//////////////////////////////////////////////////////////////////////
