#include <ast/visitors/print_visitor.hpp>

// Finally,
#include <catch2/catch.hpp>

#include <iostream>

//////////////////////////////////////////////////////////////////////

TEST_CASE("PrintVisitor: Just works", "[visitor]") {
    lex::Token plus = lex::Token(
        lex::TokenType::PLUS,
        "+",
        "",
        1,
        1,
        lex::Location()
    );
    
    LiteralExpression left(
    lex::Token(
        lex::TokenType::NUMBER,
        "",
        1,
        0,
        1,
        lex::Location()
    )
    );

    LiteralExpression right(
    lex::Token(
        lex::TokenType::NUMBER,
        "s",
        2.02,
        2,
        3,
        lex::Location()
    )
    );

    BinaryExpression sum(left, right, plus);

    PrintVisitor printer = {};
    printer.VisitBinaryExpression(sum);
}
