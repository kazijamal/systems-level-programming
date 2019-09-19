#include <stdio.h>
#include <stdlib.h>

int isDivisible(int n)
{
    for (int d = 1; d <= 20; d++)
    {
        if (n % d != 0)
            return 0;
    }
    return 1;
}

int main()
{
    int isAns = 0;
    int n = 1;
    while (!isAns)
    {
        if (isDivisible(n))
            isAns = 1;
        else
            n++;
    }

    printf("%d\n", n);
}