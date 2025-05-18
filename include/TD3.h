#ifndef TD3_H
#define TD3_H
#include "TD2.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif

typedef struct Pile{
    int x,y;
    struct Pile *next;
}Pile;

Pile* empiler(Pile *s,int x,int y);
Pile* depiler(Pile *s,int *x ,int *y);
Pile* pile_vide(Pile *s);
void show_pile(Pile *s);
void show_square_matrix(double **matrix,int n);


struct pgm* copypgm(struct pgm *image);

int apply_kernel(struct pgm *image ,int x,int y,double k[3][3]);

int apply_kernelall(struct pgm *image ,int x,int y,double **k,int n);

unsigned char max_pgm(struct pgm *image);

struct pgm *naive_x(struct pgm *image);
struct pgm *naive_y(struct pgm *image);


struct pgm *sobel_x(struct pgm *image);
struct pgm *sobel_y(struct pgm *image);
struct pgm *naive_edge_detector(struct pgm *image);

struct pgm *sobel_edge_detector(struct pgm*image);

void gaussian_blur(struct pgm *image,double sigma,int n);

double **gradiant_angle(struct pgm *grad_x,struct pgm *grad_y);

void non_maxima_supression(struct pgm *norm,double **angle);

void hysteresis_thresholding(struct pgm *image,float seuil_haut,float seuil_bas);

struct pgm *canny_edge_detector(struct pgm *image);

//ppm

rgb_t max_ppm(struct ppm *image);

struct ppm *naive_x_ppm(struct ppm *image);
struct ppm *naive_y_ppm(struct ppm *image);

struct ppm *naive_edge_detector_ppm(struct ppm *image);

struct ppm *sobel_edge_detector_ppm(struct ppm*image);

void gaussian_blur_ppm(struct ppm *image,double sigma,int n);

double **gradiant_angle_ppm(struct ppm *grad_x,struct ppm *grad_y);

void non_maxima_supression_ppm(struct ppm *norm,double **angle);


int hysteresis_voisin(Pile **p ,int x,int y);
void hysteresis_thresholding_ppm(struct ppm *image, float seuil_haut, float seuil_bas);

struct ppm *canny_edge_detector_ppm(struct ppm *image);

#endif //TD3_H