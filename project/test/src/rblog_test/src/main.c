#include <stdio.h>
#include "main.h"
#include "rblog.h"


#define TAG ("RBTEST")

int main()
{
    printf("RibbonDF system name: %s\n", CONFIG_SYSTEM_NAME);
    printf("RibbonDF version: V%d.%d.%d\n", CONFIG_PROJECT_MAJOR_VERSION, CONFIG_PROJECT_MINOR_VERSION, CONFIG_PROJECT_PATCH_VERSION);
    rblog_init();
    rblog_start();

    rblog_a(TAG, "hello rblog!, %d", __LINE__);
    rblog_e(TAG, "hello rblog!, %d", __LINE__);
    rblog_w(TAG, "hello rblog!, %d", __LINE__);
    rblog_i(TAG, "hello rblog!, %d", __LINE__);
    rblog_d(TAG, "hello rblog!, %d", __LINE__);
    rblog_v(TAG, "hello rblog!, %d", __LINE__);

    rblog_stop();
    rblog_fini();
    return 0;
}