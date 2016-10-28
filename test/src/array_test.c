#include <stdio.h>
#include <vector.h>
#include <list.h>
#include <assert.h>
typedef struct{
    int x;
}Stu;
char StuLess(Stu* self,Stu* another){
    if(self->x<another->x){
        return 1;
    }
    return 0;
}
TYPE_REGISTER_CUSTOM(Stu,StuLess)
int main(){
    int i;
    Stu s1,s2;
    //VectorType* array=VectorNew(Stu);
    ListType* array=ListNew(Stu);
    for(i=1;i<=300;i++){
        Stu s;
        s.x=i;
        Insert(Stu,array,0,s);
    }
    Sort(array,0,-1);
    Erase(array,0);
    for(i=0;i<Size(array);i++){
        printf("%d\n",Get(Stu,array,i).x);
    }
    Destroy(array);
    return 0;
}