#include <vector.h>
#include <stdlib.h>
#include <stdio.h>

VectorType* _VectorNew(usize_t t_size,type_setter_t setter){
    VectorType* vector=(VectorType*)malloc(sizeof(VectorType));
    MustHave(vector!=NULL);

    vector->$.typeSize=t_size;
    vector->$.setter=setter;
    vector->$.data=NULL;
    vector->$.rawSize=vector->$.rawCap=0;
    return vector;
}
void VectorDelete(VectorType* vector){
    if(vector->$.data!=NULL){
        free(vector->$.data);
    }
    if(vector!=NULL){
        free(vector);
    }
}
void VectorPushback(VectorType* vector , ...){
    unsigned int newRawSize,newRawCap,oldRawCap;
    va_list ap;
    MustHave(vector!=NULL);
    newRawSize=vector->$.rawSize+vector->$.typeSize;
    oldRawCap=vector->$.rawCap;
    if(newRawSize>oldRawCap){
        newRawCap=newRawSize*2;
        vector->$.data=realloc(vector->$.data,newRawCap);
        MustHave(vector->$.data!=NULL);
        vector->$.rawCap=newRawCap;
    }
    va_start(ap,vector);
    vector->$.setter(vector->$.data+vector->$.rawSize,ap);
    vector->$.rawSize=newRawSize;
}
void* _VectorGet(VectorType* vector ,usize_t index){
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));
    return vector->$.data+index*vector->$.typeSize;
}
usize_t VectorSize(VectorType* vector){
    MustHave(vector!=NULL);
    return vector->$.rawSize/vector->$.typeSize;
}
usize_t VectorCapacity(VectorType* vector){
    MustHave(vector!=NULL);
    return vector->$.rawCap/vector->$.typeSize;
}
void VectorErase(VectorType* vector,usize_t index){
    int i;
    usize_t newRawCap;
    MustHave(vector!=NULL);
    MustHave(index<VectorSize(vector));

    for(i=(index+1)*vector->$.typeSize;i<vector->$.rawSize;i++){
        vector->$.data[i-vector->$.typeSize]=vector->$.data[i];
    }
    vector->$.rawSize-=vector->$.typeSize;
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