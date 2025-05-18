#include "../include/TD4.h"

char *puzzle1_charlie="./obj/images_test/puzzle1/charlie.ppm";
char *puzzle2_charlie="./obj/images_test/puzzle2/charlie.ppm";

int main(){
    struct pgm *test1=empty_image(255,512,512);
    pgm_write_asc("./obj/test_empty.pgm",test1);
    pgm_free(test1);

    struct pgm *test2=pgm_read_asc("./obj/eye_s_asc.pgm");
    highlight_rectangle_pgm(test2,256,256,100,100);
    pgm_write_asc("./obj/test_highlight.pgm",test2);
    pgm_free(test2);

    struct pgm *test3=ppm_read_asc("./obj/eye_s_asc.ppm");
    highlight_rectangle_ppm(test3,256,256,100,100);
    ppm_write_asc("./obj/test_highlight.ppm",test3);
    ppm_free(test3);

    struct ppm *test4=ppm_read_bin(puzzle1_charlie);
    double_rgb res4=average_pixels_ppm(test4);
    printf("(%.2lf,%.2lf,%.2lf)\n",res4.r,res4.g,res4.b);
    ppm_free(test4);

    struct ppm *test5=ppm_read_bin(puzzle2_charlie);
    double_rgb res5=average_pixels_ppm(test5);
    printf("(%.2lf,%.2lf,%.2lf)\n",res5.r,res5.g,res5.b);
    ppm_free(test5);

    struct ppm *test6=ppm_read_bin(puzzle1_charlie);
    double_rgb res6=std_dev_ppm(test6,res4);
    printf("(%.2lf,%.2lf,%.2lf)\n",res6.r,res6.g,res6.b);
    ppm_free(test6);


    struct ppm *test7=ppm_read_bin(puzzle2_charlie);
    double_rgb res7=std_dev_ppm(test7,res5);
    printf("(%.2lf,%.2lf,%.2lf)\n",res7.r,res7.g,res7.b);
    ppm_free(test7);



    

    return 0;
}