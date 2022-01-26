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

    if ((outfile = fopen("out.asm", "w")) == NULL) {
        fprintf(stderr, "Unable to open out.asm: %s\n", strerror(errno));
        exit(1);
    }

    struct ASTnode *n;
    scan(&token); // Get first token
    n = binexpr(0);
    printf("%d\n", interpretAST(n));
    gencode(n);

    fclose(outfile);
    exit(0);
}
