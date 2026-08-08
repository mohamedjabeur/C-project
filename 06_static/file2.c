#include <stdio.h>

/* This tells the compiler "total exists somewhere else,
 * link to it" — this WORKS because total has external linkage. */
extern int total;

/* Trying to do the same for counter would FAIL to link:
 * extern int counter;   // compiles, but linker error: undefined reference
 */

void modify_total(void)
{
    total += 50;
    printf("total (accessed via extern from file2.c) = %d\n", total);
}

/* ---------- static inside a function: persists across calls ---------- */
void call_tracker(void)
{
    static int call_count = 0;   /* initialized ONCE, keeps value between calls */
    call_count++;
    printf("call_tracker has been called %d time(s)\n", call_count);
}
