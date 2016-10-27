#ifndef _MCLIB_LIST_H
#define _MCLIB_LIST_H
#include <common.h>

#define ListNew(type) _ListNew(sizeof(type),type##_setter)
#define ListAt(type,list,index) (*((type*)_ListAt(list,index)))
#define ListPushback(list,data) ListInsert(list,ListSize(list),data)

typedef struct ListNode{
    struct ListNode* next;
    struct ListNode* pre;
    byte_ptr_t data;
}ListNodeType;
typedef struct ListPrivate{
    CommonPrivateType common;
    ListNodeType *head_node;
}ListPrivateType;

typedef struct{
    ListPrivateType $;
}ListType;

ListType* _ListNew(usize_t t_size,type_setter_t setter);
usize_t ListSize(ListType* list);
void ListInsert(ListType* list,usize_t pos, ...);
byte_ptr_t _ListAt(ListType* list ,usize_t index);
void ListDestroy(ListType* list);
void ListErase(ListType* list,usize_t index);
void ListPopback(ListType* list);
void _ListSet(int index,va_list ap,...);
#endif