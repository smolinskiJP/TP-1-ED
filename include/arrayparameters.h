#ifndef ARRAY_PARAMETERS_H
#define ARRAY_PARAMETERS_H

#include <stdlib.h>

typedef struct s_array_parameters{
    double a;
    double b;
    double c;
    int limiarCusto;
} ArrayParameters;

ArrayParameters* setArrayParameters(double a, double b, double c, int limiarCusto, ArrayParameters* ap);
ArrayParameters* newArrayParameters(void);
void deleteArrayParameters(ArrayParameters* ap);

#endif