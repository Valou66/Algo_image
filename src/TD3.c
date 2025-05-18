#include "../include/TD3.h"

char *pgm_asc="./obj/eye_s_asc.pgm";

double kv[3][3]={{0,0,0},
                 {-1,1,0},
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
    struct pgm *test=pgm_alloc(4,4,255);
    test->pixels[0][0]=180;
    test->pixels[0][1]=18;
    test->pixels[0][2]=129;
    test->pixels[0][3]=132;

    test->pixels[1][0]=132;
    test->pixels[1][1]=19;
    test->pixels[1][2]=140;
    test->pixels[1][3]=134;

    test->pixels[2][0]=243;
    test->pixels[2][1]=243;
    test->pixels[2][2]=245;
    test->pixels[2][3]=253;

    test->pixels[3][0]=138;
    test->pixels[3][1]=135;
    test->pixels[3][2]=136;
    test->pixels[3][3]=136;

    struct pgm *res=copypgm(test);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            res->pixels[i][j]=apply_kernel(test,i,j,kv);
        }
    }

    pgm_write_asc("./obj/test_conv.pgm",res);

    pgm_free(test);
    pgm_free(res);


}

void td3_ex1_4(){
    struct pgm *testpgm=pgm_read_asc(pgm_asc);

    struct pgm *res=sobel_edge_detector(testpgm);

    pgm_write_asc("./obj/test_sobel.pgm",res);
    pgm_free(testpgm);
    pgm_free(res);
}

void test_pile(int seed1,int seed2){
    Pile *p=NULL;
    show_pile(p);
    for(int i=0;i<10;i++){
        p=empiler(p,(seed1%100)*cos(exp(2*M_PI*i)),(seed2%100)*cos(exp(2*M_PI*i)));
    }
    show_pile(p);
}

void td3_ex2_1(){
    struct pgm *testpgm=pgm_read_asc(pgm_asc);

    gaussian_blur(testpgm,0.6,5);

    pgm_write_asc("./obj/test_gaussian_blur.pgm",testpgm);
    pgm_free(testpgm);
}



int main(){
    td3_ex1_4();
    td3_ex2_1();

    struct pgm *test=pgm_read_asc(pgm_asc);
    struct pgm *sobelx=sobel_x(test);
    struct pgm *sobely=sobel_y(test);
    double **angleres=gradiant_angle(sobelx,sobely);

    //gaussian_blur(test,0.6,5);

    struct pgm *sobel=sobel_edge_detector(test);

    pgm_write_asc("./obj/test_sobel.pgm",sobel);

    non_maxima_supression(sobel,angleres);

    pgm_write_asc("./obj/test_nonmaxima.pgm",sobel);

    hysteresis_thresholding(sobel,0.4,0.2);

    pgm_write_asc("./obj/test_hysteresis.pgm",sobel);




    return 0;
}
