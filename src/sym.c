#include "defs.h"
#include "data.h"
#include "decl.h"

static int globs = 0; // Position of next free global symbol

// Find symbol s in global symbols
// If it's not in there, return -1
int
findglob(char *s)
{
    int i;
    for (i = 0; i < globs; i++) {
        if (*s == *gsym[i].name && !strcmp(s, gsym[i].name)) {
            return (i);
        }
    }
    return (-1);
}

// Get position of new global symbol slot
// Exit if none are left
static int
newglob(void)
{
    int p;
    if ((p = globs++) >= NSYMBOLS) {
        fatal("To many global symbols");
    }
    return (p);
}

// Add symbol to global symbol table
// Exit if we are out of positions
int
addglob(char *name)
{
    int y;

    // Return existing position if it's already in there
    if ((y = findglob(name)) != -1) {
        return (y);
    }

    // Otherwise get new slot en return position
    y = newglob();
    gsym[y].name = strdup(name);
    return (y);
}
