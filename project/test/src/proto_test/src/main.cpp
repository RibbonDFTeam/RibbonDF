#include <cstdio>
#include "main.h"

#include "Person.pb.h"
#include "cJSON.h"


int main()
{
    printf("RibbonDF system name: %s\n", CONFIG_SYSTEM_NAME);
    printf("RibbonDF version: V%d.%d.%d\n", CONFIG_PROJECT_MAJOR_VERSION, CONFIG_PROJECT_MINOR_VERSION, CONFIG_PROJECT_PATCH_VERSION);

    cJSON_CreateObject();
    proto_test::Person person;
    person.set_name("Alice");

    printf("Hello, %s!\n", person.name().c_str());
    return 0;
}