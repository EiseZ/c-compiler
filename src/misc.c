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
        printf("%s expected on line %d\n", what, line);
        exit(1);
    }
}

// Match the semicolon and get next statement
void
semi(void)
{
    match(T_SEMICOLON, ";");
}
