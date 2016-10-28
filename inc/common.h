#ifndef _MCLIB_COMMON_H
#define _MCLIB_COMMON_H
#include <stdarg.h>
#include <stdio.h>
#include "stdlib.h"
typedef unsigned int  usize_t;
typedef void*        void_ptr_t;
typedef char*        byte_ptr_t;
typedef void_ptr_t   container_ptr_t;
typedef void_ptr_t   iterator_t;

typedef void (*type_setter_t)(void* dest,va_list item);
typedef char (*type_less_t)(void* self,void* another);

typedef void (*set_t)(container_ptr_t container,va_list arg);
typedef void (*insert_t)(container_ptr_t container,va_list arg);
typedef void* (*get_t)(container_ptr_t container,va_list arg);
typedef usize_t (*getsize_t)(container_ptr_t container);
typedef void (*erase_t)(container_ptr_t container,va_list arg);
typedef void (*destroy_t)(container_ptr_t container);
typedef char (*less_t)(container_ptr_t,va_list arg);
typedef void (*swap_t)(container_ptr_t container,void_ptr_t a,void_ptr_t b);

void_ptr_t _Get(container_ptr_t container,...);
void Erase(container_ptr_t container,...);

usize_t Size(container_ptr_t container);
void Destroy(container_ptr_t container);
char Less(container_ptr_t container, ...);

#define GetPtr(container,key) _Get(container,key) //Get: container,key ; return val_ptr
void SetPtr(container_ptr_t container,...);    //Set: container,key,val_ptr;
void InsertPtr(container_ptr_t container,...); 
void SwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b);

#define Get(type,container,key) (*(type*)(_Get(container,key)))
#define Set(type,container,key,val) do{type tmp=(type)val;SetPtr(container,key,&tmp);}while(0)
#define Insert(type,container,key,val)  do{type tmp=(type)val;InsertPtr(container,key,&tmp);}while(0)

typedef struct{
    usize_t         type_size;
    type_setter_t   type_set;
    type_less_t     type_less;

    set_t           set;
    get_t           get;
    insert_t        insert;
    getsize_t       size;
    erase_t         erase;
    destroy_t       destroy;
    less_t          less;
    swap_t          swap;
}CommonContainerType;

// #define _TypeAt(item_type,container_func,container_var,index) (*((item_type*)container_func(container_var,index)))

#define TYPE_DECLARE_TYPE_SET(type)  void type##__set__(void* dest,va_list item){*(type*)(dest)=*(va_arg(item,type*));}
#define TYPE_REGISTER_NUMERIC(type) TYPE_DECLARE_TYPE_SET(type)\
char type##__less__(void* self,void* another){if((*(type*)(self)) < (*(type*)(another))){return 1;}return 0;}

#define TYPE_REGISTER_CUSTOM(type,less)  TYPE_DECLARE_TYPE_SET(type)\
char type##__less__(void* self,void* another){return less((type*)self,(type*)another);}


#define TYPE_REGISTER_HEADER(type) void type##__set__(void* dest,va_list item);\
char type##__less__(void* self,void* another);

#define LOG(...) printf(__VA_ARGS__)
#define MustHave(flag) do{if((flag)==0){LOG("MustHave Failed: %s:%d: %s: ['%s']", __FILE__, __LINE__,__func__,#flag);exit(-1);}}while(0)


TYPE_REGISTER_HEADER(int)
TYPE_REGISTER_HEADER(double)
TYPE_REGISTER_HEADER(long)
TYPE_REGISTER_HEADER(char)
TYPE_REGISTER_HEADER(short)

#endif