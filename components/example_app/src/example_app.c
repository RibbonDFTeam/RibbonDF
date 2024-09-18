#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "example_app.h"
#include "example_component.h"

int main()
{
    printf("DEBUG:%d, TAG:%d\n", DEBUG, TAG);

    example_component_init();

    return 0;
}
