#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sumSquares = 0;
    int squareSum = 0;
    int i = 0;

    for (i = 1; i <= 100; i++)
    {
        sumSquares += i * i;
        squareSum += i;
    }

    squareSum *= squareSum;

    int diff = squareSum - sumSquares;

    printf("%d\n", diff);

    return 0;
}
