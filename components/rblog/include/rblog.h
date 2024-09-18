#ifndef __RBLOG_H__
#define __RBLOG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define ESC_START     "\033["
#define ESC_END       "\033[0m"
#define COLOR_FATAL   "31;40;1m"
#define COLOR_ERROR   "31;40;1m"
#define COLOR_WARN    "33;40;1m"
#define COLOR_INFO    "32;40;1m"
#define COLOR_DEBUG   "34;40;1m"
#define COLOR_VERBOSE "37;40;1m"

typedef enum RBLOG_LVL
{
    RBLOG_LVL_FATAL   = 0,
    RBLOG_LVL_ERROR   = 1,
    RBLOG_LVL_WARN    = 2,
    RBLOG_LVL_INFO    = 3,
    RBLOG_LVL_DEBUG   = 4,
    RBLOG_LVL_VERBOSE = 5,
} RBLOG_LVL_E;

#define rblog_a(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_FATAL, ESC_START COLOR_FATAL _fmt_ ESC_END, ##args)
#define rblog_e(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_ERROR, ESC_START COLOR_ERROR _fmt_ ESC_END, ##args)
#define rblog_w(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_WARN, ESC_START COLOR_WARN _fmt_ ESC_END, ##args)
#define rblog_i(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_INFO, ESC_START COLOR_INFO _fmt_ ESC_END, ##args)
#define rblog_d(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_DEBUG, ESC_START COLOR_DEBUG _fmt_ ESC_END, ##args)
#define rblog_v(_tag_, _fmt_, args...) rblog_output(_tag_, RBLOG_LVL_VERBOSE, ESC_START COLOR_VERBOSE _fmt_ ESC_END, ##args)

int32_t rblog_init();
void rblog_fini(void);
void rblog_start(void);
void rblog_stop(void);

void rblog_output(const char *tag, RBLOG_LVL_E level, const char *_fmt_, ...);

#ifdef __cplusplus
}
#endif

#endif
