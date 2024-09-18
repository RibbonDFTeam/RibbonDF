#include <stdio.h>
#include "main.h"
#include "RibbonDF_config.h"
#include "securec.h"
#include <stdbool.h>

int main()
{
    char dest[100] = {0};
    char src[100]  = "Hello World!";

    bool test_memcpy = true;
    if (test_memcpy)
    {
        memcpy_s(dest, sizeof(dest), src, sizeof(src));
        memcpy_s(NULL, sizeof(dest), src, sizeof(src));
    }
    else
    {
        strcpy_s(dest, sizeof(dest), src);
    }
    printf("dest: %s\n", dest);

    return 0;
}
