#include "common.h"
TYPE_REGISTER_NUMERIC(int)
TYPE_REGISTER_NUMERIC(long)
TYPE_REGISTER_NUMERIC(double)
TYPE_REGISTER_NUMERIC(char)

void SetPtr(void *container, ...){
    va_list arg;
    CommonContainerType* $=(CommonContainerType*)container;
    va_start(arg,container);
    MustHave($!=NULL && $->set!=NULL);
    $->set(container,arg);
}
void InsertPtr(void *container,...){
    va_list arg;
    CommonContainerType* $=(CommonContainerType*)container;
    va_start(arg,container);
    MustHave($!=NULL && $->insert!=NULL);
    $->insert(container,arg);
}
void_ptr_t _Get(void *container,...){
    va_list arg;
    CommonContainerType* $=(CommonContainerType*)container;
    va_start(arg,container);
    MustHave($!=NULL && $->get!=NULL);
    return $->get(container,arg);
}
void Erase(void_ptr_t container,...){
    va_list arg;
    CommonContainerType* $=(CommonContainerType*)container;
    va_start(arg,container);
    MustHave($!=NULL && $->erase!=NULL);
    $->erase(container,arg);
}
usize_t Size(void *container){
    CommonContainerType* $=(CommonContainerType*)container;
    MustHave($!=NULL && $->size!=NULL);
    return $->size(container);
}
void Destroy(void_ptr_t container){
    CommonContainerType* $=(CommonContainerType*)container;
    MustHave($!=NULL && $->destroy!=NULL);
    return $->destroy(container);
}
char Less(container_ptr_t container, ...){
    va_list arg;
    CommonContainerType* $=(CommonContainerType*)container;
    va_start(arg,container);
    MustHave($!=NULL && $->less!=NULL);
    $->less(container,arg);
}
void SwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b){
    CommonContainerType* $=(CommonContainerType*)container;
    MustHave($!=NULL && $->less!=NULL);
    $->swap(container,a,b);
}
