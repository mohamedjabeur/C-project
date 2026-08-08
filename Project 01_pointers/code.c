#include <stdio.h>

void change_value(int *value)
{
    *value = 100;
}

int main(void)
{
    int x = 10;

    printf("Before: %d\n", x);

    change_value(&x);

    printf("After: %d\n", x);

    return 0;
}

