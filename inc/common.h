#ifndef _MCLIB_COMMON_H
#define _MCLIB_COMMON_H
typedef unsigned int usize_t;
#define LOG(...) printf(__VA_ARGS__)
#define MustHave(flag) do{if((flag)==0){LOG("MustHave Failed: %s:%d: %s: ['%s']", __FILE__, __LINE__,__func__,#flag);exit(-1);}}while(0)
#endif