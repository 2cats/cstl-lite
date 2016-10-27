#include "common.h"
#include "stdlib.h"
void Set(void *container,int index, ...){
    MustHave(container!=NULL);
    va_list valArg;
    va_start(valArg,index);
    CommonPrivateType* $=(CommonPrivateType* )container;
    MustHave($->set!=NULL);
    $->set(index,valArg,$);
}
void* _Get(void *container,int index){
    MustHave(container!=NULL);
    CommonPrivateType* $=(CommonPrivateType* )container;
    MustHave($->get!=NULL);
    $->get(index,$);
}