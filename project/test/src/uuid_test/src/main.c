#include <stdio.h>
#include "main.h"
#include "uuid4.h"

int main()
{
    char uuid[UUID4_LEN + 1];

    uuid4_init();
    uuid4_generate(uuid);

    printf("UUID4: %s\n", uuid);
    return 0;
}
