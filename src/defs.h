#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NSYMBOLS 1024 // Number of symbol table entry's
#define TEXTLEN 512 // Max length of identifier

// Possible tokens
enum {
    T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMICOLON, T_EQUALS,
    T_IDENT,
    // Keywords
    T_PRINT, T_INT
};

// Token structure
struct token {
    int token;
    int intvalue;
};

// AST node types
enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT,
    A_IDENT, A_LVIDENT, A_ASSIGN,
};

// AST structure
struct ASTnode {
    int operation; // Enum from above
    struct ASTnode *left;
    struct ASTnode *right;
    union {
        int intvalue; // Integer value of intlit
        int id; // Symbol slot for identifier
    } v;
};

// Symbol table
struct symboltable {
    char *name;
};
