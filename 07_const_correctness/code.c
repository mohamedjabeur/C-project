#include <stdio.h>

/* ---------- Example 1: const parameter — read-only access ---------- */
void print_array(const int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    /* Uncommenting the line below would cause a COMPILE error,
     * because arr is declared const int * — the function promises
     * not to modify what it points to.
     *
     * arr[0] = 999;   // error: assignment of read-only location
     */
}

int main(void)
{
    int values[3] = {1, 2, 3};
    int a = 10;
    int b = 20;

    printf("--- const correctness demo ---\n\n");

    print_array(values, 3);

    printf("\n");

    /* ---------- Example 2: const int *p  ----------
     * "pointer to a const int"
     * -> the VALUE pointed to cannot change through p.
     * -> the pointer itself CAN be reassigned to point elsewhere. */
    const int *p1 = &a;
    printf("p1 points to a = %d\n", *p1);
    /* *p1 = 99;      // ERROR: cannot modify value through p1 */
    p1 = &b;           /* OK: allowed to point somewhere else */
    printf("p1 now points to b = %d\n", *p1);

    printf("\n");

    /* ---------- Example 3: int *const p  ----------
     * "const pointer to an int"
     * -> the POINTER itself cannot change (always points to a)
     * -> the VALUE it points to CAN be modified. */
    int *const p2 = &a;
    printf("p2 points to a = %d\n", *p2);
    *p2 = 999;          /* OK: allowed to modify the value */
    printf("p2 now points to a (modified) = %d\n", *p2);
    /* p2 = &b;        // ERROR: cannot reassign p2 to point elsewhere */

    printf("\n");

    /* ---------- Example 4: const int *const p  ----------
     * "const pointer to a const int"
     * -> NEITHER the pointer NOR the value can change. Maximum safety. */
    const int *const p3 = &a;
    printf("p3 points to a = %d\n", *p3);
    /* *p3 = 5;        // ERROR: cannot modify value */
    /* p3 = &b;        // ERROR: cannot reassign pointer */

    return 0;
}
