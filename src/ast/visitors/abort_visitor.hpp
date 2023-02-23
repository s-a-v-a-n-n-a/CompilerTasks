#pragma once

#include <ast/visitors/visitor.hpp>

#include <cstdlib>

//////////////////////////////////////////////////////////////////////

class AbortVisitor : public Visitor {
    virtual void VisitComparisonExpression(ComparisonExpression *node) override { std::abort(); }
    virtual void VisitBinaryExpression(BinaryExpression *node) override { std::abort(); }
    virtual void VisitUnaryExpression(UnaryExpression *node) override { std::abort(); }
    virtual void VisitDereferenceExpression(DereferenceExpression *node) override { std::abort(); }
    virtual void VisitAddressofExpression(AddressofExpression *node) override { std::abort(); }
    virtual void VisitIfExpression(IfExpression *node) override { std::abort(); }
    virtual void VisitMatchExpression(MatchExpression *node) override { std::abort(); }
    virtual void VisitNewExpression(NewExpression *node) override { std::abort(); }
    virtual void VisitBlockExpression(BlockExpression *node) override { std::abort(); }

    virtual void VisitFnCallExpression(FnCallExpression *node) override { std::abort(); }
    virtual void VisitIntrinsicCall(IntrinsicCall *node) override { std::abort(); }
    virtual void VisitCompoundInitializerExpr(CompoundInitializerExpr *node) override { std::abort(); }
    virtual void VisitFieldAccessExpression(FieldAccessExpression *node) override { std::abort(); }
    virtual void VisitLiteralExpression(LiteralExpression *node) override { std::abort(); }
    virtual void VisitVarAccessExpression(VarAccessExpression *node) override { std::abort(); }
    virtual void VisitTypecastExpression(TypecastExpression *node) override { std::abort(); }
    virtual void VisitYieldExpression(YieldExpression *node) override { std::abort(); }
    virtual void VisitReturnExpression(ReturnExpression *node) override { std::abort(); }

    // Statements

    virtual void VisitExprStatement(ExprStatement *node) override { std::abort(); }
    virtual void VisitAssignmentStatement(AssignmentStatement *node) override { std::abort(); }

    // Declarations

    virtual void VisitVarDeclaration(VarDeclaration *node) override { std::abort(); }
    virtual void VisitFunDeclaration(FunDeclaration *node) override { std::abort(); }
    virtual void VisitTypeDeclaration(TypeDeclaration *node) override { std::abort(); }
    virtual void VisitImplDeclaration(ImplDeclaration *node) override { std::abort(); }
    virtual void VisitTraitDeclaration(TraitDeclaration *node) override { std::abort(); }

    // Patterns

    virtual void VisitBindingPattern(BindingPattern *ndoe) override { std::abort(); }
    virtual void VisitLiteralPattern(LiteralPattern *ndoe) override { std::abort(); }
    virtual void VisitStructPattern(StructPattern *ndoe) override { std::abort(); }
    virtual void VisitVariantPattern(VariantPattern *ndoe) override { std::abort(); }
    virtual void VisitDiscardingPattern(DiscardingPattern *ndoe) override { std::abort(); }
};

//////////////////////////////////////////////////////////////////////
