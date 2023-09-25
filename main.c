#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_demo1();
void string_demo2();
void string_demo3();
void string_demo4();
void string_demo5();
void string_demo6();
void test();

// gcc main.c && ./a.out
int main()
{
    string_demo6();
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

    char s3[32] = "1111122222";
    printf("s1 length=%lu\n", strlen(s1));
    strncpy(s3, s1, 5);
    printf("s3=%s\n", s3);
}

void string_demo3()
{
    char s1[32] = "hello";
    char s2[32] = "world";
    strcat(s1, s2);        // 把s2拼接到s1后面
    printf("s1=%s\n", s1); // helloworld
    strncat(s1, s2, 3);
    printf("s1=%s\n", s1); // helloworldwor
}

void string_demo4()
{
    char s1[32] = "hello";
    char s2[32] = "world";
    int r = strcmp(s1, s2); // 比较第一位不相同字符的ASCII码差值
    printf("strcmp result:%d\n", r);
    // strncmp 仅比较前 N 个字符长度
}

void string_demo5()
{
    char s1[32] = "helloworld";
    printf("%s\n", strchr(s1, 'l'));
    printf("%s\n", strrchr(s1, 'l'));
}

void string_demo6()
{
    char s1[] = "helloworld"; // 数组名是指针常量
    // s1++; 数组名不能修改
    s1[0]++; // 数组内容可以修改
    printf("%s\n", s1); // ielloworld

    char *s2 = "helloworld"; // 字符指针存放在栈空间,字符指针指向的内容存放在只读数据区
    s2++;
    // s2[0]++; bus error 只读数据区不能修改
    printf("%s\n", s2); // elloworld
}

void test()
{
    char s1[] = "hello world";
    printf("s1=%s\n", s1);
    printf("s1 length=%lu\n", strlen(s1));

    char *s2 = (char *)malloc(sizeof(char) * (strlen(s1) + 1)); // \0 结尾
    if (s2 == NULL)
        return;

    int n = strlen(s1);
    for (int i = 0; i < n; i++)
    {
        s2[i] = s1[i];
    }
    s2[n] = '\0';
    printf("s2=%s\n", s2);
    free(s2);
}