#ifndef TD2_H
#define TD2_H

#include "TD1.h"
#define N 3
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif

double B0(double x);
double B1(double x);
double B2(double x);
double B3(double x);

struct point{
    int x,y;
};

typedef struct point point;

unsigned char interpolation_pgm(struct pgm *image,double x,double y);
rgb_t interpolation_ppm(struct ppm *image,double x,double y);
struct pgm* rotation_pgm(struct pgm *image,double theta,int x0,int y0);
struct ppm* rotation_ppm(struct ppm *image,double theta,int x0,int y0);

struct ppm* zoom_ppm(struct ppm *image,double lambda,int x0,int y0,int Dx,int Dy);
struct ppm* shear_ppm(struct ppm *image,double cx,double cy,int Dx,int Dy);
double min_d(double a,double b);

int matriceinverse(double A[6][6],double inv[6][6]);
void imprimer_matrice(double A[6][6]);
void multiplication_matrice(double A[6][6],double B[6][1],double res[6][1]);
double *get_affine_transformation(point X_start[3],point X_end[3]);
struct ppm *affine_transformation(struct ppm *image, double*coeff_transformation);

#endif //TD2_H