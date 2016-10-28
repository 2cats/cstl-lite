#include <vector.h>
#include <stdlib.h>
#include <stdio.h>

void _VectorInsert(container_ptr_t container,va_list arg);
void _VectorSet(container_ptr_t container,va_list arg);
void* _VectorGet(container_ptr_t container,va_list arg);
usize_t _VectorSize(container_ptr_t container);
void _VectorErase(container_ptr_t container,va_list arg);
void _VectorDestroy(container_ptr_t container);
char _VectorLess(container_ptr_t container,va_list arg);
void _VectorSwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b);
VectorType* _VectorNew(usize_t t_size,type_setter_t type_set , type_less_t type_less){
    VectorType* vector=(VectorType*)malloc(sizeof(VectorType));
    MustHave(vector!=NULL);

    vector->$.common.type_size=t_size;
    vector->$.common.type_set=type_set;
    vector->$.common.type_less=type_less;
    vector->$.data=NULL;
    vector->$.rawSize=vector->$.rawCap=0;

    vector->$.common.set=_VectorSet;
    vector->$.common.get=_VectorGet;
    vector->$.common.insert=_VectorInsert;
    vector->$.common.size=_VectorSize;
    vector->$.common.erase=_VectorErase;
    vector->$.common.destroy=_VectorDestroy;
    vector->$.common.less=_VectorLess;
    vector->$.common.swap=_VectorSwapPtr;
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
void _VectorDestroy(void_ptr_t container){
    VectorType *vector=(VectorType *)container;
    VectorDestroy(vector);
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
void _VectorInsert(container_ptr_t container,va_list arg){
    va_list typeArg;
    int pos;
    int newRawSize,newRawCap,rawPos,i;
    byte_ptr_t newData;
    VectorType *vector=(VectorType *)container;
    pos=va_arg(arg,int);

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
        for(i=newRawSize-1-vector->$.common.type_size;i>=rawPos;i--){
            newData[i+vector->$.common.type_size]=vector->$.data[i];
        }

        vector->$.common.type_set(newData+rawPos,arg);
        free(vector->$.data);
        vector->$.data=newData;
        vector->$.rawCap=newRawCap;
    }else{
        for(i=newRawSize-1-vector->$.common.type_size;i>=rawPos;i--){
            vector->$.data[i+vector->$.common.type_size]=vector->$.data[i];
        }
        vector->$.common.type_set(vector->$.data+rawPos,arg);
    }
    vector->$.rawSize=newRawSize;

}
void _VectorSet(container_ptr_t container,va_list arg){
    int index;
    VectorType *vector=(VectorType *)container;
    MustHave(vector!=NULL);
    index=va_arg(arg,int);
    MustHave(index<VectorSize(vector));
    vector->$.common.type_set(vector->$.data+index*vector->$.common.type_size,arg);
}
void _VectorErase(container_ptr_t container,va_list arg){
    usize_t index=va_arg(arg,int);
    VectorType *vector=(VectorType *)container;
    return VectorErase(vector,index);
}
void* _VectorGet(container_ptr_t container,va_list arg){
    int index;
    VectorType *vector=(VectorType *)container;
    MustHave(vector!=NULL);
    index=va_arg(arg,int);
    MustHave(index<VectorSize(vector));
    return vector->$.data+index*vector->$.common.type_size;
}

usize_t _VectorSize(container_ptr_t container){
    return VectorSize((VectorType *)container);
}

char _VectorLess(container_ptr_t container,va_list arg){
    VectorType *vector=(VectorType *)container;
    int index_a=va_arg(arg,int);
    int index_b=va_arg(arg,int);
    usize_t vector_size=VectorSize(vector);
    MustHave(index_a<vector_size&&index_b<vector_size);
    return vector->$.common.type_less(vector->$.data+index_a*vector->$.common.type_size,vector->$.data+index_b*vector->$.common.type_size);
}
void _VectorSwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b){
    char buf;
    char *ap=(char*) a,*bp=(char*) b;
    int i;
    VectorType *vector=(VectorType *)container;
    MustHave(vector!=NULL);
    MustHave( ap>=vector->$.data &&
        ap<vector->$.data+vector->$.rawSize && 
              bp>=vector->$.data &&
        bp<vector->$.data+vector->$.rawSize );
    for(i=0;i<vector->$.common.type_size;i++){
        unsigned char tmp;
        tmp=ap[i];
        ap[i]=bp[i];
        bp[i]=tmp;
    }
}