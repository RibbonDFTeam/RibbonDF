#include <stdio.h>
#include "gcov_test.h"


int test(int num)
{
    if (num % 2 == 0)
    {
        printf("num:%d is even\n", num);
    }
    else
    {
        printf("num:%d is odd\n", num);
    }

    return 0;
}
int main()
{
    test(1);
    test(2);

    return 0;
}
