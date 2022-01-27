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
        fatald("Syntax error, token", tok);
    }
}

// Check if token is primary factor (int or global symbol)
// if so, return AST node
static struct ASTnode *
primary(void)
{
    struct ASTnode *n;
    int id;

    switch (token.token) {
        case T_INTLIT:
            n = mkastleaf(A_INTLIT, token.intvalue);
            break;
        case T_IDENT:
            // Check if inentifier exists
            id = findglob(text);
            if (id == -1) {
                fatals("Unknow variable", text);
            }

            n = mkastleaf(A_IDENT, id);
            break;
        default:
            fatald("Syntax error, token ", token.token);
    }
    scan(&token);
    return (n);
}

// Table of the precedence of the tokens
static int operatorPrecedence[] = {0, 10, 10, 20, 20, 0};
//                                 EOF  +   -   *   /  INTLIT

// Return precedence if token is operator
static int
operator_precedence(int tokentype)
{
    int prec = operatorPrecedence[tokentype];
    if (prec == 0) {
        fatald("Syntax error, token", tokentype);
    }
    return (prec);
}

// Return AST tree with binary operator as root
// ptp is previous tokens precedence
struct ASTnode *
binexpr(int ptp)
{
    struct ASTnode *left, *right;
    int tokentype;

    // Get integer on left of operator
    // And fetch next token
    left = primary();

    // Return only left node if we're at the end of the expression
    tokentype = token.token;
    if (tokentype == T_SEMICOLON) {
        return (left);
    }

    while (operator_precedence(tokentype) > ptp) {
        // Fetch next integer literal
        scan(&token);

        // Make right tree recursively
        right = binexpr(operatorPrecedence[tokentype]);

        // Create node tree
        left = mkastnode(toktoopr(tokentype), left, right, 0);

        // Return only left node if we're at the end of the expression
        tokentype = token.token;
        if (tokentype == T_SEMICOLON) {
            return (left);
        }
    }

    return (left);
}
