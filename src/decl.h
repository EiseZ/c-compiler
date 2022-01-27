int scan(struct token *t);

struct ASTnode *mkastnode(int operation, struct ASTnode *left,
    struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int operation, int intvalue);
struct ASTnode *mkastunary(int operation, struct ASTnode *left, int intvalue);

struct ASTnode *binexpr(int ptp);

int interpretAST(struct ASTnode *n);

void gencode(struct ASTnode *n);
int genAST(struct ASTnode *n, int reg);
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

void statements(void);

void match(int t, char *what);
void semi(void);
void ident(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

int findglob(char *s);
int addglob(char *name);

void var_declaration(void);
