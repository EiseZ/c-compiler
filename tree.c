#include "defs.h"

#include "data.h"
#include "decl.h"

// Create AST node
struct ASTnode *mkastnode(int operation, struct ASTnode *left,
                          struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  // Create node
  n = (struct ASTnode *)malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to alocate memory in 'mkastnode()'\n");
    exit(1);
  }

  // Build node
  n->operation = operation;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}

// Create AST leaf (no children)
struct ASTnode *mkastleaf(int operation, int intvalue) {
  return (mkastnode(operation, NULL, NULL, intvalue));
}

// Create AST unary (1 child)
struct ASTnode *mkastunary(int operation, struct ASTnode *left, int intvalue) {
  return (mkastnode(operation, left, NULL, intvalue));
}
