#include <stdio.h>
#include <stdlib.h>

int *create_dangling_pointer(void)
{
    int local_value = 42;
    return &local_value;   /* BUG: returning address of a local variable */
    /* local_value is destroyed the moment this function returns —
     * the caller receives a pointer to memory that no longer belongs
     * to anything. */
}

int main(void)
{
    int *p = create_dangling_pointer();

    printf("Dereferencing a dangling pointer...\n");
    printf("*p = %d  <-- undefined behavior, this memory is no longer valid\n", *p);

    return 0;
}
