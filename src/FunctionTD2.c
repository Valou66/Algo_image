#include "../include/TD2.h"

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

unsigned char interpolation_pgm(struct pgm *image,double x,double y){
    return B[N](image->pixels[x][y]);
}