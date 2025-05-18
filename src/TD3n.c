#include "../include/TD3n.h"

void td3_1_1(){
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    unsigned testr=max_pgm(test);
    printf("%d\n",testr);
    pgm_free(test);
}

void td3_1_2(){
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    struct pgm *res1=naive_x(test);
    struct pgm *res2=naive_y(test);

    pgm_write_asc("./obj/test_naivex.pgm",res1);
    pgm_write_asc("./obj/test_naivey.pgm",res2);

    pgm_free(test);
    pgm_free(res1);
    pgm_free(res2);

}

void td3_1_3(){
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    struct pgm *res=naive_edge_detector(test);

    pgm_write_asc("./obj/test_naive.pgm",res);

    pgm_free(test);
    pgm_free(res);
}

int main(){
    td3_1_1();
    td3_1_2();
    td3_1_3();
    return 0;
}