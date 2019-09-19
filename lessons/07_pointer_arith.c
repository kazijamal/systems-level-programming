#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int i = 261;
    int *p = &i;
    char *c = &i;

    printf("p: %p points to: %d\n", p, *p);
    printf("c: %p points to: %d\n", c, *c);

    printf("i dec: %u, hex: %#x\n", i, i);

    printf("printing each individual byte of i\n");
    int b;
    for (b = 0; b < 4; b++)
    {
        printf("byte %d of i: %hhu\n", b + 1, *c);
        c++;
    }

    printf("incrementing each byte of i by 1\n");
    c = &i;
    for (b = 0; b < 4; b++)
    {
        *c += 1;
        printf("i dec: %u, hex: %#x\n", i, i);
        c++;
    }

    printf("incrementing each byte of i by 16\n");
    c = &i;
    for (b = 0; b < 4; b++)
    {
        *c += 16;
        printf("i dec: %u, hex: %#x\n", i, i);
        c++;
    }

    return 0;
}