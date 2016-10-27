#include <list.h>
#include <stdlib.h>

ListType* _ListNew(usize_t t_size,type_setter_t setter){
    ListType* list=(ListType*)malloc(sizeof(ListType));
    MustHave(list!=NULL);

    list->$.common.type_size=t_size;
    list->$.common.setter=setter;
    list->$.head_node=NULL;

    list->$.common.set=_ListSet;

    return list;
}
usize_t ListSize(ListType* list){
    int size;
    ListNodeType *list_node;
    MustHave(list!=NULL);
    size=0;
    list_node=list->$.head_node;
    while(list_node!=NULL){
        size++;
        list_node=list_node->next;
    }
    return size;
}
ListNodeType *_promiseGetListNthNode(ListType* list,usize_t index ){
    int i;
    ListNodeType* node=list->$.head_node;
    for(i=0;i<index;i++){
        node=node->next;
    }
    return node;
}
void _ListSet(int index,va_list val,...){
    va_list typeArg;
    ListNodeType *node;
    ListType *list;
    va_start(typeArg,val);
    list=va_arg(typeArg,ListType *);
    MustHave(list!=NULL);
    MustHave(index<ListSize(list));
    node=_promiseGetListNthNode(list,index);
    list->$.common.setter(node->data,val);
}
// void _listSetx(ListType* list,int index,va_list ap){
//     ListNodeType *node;
//     MustHave(list!=NULL);
//     MustHave(index<ListSize(list));
//     node=_promiseGetListNthNode(list,index);
//     list->$.common.setter(node->data,ap);
// }
// void ListSet(ListType* list,int index,...){
//     va_list ap; 
//     va_start(ap,index);
//     _listSetx(list,index,ap);
// }
void ListInsert(ListType* list,usize_t pos, ...){
    ListNodeType* new_node,*last_node;
    va_list valist;
    MustHave(list!=NULL);
    MustHave(pos<=ListSize(list));

    new_node=(ListNodeType*)malloc(sizeof(ListNodeType));
    if(pos==0){
        new_node->next=list->$.head_node;
        new_node->pre=NULL;
        list->$.head_node=new_node;
    }else{
        last_node=_promiseGetListNthNode(list,pos-1);
        if(last_node->next!=NULL){
            last_node->next->pre=new_node;
            new_node->next=last_node->next->next;
        }else{
            new_node->next=NULL;
        }
        last_node->next=new_node;
        new_node->pre=last_node;
    }
    va_start(valist,pos);
    new_node->data=(byte_ptr_t)malloc(list->$.common.type_size);
    list->$.common.setter(new_node->data,valist);

}


byte_ptr_t _ListAt(ListType* list ,usize_t index){
    int i;
    ListNodeType* node;
    MustHave(list!=NULL);
    MustHave(index<ListSize(list));
    node=_promiseGetListNthNode(list,index);
    return node->data;
}
void ListDestroy(ListType* list){
    ListNodeType *node=list->$.head_node,*tmp;
    while(node!=NULL){
        tmp=node;
        node=node->next;
        if(tmp->data!=NULL){
            free(tmp->data);
        }
        free(tmp);
    }
    if(list!=NULL){
        free(list);
        list=NULL;
    }
}
void ListErase(ListType* list,usize_t index){
    int i;
    ListNodeType* node;
    MustHave(list!=NULL);
    MustHave(index<ListSize(list));
    node=_promiseGetListNthNode(list,index);
    if(node->pre!=NULL){
        node->pre->next=node->next;
    }
    if(node->next!=NULL){
        node->next->pre=node->pre;
    }
    free(node);
    if(node==list->$.head_node){
        list->$.head_node=NULL;
    }
}
void ListPopback(ListType* list){
    MustHave(list!=NULL);
    MustHave(ListSize(list)>0);
    ListErase(list,ListSize(list)-1);
}


