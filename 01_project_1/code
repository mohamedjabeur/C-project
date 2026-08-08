
#include <stdint.h>

/* Memory-mapped peripheral addresses (STM32F4 series example) */
#define RCC_BASE        (0x40023800UL)
#define GPIOC_BASE      (0x40020800UL)

/* Register pointers */
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE   + 0x30UL))
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00UL))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14UL))

/* Bit definitions */
#define RCC_GPIOCEN     (1U << 2)   /* Enable clock for Port C */
#define GPIO_PIN_13     (1U << 13)  /* Pin 13 bit mask */

static void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {
    /* 1. Enable Clock for GPIOC */
    RCC_AHB1ENR |= RCC_GPIOCEN;

    /* 2. Configure PC13 as General Purpose Output Mode (01) */
    GPIOC_MODER &= ~(3U << (13 * 2)); /* Clear mode bits for PC13 */
    GPIOC_MODER |=  (1U << (13 * 2)); /* Set bit 26 to 1 (Output mode) */

    while (1) {
        /* 3. Toggle PC13 output register */
        GPIOC_ODR ^= GPIO_PIN_13;

        /* 4. Software delay */
        delay(500000);
    }

    return 0;
}
