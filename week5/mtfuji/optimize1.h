#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "func1.h"

int optimize(const double alpha, const int dim, double x[], Sample *cities_p,
	     void (*calc_grad)(const double [], Sample *, double []));

#endif
