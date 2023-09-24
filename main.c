#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_demo1();
void string_demo2();
void test();

// gcc main.c && ./a.out
int main()
{
    test();
    return 0;
}

void string_demo1()
{
    char s1[32] = "helloworld";
    char s2[32] = {0};
    strcpy(s2, s1);
    printf("s2=%s\n", s2);
}

void string_demo2()
{
    char s1[32] = "hello";
    char s2[32] = "1111122222";
    strcpy(s2, s1);
    printf("s2=%s\n", s2);
}

void test() {
    char s1[] = "hello world";
    printf("s1=%s\n", s1);
    printf("s1 length=%lu\n", strlen(s1));

    char *s2 = (char *) malloc(sizeof(char) * (strlen(s1) + 1)); // \0 结尾
    if (s2 == NULL)
        return;

    int n = strlen(s1);
    for (int i = 0; i < n; i++) {
        s2[i] = s1[i];
    }
    s2[n] = '\0';
    printf("s2=%s\n", s2);
    free(s2);
}