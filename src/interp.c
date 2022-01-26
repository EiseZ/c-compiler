#include "defs.h"
#include "data.h"
#include "decl.h"

// When given a node, interpret every node after and preform the operation
int
interpretAST(struct ASTnode *n)
{
    int leftval, rightval;

    if (n->left) {
        leftval = interpretAST(n->left);
    }
    if (n->right) {
        rightval = interpretAST(n->right);
    }

    switch (n->operation) {
    case A_ADD:
        return (leftval + rightval);
    case A_SUBTRACT:
        return (leftval - rightval);
    case A_MULTIPLY:
        return (leftval * rightval);
    case A_DIVIDE:
        return (leftval / rightval);
    case A_INTLIT:
        return (n->intvalue);
    default:
        fprintf(stderr, "Unknow AST operation %d\n", n->operation);
        exit(1);
    }
}
