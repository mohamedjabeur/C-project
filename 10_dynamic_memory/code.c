#include <stdio.h>
#include <stdlib.h>

/* ---------- A simple dynamic array that grows using realloc ---------- */
typedef struct
{
    int *data;
    int size;      /* how many elements are currently used */
    int capacity;  /* how many elements are currently allocated */
} DynamicArray;

void da_init(DynamicArray *da, int initial_capacity)
{
    da->data = (int *)malloc(sizeof(int) * initial_capacity);
    da->size = 0;
    da->capacity = initial_capacity;
}

void da_push(DynamicArray *da, int value)
{
    if (da->size == da->capacity)
    {
        int new_capacity = da->capacity * 2;
        int *new_data = (int *)realloc(da->data, sizeof(int) * new_capacity);

        if (new_data == NULL)
        {
            printf("realloc failed! aborting push.\n");
            return;
        }

        da->data = new_data;
        da->capacity = new_capacity;
        printf("(grew capacity to %d)\n", da->capacity);
    }

    da->data[da->size] = value;
    da->size++;
}

void da_print(DynamicArray *da)
{
    printf("[ ");
    for (int i = 0; i < da->size; i++)
    {
        printf("%d ", da->data[i]);
    }
    printf("] (size=%d, capacity=%d)\n", da->size, da->capacity);
}

void da_free(DynamicArray *da)
{
    free(da->data);
    da->data = NULL;   /* avoid leaving a dangling pointer behind */
    da->size = 0;
    da->capacity = 0;
}

int main(void)
{
    printf("--- dynamic memory demo ---\n\n");

    DynamicArray da;
    da_init(&da, 2);

    for (int i = 1; i <= 6; i++)
    {
        da_push(&da, i * 10);
        da_print(&da);
    }

    da_free(&da);

    /* ---------- Deliberate bug, commented out on purpose ----------
     * Uncomment this block and compile with:
     *   gcc -fsanitize=address,undefined code.c -o demo
     * to see the sanitizer catch a use-after-free at runtime.
     *
     * da_push(&da, 999);   // BUG: da.data was already freed above
     */

    return 0;
}
