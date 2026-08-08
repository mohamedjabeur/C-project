#include <stdio.h>

#define ARR_LEN 5

/* ---------- Example 1: sum using array indexing ---------- */
int sum_with_indexing(int arr[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }
    return sum;
}

/* ---------- Example 2: same sum using pointer arithmetic ---------- */
int sum_with_pointers(int *arr, int len)
{
    int sum = 0;
    int *end = arr + len;

    while (arr < end)
    {
        sum += *arr;
        arr++;
    }
    return sum;
}

/* ---------- Example 3: sizeof "decay" demonstration ---------- */
void print_sizeof_inside_function(int arr[])
{
    /* Inside a function, arr is really a pointer, NOT the whole array */
    printf("sizeof(arr) inside function = %zu (this is sizeof(int*))\n",
           sizeof(arr));
}

int main(void)
{
    int numbers[ARR_LEN] = {10, 20, 30, 40, 50};

    printf("sizeof(numbers) inside main = %zu (this is the whole array: %d ints)\n",
           sizeof(numbers), ARR_LEN);

    print_sizeof_inside_function(numbers);

    printf("\n");

    printf("Sum using indexing:  %d\n", sum_with_indexing(numbers, ARR_LEN));
    printf("Sum using pointers:  %d\n", sum_with_pointers(numbers, ARR_LEN));

    printf("\n");

    /* Example 4: proving arr[i] and *(arr + i) are literally the same */
    for (int i = 0; i < ARR_LEN; i++)
    {
        printf("numbers[%d] = %d | *(numbers + %d) = %d | address = %p\n",
               i, numbers[i], i, *(numbers + i), (void *)&numbers[i]);
    }

    return 0;
}
