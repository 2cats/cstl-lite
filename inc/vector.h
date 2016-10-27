#ifndef _MCLIB_VECTOR_H
#define _MCLIB_VECTOR_H
#include <stdarg.h>
#include <common.h>
#define VECTOR_REGISTER_AT_GLOBAL(type) void type##_setter(void* dest,va_list item){*(type*)(dest)=va_arg(item,type);}
typedef void (*type_setter_t)(void* dest,va_list item);
typedef struct{
    usize_t typeSize;
    type_setter_t setter;
    char* data;
    usize_t rawSize;
    usize_t rawCap;
}VectorPrivateType;
typedef struct{
    VectorPrivateType $;
}VectorType;
#define VectorNew(type) _VectorNew(sizeof(type),type##_setter)
#define VectorGet(type,vector,index) (*((type*)_VectorGet(vector,index)))
VectorType* _VectorNew(usize_t t_size,type_setter_t setter);
void VectorDelete(VectorType* vector);
void VectorPushback(VectorType* vector,...);
void* _VectorGet(VectorType* vector ,usize_t index);
void VectorErase(VectorType* vector,usize_t index);
void VectorPopback(VectorType* vector);
usize_t VectorSize(VectorType* vector);
usize_t VectorCapacity(VectorType* vector);
#endif