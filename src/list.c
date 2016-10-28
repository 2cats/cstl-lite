#include <list.h>
#include <stdlib.h>

void _ListInsert(container_ptr_t container,va_list arg);
void _ListSet(container_ptr_t container,va_list arg);
void* _ListGet(container_ptr_t container,va_list arg);
usize_t _ListSize(container_ptr_t container);
void _ListErase(container_ptr_t container,va_list arg);
void _ListDestroy(container_ptr_t container);
char _ListLess(container_ptr_t container,va_list arg);
void _ListSwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b);
ListType* _ListNew(usize_t t_size,type_setter_t type_set, type_less_t type_less){
    ListType* list=(ListType*)malloc(sizeof(ListType));
    MustHave(list!=NULL);

    list->$.common.type_size=t_size;
    list->$.common.type_set=type_set;
    list->$.common.type_less=type_less;
    list->$.head_node=NULL;

    list->$.common.set=_ListSet;
    list->$.common.insert=_ListInsert;
    list->$.common.erase=_ListErase;
    list->$.common.get=_ListGet;
    list->$.common.size=_ListSize;
    list->$.common.destroy=_ListDestroy;
    list->$.common.less=_ListLess;
    list->$.common.swap=_ListSwapPtr;
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

void _ListDestroy(container_ptr_t container){
    ListType* list=(ListType*)container;
    ListDestroy(list);
}
void ListErase(ListType* list,usize_t index){
    int i;
    ListNodeType* node;
    MustHave(list!=NULL);
    MustHave(index<ListSize(list));
    node=_promiseGetListNthNode(list,index);
    if(node==list->$.head_node){
        list->$.head_node=node->next;
        if(list->$.head_node!=NULL){
            list->$.head_node->pre=NULL;
        }
    }else{
        if(node->pre!=NULL){
            node->pre->next=node->next;
        }
        if(node->next!=NULL){
            node->next->pre=node->pre;
        }
    }
    free(node->data);
    free(node);

}
void ListPopback(ListType* list){
    MustHave(list!=NULL);
    MustHave(ListSize(list)>0);
    ListErase(list,ListSize(list)-1);
}


void _ListInsert(container_ptr_t container,va_list arg){
    ListType* list=(ListType*)container;
    int pos=va_arg(arg,int);
    ListNodeType* new_node,*last_node;

    MustHave(list!=NULL);
    MustHave(pos<=ListSize(list));

    new_node=(ListNodeType*)malloc(sizeof(ListNodeType));
    if(pos==0){
        new_node->next=list->$.head_node;
        new_node->pre=NULL;
        if(new_node->next!=NULL){
            new_node->next->pre=new_node;
        }
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
    new_node->data=(byte_ptr_t)malloc(list->$.common.type_size);
    list->$.common.type_set(new_node->data,arg);
}

void _ListSet(container_ptr_t container,va_list arg){
    ListType* list=(ListType*)container;
    int index=va_arg(arg,int);
    ListNodeType *node;
    MustHave(list!=NULL);
    MustHave(index<ListSize(list));
    node=_promiseGetListNthNode(list,index);
    list->$.common.type_set(node->data,arg);
}
void* _ListGet(container_ptr_t container,va_list arg){
    ListType* list=(ListType*)container;
    int index=va_arg(arg,int);
    return _ListAt(list,index);
}
usize_t _ListSize(container_ptr_t container){
    ListType* list=(ListType*)container;
    return ListSize(list);
}
void _ListErase(container_ptr_t container,va_list arg){
    ListType* list=(ListType*)container;
    int index=va_arg(arg,int);
    ListErase(list,index);
}
char _ListLess(container_ptr_t container,va_list arg){
    ListType *list=(ListType *)container;
    int index_a=va_arg(arg,int);
    int index_b=va_arg(arg,int);
    usize_t list_size=ListSize(list);
    MustHave(index_a<list_size&&index_b<list_size);
    return list->$.common.type_less(_ListAt(list,index_a),_ListAt(list,index_b));
}
void _ListSwapPtr(container_ptr_t container,void_ptr_t a,void_ptr_t b){
    char buf;
    char *ap=(char*) a,*bp=(char*) b;
    int i;
    ListType *list=(ListType *)container;
    MustHave(list!=NULL);

    for(i=0;i<list->$.common.type_size;i++){
        unsigned char tmp;
        tmp=ap[i];
        ap[i]=bp[i];
        bp[i]=tmp;
    }
}