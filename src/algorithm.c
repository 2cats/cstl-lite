#include <algorithm.h>
#include <list.h>
void SelectionSort(container_ptr_t container,int start,int end){
    int i,j;
    int size=Size(container);
    if(end<0){
        end=size+1+end;
    }
    MustHave(start<=size&&end<=size && start>=0 && end>=0);
    for(i=start;i<end;i++){
        int min=i;
        for(j=i;j<end;j++){
            if(Less(container,j,min)){
               min=j;
            }
        }
        SwapPtr(container,GetPtr(container,i),GetPtr(container,min));
    }
}
void InsertionSort(container_ptr_t container,int start,int end){

}
void Sort(container_ptr_t container,int start,int end){
    SelectionSort(container,start,end);
}