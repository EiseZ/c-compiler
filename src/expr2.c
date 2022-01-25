#include "defs.h"
#include "data.h"
#include "decl.h"

// Scan token to AST operation
int
toktoopr(int tok)
{
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
static struct ASTnode *
primary(void)
{
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

// Return AST tree with binary operator "*" or "/" as root
struct ASTnode *
multiplicitive_expr(void)
{
    struct ASTnode *n, *left, *right;
    int tokentype;

    // Get integer on left of operator
    left = primary();

    // Return only left node if no tokens left
    tokentype = token.token;
    if (token.token == T_EOF) {
        return (left);
    }

    while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {
        // Get next integer literal
        scan(&token);
        right = primary();

        // Make the node
        n = mkastnode(toktoopr(tokentype), left, right, 0);

        // Break if EOF
        tokentype = token.token;
        if (tokentype == T_EOF) {
            break;
        }
    }

    return (n);
}

// Return AST tree with binary operator "+" or "-" as root
struct ASTnode *
additive_expr(void)
{
    struct ASTnode *n, *left, *right;
    int tokentype;

    // Get multiplicitive at left of node
    // This also makes sure we are dealing with a additive expression
    left = multiplicitive_expr();

    // Return only left if no tokens are left
    tokentype = token.token;
    if (tokentype == T_EOF) {
        return (left);
    }

    // Loop working on the current token
    while (1) {
        // Get next token
        scan(&token);

        // Get tree to right of node
        right = multiplicitive_expr();

        // Create the node
        n = mkastnode(toktoopr(tokentype), left, right, 0);

        // Get next token and stop if EOF
        tokentype = token.token;
        if (tokentype == T_EOF) {
            break;
        }
    }

    return (n);
}
