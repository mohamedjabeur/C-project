#include <stdio.h>
#include <limits.h>

int main(void)
{
    int max = INT_MAX;
    printf("INT_MAX = %d\n", max);

    /* Signed integer overflow is UNDEFINED BEHAVIOR in C —
     * unlike unsigned overflow, which is well-defined (wraps around). */
    int overflowed = max + 1;

    printf("max + 1 = %d  <-- undefined behavior, NOT guaranteed to be INT_MIN\n",
           overflowed);

    return 0;
}
