#pragma once

#include <lex/scanner.hpp>

#include <variant>
#include <cstddef>

namespace lex {

//////////////////////////////////////////////////////////////////////

struct Token {
    TokenType type_;
    std::string lexeme_;
    std::variant<double, std::string, std::nullopt_t> literal_;
    ssize_t offset_;
    ssize_t length_;
    Location location_;

    Token()
    : type_(TokenType::NONE),
    lexeme_(""),
    literal_(std::nullopt),
    offset_(0),
    length_(0),
    location_({0, 0})
    {}

    Token(
        TokenType type, 
        std::string lexeme, 
        std::variant<double, std::string, std::nullopt_t> literal, 
        ssize_t offset, 
        ssize_t length,
        Location location
        ) 
    : type_(type), 
    lexeme_(lexeme), 
    literal_(literal), 
    offset_(offset), 
    length_(length),
    location_(location)
    {}

    Location getLocation() {
        return location_;
    }

    std::string getName() {
        return std::get<std::string>(literal_);
    }

    double getNumber() {
        return std::get<double>(literal_);
    }
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
