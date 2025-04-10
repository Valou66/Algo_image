#include "../include/TD3.h"

char *pgm_asc="./obj/eye_s_asc.pgm";

double kv[3][3]={{0,-1,0},
                 {0,1,0},
                 {0,0,0}};

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

void test_apply_kernel(){
    //int res=apply_kernel(image)
}

int main(){
    td3_ex1_1();
    td3_ex1_2();
    td3_ex1_3();




    return 0;
}
