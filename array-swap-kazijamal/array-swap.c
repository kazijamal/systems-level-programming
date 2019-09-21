#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // create an array large enough to store 10 ints
    int arr_size = 10;
    int arr[10];

    // populate the array with random values
    int i;
    srand(time(NULL));
    for (i = 0; i < arr_size; i++)
    {
        arr[i] = rand();
    }

    // set the last value in the array to 0
    arr[arr_size - 1] = 0;

    // print out the values in this array
    for (i = 0; i < arr_size; i++)
    {
        printf("array index %d: %d\n", i, arr[i]);
    }

    // create a separate array large enough to store 10 ints
    int arr2[10];

    // populate the second array with the values in the first but in reverse order
    int *arr_p = arr;
    int *arr2_p = arr2;
    int x, y;
    for (int x = 0, y = arr_size - 1; x < arr_size; x++, y--)
    {
        *(arr2_p + y) = *(arr_p + x);
    }

    // print out the values in the second array
    printf("\n");
    for (i = 0; i < arr_size; i++)
    {
        printf("second array index %d: %d\n", i, *(arr2_p + i));
    }

    return 0;
}