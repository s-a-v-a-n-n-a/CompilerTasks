#pragma once

#include <ast/visitors/visitor.hpp>
#include <ast/syntax_tree.hpp>
#include <ast/statements.hpp>
#include <ast/expressions.hpp>
#include <ast/declarations.hpp>

#include "ast/symbol/scope/context.hpp"

#include <cstdlib>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////

class SymbolTableBuilder : public Visitor {
  private:
    Context *currentContext_;
    std::string currentFunction_;

    void setNewContext(lex::Location location, std::string name) {
        Context *newContext = currentContext_->createChild(location, name);
        currentContext_ = newContext;
    }

    void returnToLastContext() {
        currentContext_ = currentContext_->getParent();
    }
  
  public:
    SymbolTableBuilder() {
        currentContext_ = nullptr;
    }

    virtual void VisitVarAccessExpression(VarAccessExpression *expr) override {
        expr->layer_ = currentContext_;
    }

    void VisitComparisonExpression(ComparisonExpression *expr) override {
        expr->leftExpr_->Accept(this);
        expr->rightExpr_->Accept(this);
    }

  
    virtual void VisitBinaryExpression(BinaryExpression *expr) override {
        expr->leftExpr_->Accept(this);
        expr->rightExpr_->Accept(this);
    }

    virtual void VisitBlockExpression(BlockExpression *expr) override {
        expr->scope = currentContext_.getScope();
        setNewContext(expr->getLocation(), "Block scope");

        for (auto stmt : expr->stmts_) {
          stmt->Accept(this);
        }

        if (expr->result_) {
          expr->result_->Accept(this);
        }

        returnToLastContext();
    }
  
    virtual void VisitUnaryExpression(UnaryExpression *expr) override {
        expr->expr_->Accept(this);
    }

    virtual void VisitFnCallExpression(FnCallExpression *expr) override {
        expr->layer_ = currentContext_;
        expr->callable_->Accept(this);

        for (auto argument : expr->args_) {
          argument->Accept(this);
        }
    }

    virtual void VisitIfExpression(IfExpression *expr) override {
        expr->condition_->Accept(this);

        expr->thenBranch_->Accept(this);
        expr->elseBranch_->Accept(this);
    }

    virtual void VisitLiteralExpression(LiteralExpression *expr) override {
        
    }
    
    virtual void VisitReturnExpression(ReturnExpression *expr) override {
        expr->returnFrom = currentFunction_;
        expr->layer_ = currentContext_;
        expr->returnExpression_->Accept(this);
    }

    virtual void VisitVarDeclaration(VarDeclaration *expr) override {
      if (expr->lvalue_) {
        expr->lvalue_->Accept(this);
      }

      expr->layer_ = currentContext_;

      currentContext_->addSymbol(Symbol(
        expr->GetName(), SymbolType::VAR, expr->GetLocation()
      ));
    }

    virtual void VisitFunDeclaration(FunDeclaration *expr) override {
      expr->layer_ = currentContext_;

      currentContext_->addSymbol(Symbol(
        expr->GetName(), SymbolType::FUN, expr->GetLocation(),
      ));

      if (expr->body_) {
        auto symbol = currentContext_->getScope()->getSymbolByName(node->GetName());

        currentContext_ = currentContext_->createChild(
          expr->body_->GetLocation(), expr->GetName()
        );

        expr->layer_ = currentContext_;

        // Bring parameters into the scope (their very special one)

        for (auto parameter : expr->parameters_) {
          currentContext_->addSymbol(Symbol(
              parameter.getName(), SymbolType::VAR, parameter.getLocation(),
          ));
        }

        auto fn = currentFunction_;
        currentFunction_ = expr->GetName();
        expr->body_->Accept(this);
        currentFunction_ = fn;

        returnToLastContext();
      }  
    } 
};