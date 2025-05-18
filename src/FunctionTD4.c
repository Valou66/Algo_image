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