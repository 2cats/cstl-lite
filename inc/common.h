#ifndef _MCLIB_COMMON_H
#define _MCLIB_COMMON_H
#include <stdarg.h>
#include <stdio.h>
typedef unsigned int usize_t;
typedef void*        void_ptr_t;
typedef char*        byte_ptr_t;
typedef void (*type_setter_t)(void* dest,va_list item);

typedef void_ptr_t IteratorType;

typedef void (*set_t)(int i,va_list valArg,...);
typedef void* (*get_t)(int i,...);

void Set(void *container,int index, ...);
void* _Get(void *container,int index);
#define Get(type,container,index) (*(type*)(_Get(container,index)))
typedef struct{
    usize_t         type_size;
    type_setter_t   setter;
    set_t           set;
    get_t           get;
}CommonPrivateType;

// #define _TypeAt(item_type,container_func,container_var,index) (*((item_type*)container_func(container_var,index)))

#define TYPE_REGISTER_AT_GLOBAL(type) void type##_setter(void* dest,va_list item){*(type*)(dest)=va_arg(item,type);}

#define LOG(...) printf(__VA_ARGS__)
#define MustHave(flag) do{if((flag)==0){LOG("MustHave Failed: %s:%d: %s: ['%s']", __FILE__, __LINE__,__func__,#flag);exit(-1);}}while(0)
#endif