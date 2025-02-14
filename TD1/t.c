#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr=NULL;
    ptr=&ptr;

    printf("%x",*ptr);
    return 0;
}