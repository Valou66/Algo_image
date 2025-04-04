#include "../include/TD2.h"
double (*BB[4])(double)={B0,B1,B2,B3};

void td2_ex1_1(){
    double test=0.7;

    printf("%lf\n",BB[N](test));
}

void td2_ex1_2(){
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    unsigned char res=interpolation_pgm(test,2.5,3.1415);
    printf("%d\n",res); 
}

void td2_ex1_4_1(){
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    struct pgm *res=rotation_pgm(test,20,test->height/2,test->width/2);

    pgm_write_asc("./obj/test_rot.pgm",res);
    pgm_free(test);
    pgm_free(res);

}

void td2_ex1_4_2(){
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    struct ppm *res2=rotation_ppm(testppm,20,testppm->height/2,testppm->width/2);

    ppm_write_asc("./obj/test_rot.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}

void td2_ex1_5_1(){
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    struct ppm *res2=zoom_ppm(testppm,5,275,275,testppm->height,testppm->width);

    ppm_write_asc("./obj/test_zoom.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}

void td2_ex1_5_2(){
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    struct ppm *res2=shear_ppm(testppm,0.5,0.5,1000,1000);

    ppm_write_asc("./obj/test_shear.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}


int main(){
    td2_ex1_4_1();
    td2_ex1_4_2();
    td2_ex1_5_1();
    td2_ex1_5_2();
    return 0;
}