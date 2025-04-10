#include "../include/TD3.h"

unsigned char max_pgm(struct pgm *image){
    unsigned  maxi=0;
    int i,j;

    i=0;

    while(i<image->height && maxi!=255){
        j=0;
        while(j<image->width && maxi!=255){
            if(image->pixels[i][j]>maxi){
                maxi=image->pixels[i][j];
            }
            j++;
        }
        i++;
    }
    return maxi;
}

int apply_kernel(struct pgm *image ,int x,int y,double k[3][3]){
    int somme=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(x+i-1 >= 0 && x+i-1<image->height && y+j-1 >= 0 && y+j-1<image->width)
            somme=somme+(int)image->pixels[x+i-1][y+j-1]*k[i][j];
        }
    }
    return somme;
}

struct pgm *naive_x(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    int calcul;
    for(short i=1;i<res->height;i++){
        for(short j=0;j<res->width;j++){
            calcul=image->pixels[i][j]-image->pixels[i-1][j];
            if(calcul>255){
                calcul=255;
            }
            if(calcul<0){
                calcul=0;
            }
            res->pixels[i][j]=(unsigned char)calcul;
        }
    }
    return res;
}

struct pgm *naive_y(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    int calcul;
    for(short i=0;i<res->height;i++){
        for(short j=1;j<res->width;j++){
            calcul=image->pixels[i][j]-image->pixels[i][j-1];
            if(calcul>255){
                calcul=255;
            }
            if(calcul<0){
                calcul=0;
            }
            res->pixels[i][j]=(unsigned char)calcul;
        }
    }
    return res;
}

struct pgm *naive_edge_detector(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    struct pgm *naivex=naive_x(image);
    struct pgm *naivey=naive_y(image);

    int calcul;

    for(short i=0;i<res->height;i++){
        for(short j=1;j<res->width;j++){
            calcul=(int)sqrt(pow(naivex->pixels[i][j],2)+pow(naivey->pixels[i][j],2));
            calcul=(int)(calcul/sqrt(2.0));
            res->pixels[i][j]=(unsigned char)calcul;

        }
    }

    pgm_free(naivex);
    pgm_free(naivey);

    return res;

}

struct pgm *sobel_edge_detector(struct pgm*image){

}