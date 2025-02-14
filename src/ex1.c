#include "../include/ex1.h"

int main(){
    struct pgm *test1=NULL;
    test1=pgm_read_asc("../obj/eye_s_asc.pgm");
    pgm_write_asc("../obj/test.pgm",test1);

    struct pgm *test2=NULL;
    test2=pgm_read_bin("../obj/eye_s_asc_bin.pgm");
    pgm_write_bin("../obj/test_bin.pgm",test2);

    struct pgm *test3=NULL;
    pgm_negative(test1,&test3);
    pgm_write_bin("../obj/test_negatif.pgm",test3);

    pgm_extract("../obj/test_extract.pgm",*test1,202,210,72,102);
    
    pgm_free(test1);
    pgm_free(test2);
    pgm_free(test3);

    return 0;
}