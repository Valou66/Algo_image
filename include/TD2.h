#ifndef TD2_H
#define TD2_H

#include "TD1.h"
#define N 1



double B0(double x);
double B1(double x);
double B2(double x);
double B3(double x);

unsigned char interpolation_pgm(struct pgm *image,double x,double y);

#endif //TD2_H