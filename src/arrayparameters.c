#include "arrayparameters.h"

ArrayParameters* newArrayParameters(int a, int b, int c, int limiarCusto){
    ArrayParameters* ap = (ArrayParameters*)malloc(sizeof(ArrayParameters));
    ap->a = a;
    ap->b = b;
    ap->c = c;
    ap->limiarCusto = limiarCusto;
    return ap;
}

void deleteArrayParameters(ArrayParameters* ap){
    free(ap);
}