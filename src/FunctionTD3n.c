#include "../include/TD3n.h"

unsigned char max_pgm(struct pgm *image){
    unsigned char res=0;
    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            if(image->pixels[i][j]>res){
                res=image->pixels[i][j];
            }
        }
    }
    return res;
}

struct pgm* naive_x(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);


    int calcul;
    for(int i=1;i<res->height;i++){
        for(int j=1;j<res->width;j++){
            calcul=image->pixels[i][j]-image->pixels[i-1][j];
            if(calcul>255)calcul=255;
            if(calcul<0)calcul=0;
            res->pixels[i][j]=calcul;
        }
    }
    return res;
}


struct pgm* naive_y(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    int calcul;
    for(int i=1;i<res->height;i++){
        for(int j=1;j<res->width;j++){
            calcul=image->pixels[i][j]-image->pixels[i][j-1];
            if(calcul>255)calcul=255;
            if(calcul<0)calcul=0;
            res->pixels[i][j]=calcul;
        }
    }
    return res;
}

struct pgm* naive_edge_detector(struct pgm *image){
    struct pgm *x=naive_x(image);
    struct pgm *y=naive_y(image);

    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    for(int i=1;i<res->height;i++){
        for(int j=1;j<res->width;j++){
            res->pixels[i][j]=(int)sqrt(pow(x->pixels[i][j],2)+pow(y->pixels[i][j],2));
        }
    }


    for(int i=0;i<res->height;i++){
        for(int j=0;j<res->width;j++){
            res->pixels[i][j]=(int)res->pixels[i][j]/sqrt(2);
        }
    }

    return res;

}