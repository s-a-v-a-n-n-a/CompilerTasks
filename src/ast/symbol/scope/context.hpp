#pragma once

#include <string>
#include <deque>
#include <unordered_map>

#include "symbol.hpp"

namespace ast::scope {

class Context {
  public:
    class ScopeLayer {
      private: 
        using List = std::deque<Symbol>;
        using HashMap = std::unordered_map<std::string, Symbol &>;

        List symbols_;
        HashMap symbolMap_;

      public:
        void addSymbol(Symbol symbol);
        Symbol *getSymbolByName(std::string name);
        List getSymbols() const;
    };
  
  private:
    Context *parent_;
    std::vector<Context *> children_{};

    ScopeLayer currentScope_{};

    std::string name_;
    lex::Location declaration_;

    size_t level_;

  public:
    Context(Context *parent, lex::Location declaration, std::string name, size_t level);

    Context *getParent();
    void setParent(Context *parent);

    void addChild(Context *child);
    std::vector<Context *> getChildren();  

    bool addSymbol(Symbol symbol);

    lex::Location GetLocation() const;

    Context *createChild(lex::Location location, std::string name);

    ScopeLayer *getScope();

    void print();
};
}
