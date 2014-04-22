#ifndef COUNT_VISITOR_H
#define COUNT_VISITOR_H

#include "ast.h"

class CountVisitor : public AstVisitor {
public:
    CountVisitor() : result_(0)
    {}

    virtual void visit(AstNode& node) {
        node.visit(*this);
    }

    virtual void visit(UnaryOpNode& node) {
        visit(*node.getChild());
        if (node.getOpKind() == tMINUS) {
            result_ = -result_;
        }
    }

    virtual void visit(BinaryOpNode& node) {
        visit(*node.getLeftChild());
        auto leftResult = result_;
        visit(*node.getRightChild());
        auto kind = node.getOpKind();
        if (kind == tPLUS) {
            result_ += leftResult;
        } else if (kind == tMINUS) {
            result_ = leftResult - result_;
        } else if (kind == tMUL) {
            result_ *= leftResult;
        } else if (kind == tDIV) {
            result_ = leftResult / result_;
        }
    }

    virtual void visit(IntLiteralNode& node) {
        result_ = node.getValue();
    }

    int getResult() {
        return result_;
    }

private:
    int result_;
};

#endif // COUNT_VISITOR_H