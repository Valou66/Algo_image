#ifndef TD2_H
#define TD2_H

#include "TD1.h"
#define N 1



double B0(double x);
double B1(double x);
double B2(double x);
double B3(double x);

unsigned char interpolation_pgm(struct pgm *image,double x,double y);
rgb_t interpolation_ppm(struct ppm *image,double x,double y);
struct pgm* rotation_pgm(struct pgm *image,double theta,int x0,int y0);
struct ppm* rotation_ppm(struct ppm *image,double theta,int x0,int y0);

#endif //TD2_H