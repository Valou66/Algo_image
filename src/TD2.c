#include "../include/TD2.h"
double (*B[4])(double)={B0,B1,B2,B3};

void td2_ex1_1(){
    double test=0.7;

    printf("%lf\n",B[N](test));
}


int main(){
    td2_ex1_1();

    return 0;
}