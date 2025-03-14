#include "../include/TD1.h"

double exemple_cour[8][8]={{139.0,144.0,149.0,153.0,155.0,155.0,155.0,155.0},
                           {144.0,151.0,153.0,156.0,159.0,156.0,156.0,156.0},
                           {150.0,155.0,160.0,163.0,158.0,156.0,156.0,156.0},
                           {159.0,161.0,162.0,160.0,160.0,159.0,159.0,159.0},
                           {159.0,160.0,161.0,162.0,162.0,155.0,155.0,155.0},
                           {161.0,161.0,161.0,161.0,160.0,157.0,157.0,157.0},
                           {162.0,162.0,161.0,163.0,162.0,157.0,157.0,157.0},
                           {162.0,162.0,161.0,161.0,163.0,158.0,158.0,158.0}};

double Q_t[8][8]={{16.0,11.0,10.0,16.0,24.0,40.0,51.0,61.0},
                           {12.0,12.0,14.0,19.0,26.0,58.0,60.0,55.0},
                           {14.0,13.0,16.0,24.0,40.0,57.0,69.0,56.0},
                           {14.0,17.0,22.0,29.0,51.0,87.0,80.0,62.0},
                           {18.0,22.0,37.0,56.0,68.0,109.0,103.0,77.0},
                           {24.0,35.0,55.0,64.0,81.0,104.0,113.0,92.0},
                           {49.0,64.0,78.0,87.0,103.0,121.0,120.0,101.0},
                           {72.0,92.0,95.0,98.0,112.0,100.0,103.0,99.0}};

int test_rle[64]={48,0,0,0,0,48,0,0,0,48,0,0,48,0,48,0,0,0,0,0,0,0,0,48,48,48,0,0,48,0,0,0,0,0,0,0,0,0,0,0,48,65,0,0,0,0,0,0,48,50,51,52,53,0,0,0,0,0,59,60,61,0,0,0};

void test_ex1(){
    struct pgm *test1=NULL;
    test1=pgm_read_asc("./obj/eye_s_asc.pgm");
    pgm_write_asc("./obj/test.pgm",test1);

    struct pgm *test2=NULL;
    test2=pgm_read_bin("./obj/eye_s_asc_bin.pgm");
    pgm_write_bin("./obj/test_bin.pgm",test2);

    struct pgm *test3=NULL;
    pgm_negative(test1,&test3);
    pgm_write_bin("./obj/test_negatif.pgm",test3);
    pgm_extract("./obj/test_extract.pgm",test1,100,112,288,218);
    pgm_write_histogram(test1,"./obj/test_hist.pgm");

    pgm_free(test1);
    pgm_free(test2);
    pgm_free(test3);
}

void test_ex2(){
    struct ppm *ppm1=NULL;
    ppm1=ppm_read_asc("./obj/eye_s_asc.ppm");
    ppm_write_asc("./obj/test.ppm",ppm1);

    struct ppm *ppm2=NULL;
    ppm2=ppm_read_bin("./obj/eye_s_asc_bin.ppm");
    ppm_write_bin("./obj/test_bin.ppm",ppm2);

    struct ppm *ppm3=NULL;
    ppm_negative(ppm1,&ppm3);
    ppm_write_bin("./obj/test_negatif.ppm",ppm3);
    ppm_extract("./obj/test_extract.ppm",ppm1,100,112,288,218);
    ppm_write_histogram(ppm1,"./obj/test_hist.ppm");

    struct pgm *test;

    ppm_to_pgm(ppm1,&test);
    pgm_write_bin("./obj/test_conversion.pgm",test);

    ppm_free(ppm1);
    ppm_free(ppm2);
    ppm_free(ppm3);
    pgm_free(test);
}

void test_ex3(){
    struct pgm *test1=NULL;
    test1=pgm_read_bin("./obj/eye_s_asc_bin.pgm");
    pgm_extract("./obj/test_intermed_extract.pgm",test1,0,0,256,256);
    struct pgm *extract=NULL;
    extract=pgm_read_asc("./obj/test_intermed_extract.pgm");

    pgm_to_jpeg(extract,"./obj/test.jpeg");

    double size_pgm,size_jpeg;
    double taux;

    size_pgm=fsize("./obj/test_intermed_extract.pgm");
    size_jpeg=fsize("./obj/test.jpeg");
    
    printf("size pgm:%lf\n",size_pgm);
    printf("size jpeg:%lf\n",size_jpeg);
    taux=size_jpeg/size_pgm;

    printf("taux de compression:%lf\n",taux);
    
    

    pgm_free(test1);
    pgm_free(extract);
}

void test_ex4(){
    jpeg_to_pgm("./obj/test.jpeg");
}

void test_ex5(){
    struct ppm *test1=NULL;
    test1=ppm_read_bin("./obj/eye_s_asc_bin.ppm");
    ppm_extract("./obj/test_intermed_extract.ppm",test1,0,0,256,256);
    struct ppm *extract=NULL;
    extract=ppm_read_asc("./obj/test_intermed_extract.ppm");
    ppm_to_jpeg(extract,"./obj/test_ppm.jpeg");
}

void test_ex6(){
    double G[8][8]={{16.0,11.0,10.0,16.0,24.0,40.0,51.0,61.0},
                {12.0,12.0,14.0,19.0,26.0,58.0,60.0,55.0},
                {14.0,13.0,16.0,24.0,40.0,57.0,69.0,56.0},
                {14.0,17.0,22.0,29.0,51.0,87.0,80.0,62.0},
                {18.0,22.0,37.0,56.0,68.0,109.0,103.0,77.0},
                {24.0,35.0,55.0,64.0,81.0,104.0,113.0,92.0},
                {49.0,64.0,78.0,87.0,103.0,121.0,120.0,101.0},
                {72.0,92.0,95.0,98.0,112.0,100.0,103.0,99.0}};
    struct ppm *test1=NULL;
    test1=ppm_read_bin("./obj/eye_s_asc_bin.ppm");
    ppm_extract("./obj/test_intermed_extract.ppm",test1,0,0,256,256);
    struct ppm *extract=NULL;
    extract=ppm_read_asc("./obj/test_intermed_extract.ppm");

    double res_blk_y[8][8];
    double res_blk_u[8][8];
    double res_blk_v[8][8];
    int res_zgzg_y[64];
    int res_zgzg_u[64];
    int res_zgzg_v[64];


    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].r);

        printf(" ");

        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].g);
        
            printf(" ");
        
        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].b);

        printf(" ");

        printf("\n");
    }
    printf("\n");
    ppm_extract_blk(extract,res_blk_y,res_blk_u,res_blk_v,0,0);
    //ppm_dct(res_blk_y,res_blk_u,res_blk_v);
    //ppm_quantify(res_blk_y,res_blk_u,res_blk_v,G);
    //ppm_quantify_reverse(res_blk_y,res_blk_u,res_blk_v,G);
    //ppm_idct(res_blk_y,res_blk_u,res_blk_v);
    ppm_extract_blk_reverse(extract,res_blk_y,res_blk_u,res_blk_v,0,0);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].r);

        printf(" ");

        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].g);
        
        printf(" ");

        for(int j=0;j<8;j++)
            printf("%d ",extract->pixels[i][j].b);

        printf(" ");

        printf("\n");
    }
}

int main(){
    test_ex1();
    test_ex2();
    test_ex3();
    test_ex4();
    test_ex5();
    test_ex6();
    

    return 0;
}