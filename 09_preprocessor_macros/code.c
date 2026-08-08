#include <stdio.h>

/* ---------- Example 1: object-like macro (constant) ---------- */
#define MAX_BUFFER_SIZE 64

/* ---------- Example 2: function-like macro — and its classic bug ---------- */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* ---------- Example 3: register-address style macro ----------
 * (simulated here since we're not on real hardware yet — this
 * mirrors exactly how register addresses are defined in STM32 code) */
#define GPIOA_BASE_ADDR   0x40020000U
#define GPIOA_ODR_OFFSET  0x14U
#define GPIOA_ODR         (GPIOA_BASE_ADDR + GPIOA_ODR_OFFSET)

/* ---------- Example 4: conditional compilation ---------- */
#define DEBUG 1

#if DEBUG
    #define LOG(msg) printf("[DEBUG] %s\n", msg)
#else
    #define LOG(msg)   /* compiles to nothing when DEBUG is off */
#endif

/* ---------- Example 5: multi-line macro using backslash continuation ---------- */
#define PRINT_POINT(x, y) \
    printf("Point: (%d, %d)\n", (x), (y))

int main(void)
{
    printf("--- preprocessor / macros demo ---\n\n");

    /* Example 1 */
    printf("MAX_BUFFER_SIZE = %d\n\n", MAX_BUFFER_SIZE);

    /* Example 2a: MIN/MAX work fine with simple values */
    printf("MIN(3, 7) = %d\n", MIN(3, 7));
    printf("MAX(3, 7) = %d\n\n", MAX(3, 7));

    /* Example 2b: THE CLASSIC MACRO BUG.
     * Because macros do pure TEXT SUBSTITUTION, not evaluation,
     * passing an expression with side effects breaks it. */
    int x = 5, y = 10;
    printf("Before buggy call: x=%d, y=%d\n", x, y);
    int result = MIN(x++, y++);
    /* This EXPANDS to: ((x++) < (y++) ? (x++) : (y++))
     * -> x++ (or y++) gets evaluated TWICE, not once! */
    printf("MIN(x++, y++) = %d\n", result);
    printf("After buggy call: x=%d, y=%d  <-- x or y incremented twice, not once!\n\n",
           x, y);

    /* Example 3: register-address style macro */
    printf("Simulated GPIOA_ODR address = 0x%X\n\n", GPIOA_ODR);

    /* Example 4: conditional compilation */
    LOG("this line only exists in the compiled binary if DEBUG == 1");

    /* Example 5 */
    PRINT_POINT(4, 9);

    return 0;
}
