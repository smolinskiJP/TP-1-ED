#ifndef ARRAY_PARAMETERS_H
#define ARRAY_PARAMETERS_H

#include <stdlib.h>

typedef struct s_array_parameters{
    unsigned int seed;
    double a;
    double b;
    double c;
    double limiarCusto;
} ArrayParameters;

ArrayParameters* setArrayParameters(unsigned int seed, double a, double b, double c, double limiarCusto, ArrayParameters* ap);
ArrayParameters* newArrayParameters(void);
void deleteArrayParameters(ArrayParameters* ap);

#endif