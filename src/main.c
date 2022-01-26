#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"

#include <errno.h>

static void
init()
{
    line = 1;
    putback = '\n';
}

// List of printable tokens
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

void
main(int argc, char *argv[])
{
    init();

    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    if ((outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Unable to open out.asm: %s\n", strerror(errno));
        exit(1);
    }

    scan(&token); // Get first token
    genpreamble();
    statements(); // Parse statements
    genpostamble();

    fclose(outfile);
    exit(0);
}
