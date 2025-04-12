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

Pile* empiler(Pile *s,double x){
    Pile *new=(Pile*)malloc(sizeof(Pile));
    new->x=x;
    new->next=s;
    return new;
}

Pile* depiler(Pile *s,double *x){
    Pile *new=s->next;
    *x=new->x;
    free(s);
    return new;
}

Pile* pile_vide(Pile *s){
    if(s==NULL){
        return 1;
    }
    return 0;
}

void show_pile(Pile *s){
    Pile *temp=s;

    while(temp!=NULL){
        printf("%lf <- ",temp->x);
        temp=temp->next;
    }
    printf("NULL \n");
}

struct pgm* copypgm(struct pgm *image){
    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            res->pixels[i][j]=image->pixels[i][j];
        }
    }
    return res;
}

int apply_kernel(struct pgm *image ,int x,int y,double k[3][3]){
    int somme=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(x+i-1 >=0 && x+i-1<image->height && y+j-1 >=0 && y+j-1 <image->width)
                somme=somme+(k[i][j]*image->pixels[x+i-1][y+j-1]);
            else{
                return 0;
            }
        }
    }

    return abs(somme);
}

int apply_kernelall(struct pgm *image ,int x,int y,double **k,int n){
    int somme=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(x+i-n/2 >=0 && x+i-n/2<image->height && y+j-n/2 >=0 && y+j-n/2 <image->width)
                somme=somme+(k[i][j]*image->pixels[x+i-n/2][y+j-n/2]);
            else{
                return 0;
            }
        }
    }

    return abs(somme);
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
    int c=2;
    int sumx,sumy,sum;

    struct pgm *res=pgm_alloc(image->height,image->width,image->max_value);

    double ky[3][3]={{-1,0,1},
                    {-c,0,c},
                    {-1,0,1}};
    
    double kx[3][3]={{-1,-c,-1},
                     {0,0,0},
                     {1,c,1}};

    for(short i=1;i<res->height-1;i++){
        for(short j=1;j<res->width-1;j++){
            sumx=0;
            sumy=0;

            sumx=apply_kernel(image,i,j,kx);
            sumy=apply_kernel(image,i,j,ky);

            sum=sqrt(pow(sumx,2)+pow(sumy,2));
            if(sum<0) sum=0;
            if(sum>255) sum=255;

            res->pixels[i][j]=(unsigned char)sum;
        }
    }

    return res;
}

void gaussian_blur(struct pgm *image,double sigma,int n){
    double **filtre=(double**)malloc(n*sizeof(double*));
    double somme;
    for(int i=0;i<n;i++){
        filtre[i]=(double*)malloc(n*sizeof(double));
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x=i-n/2;
            int y=j-n/2;
            filtre[i][j]=(1/(2*M_PI*sigma*sigma))*exp(-((x*x+y*y)/(2*sigma*sigma)));
        }
    }

    struct pgm *res=copypgm(image);

    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            res->pixels[i][j]=apply_kernelall(image,i,j,filtre,n);
        }
    }

    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            image->pixels[i][j]=res->pixels[i][j];
        }
    }

    pgm_free(res);
}

double **gradiant_angle(struct pgm *grad_x,struct pgm *grad_y){
    double **angle=(double**)malloc(grad_x->height*sizeof(double*));
    for(int i=0;i<grad_x->height;i++){
        angle[i]=(double*)malloc(grad_x->width*sizeof(double));
    }

    for(int i=0;i<grad_x->height;i++){
        for(int j=0;j<grad_x->width;j++){
            double x=grad_x->pixels[i][j];

            angle[i][j]=atan2(grad_y->pixels[i][j],grad_x->pixels[i][j]);
        }
    }
    return angle;
}