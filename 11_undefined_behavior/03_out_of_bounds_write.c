#include <stdio.h>

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    printf("Writing to arr[5], one past the end of a 5-element array...\n");

    /* Valid indices are 0..4. Index 5 is OUT OF BOUNDS.
     * The compiler will NOT stop you — it silently corrupts
     * whatever memory happens to sit right after the array. */
    arr[5] = 999;

    printf("Program did not crash immediately, but memory is now corrupted.\n");

    return 0;
}
