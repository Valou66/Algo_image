#include "../include/TD4.h"

struct pgm *empty_image(int value_max,int height,int width)
{
    struct pgm *res=pgm_alloc(height,width,value_max);
    for(int i=0;i<res->height;i++)
    {
        for(int j=0;j<res->width;j++)
        {
            res->pixels[i][j]=0;
        }
    }
    return res;
}

void highlight_rectangle_pgm(struct pgm *image,int x,int y,int height,int width)
{
    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            if((i>y && j>x && i<y+height && j<x+width))
            {
                image->pixels[i][j]=image->pixels[i][j]/3;
            }

        }
    }
}

void highlight_rectangle_ppm(struct ppm *image,int x,int y,int height,int width)
{
    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            if((i>y && j>x && i<y+height && j<x+width))
            {
                image->pixels[i][j].r=image->pixels[i][j].r/3;
                image->pixels[i][j].g=image->pixels[i][j].g/3;
                image->pixels[i][j].b=image->pixels[i][j].b/3;
            }

        }
    }
}

double average_pixels_pgm(struct pgm *image)
{
    double somme=0.0;
    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            somme+=image->pixels[i][j];
        }
    }
    somme=somme/(image->height*image->width);
    return somme;
}

double_rgb average_pixels_ppm(struct ppm *image)
{
    double_rgb somme={0.0,0.0,0.0};

    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            somme.r+=image->pixels[i][j].r;
            somme.g+=image->pixels[i][j].g;
            somme.b+=image->pixels[i][j].b;
        }
    }

    somme.r=somme.r/(image->height*image->width);
    somme.g=somme.g/(image->height*image->width);
    somme.b=somme.b/(image->height*image->width);

    return somme;
}

double std_dev_pgm(struct pgm *image,double average)
{
    double somme=0.0;
    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            somme+=pow(image->pixels[i][j]-average,2);
        }
    }
    somme=sqrt(somme);
    return somme;
}

double_rgb std_dev_ppm(struct ppm *image,double_rgb average)
{
    double_rgb somme={0.0,0.0,0.0};
    for(int i=0;i<image->height;i++)
    {
        for(int j=0;j<image->width;j++)
        {
            somme.r+=pow(image->pixels[i][j].r-average.r,2);
            somme.g+=pow(image->pixels[i][j].g-average.g,2);
            somme.b+=pow(image->pixels[i][j].b-average.b,2);
        }
    }
    somme.r=sqrt(somme.r);
    somme.g=sqrt(somme.g);
    somme.b=sqrt(somme.b);
    return somme;
}

unsigned char NCC_pgm(struct pgm* image, struct pgm* pattern, int x, int y, double average_pattern, double std_dev_pattern){
        struct pgm* sous_image = pgm_alloc(pattern->height,pattern->width,pattern->max_value);

        //On crée la sous image
        for(int i =0; i <  pattern->height ; ++i){
            for(int j=0 ; j < pattern->width ; ++j){
                sous_image->pixels[i][j] = image->pixels[y+i][x+j];
            }
        }

        double moy_Ixy = average_pixels_pgm(sous_image);
        double std_dev_Ixy = std_dev_pgm(sous_image, moy_Ixy);
        double somme = 0;

        for(int i = 0 ; i < pattern->height ; ++i){
            for(int j = 0 ; j < pattern->width ; ++j){
                somme += (pattern->pixels[i][j] - average_pattern)*(image->pixels[y+i][x+j] - moy_Ixy);
            }
        }

        pgm_free(sous_image);

        double ncc = (somme)/(std_dev_pattern*std_dev_Ixy);
        unsigned char ncc_renormaliser = (unsigned char) ((ncc+1)*127.5);
        return ncc_renormaliser;
}

unsigned char NCC_ppm(struct ppm* image, struct ppm* pattern, int x, int y,double_rgb average_pattern, double_rgb std_dev_pattern){
        struct ppm* sous_image = ppm_alloc(pattern->height,pattern->width,pattern->max_value);

        //On crée la sous image
        for(int i =0; i <  pattern->height ; ++i){
            for(int j=0 ; j < pattern->width ; ++j){
                sous_image->pixels[i][j].r = image->pixels[y+i][x+j].r;
                sous_image->pixels[i][j].g = image->pixels[y+i][x+j].g;
                sous_image->pixels[i][j].b = image->pixels[y+i][x+j].b;
            }
        }

        double_rgb moy_Ixy = average_pixels_ppm(sous_image);
        double_rgb std_dev_Ixy = std_dev_ppm(sous_image, moy_Ixy);
        double sommer = 0;
        double sommeg = 0;
        double sommeb = 0;

        for(int i = 0 ; i < pattern->height ; ++i){
            for(int j = 0 ; j < pattern->width ; ++j){
                sommer += (pattern->pixels[i][j].r - average_pattern.r)*(image->pixels[y+i][x+j].r - moy_Ixy.r);
                sommeg += (pattern->pixels[i][j].g - average_pattern.g)*(image->pixels[y+i][x+j].g - moy_Ixy.g);
                sommeb += (pattern->pixels[i][j].b - average_pattern.b)*(image->pixels[y+i][x+j].b - moy_Ixy.b);
            }
        }

        ppm_free(sous_image);
        
        double nccr;
        if(std_dev_pattern.r == 0 || std_dev_Ixy.r == 0){
            nccr  = 0;
        }
        else{
            nccr = (sommer)/(std_dev_pattern.r*std_dev_Ixy.r);
        }
        double nccg;
        if(std_dev_pattern.g == 0 || std_dev_Ixy.g == 0){
            nccg  = 0;
        }
        else{
            nccg = (sommeg)/(std_dev_pattern.g*std_dev_Ixy.g);
        }
        double nccb;
        if(std_dev_pattern.b == 0 || std_dev_Ixy.b == 0){
            nccb  = 0;
        }
        else{
            nccb = (sommeb)/(std_dev_pattern.b*std_dev_Ixy.b);
        }
        double ncc = sqrt((nccr)*(nccr)+(nccg)*(nccg)+(nccb)*(nccb))/sqrt(3); 
        unsigned char ncc_renormaliser = (unsigned char) ((ncc+1)*127.5);
        return ncc_renormaliser;
}

struct pgm* compute_NCC(struct pgm* image, struct pgm* pattern){
    struct pgm * NCC_image = pgm_alloc(image->height-pattern->height,image->width-pattern->width,image->max_value);

    double avg_patt = average_pixels_pgm(pattern);
    double std_patt = std_dev_pgm(pattern,avg_patt); 

    for(int y = 0 ; y < NCC_image->height ; ++y){
        for(int x = 0 ; x < NCC_image->width  ; ++x){
            NCC_image->pixels[y][x] = NCC_pgm(image,pattern,x,y,avg_patt,std_patt);
        }
    }

    return NCC_image;
}
