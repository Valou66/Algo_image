#ifndef TD2_H
#define TD2_H

#include "TD1.h"
#define N 3
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct point{
    int x,y;
};
typedef struct point point_t;
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
#endif //TD2_H