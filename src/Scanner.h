#ifndef SCANNER_H
#define SCANNER_H

#include <locale>
#include <stdexcept>

#include "calc.h"

class Scanner {
    typedef std::vector<TokenInfo> tokens_type;
public:
    Scanner(const std::string& text);

    TokenList scan();

private:
    bool isNotEnd();
    bool isEnd();
    char nextChar();
    char readChar();
    void scanInt();
    void scanToken(TokenKind kind);
    void skipWhiteSpaces();

    tokens_type tokens_;
    std::string text_;
    size_t position_;
};

Scanner::Scanner(const std::string& text) :
    text_(text),
    position_(0)
{}

TokenList Scanner::scan() {
    while (isNotEnd()) {
        skipWhiteSpaces();
        if (isEnd()) {
            break;
        }
        char c = readChar();
        if (c == '+') {
            scanToken(tPLUS);
        } else if (c == '-') {
            scanToken(tMINUS);
        } else if (c == '*') {
            scanToken(tMUL);
        } else if (c == '/') {
            scanToken(tDIV);
        } else if (c == '(') {
            scanToken(tPAR_OPEN);
        } else if (c == ')') {
            scanToken(tPAR_CLOSE);
        } else if (std::isdigit(c)) {
            scanInt();
        } else {
            throw std::logic_error("Unknown token. ");
        }
    }
    std::string value("");
    tokens_.push_back(TokenInfo(tEND, text_.size(), value));
    return TokenList(tokens_);
}

bool Scanner::isNotEnd() {
    return position_ < text_.size();
}

bool Scanner::isEnd() {
    return !isNotEnd();
}

char Scanner::nextChar() {
    return text_[position_++];
}

char Scanner::readChar() {
    return text_[position_];
}

void Scanner::scanInt() {
    std::string value;
    char c;
    size_t startPosition = position_;
    while (isNotEnd() && std::isdigit(c = readChar())) {
        value.push_back(c);
        nextChar();
    }
    if (value.size() > 1 && value[0] == '0') {
        throw std::logic_error("Invalid integer. ");
    }
    tokens_.push_back(TokenInfo(tINT, startPosition, value));
}

void Scanner::scanToken(TokenKind kind) {
    std::string value;
    size_t startPosition = position_;
    value.push_back(nextChar());
    tokens_.push_back(TokenInfo(kind, startPosition, value));
}

void Scanner::skipWhiteSpaces() {
    while (isNotEnd() && std::isspace(readChar())) {
        nextChar();
    }
}

#endif // SCANNER_H