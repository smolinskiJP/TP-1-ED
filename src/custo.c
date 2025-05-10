#include "custo.h"

Custo* newCusto(void){
    Custo* c = (Custo*)malloc(sizeof(Custo));
    c->calls = 0;
    c->compare = 0;
    c->moves = 0;
    return c;
}

void deleteCusto(Custo* c){
    free(c);
}

void resetCusto(Custo* c){
    c->calls = 0;
    c->compare = 0;
    c->moves = 0;
}

void increaseCompare(Custo* c){
    c->compare++;
}

void increaseCalls(Custo* c){
    c->calls++;
}

void increaseMoves(Custo* c){
    c->moves++;
}

double calcCusto(Custo* custo, double a, double b, double c){
    return (custo->compare * a) + (custo->moves * b) + (custo->calls * c);
}