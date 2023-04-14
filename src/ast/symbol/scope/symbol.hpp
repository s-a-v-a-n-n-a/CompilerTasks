#pragma once

#include <string>
#include <vector>

#include "lex/location.hpp"

namespace ast::scope
{
class Symbol {
  public:
    enum class SymbolType {
        TYPE, 
        FUNC,
        VAR
    };

    struct TypeType {};
    struct FuncType {};
    struct VarType {};
    
  private:
    union {
      TypeType typeStruct{};
      FuncType functStruct{};
      VarType verStruct{};
    }

    std::string initialName;
    SymbolType type;

    lex::Location declaration;
    std::vector<lex::Location> symbolUses;

  public:
    Symbol(std::string symbolName, SymbolType symbolType, lex::Location symbolDeclaration)
    : symbolUses{} {
      initialName = std::copy(symbolName);
      type = symbolType;
      delaration = symbolDeclaration;
    }

    void setName(std::string symbolName) {
      initialName = std::copy(symbolName);
    }

    std::string getName() {
      return initialName;
    }
};

} // namespace ast::scope

