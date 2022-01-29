#include "defs.h"
#include "data.h"
#include "decl.h"

// Generate assembly from given AST
int
genAST(struct ASTnode *n, int reg, int parentASToperation)
{
    int leftreg, rightreg;

    switch (n->operation) {
    case A_IF:
        return (genIFAST(n));
    case A_WHILE:
        return (genWHILEAST(n));
    case A_GLUE:
        // Execute the child satements
        genAST(n->left, NOREG, n->operation);
        genfreeregs();
        genAST(n->right, NOREG, n->operation);
        genfreeregs();
        return (NOREG);
    }

    if (n->left) {
        leftreg = genAST(n->left, NOREG, n->operation);
    }
    if (n->right) {
        rightreg = genAST(n->right, leftreg, n->operation);
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
    case A_EQUALS:
    case A_NOTEQUALS:
    case A_LESSTHAN:
    case A_GREATERTHAN:
    case A_LESSEQUALS:
    case A_GREATEREQUALS:
        // If parent node is IF satement, compare and jump
        // Else compare and set register
        if (parentASToperation == A_IF || parentASToperation == A_WHILE) {
            return (cgcompare_and_jump(n->operation, leftreg, rightreg, reg));
        }
        else {
            return (cgcompare_and_set(n->operation, leftreg, rightreg));
        }
    case A_INTLIT:
        return (cgloadint(n->v.intvalue));
    case A_IDENT:
        return (cgloadglob(gsym[n->v.id].name));
    case A_LVIDENT:
        return (cgstorglob(reg, gsym[n->v.id].name));
    case A_ASSIGN:
        // This has already been done
        return (rightreg);
    case A_PRINT:
        genprintint(leftreg);
        genfreeregs();
        return (NOREG);
    default:
        fatald("Unknow AST operation", n->operation);
    }
}

// Return new label number
static int
label(void)
{
    static int id = 1;
    return (id++);
}

static int
genIFAST(struct ASTnode *n)
{
    int lfalse, lend;

    // Generate 2 labels, one for false, and one for end
    // If there is no else clause, the false label is the end
    lfalse = label();
    if (n->right) {
        lend = label();
    }

    // Generate the conditional code
    genAST(n->left, lfalse, n->operation);
    genfreeregs();

    // Generate true compound statement
    genAST(n->mid, NOREG, n->operation);
    genfreeregs();

    // If there is an else clause, generate a jump to that label
    if (n->right) {
        cgjump(lend);
    }

    // And the false label
    cglabel(lfalse);

    // If there is an else clause, generate that compound statement
    if (n->right) {
        genAST(n->right, NOREG, n->operation);
        genfreeregs();
        cglabel(lend);
    }

    return (NOREG);
}

static int
genWHILEAST(struct ASTnode *n)
{
    int lstart, lend;

    lstart = label();
    lend = label();
    cglabel(lstart);

    // Generate AST for code in condition
    genAST(n->left, lend, n->operation);
    genfreeregs();

    // Generate AST for code in compound statement
    genAST(n->right, NOREG, n->operation);

    // First jump to start
    // Then jump to end if condition is not met anymore
    cgjump(lstart);
    cglabel(lend);
    return (NOREG);
}

// Define simple functions so we don't have to call any function from cg.c
void genpreamble()          { cgpreamble(); }
void genpostamble()         { cgpostamble(); }
void genfreeregs()          { freeallregisters(); }
void genprintint(int reg)   { cgprintint(reg); }
void genglobsym(char *s)    { cgglobsym(s); }
