#ifndef ARRAY_PARAMETERS_H
#define ARRAY_PARAMETERS_H

#include <stdlib.h>

typedef struct s_array_parameters{
    int a;
    int b;
    int c;
    int limiarCusto;
} ArrayParameters;

ArrayParameters* newArrayParameters(int a, int b, int c, int limiarCusto);
void deleteArrayParameters(ArrayParameters* ap);

#endif