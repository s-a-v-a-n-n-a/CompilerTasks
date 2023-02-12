#pragma once

#include <lex/token_type.hpp>

#include <string>
#include <map>

#include <fmt/core.h>

namespace lex {

class IdentTable {
 public:
  IdentTable() {
    Populate();
  }

  // Use-of-string-view-for-map-lookup
  // https://stackoverflow.com/questions/35525777

  TokenType LookupWord(const std::string_view lexeme) {
    if (map_.contains(lexeme)) {
      return (map_.find(lexeme))->second;
    } else {
      return TokenType::IDENTIFIER;
    }
  }

 private:
  void Populate() {
    map_.insert({"Int", TokenType::TY_INT});
    map_.insert({"Bool", TokenType::TY_BOOL});
    map_.insert({"Char", TokenType::TY_CHAR});
    map_.insert({"Unit", TokenType::TY_UNIT});
    map_.insert({"String", TokenType::TY_STRING});

    map_.insert({"true", TokenType::TRUE});
    map_.insert({"false", TokenType::FALSE});
    
    map_.insert({"+", TokenType::PLUS});
    map_.insert({"-", TokenType::MINUS});
    map_.insert({"*", TokenType::STAR});
    map_.insert({"/", TokenType::DIV});

    map_.insert({"=", TokenType::ASSIGN});
    map_.insert({"==", TokenType::EQUALS});
    map_.insert({"!", TokenType::NOT});
    map_.insert({"!=", TokenType::NOT_EQ});
    map_.insert({"<", TokenType::LT});
    map_.insert({">", TokenType::GT});

    map_.insert({"[", TokenType::LEFT_PAREN});
    map_.insert({"]", TokenType::RIGHT_PAREN});
    map_.insert({"(", TokenType::LEFT_BRACE});
    map_.insert({")", TokenType::RIGHT_BRACE});
    map_.insert({"{", TokenType::LEFT_CBRACE});
    map_.insert({"}", TokenType::RIGHT_CBRACE});

    map_.insert({",", TokenType::COMMA});
    map_.insert({":", TokenType::COLON});
    map_.insert({";", TokenType::SEMICOLUMN});

    map_.insert({"fun", TokenType::FUN});
    map_.insert({"var", TokenType::VAR});

    map_.insert({"for", TokenType::FOR});
    map_.insert({"if", TokenType::IF});
    map_.insert({"then", TokenType::THEN});
    map_.insert({"else", TokenType::ELSE});

    map_.insert({"yield", TokenType::YIELD});
    map_.insert({"return", TokenType::RETURN});
    
    map_.insert({"EOF", TokenType::TOKEN_EOF});
  }

 private:
  // What-are-transparent-comparators
  // https://stackoverflow.com/questions/20317413


  std::map<std::string, TokenType, std::less<>> map_;
};

}  // namespace lex
