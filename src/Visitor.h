#ifndef VISITOR_H
#define VISITOR_H

class AstNode;
class UnaryOpNode;
class BinaryOpNode;
class IntLiteralNode;

class AstVisitor {
public:
    virtual void visit(AstNode& node) = 0;
    virtual void visit(UnaryOpNode& node) = 0;
    virtual void visit(BinaryOpNode& node) = 0;
    virtual void visit(IntLiteralNode& node) = 0;

    virtual ~AstVisitor() {}
};

#endif // VISITOR_H