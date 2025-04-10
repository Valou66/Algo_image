#include "../include/TD3.h"

char *pgm_asc="./obj/eye_s_asc.pgm";

void td3_ex1_1(){
    struct pgm *testpgm=pgm_read_asc(pgm_asc);
    unsigned char res=max_pgm(testpgm);

    printf("max_pgm=%d\n",res);
    pgm_free(testpgm);
}

void td3_ex1_2(){
    struct pgm *testpgm=pgm_read_asc(pgm_asc);

    struct pgm *resx=naive_x(testpgm);
    struct pgm *resy=naive_y(testpgm);
    pgm_write_asc("./obj/test_naivex.pgm",resx);
    pgm_write_asc("./obj/test_naivey.pgm",resy);

    pgm_free(testpgm);
    pgm_free(resx);
    pgm_free(resy);
}

void td3_ex1_3(){
    struct pgm *testpgm=pgm_read_asc(pgm_asc);

    struct pgm *res=naive_edge_detector(testpgm);

    pgm_write_asc("./obj/test_naive.pgm",res);
    pgm_free(testpgm);
    pgm_free(res);
}

int main(){
    td3_ex1_1();
    td3_ex1_2();
    td3_ex1_3();




    return 0;
}
