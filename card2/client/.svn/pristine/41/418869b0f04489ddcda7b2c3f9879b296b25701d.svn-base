#ifndef _LOG_H_
#define _LOG_H_

#define HLOG_LEVEL_NONE               0
#define HLOG_LEVEL_ERROR             (HLOG_LEVEL_NONE | 0x01)
#define HLOG_LEVEL_WARN              ((HLOG_LEVEL_ERROR << 1) | HLOG_LEVEL_ERROR)
#define HLOG_LEVEL_DEBUG            ((HLOG_LEVEL_WARN << 1) | HLOG_LEVEL_WARN)
#define HLOG_LEVEL_INFO                 ((HLOG_LEVEL_DEBUG << 1) | HLOG_LEVEL_DEBUG)
#define HLOG_LEVEL_VERBOSE        ((HLOG_LEVEL_INFO << 1) | HLOG_LEVEL_INFO)

#define HLOG_MASK_NONE               0
#define HLOG_MASK_ERROR             0x01
#define HLOG_MASK_WARN              (HLOG_MASK_ERROR << 1)
#define HLOG_MASK_DEBUG            (HLOG_MASK_WARN << 1)
#define HLOG_MASK_INFO                 (HLOG_MASK_DEBUG << 1)

//#define HLOGLEVEL                              (HLOG_LEVEL_VERBOSE)

#define HASSERT(cond, msg) CCAssert(cond, msg)

#if ((HLOGLEVEL & HLOG_MASK_INFO) != 0)
#define HLOGI(format, ...)      CCLOG(format, ##__VA_ARGS__)
#else
#define HLOGI(format, ...)
#endif
#if ((HLOGLEVEL & HLOG_MASK_WARN) != 0)
#define HLOGW(format, ...)      CCLOGWARN(format, ##__VA_ARGS__)
#else
#define HLOGW(format, ...)
#endif
#if ((HLOGLEVEL & HLOG_MASK_DEBUG) != 0)
#define HLOGD(format, ...)      CCLOGINFO(format, ##__VA_ARGS__)
#else
#define HLOGD(format, ...)
#endif
#if ((HLOGLEVEL & HLOG_MASK_ERROR) != 0)
#define HLOGE(format, ...)      CCLOGERROR(format, ##__VA_ARGS__)
#else
#define HLOGE(format, ...)
#endif

#endif //_LOG_H_
