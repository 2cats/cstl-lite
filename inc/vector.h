#ifndef _MCLIB_VECTOR_H
#define _MCLIB_VECTOR_H

#include <common.h>

typedef struct{
    CommonPrivateType   common;
    byte_ptr_t          data;
    usize_t             rawSize;
    usize_t             rawCap;
}VectorPrivateType;

typedef struct{
    VectorPrivateType $;
}VectorType;
#define VectorNew(type) _VectorNew(sizeof(type),type##_setter)
#define VectorAt(type,vector,index) (*((type*)_VectorAt(vector,index)))
#define VectorPushback(vector,data) VectorInsert(vector,VectorSize(vector),data)

VectorType* _VectorNew(usize_t t_size,type_setter_t setter);
void VectorDestroy(VectorType* vector);
void VectorInsert(VectorType* vector,usize_t pos, ...);
byte_ptr_t _VectorAt(VectorType* vector ,usize_t index);
void VectorErase(VectorType* vector,usize_t index);
void VectorPopback(VectorType* vector);
usize_t VectorSize(VectorType* vector);
usize_t VectorCapacity(VectorType* vector);

void _VectorSet(int index,va_list val,...);
void* _VectorGet(int index,...);
#endif