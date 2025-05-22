#include "custo.h"

//Aloca memoria para a variavel e a inicia com os valores zerados
Custo* newCusto(void){
    Custo* c = (Custo*)malloc(sizeof(Custo));
    c->calls = 0;
    c->compare = 0;
    c->moves = 0;
    return c;
}

//Libera a memoria da variavel
void deleteCusto(Custo* c){
    free(c);
}

//Reseta todos os contadores para 0
void resetCusto(Custo* c){
    c->calls = 0;
    c->compare = 0;
    c->moves = 0;
}

//Aumenta em 1 o contador de comparacoes
void increaseCompare(Custo* c){
    c->compare++;
}

//Aumenta em 1 o contador de chamadas
void increaseCalls(Custo* c){
    c->calls++;
}

//Aumenta em 1 o contador de movimentos
void increaseMoves(Custo* c){
    c->moves++;
}

//Calcula a funcao de custo do enunciado com os parametros recebidos
double calcCusto(Custo* custo, double a, double b, double c){
    return (custo->compare * a) + (custo->moves * b) + (custo->calls * c);
}