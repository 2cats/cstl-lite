#include <stdio.h>
#include <vector.h>
#include <assert.h>
 
TYPE_REGISTER_AT_GLOBAL(int)
int main(){
    int i;
    VectorType* vector=VectorNew(int);

    for(i=0;i<3;i++){
        VectorPushback(vector,99);
        printf("[%02d]\tsize:%d\tcap:%d\n",i,VectorSize(vector),VectorCapacity(vector));
    }
    Set(vector,1,31);
    printf("%d\n",Get(int,vector,1));

    // printf("=================\n");
    // for(i=0;i<32;i++){
    //     printf("id:%02d,text:%s",VectorAt(Student,vector,VectorSize(vector)-1).id,VectorAt(Student,vector,VectorSize(vector)-1).text);
    //     VectorPopback(vector);
    //     printf("\tsize:%d\tcap:%d\n",VectorSize(vector),VectorCapacity(vector));
    // }
    VectorDestroy(vector);
    return 0;
}