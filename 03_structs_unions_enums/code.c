#include <stdio.h>
#include <string.h>

/* ---------- Example 1: struct — grouping related data ---------- */
struct Point
{
    int x;
    int y;
};

/* ---------- Example 2: enum — named constants instead of magic numbers ---------- */
enum Color
{
    RED,    /* 0 */
    GREEN,  /* 1 */
    BLUE    /* 2 */
};

/* ---------- Example 3: union — same memory, different interpretations ---------- */
union RawValue
{
    float f;
    unsigned char bytes[4];
};

/* ---------- Example 4: struct combined with enum (common embedded pattern) ---------- */
struct Led
{
    enum Color color;
    struct Point position;
    int is_on;
};

void print_point(struct Point p)
{
    printf("Point(x=%d, y=%d)\n", p.x, p.y);
}

const char *color_to_string(enum Color c)
{
    switch (c)
    {
        case RED:   return "RED";
        case GREEN: return "GREEN";
        case BLUE:  return "BLUE";
        default:    return "UNKNOWN";
    }
}

int main(void)
{
    /* Example 1: struct */
    struct Point p1 = {10, 20};
    print_point(p1);
    printf("sizeof(struct Point) = %zu bytes\n", sizeof(struct Point));

    printf("\n");

    /* Example 2: enum */
    enum Color c = GREEN;
    printf("Color value = %d (%s)\n", c, color_to_string(c));

    printf("\n");

    /* Example 3: union — type punning, reading raw bytes of a float */
    union RawValue rv;
    rv.f = 3.14f;

    printf("rv.f as float = %f\n", rv.f);
    printf("rv.bytes as raw memory = ");
    for (int i = 0; i < 4; i++)
    {
        printf("%02X ", rv.bytes[i]);
    }
    printf("\n");
    printf("sizeof(union RawValue) = %zu bytes (union takes the size of its LARGEST member)\n",
           sizeof(union RawValue));

    printf("\n");

    /* Example 4: struct + enum combined, like a peripheral config object */
    struct Led led1 = { .color = RED, .position = {0, 0}, .is_on = 1 };
    printf("LED color = %s, position = (%d,%d), state = %s\n",
           color_to_string(led1.color),
           led1.position.x, led1.position.y,
           led1.is_on ? "ON" : "OFF");

    return 0;
}
