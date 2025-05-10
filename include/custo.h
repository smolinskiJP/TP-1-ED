#ifndef CUSTO_H
#define CUSTO_H

#include <stdlib.h>

typedef struct s_custo{
    int compare;
    int calls;
    int moves;
} Custo;

Custo* newCusto(void);
void deleteCusto(Custo* c);

void resetCusto(Custo* c);

void increaseCompare(Custo* c);
void increaseCalls(Custo* c);
void increaseMoves(Custo* c);

double calcCusto(Custo* custo, double a, double b, double c);

#endif