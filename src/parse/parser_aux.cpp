#include <parse/parse_error.hpp>
#include <parse/parser.hpp>

Parser::Parser(lex::Lexer& l) : lexer_{l} {}

std::string Parser::FormatLocation() {
    return lexer_.GetPreviousToken().getLocation().Format();
}

bool Parser::Matches(lex::TokenType type) {
    if (lexer_.Peek().getType() != type) {
        return false;
    } else {
        lexer_.Advance();

        return true;
    }
}

void Parser::Consume(lex::TokenType type) {
    if (!Matches(type)) {
        throw parse::errors::ParseTokenError(lex::FormatTokenType(type), FormatLocation());
    }
}

bool Parser::MatchesComparisonSign(lex::TokenType type) {
    if (type == lex::TokenType::GT || type == lex::TokenType::LT) {
        lexer_.Advance();

        return true;
    }

    return false;
}

