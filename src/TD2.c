#include "../include/TD2.h"
double (*BB[4])(double)={B0,B1,B2,B3};

void td2_ex1_1(){
    double test=0.7;

    printf("%lf\n",BB[N](test));
}

void td2_ex1_4(){
    struct pgm *test=pgm_read_asc("./obj/test_intermed_extract.pgm");
    struct pgm *res=rotation_pgm(test,20,0,0);

    pgm_write_asc("./obj/test_rot.pgm",res);
}


int main(){
    td2_ex1_4();

    return 0;
}