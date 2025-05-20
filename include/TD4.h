#ifndef TD4_H
#define TD4_H
#include "TD1.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif

struct double_rgb{
    double r,g,b;
};
typedef struct double_rgb double_rgb;

struct pgm *empty_image(int value_max,int height,int width);

void highlight_rectangle_pgm(struct pgm *image,int x,int y,int height,int width);
void highlight_rectangle_ppm(struct ppm *image,int x,int y,int height,int width);

double average_pixels_pgm(struct pgm *image);
double_rgb average_pixels_ppm(struct ppm *image);

double std_dev_pgm(struct pgm *image,double average);
double_rgb std_dev_ppm(struct ppm *image,double_rgb average);

unsigned char NCC_pgm(struct pgm* image, struct pgm* pattern, int x, int y, double average_pattern, double std_dev_pattern);
unsigned char NCC_ppm(struct ppm* image, struct ppm* pattern, int x, int y,double_rgb average_pattern, double_rgb std_dev_pattern);

struct pgm* compute_NCC(struct pgm* image, struct pgm* pattern);

#endif //TD4_H