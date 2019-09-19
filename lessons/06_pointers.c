#include <stdio.h>
#include <stdlib.h>

int main()
{
    // int x = 5;
    // int *p = &x;
    // int y = *p + 10;
    // printf("x: %d, address of x: %p\n", x, &x);
    // printf("p: %p\n", p);
    // printf("y: %d, address of y: %p\n", y, &y);

    char c = 'b';
    int i = 7;
    long l = 7777;

    printf("c: %c address of c: hex = %p, dec = %lu\n", c, &c, &c);
    printf("i: %d address of i: hex = %p, dec = %lu\n", i, &i, &i);
    printf("l: %ld address of l: hex = %p, dec = %lu\n", l, &l, &l);

    char *p_c = &c;
    int *p_i = &i;
    long *p_l = &l;

    printf("pointer of c: %p\n", p_c);
    printf("pointer of i: %p\n", p_i);
    printf("pointer of l: %p\n", p_l);

    *p_c = 'c';
    *p_i = 8;
    *p_l = 8888;
    printf("c: %c\n", c);
    printf("i: %d\n", i);
    printf("l: %ld\n", l);

    char *p_i2 = &i;
    printf("2nd pointer of i: %p\n", p_i2);

    *p_i2 = 'f';
    printf("i: %d\n", i);

    return 0;
}