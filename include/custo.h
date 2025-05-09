#ifndef CUSTO_H
#define CUSTO_H

#include <stdlib.h>

typedef struct s_custo{
    int compare;
    int calls;
    int moves;
} Custo;

Custo* newCusto();
void deleteCusto(Custo* c);
void increaseCompare(Custo* c);
void increaseCalls(Custo* c);
void increaseMoves(Custo* c);
float calcCusto(Custo* custo, float a, float b, float c);

#endif