#include "defs.h"
#include "data.h"
#include "decl.h"

// Generate full code from AST
void
gencode(struct ASTnode *n)
{
    int reg;

    cgpreamble();
    reg = genAST(n);
    cgprintint(reg);
    cgpostamble();
}

// Generate assembly from given AST
int
genAST(struct ASTnode *n)
{
    int leftreg, rightreg;

    if (n->left) {
        leftreg = genAST(n->left);
    }
    if (n->right) {
        rightreg = genAST(n->right);
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
        return (cgload(n->intvalue));
    default:
        fprintf(stderr, "Unknow AST operator %d\n", n->operation);
        exit(1);
    }
}

// Define simple functions so we don't have to call any function from cg.c
void genpreamble()          { cgpreamble(); }
void genpostamble()         { cgpostamble(); }
void genfreeregs()          { freeallregisters(); }
void genprintint(int reg)   { cgprintint(reg); }
