#include "defs.h"
#include "data.h"
#include "decl.h"

// Generate assembly from given AST
int
genAST(struct ASTnode *n, int reg)
{
    int leftreg, rightreg;

    if (n->left) {
        leftreg = genAST(n->left, -1);
    }
    if (n->right) {
        rightreg = genAST(n->right, leftreg);
    }

    switch (n->operation) {
    case A_ADD:
        return (cgadd(leftreg, rightreg));
    case A_SUBTRACT:
        return (cgsub(leftreg, rightreg));
    case A_MULTIPLY:
        return (cgmul(leftreg, rightreg));
    case A_DIVIDE:
        return (cgdiv(leftreg, rightreg));
    case A_INTLIT:
        return (cgloadint(n->v.intvalue));
    case A_IDENT:
        return (cgloadglob(gsym[n->v.id].name));
    case A_LVIDENT:
        return (cgstorglob(reg, gsym[n->v.id].name));
    case A_ASSIGN:
        // This has already been done
        return (rightreg);
    default:
        fatald("Unknow AST operation", n->operation);
    }
}

// Define simple functions so we don't have to call any function from cg.c
void genpreamble()          { cgpreamble(); }
void genpostamble()         { cgpostamble(); }
void genfreeregs()          { freeallregisters(); }
void genprintint(int reg)   { cgprintint(reg); }
void genglobsym(char *s)    { cgglobsym(s); }
