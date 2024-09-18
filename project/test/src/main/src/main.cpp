#include <stdio.h>
#include "main.h"
#include "RibbonDF_config.h"
#include <string>

int main()
{
    std::string url("://");
    std::string server_name("test");
    url         += server_name;
    server_name += "_server";

    printf("server_name: %s\n", server_name.c_str());
    return 0;
}
