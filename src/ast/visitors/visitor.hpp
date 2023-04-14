#pragma once

//////////////////////////////////////////////////////////////////////

class Expression;
class ComparisonExpression;
class BinaryExpression;
class UnaryExpression;
class DereferenceExpression;
class AddressofExpression;
class IfExpression;
class MatchExpression;
class NewExpression;
class BlockExpression;
class FnCallExpression;
class IntrinsicCall;
class CompoundInitializerExpr;
class FieldAccessExpression;
class LiteralExpression;
class VarAccessExpression;
class TypecastExpression;
class YieldExpression;
class ReturnExpression;

//////////////////////////////////////////////////////////////////////

class Statement;
class ExprStatement;
class AssignmentStatement;

//////////////////////////////////////////////////////////////////////

class VarDeclaration;
class FunDeclaration;
class TypeDeclaration;
class ImplDeclaration;
class TraitDeclaration;

//////////////////////////////////////////////////////////////////////

class BindingPattern;
class LiteralPattern;
class StructPattern;
class VariantPattern;
class DiscardingPattern;

//////////////////////////////////////////////////////////////////////

class Visitor {
 public:
  virtual ~Visitor() = default;

  // Expressions

  virtual void VisitComparisonExpression(ComparisonExpression *node) = 0;
  virtual void VisitBinaryExpression(BinaryExpression *node) = 0;
  virtual void VisitUnaryExpression(UnaryExpression *node) = 0;
  virtual void VisitDereferenceExpression(DereferenceExpression *node) = 0;
  virtual void VisitAddressofExpression(AddressofExpression *node) = 0;
  virtual void VisitIfExpression(IfExpression *node) = 0;
  virtual void VisitMatchExpression(MatchExpression *node) = 0;
  virtual void VisitNewExpression(NewExpression *node) = 0;
  virtual void VisitBlockExpression(BlockExpression *node) = 0;
  virtual void VisitFnCallExpression(FnCallExpression *node) = 0;
  virtual void VisitIntrinsicCall(IntrinsicCall *node) = 0;
  virtual void VisitCompoundInitializerExpr(CompoundInitializerExpr *node) = 0;
  virtual void VisitFieldAccessExpression(FieldAccessExpression *node) = 0;
  virtual void VisitLiteralExpression(LiteralExpression *node) = 0;
  virtual void VisitVarAccessExpression(VarAccessExpression *node) = 0;
  virtual void VisitTypecastExpression(TypecastExpression *node) = 0;
  virtual void VisitYieldExpression(YieldExpression *node) = 0;
  virtual void VisitReturnExpression(ReturnExpression *node) = 0;

  // Statements

  virtual void VisitExprStatement(ExprStatement *node) = 0;
  virtual void VisitAssignmentStatement(AssignmentStatement *node) = 0;

  // Declarations

  virtual void VisitVarDeclaration(VarDeclaration *node) = 0;
  virtual void VisitFunDeclaration(FunDeclaration *node) = 0;
  virtual void VisitTypeDeclaration(TypeDeclaration *node) = 0;
  virtual void VisitImplDeclaration(ImplDeclaration *node) = 0;
  virtual void VisitTraitDeclaration(TraitDeclaration *node) = 0;

  // Patterns

  virtual void VisitBindingPattern(BindingPattern *ndoe) = 0;
  virtual void VisitLiteralPattern(LiteralPattern *ndoe) = 0;
  virtual void VisitStructPattern(StructPattern *ndoe) = 0;
  virtual void VisitVariantPattern(VariantPattern *ndoe) = 0;
  virtual void VisitDiscardingPattern(DiscardingPattern *ndoe) = 0;

  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here
  // Your code goes here

};

//////////////////////////////////////////////////////////////////////
