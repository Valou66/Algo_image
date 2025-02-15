#include "../include/TD1.h"

void test_ex1(){
    struct pgm *test1=NULL;
    test1=pgm_read_asc("../obj/eye_s_asc.pgm");
    pgm_write_asc("../obj/test.pgm",test1);

    struct pgm *test2=NULL;
    test2=pgm_read_bin("../obj/eye_s_asc_bin.pgm");
    pgm_write_bin("../obj/test_bin.pgm",test2);

    struct pgm *test3=NULL;
    pgm_negative(test1,&test3);
    pgm_write_bin("../obj/test_negatif.pgm",test3);
    pgm_extract("../obj/test_extract.pgm",test1,100,112,288,218);
    pgm_write_histogram(test1,"../obj/test_hist.pgm");

    pgm_free(test1);
    pgm_free(test2);
    pgm_free(test3);
}

void test_ex2(){
    struct ppm *ppm1=NULL;
    ppm1=ppm_read_asc("../obj/eye_s_asc.ppm");
    ppm_write_asc("../obj/test.ppm",ppm1);

    struct ppm *ppm2=NULL;
    ppm2=ppm_read_bin("../obj/eye_s_asc_bin.ppm");
    ppm_write_bin("../obj/test_bin.ppm",ppm2);

    struct ppm *ppm3=NULL;
    ppm_negative(ppm1,&ppm3);
    ppm_write_bin("../obj/test_negatif.ppm",ppm3);
    ppm_extract("../obj/test_extract.ppm",ppm1,100,112,288,218);
    ppm_write_histogram(ppm1,"../obj/test_hist.ppm");

    struct pgm *test;

    ppm_to_pgm(ppm1,&test);
    pgm_write_bin("../obj/test_conversion.pgm",test);

    ppm_free(ppm1);
    ppm_free(ppm2);
    ppm_free(ppm3);
    pgm_free(test);
}

void test_ex3(){
    struct pgm *test1=NULL;
    test1=pgm_read_asc("../obj/eye_s_asc.pgm");

    double res_blk[8][8];

    pgm_extract_blk(test1,res_blk,0,0);

    for(short i = 0;i<8;i++){
        for(short j = 0;j<8;j++){
            printf("%lf ",res_blk[i][j]);
        }
        printf("\n");
    }

    printf("%lf",M_PI);

    pgm_free(test1);
}

int main(){
    test_ex1();
    test_ex2();
    test_ex3();
    

    

    return 0;
}