#ifndef __DEBUG_H__
#define __DEBUG_H__

/*
 *1.颜色输入的基本格式: \033[背景色;字体色m字符\033[0m
 *当背景色为0时，则使用当前控制端默认背景色，最后的\033[0m是对颜色的还原
 *字体色有如下几种,背景色在字体色数值上加10，就是一样的颜色
 *30 黑   31 红
 *32 绿   33 黄
 *34 蓝   35 紫
 *36 深绿 37 白
 */

#include <stdio.h>
#include <errno.h>
extern void kernel_print(const char *fmt, ...);
#if __SIZEOF_POINTER__ == 8
#define PRINT   printf
#else
//#define PRINT  kernel_print
#define PRINT  printf
#endif

#define UNIT_RETURN(fmt,...)                            \
do                                                      \
{                                                       \
    PRINT("\033[0;36mUNIT_RETURN\033[0m: "fmt"",##__VA_ARGS__);                             \
} while(0)                                              \
//debug switch
#define CONFIG_ENABLE_DEBUG

enum debugLevel
{
    DEBUG_LEVEL_DISABLE = 0,
    DEBUG_LEVEL_ERR,
    DEBUG_LEVEL_INFO,
    DEBUG_LEVEL_DEBUG,
};

extern const char * errorGet(int error);
extern void kernel_buf_init(void);
#ifdef CONFIG_ENABLE_DEBUG

#define DEBUG_SET_LEVEL(x) static enum debugLevel en_debug = x

#define ASSERT(condition)                               \
do                                                      \
{                                                       \
    if(!(condition))                                    \
    {                                                   \
        PRINT("\033[0;33m[[U]ASSERT]\033[0m : %s-->%s [%d]\r\n",            \
                __FILE__,__FUNCTION__,__LINE__);        \
        while(1);                                       \
    }                                                   \
} while (0)                                             \

#define ERR(fmt,...)                                    \
do                                                      \
{                                                       \
    if(en_debug >= DEBUG_LEVEL_ERR)                     \
    {                                                   \
        PRINT("\033[0;31m[U]ERROR\033[0m:<%10s>-(%5d)>> "fmt"",__FILE__, __LINE__, ##__VA_ARGS__);                             \
    }                                                   \
} while(0)                                              \

#define INFO(fmt,...)                                   \
do                                                      \
{                                                       \
    if(en_debug >= DEBUG_LEVEL_INFO)                    \
    {                                                   \
        PRINT("\033[0;34m[U]INFO \033[0m:<%10s>-(%5d)>> "fmt"",__FILE__, __LINE__, ##__VA_ARGS__);                             \
    }                                                   \
} while(0)                                              \

#define DEBUG(fmt,...)                                  \
do                                                      \
{                                                       \
    if(en_debug >= DEBUG_LEVEL_DEBUG)                   \
    {                                                   \
        PRINT("\033[0;32m[U]DEBUG\033[0m:<%10s>-(%5d)>> "fmt"",__FILE__, __LINE__, ##__VA_ARGS__);                             \
    }                                                   \
} while(0)                                              \


#else
#define DEBUG_SET_LEVEL(x)
#define ASSERT(...)
#define ERR(fmt,...)
#define INFO(fmt,...)
#define DEBUG(fmt,...)
#endif

#endif

