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
        return 0.5*(x+1.5)*(x+1.5);
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
        //printf("%d\n",x);
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
        //printf("%d\n",x);
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
        //printf("%d\n",i);
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
        //printf("%d\n",x);
        for(int y=0;y<Dx;y++){
            xp=x-cx*y;
            yp=y-cy*x;
            res->pixels[y][x]=interpolation_ppm(image,yp,xp);
        }
    }
    return res;
}
void imprimer_matrice(double A[6][6]){
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            printf("%lf ",A[i][j]);
        }
        printf("\n");
    }
}
int matriceinverse(double A[6][6],double inv[6][6]){
    int i,j,k;
    double ratio,tmp;
    int n=6;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                inv[i][j]=1.0;
            }
            else{
                inv[i][j]=0.0;
            }
        }
    }

    for(i=0;i<n;i++){
        tmp=A[1][i];
        A[1][i]=A[4][i];
        A[4][i]=tmp;

        tmp=inv[1][i];
        inv[1][i]=inv[4][i];
        inv[4][i]=tmp;
    }

    for(i=0;i<n;i++){
        if(A[i][i]==0.0){
            printf("non\n");
            imprimer_matrice(A);
            return 0;
        }

        double diag=A[i][i];

        for(j=0;j<n;j++){
            A[i][j] /= diag;
            inv[i][j] /= diag;
        }

        for (k = 0; k < n; k++) {
            if (k != i) {
                ratio = A[k][i];
                for (j = 0; j < n; j++) {
                    A[k][j] -= ratio * A[i][j];
                    inv[k][j] -= ratio * inv[i][j];
                }
            }
        }

    }
    return 1;
}

void multiplication_matrice(double A[6][6],double B[6][1],double res[6][1]){
    for(int i=0;i<6;i++){
        for(int j=0;j<1;j++){
            res[i][j]=0;
        }
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<1;j++){
            for(int k=0;k<6;k++){
                res[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}

double *get_affine_transformation(point X_start[3],point X_end[3]){
    double *res=(double*)malloc(6*sizeof(double));

    double matrix[6][6]={{X_start[0].x,X_start[0].y,1,0,0,0},
                         {0,0,0,X_start[0].x,X_start[0].y,1},
                         {X_start[1].x,X_start[1].y,1,0,0,0},
                         {0,0,0,X_start[1].x,X_start[1].y,1},
                         {X_start[2].x,X_start[2].y,1,0,0,0},
                         {0,0,0,X_start[2].x,X_start[2].y,1}};

    double A[6][1]={
        {X_end[0].x},
        {X_end[0].y},
        {X_end[1].x},
        {X_end[1].y},
        {X_end[2].x},
        {X_end[2].y}
    };

    double inv[6][6];
    double res_tab[6][1];

    matriceinverse(matrix,inv);
    multiplication_matrice(inv,A,res_tab);

    for(int i=0;i<6;i++){
        res[i]=res_tab[i][0];
    }
    return res;
}

struct ppm *affine_transformation(struct ppm *image, double*coeff_transformation){
    double xp,yp;

    struct ppm *res=ppm_alloc(image->height,image->width,image->max_value);

    for(int i=0;i<image->height;i++){
        printf("%d\n",i);
        for(int j=0;j<image->width;j++){
            xp=i*coeff_transformation[0]+j*coeff_transformation[1]+1*coeff_transformation[2];
            yp=i*coeff_transformation[3]+j*coeff_transformation[4]+1*coeff_transformation[5];
            res->pixels[i][j]=interpolation_ppm(image,xp,yp);
            
        }
    }
    return res;
}