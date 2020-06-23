#include <stdio.h>
#include <stdlib.h>

float avg(int *arr, int arr_len)
{
    float sum = 0.0;
    int i;
    for (i = 0; i < arr_len; i++)
    {
        sum += arr[i];
    }
    return sum / arr_len;
}

void arrcp(int *arr1, int *arr2, int arr_len)
{
    int i;
    for (i = 0; i < arr_len; i++)
    {
        arr2[i] = arr1[i];
    }
}

int lenstr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int main()
{
    // testing avg
    int i;
    int arr_len = 10;
    int arr[arr_len];
    for (i = 0; i < arr_len; i++)
    {
        arr[i] = i + 1;
    }
    printf("average: %f\n", avg(arr, arr_len));

    // testing arrcp
    printf("\n");
    int arr2[arr_len];
    for (i = 0; i < arr_len; i++)
    {
        printf("arr2 index %d before copy: %d\n", i, arr2[i]);
    }
    arrcp(arr, arr2, arr_len);
    printf("\n");
    for (i = 0; i < arr_len; i++)
    {
        printf("arr2 index %d after copy: %d\n", i, arr2[i]);
    }

    // testing strlen
    printf("\n");
    char str[] = "testring";
    printf("string: %s\n", str);
    int str_len = lenstr(str);
    printf("string length: %d\n", str_len);

    return 0;
}