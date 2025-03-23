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
    int dim=256;
    struct pgm *test=pgm_read_asc("./obj/eye_s_asc.pgm");
    pgm_extract("./obj/test_extract.pgm",test,0,0,dim,dim);
    pgm_free(test);

    test=pgm_read_asc("./obj/test_extract.pgm");
    printf("%d %d\n",test->height,test->width);
    struct pgm *res=rotation_pgm(test,20,dim/2,dim/2);

    pgm_write_asc("./obj/test_rot.pgm",res);
    pgm_free(test);
    pgm_free(res);
}

void td2_ex1_4_2(){
    int dim=256;
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    ppm_extract("./obj/test_extract.ppm",testppm,0,0,dim,dim);
    ppm_free(testppm);

    testppm=ppm_read_asc("./obj/test_extract.ppm");
    struct ppm *res2=rotation_ppm(testppm,20,dim/2,dim/2);

    ppm_write_asc("./obj/test_rot.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}

void td2_ex1_5_1(){
    int dim=256;
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    ppm_extract("./obj/test_extract.ppm",testppm,0,0,dim,dim);
    ppm_free(testppm);

    testppm=ppm_read_asc("./obj/test_extract.ppm");
    struct ppm *res2=zoom_ppm(testppm,2,200,200,256,256);

    ppm_write_asc("./obj/test_zoom.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}

void td2_ex1_5_2(){
    int dim=256;
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    ppm_extract("./obj/test_extract.ppm",testppm,0,0,dim,dim);
    ppm_free(testppm);

    testppm=ppm_read_asc("./obj/test_extract.ppm");
    struct ppm *res2=shear_ppm(testppm,0.4,0.0,384,384);

    ppm_write_asc("./obj/test_sheer2.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}


int main(){
    td2_ex1_5_2();
    return 0;
}