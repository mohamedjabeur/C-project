#include <stdio.h>

/* ---------- Example 1: basic function pointer ---------- */
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

/* ---------- Example 2: array of function pointers, selected by enum ---------- */
typedef enum
{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_COUNT
} Operation;

/* function pointer type: takes (int,int), returns int */
typedef int (*MathFunc)(int, int);

/* ---------- Example 3: function pointer as a callback argument ---------- */
void for_each(int *arr, int len, void (*callback)(int))
{
    for (int i = 0; i < len; i++)
    {
        callback(arr[i]);
    }
}

void print_value(int v)
{
    printf("value = %d\n", v);
}

void print_squared(int v)
{
    printf("squared = %d\n", v * v);
}

/* ---------- Example 4: custom comparator, like qsort() uses internally ---------- */
int ascending(int a, int b)  { return a - b; }
int descending(int a, int b) { return b - a; }

void bubble_sort(int *arr, int len, int (*compare)(int, int))
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (compare(arr[j], arr[j + 1]) > 0)
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    printf("--- function pointers demo ---\n\n");

    /* Example 1 + 2: array of function pointers, chosen by enum index */
    MathFunc operations[OP_COUNT] = { add, sub, mul };
    const char *names[OP_COUNT] = { "ADD", "SUB", "MUL" };

    for (int i = 0; i < OP_COUNT; i++)
    {
        printf("%s(6, 3) = %d\n", names[i], operations[i](6, 3));
    }

    printf("\n");

    /* Example 3: passing behavior into a function via callback */
    int nums[4] = {1, 2, 3, 4};

    printf("Using print_value callback:\n");
    for_each(nums, 4, print_value);

    printf("Using print_squared callback:\n");
    for_each(nums, 4, print_squared);

    printf("\n");

    /* Example 4: sort direction chosen at runtime via function pointer */
    int data[5] = {5, 2, 8, 1, 9};

    printf("Original:   "); print_array(data, 5);

    bubble_sort(data, 5, ascending);
    printf("Ascending:  "); print_array(data, 5);

    bubble_sort(data, 5, descending);
    printf("Descending: "); print_array(data, 5);

    return 0;
}
