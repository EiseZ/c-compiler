#include <stdio.h>

#ifndef extern_
#define extern_ extern
#endif

extern_ int line;
extern_ int putback;
extern_ FILE *infile;
extern_ FILE *outfile;
extern_ struct token token;
