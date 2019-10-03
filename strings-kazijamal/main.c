#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    char s1[32] = "??W?";
    char s2[32] = "hello";
    char s3[32] = "goodbye";
    char mys1[32] = "??W?";
    char mys2[32] = "hello";
    char mys3[32] = "goodbye";

    printf("s1: [%s]\n", s1);
    printf("s2: [%s]\n", s2);
    printf("s3: [%s]\n", s3);

    printf("\n");
    printf("Testing strlen(s2):\n");
    printf("[standard]: %ld\n", strlen(s2));
    printf("[mine]: %d\n", mystrlen(mys2));

    printf("\n");
    printf("Testing strcpy(s1, s2):\n");
    printf("[standard]: [%s]\n", strcpy(s1, s2));
    printf("[mine]: [%s]\n", mystrcpy(mys1, mys2));

    printf("\n");
    printf("Testing strncpy(s1, s3, 3):\n");
    printf("[standard]: [%s]\n", strncpy(s1, s3, 3));
    printf("[mine]: [%s]\n", mystrncpy(mys1, mys3, 3));

    printf("\n");
    printf("Testing strcat(s1, s3):\n");
    printf("[standard]: [%s]\n", strcat(s1, s3));
    printf("[mine]: [%s]\n", mystrcat(mys1, mys3));

    printf("\n");
    printf("Testing strncat(s1, s2, 3):\n");
    printf("[standard]: [%s]\n", strncat(s1, s2, 3));
    printf("[mine]: [%s]\n", mystrncat(mys1, mys2, 3));

    printf("\n");
    printf("Comparing ab to abc:\n");
    printf("[standard]: [%d]\n", strcmp("ab", "abc"));
    printf("[mine]: [%d]\n", mystrcmp("ab","abc"));

    printf("\n");
    printf("Comparing abc to ab:\n");
    printf("[standard]: [%d]\n", strcmp("abc", "ab"));
    printf("[mine]: [%d]\n", mystrcmp("abc","ab"));

    printf("\n");
    printf("Comparing abc to abc:\n");
    printf("[standard]: [%d]\n", strcmp("abc", "abc"));
    printf("[mine]: [%d]\n", mystrcmp("abc","abc"));
    
    printf("\n");
    printf("Testing strchr(s1, \'l\'):\n");
    printf("[standard]: [%x]\n", strchr(s1, 'l'));
    printf("[mine]: [%x]\n", mystrchr(s1, 'l'));
    
    printf("\n");
    printf("Testing strchr(s2, \'h\'):\n");
    printf("[standard]: [%x]\n", strchr(s2, 'h'));
    printf("[mine]: [%x]\n", mystrchr(s2, 'h'));

    printf("\n");
    printf("Testing strchr(s3, \'o\'):\n");
    printf("[standard]: [%x]\n", strchr(s3, 'o'));
    printf("[mine]: [%x]\n", mystrchr(s3, 'o'));

    return 0;
}
