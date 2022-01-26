#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Possible tokens
enum { T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMICOLON, T_PRINT };

// Token structure
struct token {
    int token;
    int intvalue;
};

// AST node types
enum { A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT };

// AST structure
struct ASTnode {
    int operation; // Enum from above
    struct ASTnode *left;
    struct ASTnode *right;
    int intvalue;
};
