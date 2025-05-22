#include "arrayparameters.h"

//Define os valores da variavel com base nos parametros passados
ArrayParameters* setArrayParameters(unsigned int seed, double a, double b, double c, double limiarCusto, ArrayParameters* ap){
    ap->seed = seed;
    ap->a = a;
    ap->b = b;
    ap->c = c;
    ap->limiarCusto = limiarCusto;
    return ap;
}

//Aloca memoria para a variavel
ArrayParameters* newArrayParameters(void){
    ArrayParameters* ap = (ArrayParameters*)malloc(sizeof(ArrayParameters));
    return ap;
}

//Libera a memoria da variavel
void deleteArrayParameters(ArrayParameters* ap){
    free(ap);
}