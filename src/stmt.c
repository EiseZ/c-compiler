#include "defs.h"
#include "data.h"
#include "decl.h"

void
print_statement(void)
{
    struct ASTnode *tree;
    int reg;

    // Make sure we are on a print keyword
    match(T_PRINT, "print");

    // Parse the expression and generate code for it
    tree = binexpr(0);
    reg = genAST(tree, -1);
    genprintint(reg);
    genfreeregs();

    // Make sure we are on a semicolon
    semi();
}

void
assignment_statement()
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
    match(T_EQUALS, "=");

    // Parse the expression
    left = binexpr(0);

    // Make the AST tree
    tree = mkastnode(A_ASSIGN, left, right, 0);

    // Generate assembly code
    genAST(tree, -1);
    genfreeregs();

    // Match the semicolon
    semi();
}

// Parse one or more statements (keyword + expression + semicolon)
void
statements(void)
{
    while(1) {
        switch(token.token) {
        case T_PRINT:
            print_statement();
            break;
        case T_INT:
            var_declaration();
            break;
        case T_IDENT:
            assignment_statement();
            break;
        case T_EOF:
            return;
        default:
            fatald("Syntax error, token", token.token);
        }
    }
}
