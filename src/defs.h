#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NSYMBOLS 1024 // Number of symbol table entry's
#define TEXTLEN 512 // Max length of identifier
#define NOREG -1 // When there is no register in AST generation

// Possible tokens
enum {
    T_EOF,
    T_PLUS, T_MINUS,
    T_STAR, T_SLASH,
    T_EQUALS, T_NOTEQUALS,
    T_LESSTHAN, T_GREATERTHAN, T_LESSEQUALS, T_GREATEREQUALS,
    T_INTLIT, T_SEMICOLON, T_ASSIGN, T_IDENT,
    T_LEFTBRACE, T_RIGHTBRACE, T_LEFTPAREN, T_RIGHTPAREN,
    // Keywords
    T_PRINT, T_INT, T_IF, T_ELSE, T_WHILE,
};

// Token structure
struct token {
    int token;
    int intvalue;
};

// AST node types
enum {
    A_ADD=1, A_SUBTRACT,
    A_MULTIPLY, A_DIVIDE,
    A_EQUALS, A_NOTEQUALS,
    A_LESSTHAN, A_GREATERTHAN, A_LESSEQUALS, A_GREATEREQUALS,
    A_INTLIT,
    A_IDENT, A_LVIDENT, A_ASSIGN,
    A_PRINT, A_GLUE, A_IF, A_WHILE,
};

// AST structure
struct ASTnode {
    int operation; // Enum from above
    struct ASTnode *left;
    struct ASTnode *mid;
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
