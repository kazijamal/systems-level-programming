#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *s = "hello";
    char s1[10] = "hello";
    printf("s points to: %p\n", s);
    printf("s1 points to: %p\n", s1);
    printf("address of \"hello\": %p\n", &"hello");

    // strcpy
    printf("\n");
    char og[] = "original";
    char cp[] = "";
    strcpy(cp, og);
    printf("original: %s\n", og);
    printf("copy: %s\n", cp);

    // strcat
    printf("\n");
    char str1[] = "first";
    char str2[] = "second";
    printf("string 1: %s\n", str1);
    printf("string 2: %s\n", str2);
    strcat(str1, str2);
    printf("concatenated: %s\n", str1);

    // strcmp
    printf("\n");
    char first[] = "first";
    char second[] = "second";
    printf("string 1: %s\n", first);
    printf("string 2: %s\n", second);
    printf("string 1 compared to string 2: %d\n", strcmp(first, second));

    // strchr
    printf("\n");
    char string[] = "find";
    int c = 110;
    char *find = strchr(string, c);
    printf("string: %s\n", string);
    printf("character: %c\n", c);
    printf("locate %c in %s: found %c at memory address %p\n", c, string, *find, find);

    return 0;
}