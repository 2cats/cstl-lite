#include <stdio.h>
#include <list.h>

TYPE_REGISTER_AT_GLOBAL(int)
int main(){
    int i;
    ListType* list=ListNew(int);
    for(i=0;i<3;i++){
        ListPushback(list,99);
        
        printf("[%02d]\tsize:%d\t\n",i,ListSize(list));
    }
    // sort(list,list);
    Set(list,1,31);
    printf("%d\n",ListAt(int,list,1));
    // for(i=0;i<3;i++){
    //     printf("[%02d]\tval:%d\tsize:%d\n",i,ListAt(int,list,ListSize(list)-1), ListSize(list));
    //     ListPopback(list);
    // }

     ListDestroy(list);
    return 0;
}