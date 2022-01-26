#include "defs.h"
#include "data.h"
#include "decl.h"

// Parse one or more statements (keyword + expression + semicolon)
void
statements(void)
{
    struct ASTnode *tree;
    int reg;

    while (1) {
        // Make sure we are on a print keyword
        match(T_PRINT, "print");

        // Parse the expression and generate code for it
        tree = binexpr(0);
        reg = genAST(tree);
        genprintint(reg);
        genfreeregs();

        // Make sure we are on a semicolon
        semi();

        // Return if EOF
        if (token.token == T_EOF) {
            return;
        }
    }
}
