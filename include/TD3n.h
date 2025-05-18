#ifndef TD3n_H
#define TD3n_H
#include "TD2.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif

unsigned char max_pgm(struct pgm *image);
struct pgm* naive_x(struct pgm *image);
struct pgm* naive_y(struct pgm *image);
struct pgm* naive_edge_detector(struct pgm *image);

#endif //TD3n_H