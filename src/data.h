#include <stdio.h>

#ifndef extern_
#define extern_ extern
#endif

#define TEXTLEN 512 // Max length of identifier
extern_ char text[TEXTLEN + 1];

extern_ int line;
extern_ int putback;
extern_ FILE *infile;
extern_ FILE *outfile;
extern_ struct token token;
