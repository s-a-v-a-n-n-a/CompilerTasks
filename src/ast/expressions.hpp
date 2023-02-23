#pragma once

#include <ast/syntax_tree.hpp>

#include <lex/token.hpp>

#include <vector>

//////////////////////////////////////////////////////////////////////

class Expression : public TreeNode {
 public:
  virtual void Accept(Visitor*) = 0;

  // Later

  // virtual types::Type* GetType() = 0;
};

//////////////////////////////////////////////////////////////////////

// Assignable entity

class LvalueExpression : public Expression {};

//////////////////////////////////////////////////////////////////////

class ComparisonExpression : public Expression {
 public:
  // Constructor
  ComparisonExpression(Expression *leftExpr, Expression *rightExpr, lex::Token comparator)
  : leftExpr_(leftExpr), rightExpr_(rightExpr), comparator_(comparator) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitComparisonExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return comparator_.getLocation();
  }

  // TODO: fields, helpers, etc...

  Expression *leftExpr_;
  Expression *rightExpr_;

  lex::Token comparator_;
};

//////////////////////////////////////////////////////////////////////

// Binary arithmetic: + - / *

class BinaryExpression : public Expression {
 public:
  BinaryExpression(Expression *leftExpr, Expression *rightExpr, lex::Token arithmetic)
  : leftExpr_(leftExpr), rightExpr_(rightExpr), arithmetic_(arithmetic) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitBinaryExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return arithmetic_.getLocation();
  }

  // TODO: fields, helpers, etc...

  Expression *leftExpr_;
  Expression *rightExpr_;

  lex::Token arithmetic_;
};

//////////////////////////////////////////////////////////////////////

class UnaryExpression : public Expression {
 public:
  // Constructor
  UnaryExpression(Expression *expr, lex::Token unary)
  : expr_(expr), unary_(unary) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitUnaryExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return unary_.getLocation();
  }

  Expression *expr_;

  lex::Token unary_;
};

//////////////////////////////////////////////////////////////////////

class FnCallExpression : public Expression {
 public:
  FnCallExpression(lex::Token *functionName, const std::vector<Expression*> &args)
  : functionName_(functionName), args_(args) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitFnCallExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return functionName_->getLocation();
  }

  lex::Token *functionName_;
  std::vector<Expression*> args_;
};

//////////////////////////////////////////////////////////////////////

class BlockExpression : public Expression {
 public:
  BlockExpression(lex::Token brace, const std::vector<Statement*> &body, Expression *result)
  : brace_(brace), body_(body), result_(result) {}

  virtual void Accept(Visitor *visitor) override {
    visitor->VisitBlockExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return brace_.getLocation();
  }

  lex::Token brace_ = {};
  std::vector<Statement*> body_;

  Expression *result_;
};

//////////////////////////////////////////////////////////////////////

class IfExpression : public Expression {
 public:
  IfExpression(Expression *condition, Expression *thenBranch, Expression *elseBranch)
  : condition_(condition), thenBranch_(thenBranch), elseBranch_(elseBranch) {}

  virtual void Accept(Visitor *visitor) override {
    visitor->VisitIfExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return condition_->GetLocation();
  }

  Expression *condition_;
  Expression *thenBranch_;
  Expression *elseBranch_;
};

//////////////////////////////////////////////////////////////////////

class LiteralExpression : public Expression {
 public:
  explicit LiteralExpression(lex::Token name)
  : literalName_(name) {}

  virtual void Accept(Visitor *visitor) override {
    visitor->VisitLiteralExpression(this);
  }

  virtual lex::Location GetLocation() override {
    literalName_->getLocation();
  }

  lex::Token literalName_;
};

//////////////////////////////////////////////////////////////////////

class VarAccessExpression : public LvalueExpression {
 public:
  explicit VarAccessExpression(lex::Token var) 
  : var_(var) {}

  virtual void Accept(Visitor* visitor) override {
    visitor->VisitVarAccessExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return var_.getLocation();
  }

  lex::Token var_;
};

//////////////////////////////////////////////////////////////////////

class ReturnExpression : public Expression {
 public:
  ReturnExpression(Expression *returnExpr)
  : returnExpression_(returnExpr) {}

  virtual void Accept(Visitor *visitor) override {
    visitor->VisitReturnExpression(this);
  }

  virtual lex::Location GetLocation() override {
    return returnExpression_->GetLocation();
  }

  Expression *returnExpression_;
};

//////////////////////////////////////////////////////////////////////
