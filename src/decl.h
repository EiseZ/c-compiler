int scan(struct token *t);
struct ASTnode *mkastnode(int operation, struct ASTnode *left,
    struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int operation, int intvalue);
struct ASTnode *mkastunary(int operation, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *n);
void gencode(struct ASTnode *n);
static int genAST(struct ASTnode *n);

void freeall_registers(void);
void cgpreamble(void);
void cgpostamble(void);
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
