#include <stdio.h>
#include <stdlib.h>

/* ---------- Different memory segments, demonstrated by address ---------- */

int global_initialized = 42;      /* lives in .data segment (initialized globals) */
int global_uninitialized;         /* lives in .bss segment (uninitialized globals, zeroed at startup) */

void show_stack_growth(int depth)
{
    int local_var;   /* a new copy on the stack every call */

    if (depth == 0)
    {
        return;
    }

    printf("stack depth %d: local_var address = %p\n", depth, (void *)&local_var);
    show_stack_growth(depth - 1);
}

int main(void)
{
    printf("--- memory layout demo ---\n\n");

    /* Local variables live on the STACK */
    int stack_var = 10;

    /* Heap-allocated memory lives on the HEAP */
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 20;

    /* static local: NOT on the stack, lives in .data/.bss just like a global,
     * but its NAME is only visible inside this function */
    static int static_local = 30;

    printf("Address of global_initialized   (.data segment) = %p\n", (void *)&global_initialized);
    printf("Address of global_uninitialized (.bss segment)   = %p\n", (void *)&global_uninitialized);
    printf("Address of static_local         (.data segment)  = %p\n", (void *)&static_local);
    printf("Address of stack_var            (stack)          = %p\n", (void *)&stack_var);
    printf("Address of heap_var pointer itself (stack)        = %p\n", (void *)&heap_var);
    printf("Address heap_var POINTS TO (heap)                 = %p\n", (void *)heap_var);

    printf("\n");

    /* Demonstrate stack growth across recursive calls */
    printf("Recursive calls, watch the addresses change:\n");
    show_stack_growth(3);

    printf("\n");

    /* Demonstrate global_uninitialized is auto-zeroed (bss = "zero-initialized" by the runtime) */
    printf("global_uninitialized (never explicitly set) = %d  <-- auto-zeroed by the C runtime\n",
           global_uninitialized);

    free(heap_var);
    heap_var = NULL;

    return 0;
}
