#include "defs.h"
#include "data.h"
#include "decl.h"

// Make sure the current token is token t and get the next token
// Otherwise return error
void
match(int t, char *what)
{
    if (token.token == t) {
        scan(&token);
    } else {
        fatals("Expected", what);
    }
}

// Match the semicolon and get next statement
void
semi(void)
{
    match(T_SEMICOLON, ";");
}

// Match identifier
void
ident(void)
{
    match(T_IDENT, "identifier");
}

void
rightbrace(void)
{
    match(T_RIGHTBRACE, "}");
}

void
leftbrace(void)
{
    match(T_LEFTBRACE, "{");
}

void
rightparen(void)
{
    match(T_RIGHTPAREN, ")");
}

void
leftparen(void)
{
    match(T_LEFTPAREN, "(");
}

// Fatal messages
void fatal(char *s) {
  fprintf(stderr, "%s on line %d\n", s, line);
  exit(1);
}

void fatals(char *s1, char *s2) {
  fprintf(stderr, "%s: %s on line %d\n", s1, s2, line);
  exit(1);
}

void fatald(char *s, int d) {
  fprintf(stderr, "%s: %d on line %d\n", s, d, line);
  exit(1);
}

void fatalc(char *s, int c) {
  fprintf(stderr, "%s: %c on line %d\n", s, c, line);
  exit(1);
}
