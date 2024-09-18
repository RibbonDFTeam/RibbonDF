#include <stdio.h>
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include "RibbonDF_config.h"

#define WRAP_FUNC

#ifdef CONFIG_LIBC_SUBSTITUTE_WRAP
extern void *__real_malloc(size_t size);
extern void __real_free(void *ptr);
void *__wrap_malloc(size_t size)
{
    printf("Malloc called with size %zu\n", size);
    return __real_malloc(size);
}

void __wrap_free(void *ptr)
{
    printf("Free called on %p\n", ptr);
    __real_free(ptr);
}
#endif

#ifdef CONFIG_LIBC_SUBSTITUTE_ALIAS
#include <stdarg.h>
extern void *__libc_malloc(size_t size);

// printf("");
int my_printf(const char * __restrict __format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, __format);
    int len = vsnprintf(buffer, sizeof(buffer), __format, args);
    va_end(args);
    write(STDOUT_FILENO, buffer, len);
    return len;
}

void *my_malloc(size_t size)
{
    printf("malloc %lu bytes\n", size);

    return __libc_malloc(size);
}
int printf(const char * __restrict __format, ...) __attribute__((alias("my_printf")));
void *malloc(size_t size) __attribute__((alias("my_malloc")));

#endif

int main()
{
    void *buf = malloc(10);

    free(buf);
    return 0;
}
