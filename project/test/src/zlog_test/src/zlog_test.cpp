
#include "zlog.h"

#include <cstdio>

#define zlog_i(TAG, fmt, ...) \
    do                        \
    {                         \
    } while (0)
int main()
{
    zlog_init(NULL);

    zlog_category_t *category = zlog_get_category("ZLOG_TEST");
    zlog_info(category, "hello, zlog, CONFIG_SYSTEM_NAME:%s", CONFIG_SYSTEM_NAME);
    zlog_fini();
    return 0;
}
