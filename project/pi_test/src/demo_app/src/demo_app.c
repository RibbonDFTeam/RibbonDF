#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "demo_app.h"
#include "demo_component.h"
#include "rblog.h"

int main()
{
    printf("DEBUG:%d, TAG:%d\n", DEBUG, TAG);

    demo_component_init();

    rblog_init();

    rblog_d("DEMO", "Hello, world!");

    return 0;
}
