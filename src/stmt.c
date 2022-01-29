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

    // Make sure we are on a semicolon
    semi();
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

    // Match the semicolon
    semi();
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

// Parse a compound statements (keyword + expression + semicolon)
//
struct ASTnode *
compound_statement(void)
{
    struct ASTnode *left = NULL;
    struct ASTnode *tree;

    // Make sure there is left curly brace
    leftbrace();

    while(1) {
        switch(token.token) {
        case T_PRINT:
            tree = print_statement();
            break;
        case T_INT:
            var_declaration();
            tree = NULL;
            break;
        case T_IDENT:
            tree = assignment_statement();
            break;
        case T_IF:
            tree = if_statement();
            break;
        case T_WHILE:
            tree = while_statement();
            break;
        case T_RIGHTBRACE:
            // Skip it and return
            rightbrace();
            return (left);
        default:
            fatald("Syntax error, token", token.token);
        }

        // If left is empty, make left the tree
        // Else glue the tree to the left
        if (tree) {
            if (left == NULL) {
                left = tree;
            } else {
                left = mkastnode(A_GLUE, left, NULL, tree, 0);
            }
        }
    }
}
