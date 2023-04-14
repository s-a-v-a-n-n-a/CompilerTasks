#include "context.hpp"

namespace ast::scope {
// -------------------------------------------------------------------------
// ScopeLayer -----------------------------------------------------------------
// -------------------------------------------------------------------------

void Context::ScopeLayer::addSymbol(Symbol symbol) {
    symbols_.push_back(std::move(symbol));
    symbolMap_.insert({ symbols_.back().getName(), &symbols_.back() });
}

Symbol *Context::ScopeLayer::getSymbolByName(std::string name) {
    if (symbolMap_.find(name) == symbolMap_.end()) {
        return nullptr;
    }

    return symbolMap_.find(name);
}

List Context::ScopeLayer::getSymbols() const {
    return symbols_;
}

// -------------------------------------------------------------------------
// Context -----------------------------------------------------------------
// -------------------------------------------------------------------------

Context::Context(Context *parent, lex::Location declaration, std::string name, size_t level) {
    parent_ = parent;
    declaration_ = declaration;
    name_ = std::copy(name);
    level_ = level;
}

Context *Context::getParent() {
    return parent_;
}

void Context::setParent(Context *parent) {
    parent_ = parent;
}

void Context::addChild(Context *child) {
    children_.push_back(child);
}

std::vector<Context *> Context::getChildren() {
    return children_;
} 

lex::Location Context::GetLocation() const {
    return declaration_;
}

bool Context::addSymbol(Symbol symbol) {
    if (currentScope_.getSymbolByName(symbol.getName()) == nullptr) {
        currentScope_.addSymbol(symbol);

        return true;
    }

    return false;
}

Context *Context::createChild(lex::Location location, std::string name) {
    Context *child = new Context(this, location, name, level_  + 1);
    children_.push_back(child);

    return child;
}

ScopeLayer *Context::getScope() {
    return &currentScope_;
}

void Context::print() {
    fmt::print("[!] Context {} at {}, level {}\n", name_, declaration_.Format(), level_);

    fmt::print("Bindings: \n");
    for (auto &symbol : currentScope_.getSymbols()) {
        fmt::print("{}\n", symbol.getName());
    }

    fmt::print("\n\n\n");

    for (auto &child : children_) {
        child->print();
    }
}

}