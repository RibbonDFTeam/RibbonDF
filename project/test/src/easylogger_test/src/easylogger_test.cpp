#include <cstdio>
#include <stdio.h>
#include <cstdint>
#include <string>
#include "elog.h"
#include "elog_cfg.h"


int main()
{
    printf("%s start\n", __FUNCTION__);
    // setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();

    elog_a("EASY_LOG", "Easylog init");
    elog_e("EASY_LOG", "Easylog init");
    elog_w("EASY_LOG", "Easylog init");
    elog_i("EASY_LOG", "Easylog init");
    elog_d("EASY_LOG", "Easylog init");
    elog_v("EASY_LOG", "Easylog init");
    return 0;
}
