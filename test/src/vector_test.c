#include <stdio.h>
#include <vector.h>
#include <assert.h>
typedef struct{
    char text[16];
    int  id;
}Student;
VECTOR_REGISTER_AT_GLOBAL(Student)
int main(){
    int i;
    VectorType* vector=VectorNew(Student);
    Student student;
    for(i=0;i<32;i++){
        student.id=i;
        sprintf(student.text,"No.%d",student.id);
        VectorPushback(vector,student);
        printf("[%02d]\tsize:%d\tcap:%d\n",i,VectorSize(vector),VectorCapacity(vector));
    }
    printf("=================\n");
    for(i=0;i<415;i++){
        printf("id:%02d,text:%s",VectorGet(Student,vector,VectorSize(vector)-1).id,VectorGet(Student,vector,VectorSize(vector)-1).text);
        VectorPopback(vector);
        printf("\tsize:%d\tcap:%d\n",VectorSize(vector),VectorCapacity(vector));
    }
    VectorDelete(vector);
    return 0;
}