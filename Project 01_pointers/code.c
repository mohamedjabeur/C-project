#include <stdio.h>
#include <string.h>

/* ---------- Example 1: pass-by-pointer to modify a value ---------- */
void change_value(int *value)
{
    *value = 100;
}

/* ---------- Example 2: reverse a string in-place using two pointers ---------- */
void reverse_string(char *str)
{
    char *start = str;
    char *end   = str + strlen(str) - 1;

    while (start < end)
    {
        char tmp = *start;
        *start = *end;
        *end   = tmp;
        start++;
        end--;
    }
}

/* ---------- Example 3: pointer-to-pointer + NULL check ---------- */
void safe_increment(int **pp)
{
    if (pp == NULL || *pp == NULL)
    {
        printf("safe_increment: invalid pointer, aborting\n");
        return;
    }
    (**pp)++;
}

int main(void)
{
    /* Example 1 */
    int x = 10;
    printf("Before: %d\n", x);
    change_value(&x);
    printf("After: %d\n", x);

    printf("\n");

    /* Example 2 */
    char msg[] = "embedded";
    printf("Before reverse: %s\n", msg);
    reverse_string(msg);
    printf("After reverse: %s\n", msg);

    printf("\n");

    /* Example 3 */
    int y = 5;
    int *p = &y;
    int **pp = &p;

    printf("Before increment: y = %d\n", y);
    safe_increment(pp);
    printf("After increment: y = %d\n", y);

    /* demonstrate the NULL check actually works */
    int *null_ptr = NULL;
    safe_increment(&null_ptr);

    return 0;
}
