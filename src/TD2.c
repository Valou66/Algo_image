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
    char *fname="./obj/test_rot.ppm";
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    struct ppm *res2=rotation_ppm(testppm,20,testppm->height/2,testppm->width/2);

    ppm_write_asc(fname,res2);
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
    struct ppm *res2=shear_ppm(testppm,0.4,0.4,2048,2048);

    ppm_write_asc("./obj/test_shear.ppm",res2);
    ppm_free(testppm);
    ppm_free(res2);
}

void td2_ex2_1(){
    point start[3];
    point end[3];


    start[0].x = 1;
    start[0].y = 2;
    start[1].x = 7;
    start[1].y = 23;
    start[2].x = 5;
    start[2].y = 76;

    end[0].x = 12;
    end[0].y = 11;
    end[1].x = 10;
    end[1].y = 9;
    end[2].x = 8;
    end[2].y = 7;

    double *affine=get_affine_transformation(start,end);

    for(int i=0;i<8;i++){
        printf("%lf\n",affine[i]);
    }
}

void td2_ex2_2(){
    struct ppm *testppm=ppm_read_asc("./obj/eye_s_asc.ppm");
    double test[6]={1.27,-0.82,200.0,0.78,0.78,20.0};
    struct ppm *res=affine_transformation(testppm,test);

    ppm_write_asc("./obj/test_aff.ppm",res);
    ppm_free(testppm);
    ppm_free(res);

}


int main(){
    td2_ex2_2();
    return 0;
}