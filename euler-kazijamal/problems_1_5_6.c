#include <stdio.h>
#include <stdlib.h>

// function declarations
int problem1();
int isDivisible();
int isDivisiblev2();
int problem5();
int problem5v2();
int problem6();

// returns the sum of all the multiples of 3 or 5 below 100
int problem1()
{
    int i = 0;
    int sum = 0;
    for (i = 1; i < 1000; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum += i;
        }
    }
    return sum;
}

// returns 1 if a number is evenly divisible by all of the numbers from 1 to 20, 0 otherwise
int isDivisible(int n)
{
    int d = 0;
    for (d = 1; d <= 20; d++)
    {
        if (n % d != 0)
            return 0;
    }
    return 1;
}
int isDivisiblev2(int n)
{
    if (n % 20)
        return 0;
    if (n % 19)
        return 0;
    if (n % 18)
        return 0;
    if (n % 17)
        return 0;
    if (n % 16)
        return 0;
    if (n % 14)
        return 0;
    if (n % 13)
        return 0;
    if (n % 11)
        return 0;
    return 1;
}

// returns the smallest positive number that is evenly divisble by all of the numbers from 1 to 20
int problem5()
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
    return n;
}
int problem5v2()
{
    int isAns = 0;
    int n = 1;
    while (!isAns)
    {
        if (isDivisiblev2(n))
            isAns = 1;
        else
            n++;
    }
    return n;
}

// returns the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum
int problem6()
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
    return diff;
}

int main()
{
    printf("Problem 1 answer: %d\n", problem1());
    printf("Problem 5 method 1 answer: %d\n", problem5());
    printf("Problem 5 method 2 answer: %d\n", problem5v2());
    printf("Problem 6 answer: %d\n", problem6());
    return 0;
}
