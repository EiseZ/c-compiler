#include "defs.h"
#include "data.h"
#include "decl.h"

// Get next char from input file
static int
next(void)
{
    int c;

    if (putback) {
        c = putback;
        putback = 0;
        return c;
    }

    c = fgetc(infile);
    if (c == '\n')
        line++;
    return c;
}

// Putback unwanted char
static void
goback(int c)
{
    putback = c;
}

// Skip not needed chars, such as whitespace, newline etc
static int
skip(void)
{
    int c;

    c = next();
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f') {
        c = next();
    }
    return c;
}

// Check if char at pos is in given string
// If so return pos of char in string, else return -1
static int
chrpos(char *s, int c)
{
    char *p;

    p = strchr(s, c);
    return (p ? p - s : -1);
}

// Return value of int at c
static int
scanint(int c)
{
    int k, val = 0;

    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    // Go back 1 char because we reached non int
    goback(c);
    return val;
}

// Scan input file
// Return 1 of token is valid, 0 if not
int
scan(struct token *t)
{
    int c;

    // Skip whitespace
    c = skip();

    // Determin what token it is
    switch (c) {
    case EOF:
        t->token = T_EOF;
        return 0;
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c)) {
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        }

        printf("Invalid character %c on line %d\n", c, line);
        exit(1);
    }

    return (1);
}
