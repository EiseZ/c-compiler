int scan(struct token *t);

struct ASTnode *mkastnode(int operation, struct ASTnode *left,
    struct ASTnode* mid, struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int operation, int intvalue);
struct ASTnode *mkastunary(int operation, struct ASTnode *left, int intvalue);

struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *n);

void gencode(struct ASTnode *n);
int genAST(struct ASTnode *n, int reg, int parentASToperation);
static int genIFAST(struct ASTnode *n);
static int genWHILEAST(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint();
void genglobsym(char *s);

void freeallregisters(void);
void cgpreamble(void);
void cgpostamble(void);
int cgloadint(int value);
int cgloadglob(char *identifier);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
int cgstorglob(int r, char *identifier);
void cgglobsym(char *sym);
int cgcompare_and_set(int ASToperation, int r1, int r2);
int cgcompare_and_jump(int ASToperation, int r1, int r2, int label);
void cglabel(int l);
void cgjump(int l);

struct ASTnode *compound_statement(void);

void match(int t, char *what);
void semi(void);
void ident(void);
void rightbrace(void);
void leftbrace(void);
void rightparen(void);
void leftparen(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

int findglob(char *s);
int addglob(char *name);

void var_declaration(void);
