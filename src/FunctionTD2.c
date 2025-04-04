#include "../include/TD2.h"
double (*B[4])(double)={B0,B1,B2,B3};

double B0(double x){
    double x_abs=fabs(x);
    if(x_abs>0.5) 
        return 0.0;
    
    else if(x_abs<0.5) 
        return 1.0;
    
    else 
        return 0.5;
}

double B1(double x){
    double x_abs=fabs(x);
    if(x_abs>1.0){
        return 0.0;
    }

    else if(x>=-1.0 && x<=0.0){
        return x+1.0;
    }

    else{
        return 1.0-x;
    }
}

double B2(double x){
    double x_abs=fabs(x);
    if(x_abs>1.5){
        return 0.0;
    }

    else if(x>=-1.5 && x<=-0.5){
        return 0.5*(x+1.4)*(x+1.4);
    }

    else if(x>=-0.5 && x<=0.5){
        return 0.75-x*x;
    }

    else{
        return 0.5*(x-1.5)*(x-1.5);
    }
}

double B3(double x){
    double x_abs=fabs(x);
    if(x_abs>2.0){
        return 0.0;
    }

    else if(x_abs>=0.0 && x_abs<=1.0){
        return (0.5*x_abs*x_abs*x_abs)-(x*x)+(2.0/3.0);
    }

    else{
        return (1.0/6.0)*(2-x_abs)*(2-x_abs)*(2-x_abs);
    }
}

double min_d(double a,double b){
    if(a<b){
        return a;
    }
    else{
        return b;
    }
}

unsigned char interpolation_pgm(struct pgm *image,double x,double y){
    double somme=0.0;
    int xc=round(x);
    int yc=round(y);
    int xi,yj;

    for(short i=-N;i<=N;i++){
        for(short j=-N;j<=N;j++){
            xi=xc+i;
            yj=yc+j;
            if(xi >=0 && xi<image->height && yj>=0 && yj<image->width){
                somme=somme+B[N](x-xi)*B[N](y-yj)*image->pixels[xi][yj];
            }
        }
    }

    
    return (unsigned char)somme;
}

rgb_t interpolation_ppm(struct ppm *image,double x,double y){
    double sommer=0.0,sommeg=0.0,sommeb=0.0;
    int xc=round(x);
    int yc=round(y);
    int xi,yj;

    for(short i=-N;i<=N;i++){
        for(short j=-N;j<=N;j++){
            xi=xc+i;
            yj=yc+j;
            if(xi >=0 && xi<image->height && yj>=0 && yj<image->width){
                sommer+=B[N](x-xi)*B[N](y-yj)*image->pixels[xi][yj].r;
                sommeg+=B[N](x-xi)*B[N](y-yj)*image->pixels[xi][yj].g;
                sommeb+=B[N](x-xi)*B[N](y-yj)*image->pixels[xi][yj].b;
            }
        }
    }
    rgb_t somme;
    somme.r=sommer;
    somme.g=sommeg;
    somme.b=sommeb;

    return somme;
}

struct pgm* rotation_pgm(struct pgm *image,double theta,int x0,int y0){
    
    double theta_radian=theta*(M_PI/180);
    struct pgm *res= pgm_alloc(image->height,image->width,image->max_value);
    for(int x=0;x<res->height;x++){
        printf("%d\n",x);
        for(int y=0;y<res->width;y++){
            
            double xp = x0+((x-x0)*cos(-theta_radian))-(y-y0)*sin(-theta_radian);
            double yp = y0+(x-x0)*sin(-theta_radian)+(y-y0)*cos(-theta_radian);

            res->pixels[x][y]=interpolation_pgm(image,xp,yp);
        }
    }
    return res;
}

struct ppm* rotation_ppm(struct ppm *image,double theta,int x0,int y0){
    double theta_radian=theta*(M_PI/180);
    struct ppm *res= ppm_alloc(image->height,image->width,image->max_value);
    for(int x=0;x<res->height;x++){
        printf("%d\n",x);
        for(int y=0;y<res->width;y++){
            
            double xp = x0+(x-x0)*cos(-theta_radian)-(y-y0)*sin(-theta_radian);
            double yp = y0+(x-x0)*sin(-theta_radian)+(y-y0)*cos(-theta_radian);

            res->pixels[x][y]=interpolation_ppm(image,xp,yp);
        }
    }
    return res;
}

struct ppm* zoom_ppm(struct ppm *image,double lambda,int x0,int y0,int Dx,int Dy){
    struct ppm *res=ppm_alloc(Dx,Dy,image->max_value);
    double xp,yp;
    for(int i=0;i<Dy;i++){
        printf("%d\n",i);
        for(int j=0;j<Dx;j++){
            xp=x0+(j-x0)/lambda;
            yp=y0+(i-y0)/lambda;
            res->pixels[j][i]=interpolation_ppm(image,xp,yp);
        }
    }
    return res;
}
struct ppm* shear_ppm(struct ppm *image,double cx,double cy,int Dx,int Dy){
    struct ppm *res=ppm_alloc(Dx,Dy,image->max_value);
    double xp,yp;
    for(int x=0;x<Dy;x++){
        printf("%d\n",x);
        for(int y=0;y<Dx;y++){
            xp=x-cx*y;
            yp=y-cy*x;
            res->pixels[y][x]=interpolation_ppm(image,yp,xp);
        }
    }
    return res;
}