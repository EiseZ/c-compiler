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

// Table of the precedence of the tokens
static int operatorPrecedence[] = {0, 10, 10, 20, 20, 0};
//                                 EOF  +   -   *   /  INTLIT

// Return precedence if token is operator
static int operator_precedence(int tokentype) {
  int prec = operatorPrecedence[tokentype];
  if (prec == 0) {
    fprintf(stderr, "Syntax error on line %d, token %d\n", line, tokentype);
    exit(1);
  }
  return (prec);
}

// Return AST tree with binary operator as root
// ptp is previous tokens precedence
struct ASTnode *binexpr(int ptp) {
  struct ASTnode *left, *right;
  int tokentype;

  // Get integer on left of operator
  // And fetch next token
  left = primary();

  // Return only left node if no tokens left
  tokentype = token.token;
  if (tokentype == T_EOF) {
    return (left);
  }

  while (operator_precedence(tokentype) > ptp) {
    // Fetch next integer literal
    scan(&token);

    // Make right tree recursively
    right = binexpr(operatorPrecedence[tokentype]);

    // Create node tree
    left = mkastnode(toktoopr(tokentype), left, right, 0);

    // Return if EOF
    tokentype = token.token;
    if (tokentype == T_EOF) {
      return (left);
    }
  }

  return (left);
}
