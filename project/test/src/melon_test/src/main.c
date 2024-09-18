#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "main.h"
#include "mln_thread_pool.h"
#include "RibbonDF_config.h"

static int dispatch_func(void *data)
{
    while (true) {

        char *msg = "hello world";
        mln_thread_pool_resource_add(msg);
        printf("dispatch_func: %s\n", msg);
        sleep(1);
    }
}

static int msg_process(void *data)
{
    printf("msg_process: %s\n", (char *)data);
}

static void free_handler(void *data)
{

}

int main()
{
    struct mln_thread_pool_attr tpattr;

    tpattr.main_data = NULL;
    tpattr.main_process_handler = dispatch_func;
    tpattr.child_process_handler = msg_process;
    tpattr.free_handler = free_handler;
    tpattr.cond_timeout = 10;
    tpattr.max = 10;
    tpattr.concurrency = 0;
    return mln_thread_pool_run(&tpattr);
}
