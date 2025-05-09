#include "arrayparameters.h"

ArrayParameters* setArrayParameters(double a, double b, double c, int limiarCusto, ArrayParameters* ap){
    ap->a = a;
    ap->b = b;
    ap->c = c;
    ap->limiarCusto = limiarCusto;
    return ap;
}

ArrayParameters* newArrayParameters(){
    ArrayParameters* ap = (ArrayParameters*)malloc(sizeof(ArrayParameters));
    return ap;
}

void deleteArrayParameters(ArrayParameters* ap){
    free(ap);
}