#include "defs.h"
#include "data.h"
#include "decl.h"

// Names of registers, and if they're free
static int freereg[4];
static char *reglist[4] = {"%r8", "%r9", "%r10", "%r11"};

// Set all registers as available
void
freeallregisters(void)
{
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// Give next free register
// Exit if none are free
static int
allocregister(void)
{
    for (int i = 0; i < 4; i++) {
        if (freereg[i]) {
            freereg[i] = 0;
            return (i);
        }
    }
    fprintf(stderr, "Out of registers\n");
    exit(1);
}

// Free a register
static void
freeregister(int reg)
{
    if (freereg[reg] != 0) {
        fprintf(stderr, "Trying to free already free register %d\n", reg);
        exit(1);
    }
    freereg[reg] = 1;
}

// Allocate register and move value into it
int
cgload(int value)
{
    // Get new register
    int r = allocregister();

    // Generate code
    fprintf(outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);
    return (r);
}

// Add value of register 1 and register 2, value is stored in register 2
int
cgadd(int r1, int r2)
{
    fprintf(outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
    freeregister(r1);
    return (r2);
}

// Multiply value of register 1 and 2, value is stored in register 2
int
cgmul(int r1, int r2)
{
    fprintf(outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
    freeregister(r1);
    return (r2);
}

// Subtract value of register 2 from 1, value is stored in register 1
int
cgsub(int r1, int r2)
{
    fprintf(outfile, "\tsubq\t%s, %s\n", reglist[r1], reglist[r2]);
    freeregister(r2);
    return (r1);
}

// Devide value of register 1 by 2, value is stored in register 1
int
cgdiv(int r1, int r2)
{
    // Value from register 1 into rax
    fprintf(outfile, "\tmovq\t%s, %%rax\n", reglist[r1]);
    // Extend rax to 8 bytes
    fprintf(outfile, "\tcqo\n");
    // Divide rax by register 2
    fprintf(outfile, "\tidivq\t%s\n", reglist[r2]);
    // Move result from rax back into r1
    fprintf(outfile, "\tmovq\t%%rax, %s\n", reglist[r1]);
    freeregister(r2);
    return (r1);
}

// Call printfuction from preamble to print register
void
cgprintint(int r)
{
    fprintf(outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
    fprintf(outfile, "\tcall\tprintint\n");
    freeregister(r);
}

// Print out setup assembly
void
cgpreamble(void)
{
    freeallregisters();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n",
    outfile);
}

void
cgpostamble(void)
{
    fputs(
        "\tmovl	$0, %eax\n"
        "\tpopq	%rbp\n"
        "\tret\n",
    outfile);
}
