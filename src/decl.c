#include "defs.h"
#include "data.h"
#include "decl.h"

// Parse variable declaration
void
var_declaration(void)
{
    // Make sure there is an int, followed by identifier, follow by semicolon
    // Add it to the globs
    match(T_INT, "int");
    ident();
    addglob(text);
    genglobsym(text);
    semi();
}
