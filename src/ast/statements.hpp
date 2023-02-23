#pragma once

#include <ast/syntax_tree.hpp>
#include <ast/expressions.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Statement : public TreeNode {
 public:
  virtual void Accept(Visitor* /* visitor */){};
};

//////////////////////////////////////////////////////////////////////

class ExprStatement : public Statement {
 public:
  ExprStatement(Expression* expr) : expr_{expr} {
  }

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitExprStatement(this);
  }

  virtual lex::Location GetLocation() override {
    return expr_->GetLocation();
  }

  Expression* expr_;
};

//////////////////////////////////////////////////////////////////////

class AssignmentStatement : public Statement {
 public:
  AssignmentStatement(LvalueExpression *lvalue, Expression *expr, lex::Token *assignment)
  : lvalue_(lvalue), expr_(expr), assign_token_(assignment) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitAssignmentStatement(this);
  }

  virtual lex::Location GetLocation() override {
    return assign_token_->getLocation();
  }

  LvalueExpression *lvalue_;
  Expression *expr_;

  lex::Token *assign_token_;
};

//////////////////////////////////////////////////////////////////////
