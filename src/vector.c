#include <vector.h>
#include <stdlib.h>
#include <stdio.h>

VectorType* _VectorNew(usize_t t_size,type_setter_t setter){
    VectorType* vector=(VectorType*)malloc(sizeof(VectorType));
    MustHave(vector!=NULL);

    vector->$.common.type_size=t_size;
    vector->$.common.setter=setter;
    vector->$.data=NULL;
    vector->$.rawSize=vector->$.rawCap=0;

    vector->$.common.set=_VectorSet;
    vector->$.common.get=_VectorGet;
    return vector;
}
void VectorDestroy(VectorType* vector){
    if(vector->$.data!=NULL){
        free(vector->$.data);
        vector->$.data=NULL;
    }
    if(vector!=NULL){
        free(vector);
        vector=NULL;
    }
}
void VectorInsert(VectorType* vector,usize_t pos, ...){
    usize_t newRawSize,newRawCap,rawPos,i;
    byte_ptr_t newData;
    va_list ap;
    
    MustHave(vector!=NULL);
    rawPos=pos*vector->$.common.type_size;
    newRawSize=vector->$.rawSize+vector->$.common.type_size;
    MustHave(rawPos<newRawSize);

    if(newRawSize>vector->$.rawCap){
        newRawCap=newRawSize*2;
        newData=malloc(newRawCap);
        MustHave(newData!=NULL);
        for(i=0;i<rawPos;i++){
            newData[i]=vector->$.data[i];
        }
        va_start(ap,pos);
        vector->$.common.setter(newData+i,ap);
        for(i=rawPos+vector->$.common.type_size;i<newRawSize;i++){
            newData[i]=vector->$.data[i-vector->$.common.type_size];
        }
        free(vector->$.data);
        vector->$.data=newData;
        vector->$.rawCap=newRawCap;
    }else{
        for(i=newRawSize-1-vector->$.common.type_size;i>rawPos;i--){
            vector->$.data[i+vector->$.common.type_size]=vector->$.data[i];
        }
        vector->$.common.setter(newData+rawPos,ap);
    }
    vector->$.rawSize=newRawSize;
}

byte_ptr_t _VectorAt(VectorType* vector ,usize_t index){
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));
    return vector->$.data+index*vector->$.common.type_size;
}

usize_t VectorSize(VectorType* vector){
    MustHave(vector!=NULL);
    return vector->$.rawSize/vector->$.common.type_size;
}
usize_t VectorCapacity(VectorType* vector){
    MustHave(vector!=NULL);
    return vector->$.rawCap/vector->$.common.type_size;
}
void VectorErase(VectorType* vector,usize_t index){
    int i;
    usize_t newRawCap;
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));

    for(i=(index+1)*vector->$.common.type_size;i<vector->$.rawSize;i++){
        vector->$.data[i-vector->$.common.type_size]=vector->$.data[i];
    }
    vector->$.rawSize-=vector->$.common.type_size;
    if(vector->$.rawSize<vector->$.rawCap/4){
        newRawCap=vector->$.rawCap/2;
        vector->$.data=realloc(vector->$.data,newRawCap);
        MustHave(vector->$.data!=NULL);
        vector->$.rawCap=newRawCap;
    }
}
void VectorPopback(VectorType* vector){
    MustHave(vector!=NULL);
    MustHave(VectorSize(vector)>0);
    VectorErase(vector,VectorSize(vector)-1);
}

void _VectorSet(int index,va_list val,...){
    va_list typeArg;
    VectorType *vector;
    va_start(typeArg,val);
    vector=va_arg(typeArg,VectorType *);
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));

    vector->$.common.setter(vector->$.data+index*vector->$.common.type_size,val);
}
void* _VectorGet(int index,...){
    va_list typeArg;
    VectorType *vector;
    va_start(typeArg,index);
    vector=va_arg(typeArg,VectorType *);
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));
    return vector->$.data+index*vector->$.common.type_size;
}