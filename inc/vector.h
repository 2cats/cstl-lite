#ifndef _MCLIB_VECTOR_H
#define _MCLIB_VECTOR_H

#include <common.h>

typedef struct{
    CommonContainerType     common;
    byte_ptr_t              data;
    usize_t                 rawSize;
    usize_t                 rawCap;
}VectorPrivateType;

typedef struct{
    VectorPrivateType $;
}VectorType;
#define VectorNew(type) _VectorNew(sizeof(type),type##__set__,type##__less__)
VectorType* _VectorNew(usize_t t_size,type_setter_t type_set,type_less_t type_less);
void VectorDestroy(VectorType* vector);
void VectorErase(VectorType* vector,usize_t index);
void VectorPopback(VectorType* vector);
usize_t VectorSize(VectorType* vector);
usize_t VectorCapacity(VectorType* vector);


#endif