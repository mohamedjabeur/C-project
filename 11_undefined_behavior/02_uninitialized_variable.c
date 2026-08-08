#include <stdio.h>

int main(void)
{
    int x;   /* uninitialized: contains garbage, whatever was already in memory */

    /* Reading x here is undefined behavior — the value is
     * unpredictable and can even change between runs/compilers. */
    if (x > 0)
    {
        printf("x was positive: %d\n", x);
    }
    else
    {
        printf("x was not positive: %d\n", x);
    }

    return 0;
}
