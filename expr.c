#include "defs.h"

#include "data.h"
#include "decl.h"

// Scan token to AST operation
int toktoopr(int tok) {
  switch (tok) {
  case T_PLUS:
    return (A_ADD);
  case T_MINUS:
    return (A_SUBTRACT);
  case T_STAR:
    return (A_MULTIPLY);
  case T_SLASH:
    return (A_DIVIDE);
  default:
    fprintf(stderr, "Unknow token %d in 'toktoopr()' on line %d\n", tok, line);
    exit(1);
  }
}

// Check if token is primary factor (int)
// if so, return AST node
static struct ASTnode *primary(void) {
  struct ASTnode *n;

  switch (token.token) {
  case T_INTLIT:
    n = mkastleaf(A_INTLIT, token.intvalue);
    scan(&token);
    return (n);
  default:
    fprintf(stderr, "Syntax error on line %d\n", line);
    exit(1);
  }
}

// Return AST tree with binary operator as root
struct ASTnode *binexpr(void) {
  struct ASTnode *n, *left, *right;
  int nodetype;

  // Get integer on left of operator
  left = primary();
  // Return only left node if no tokens left
  if (token.token == T_EOF) {
    return (left);
  }

  // Convert token into node
  nodetype = toktoopr(token.token);

  // Get next token
  scan(&token);

  // Get everything on right
  right = binexpr();

  // Build the tree
  n = mkastnode(nodetype, left, right, 0);
  return (n);
}
