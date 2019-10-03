#include <stdio.h>
#include <stdlib.h>

int mystrlen(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

char *mystrcpy(char *dest, char *src)
{
    int destlen = mystrlen(dest);
    int srclen = mystrlen(src);
    int i;
    for (i = 0; i < destlen+srclen; i++) {
      dest[i] = src[i];
    }
    return dest;
}

char *mystrncpy(char *dest, char *src, size_t n)
{
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *mystrcat(char *dest, char *src)
{
    int destlen = mystrlen(dest);
    int srclen = mystrlen(src);
    int i;
    for (i = 0; i < srclen; i++)
    {
        dest[destlen + i] = src[i];
    }
    return dest;
}

char *mystrncat(char *dest, char *src, size_t n)
{
    int destlen = mystrlen(dest);
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[destlen + i] = src[i];
    }
    dest[destlen + i] = '\0';
    return dest;
}

int mystrcmp(char *s1, char *s2)
{
    int i, j = 0;
    while (s1[i] != '\0')
        i++; //length of s1
    while (s2[j] != '\0')
        j++; //length of s2
    if (i == 0 && j == 0)
    {
        return 0; //both empty or "" strings
    }
    else
    {                                 //nonempty strings
        int counter = i >= j ? j : i; //counter is the least length of either s1 or s2
        int k;
        for (k = 0; k < counter; k++)
        {
            if ((int)s1[k] == (int)s2[k])
                continue;
            int s1ASCII = s1[k]; //kth letter is not equal to each other
            int s2ASCII = s2[k];
            return s1ASCII - s2ASCII;
        }
        //strings are equal up to index counter - 1
        return i == j ? 0 : i > j ? (int)s1[j] : (int)-s2[i];
    }
}

char *mystrchr(char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return &s[i];
        }
        i++;
    }
    return NULL;
}

// char *mystrstr(char *haystack, char *needle) //given that haystack length > needle length
// {
//     int haystackLength = 0;
//     while (haystack[haystackLength] != '\0')
//     {
//         haystackLength++;
//     }
//     int needleLength = 0;
//     while (needle[needleLength] != '\0')
//     {
//         needleLength++;
//     }
//     int i;
//     for (i = 0; i <= haystackLength; i++) {
        
//     }
// }
