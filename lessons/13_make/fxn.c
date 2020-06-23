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