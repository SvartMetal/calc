#ifndef RD_PARSER_H
#define RD_PARSER_H

#include "ast.h"
#include "Scanner.h"

class RDParser {
public:
    RDParser(const std::string& text);

    node_ptr_type parse();

private:
    node_ptr_type parseMain();
    bool ensureToken(TokenKind kind);
    TokenKind readToken();
    void consumeToken();
    bool parseInt(int& value);

    node_ptr_type parseIntLiteralNode();
    node_ptr_type parseGenericMain(bool ensureEnd);
    node_ptr_type parseT();
    binary_node_ptr_type parseT1();
    node_ptr_type parseE();
    binary_node_ptr_type parseE1();
    node_ptr_type parseF();

    TokenList tokenList_;
    TokenList::const_iterator next_;
    node_ptr_type empty_;
};

RDParser::RDParser(const std::string& text) :
    tokenList_(Scanner(text).scan()),
    next_(tokenList_.cbegin())
{}

node_ptr_type RDParser::parse() {
    auto result = parseMain();
    if (result) {
        return result;
    }
    throw std::logic_error("Parse error. ");
}

node_ptr_type RDParser::parseGenericMain(bool ensureEnd) 
{
    auto result = empty_;
    auto save = next_;
    binary_node_ptr_type rest;
    if ((result = parseT()) && (rest = parseE1()) && 
        (!ensureEnd || ensureToken(tEND))) 
    {
        result = std::make_shared<BinaryOpNode>(result, 
            rest->getRightChild(), rest->getOpKind());
        return result;
    }
    next_ = save;
    if ((result = parseT()) && (!ensureEnd || ensureToken(tEND))) {
        return result;
    }
    return empty_;
}

node_ptr_type RDParser::parseMain() {
    return parseGenericMain(true);
}

node_ptr_type RDParser::parseE() {
    return parseGenericMain(false);
}

binary_node_ptr_type RDParser::parseE1() {
    binary_node_ptr_type result;
    auto save = next_;
    TokenKind op;
    if (readToken() == tPLUS) {
        consumeToken();
    } else if (readToken() != tMINUS) {
        return result;
    }
    auto left = empty_;
    if (left = parseT()) {
        save = next_;
        auto rest = parseE1();
        if (rest) {
            auto right = std::make_shared<BinaryOpNode>(left, 
                rest->getRightChild(), rest->getOpKind());
            return std::make_shared<BinaryOpNode>(empty_, right, tPLUS);
        }
        next_ = save;
        result = std::make_shared<BinaryOpNode>(empty_, left, tPLUS);
    }
    return result;   
}

node_ptr_type RDParser::parseT() {
    auto result = empty_;
    auto save = next_;
    binary_node_ptr_type rest;
    if ((result = parseF()) && (rest = parseT1()))
    {
        result = std::make_shared<BinaryOpNode>(result, 
            rest->getRightChild(), rest->getOpKind());
        return result;
    }
    next_ = save;
    return parseF();
}

binary_node_ptr_type RDParser::parseT1() {
    binary_node_ptr_type result;
    TokenKind op;
    if ((op = readToken()) != tMUL && op != tDIV) {
        return result;
    }
    consumeToken();
    auto left = empty_;
    if (left = parseF()) {
        auto save = next_;
        auto rest = parseT1();
        if (rest) {
            auto right = std::make_shared<BinaryOpNode>(left, 
                rest->getRightChild(), rest->getOpKind());
            return std::make_shared<BinaryOpNode>(empty_, right, op);
        }
        next_ = save;
        result = std::make_shared<BinaryOpNode>(empty_, left, op);
    }
    return result;
}

TokenKind RDParser::readToken() {
    return next_->kind;
}

void RDParser::consumeToken() {
    next_++;
}

node_ptr_type RDParser::parseF() {
    auto result = empty_;
    auto save = next_;
    if (ensureToken(tPAR_OPEN) && (result = parseE()) && ensureToken(tPAR_CLOSE)) {
        return result;
    }
    next_ = save;
    if (result = parseIntLiteralNode()) {
        return result;
    }
    next_ = save;
    if (ensureToken(tMINUS) && (result = parseF())) {
        result = std::make_shared<UnaryOpNode>(result, tMINUS);
    }
    return result;
}

bool RDParser::ensureToken(TokenKind kind) {
    return next_++->kind == kind;
}

bool RDParser::parseInt(int& value) {
    auto token = *next_++;
    if (token.kind == tINT) {
        value = std::stoi(token.value);
        return true;
    }
    return false;
}

node_ptr_type RDParser::parseIntLiteralNode() {
    int value;
    if (parseInt(value)) {
        return std::make_shared<IntLiteralNode>(value);
    }
    return empty_;
}

#endif // RD_PARSER_H