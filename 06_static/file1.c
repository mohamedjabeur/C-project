#include <stdio.h>

/* A static global variable — file scope only.
 * It CANNOT be accessed from any other .c file, even with extern. */
static int counter = 0;

/* A plain global variable — external linkage.
 * It CAN be accessed from other .c files using extern. */
int total = 100;

void increment_counter(void)
{
    /* counter keeps its value between calls because it's
     * declared outside any function (file scope), not because
     * it's "static" in this specific case — but see file2.c's
     * function for the OTHER meaning of static. */
    counter++;
    printf("counter (file-scope static) = %d\n", counter);
}
