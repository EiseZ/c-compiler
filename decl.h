int scan(struct token *t);
struct ASTnode *mkastnode(int operation, struct ASTnode *left,
                          struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int operation, int intvalue);
struct ASTnode *mkastunary(int operation, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int ptp);
int interpretAST(struct ASTnode *n);
