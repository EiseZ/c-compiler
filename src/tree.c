#include "defs.h"
#include "data.h"
#include "decl.h"

// Create AST node
struct ASTnode *
mkastnode(int operation, struct ASTnode *left, struct ASTnode *right,
    int intvalue)
{
    struct ASTnode *n;

    // Create node
    n = (struct ASTnode *)malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fatal("Unable to alocate memory in 'mkastnode()'");
    }

    // Build node
    n->operation = operation;
    n->left = left;
    n->right = right;
    n->v.intvalue = intvalue;
    return (n);
}

// Create AST leaf (no children)
struct ASTnode *
mkastleaf(int operation, int intvalue)
{
    return (mkastnode(operation, NULL, NULL, intvalue));
}

// Create AST unary (1 child)
struct ASTnode *
mkastunary(int operation, struct ASTnode *left, int intvalue)
{
    return (mkastnode(operation, left, NULL, intvalue));
}
