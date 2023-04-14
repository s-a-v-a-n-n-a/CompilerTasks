#pragma once

#include <ast/visitors/visitor.hpp>
#include <ast/syntax_tree.hpp>
#include <ast/statements.hpp>
#include <ast/expressions.hpp>
#include <ast/declarations.hpp>

#include <cstdlib>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////

class PrintVisitor : public Visitor {
private:
    size_t tabs = 0;

    void indent() const {
        for (ssize_t i = 0; i < tabs; ++i) {
            fmt::print(" ");    
        }
    }

public:
    virtual void VisitVarAccessExpression(VarAccessExpression *expr) override {
        indent();

        fmt::print("{}\n", expr->var_.getName());
    }

    void VisitComparisonExpression(ComparisonExpression *expr) override {
        indent();

        fmt::print("{}\n", lex::FormatTokenType(expr->comparator_.type_));
        fmt::print("Left:\n");
        
        ++tabs;
        expr->leftExpr_->Accept(this);
        --tabs;

        indent();
        
        fmt::print("Right:\n");
        
        ++tabs;
        expr->rightExpr_->Accept(this);
        --tabs;
    }

  
    virtual void VisitBinaryExpression(BinaryExpression *expr) override {
        indent();
        
        fmt::print("{}\n", lex::FormatTokenType(expr->arithmetic_.type_));
        fmt::print("Left:\n");
        
        ++tabs;
        expr->leftExpr_->Accept(this);
        --tabs;

        indent();

        fmt::print("Right:\n");
        
        ++tabs;
        expr->rightExpr_->Accept(this);
        --tabs;
    }

    virtual void VisitBlockExpression(BlockExpression *expr) override {
        indent();
        fmt::print("{\n");

        ++tabs;
        for (Statement *child : expr->body_) {
            child->Accept(this);
        }
        --tabs;

        indent();
        fmt::print("}\n");
    }
  
    virtual void VisitUnaryExpression(UnaryExpression *expr) override {
        indent();
        fmt::print("{}\n", expr->unary_);

        ++tabs;
        expr->expr_->Accept(this);
        --tabs;
    }

    virtual void VisitFnCallExpression(FnCallExpression *expr) override {
        indent();
        fmt::print("Call {}(\n", expr->functionName_->getName());

        ++tabs;
        for (Expression *arg : expr->args_) {
            arg->Accept(this);
        }
        --tabs;

        indent();
        fmt::print(");\n");
    }

    virtual void VisitIfExpression(IfExpression *expr) override {
        indent();
        fmt::print("If:\ncondition:\n");
        
        ++tabs;
        expr->condition_->Accept(this);
        --tabs;
        
        indent();
        fmt::print("Then:\n");
        
        ++tabs;
        expr->thenBranch_->Accept(this);
        --tabs;

        indent();
        fmt::print("Else:\n");

        ++tabs;
        expr->elseBranch_->Accept(this);
        --tabs;
    }

    virtual void VisitLiteralExpression(LiteralExpression *expr) override {
        indent();

        fmt::print("{}\n", expr->literalName_.getNumber());
    }
    
    virtual void VisitVarAccessExpression(VarAccessExpression *expr) override {
        indent();
        fmt::print("{}\n", expr->var_.getName());
    }
    
    virtual void VisitReturnExpression(ReturnExpression *expr) override {
        indent();
        fmt::print("Return:\n");

        ++tabs;
        expr->returnExpression_->Accept(this);
        --tabs;
    }

    virtual void VisitVarDeclaration(VarDeclaration *expr) override {
        indent();
        fmt::print("{}\n", expr->GetName());

        ++tabs;
        expr->lvalue_->Accept(this);
        --tabs;
    }

    virtual void VisitFunDeclaration(FunDeclaration *expr) override {
        indent();
        fmt::print("{}\n", expr->GetName());
        fmt::print("(");

        for (auto parameter : expr->parameters_) {
            fmt::print("{}\n", parameter.getName());
        }

        fmt::print(")");
    } 
 };

//////////////////////////////////////////////////////////////////////