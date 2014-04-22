#ifndef AST_H
#define AST_H

#include <memory>

#include "calc.h"
#include "Visitor.h"

class AstNode {
public:
    virtual void visit(AstVisitor& visitor) {
        visitor.visit(*this);
    }

    virtual ~AstNode() {}
};

typedef std::shared_ptr<AstNode> node_ptr_type;
typedef std::shared_ptr<BinaryOpNode> binary_node_ptr_type;

class UnaryOpNode : public AstNode {
public:
    UnaryOpNode(node_ptr_type childPtr, TokenKind kind) :
        child_(childPtr),
        opKind_(kind)
    {}

    virtual void visit(AstVisitor& visitor) {
        visitor.visit(*this);
    }

    node_ptr_type getChild() {
        return child_;
    }

    TokenKind getOpKind() {
        return opKind_;
    }

private:
    node_ptr_type child_;
    TokenKind opKind_;
};

class BinaryOpNode : public AstNode {
public:
    BinaryOpNode(node_ptr_type leftPtr, node_ptr_type rightPtr, TokenKind kind) :
        left_(leftPtr),
        right_(rightPtr),
        opKind_(kind)
    {}

    virtual void visit(AstVisitor& visitor) {
        visitor.visit(*this);
    }

    TokenKind getOpKind() {
        return opKind_;
    }

    node_ptr_type getLeftChild() {
        return left_;
    }

    node_ptr_type getRightChild() {
        return right_;
    }

private:
    node_ptr_type left_;
    node_ptr_type right_;

    TokenKind opKind_;
};

class IntLiteralNode : public AstNode {
public:
    IntLiteralNode(int value) :
        value_(value)
    {}

    int getValue() {
        return value_;
    }

    virtual void visit(AstVisitor& visitor) {
        visitor.visit(*this);
    }

private:
    int value_;
};


#endif // AST_H