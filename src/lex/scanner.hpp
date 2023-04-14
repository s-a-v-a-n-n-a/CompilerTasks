#pragma once

#include <lex/token_type.hpp>
#include <lex/location.hpp>

#include <fmt/core.h>

#include <string_view>
#include <filesystem>
#include <iostream>
#include <istream>
#include <vector>
#include <span>

#include <cassert>

namespace lex {

//////////////////////////////////////////////////////////////////////

class Scanner {
private:
  const ssize_t START_BUFFER_SIZE = 10000;

private:
  std::istream &sourceCode_;
  
  std::string buffer_;
  std::vector<std::string> lines_;

  std::string currentLine_;

  ssize_t currentState_;
  ssize_t lineCounter_;

  Location position_;

private:
  void addLine() {
    lines_.push_back(currentLine_);
    currentLine_.clear();

    ++lineCounter_;

    position_.columnno = 0;
    ++position_.lineno;

    assert(lineCounter_ == position_.lineno);
  }

  void readSymbol() {
    if (atEnd())  {
      return;
    }

    char symbol = sourceCode_.get();
    
    buffer_.push_back(symbol);
    currentLine_.push_back(symbol);
  }

public:
  Scanner(std::istream &sourceCode) 
  : sourceCode_(sourceCode) {
    buffer_.reserve(START_BUFFER_SIZE);
    
    // startState_ = 0;
    currentState_ = 0;
    lineCounter_ = 0;

    currentLine_ = "";

    readSymbol();
  }

  bool atEnd() const {
    return sourceCode_.eof();
  }

  ssize_t getCurrentState() const {
    return currentState_;
  }

  char getCurrentSymbol() {
    return buffer_[currentState_];
  }

  char getNextSymbol() const {
    if (atEnd()) {
      return EOF;
    }

    return sourceCode_.peek();
  }

  const std::vector<std::string> &getLines() const {
    return lines_;
  }

  Location getPosition() {
    return position_;
  }

  void shift(ssize_t offset = 1) {
    for (int i = 0; i < offset; ++i) {
      switch (getCurrentSymbol()) {
        case '\n':
          addLine();
          ++currentState_;

          break;

        case EOF:
          break;

        default:
          ++currentState_;

          break;
      }

      readSymbol();
    }
  }

  void skipRestLine() {
    while (getCurrentSymbol() != '\n' && !atEnd()) {
      shift(1);
    }

    if (!atEnd()) {
      shift(1);
    }
  }
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
