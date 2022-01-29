#include "defs.h"
#include "data.h"
#include "decl.h"

static struct ASTnode *
print_statement(void)
{
    struct ASTnode *tree;
    int reg;

    // Make sure we are on a print keyword
    match(T_PRINT, "print");

    // Parse the expression and generate code for it
    tree = binexpr(0);

    // Make AST tree
    tree = mkastunary(A_PRINT, tree, 0);

    return (tree);
}

static struct ASTnode *
assignment_statement(void)
{
    struct ASTnode *left, *right, *tree;
    int id;

    // Make sure this is identifier
    ident();

    // Check if it has been defined, if so, make a leaf for it
    if((id = findglob(text)) == -1) {
        fatals("Undeclared variable", text);
    }
    right = mkastleaf(A_LVIDENT, id);

    // Make sure we are on an equals sign
    match(T_ASSIGN, "=");

    // Parse the expression
    left = binexpr(0);

    // Make the AST tree
    tree = mkastnode(A_ASSIGN, left, NULL, right, 0);

    return (tree);
}

struct ASTnode *
if_statement(void)
{
    struct ASTnode *condAST, *trueAST, *falseAST = NULL;

    // Make sure there is an if statement
    match(T_IF, "if");
    leftparen();

    // Parse expression between parentheses
    condAST = binexpr(0);

    // Make sure there is a valid comparison to check
    if (condAST->operation < A_EQUALS || condAST->operation > A_GREATEREQUALS) {
        fatal("Invalid comparison in if statement");
    }

    rightparen();

    // Get AST for compound statement
    trueAST = compound_statement();

    // If there is an else statement, get that compound statement
    if (token.token == T_ELSE) {
        scan(&token);
        falseAST = compound_statement();
    }

    // Build the AST and return it
    return (mkastnode(A_IF, condAST, trueAST, falseAST, 0));
}

// Parse while statement and return AST
struct ASTnode *
while_statement(void)
{
    struct ASTnode *condAST, *bodyAST;

    // Make sure this is a while loop
    match(T_WHILE, "while");
    leftparen();

    // Parse expression between parentheses
    // And make sure it is a comparison
    condAST = binexpr(0);
    if (condAST->operation < A_EQUALS || condAST->operation > A_GREATEREQUALS) {
        fatal("Invalid comparison in while statement");
    }
    rightparen();

    // Get code to execute if expression it true
    bodyAST = compound_statement();

    return (mkastnode(A_WHILE, condAST, NULL, bodyAST, 0));
}

// Parse a for statement
static struct ASTnode *
for_statement(void)
{
    struct ASTnode *condAST, *bodyAST;
    struct ASTnode *preopAST, *postopAST;
    struct ASTnode *tree;

    // Make sure there is a for loop and left parenthese
    match(T_FOR, "for");
    leftparen();

    // Get the preop statement and semicolon
    preopAST = single_statement();
    semi();

    // Get the condition and semicolon
    condAST = binexpr(0);
    if (condAST->operation < A_EQUALS || condAST->operation > A_GREATEREQUALS) {
        fatal("Invalid comparison in while statement");
    }
    semi();

    // Get the postop and closing parenthese
    postopAST = single_statement();
    rightparen();

    // Get the compound statement
    bodyAST = compound_statement();

    // Glue the compound statement and postop
    tree = mkastnode(A_GLUE, bodyAST, NULL, postopAST, 0);

    // Make it a while loop with extra steps
    tree = mkastnode(A_WHILE, condAST, NULL, tree, 0);

    // And glue the preop tree to it
    return (mkastnode(A_GLUE, preopAST, NULL, tree, 0));
}


// Parse a single satement and return the AST
static struct ASTnode *
single_statement(void)
{
    switch(token.token) {
    case T_PRINT:
        return (print_statement());
    case T_INT:
        var_declaration();
        return (NULL);
    case T_IDENT:
        return (assignment_statement());
    case T_IF:
        return (if_statement());
    case T_WHILE:
        return (while_statement());
    case T_FOR:
        return (for_statement());
    default:
        fatald("Syntax error, token", token.token);
    }
}

// Parse a compound statements (keyword + expression + semicolon)
struct ASTnode *
compound_statement(void)
{
    struct ASTnode *left = NULL;
    struct ASTnode *tree;

    // Make sure there is left curly brace
    leftbrace();

    while(1) {
        // Parse a single statement
        tree = single_statement();

        // Check if it need a semicolon
        if (tree != NULL &&
            (tree->operation == A_PRINT || tree->operation == A_ASSIGN)) {
            semi();
        }

        // If left is empty, make left the tree
        // Else glue the tree to the left
        if (tree != NULL) {
            if (left == NULL) {
                left = tree;
            } else {
                left = mkastnode(A_GLUE, left, NULL, tree, 0);
            }
        }

        // When we hit a right curly brace
        // Skip it and return AST
        if (token.token == T_RIGHTBRACE) {
            rightbrace();
            return (left);
        }
    }
}
