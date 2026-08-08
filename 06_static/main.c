#include <stdio.h>

extern int total;              /* defined in file1.c */
void increment_counter(void);  /* defined in file1.c */
void modify_total(void);       /* defined in file2.c */
void call_tracker(void);       /* defined in file2.c */

int main(void)
{
    printf("--- static vs global demo ---\n\n");

    increment_counter();
    increment_counter();
    increment_counter();

    printf("\n");

    printf("total before = %d\n", total);
    modify_total();
    printf("total after (from main) = %d\n", total);

    printf("\n");

    /* demonstrate function-local static persisting across calls */
    call_tracker();
    call_tracker();
    call_tracker();

    return 0;
}
