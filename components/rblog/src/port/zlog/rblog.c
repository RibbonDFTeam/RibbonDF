#include "rblog.h"

#include "zlog.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "rblog_private.h"

int32_t rblog_init()
{
    if (0 == strlen(CONFIG_MODULE_RBLOG_ZLOG_CFG_FILE_PATH))
    {
        return zlog_init(NULL);
    }
    else
    {
        return zlog_init(CONFIG_MODULE_RBLOG_ZLOG_CFG_FILE_PATH);
    }
}

void rblog_fini(void)
{
    zlog_fini();
}

void rblog_start(void)
{
}
void rblog_stop(void)
{
}

void rblog_output(const char *tag, RBLOG_LVL_E level, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    switch (level)
    {
    case RBLOG_LVL_FATAL:
        vzlog_fatal(zlog_get_category(tag), fmt, args);
        break;
    case RBLOG_LVL_ERROR:
        vzlog_error(zlog_get_category(tag), fmt, args);
        break;
    case RBLOG_LVL_WARN:
        vzlog_warn(zlog_get_category(tag), fmt, args);
        break;
    case RBLOG_LVL_INFO:
        vzlog_notice(zlog_get_category(tag), fmt, args);
        break;
    case RBLOG_LVL_DEBUG:
        vzlog_info(zlog_get_category(tag), fmt, args);
        break;
    case RBLOG_LVL_VERBOSE:
        vzlog_debug(zlog_get_category(tag), fmt, args);
        break;
    default:
        zlog_fatal(zlog_get_category(RBLOG_TAG), "log level:%d invalid", level);
    }
    va_end(args);
}
