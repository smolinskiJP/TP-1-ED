#ifndef UNIVERSAL_SORT_H
#define UNIVERSAL_SORT_H

#include <stdlib.h>
#include "custo.h"

void swap(int* a, int* b, Custo* c);
void quickSort3Ins(int * A, int l, int r, Custo* custo);
void partition3(int * A, int l, int r, int *i, int *j, Custo* custo);
void insertionSort(int v[], int l, int r, Custo* custo);
int median(int a, int b, int c);
//void universalSort(int * A, int tam, int minSizePartition, int breakMax);
int countBreak(int * A, int tam);
void OrdenadorUniversalOptimizer(int * A, int tam, int minSizePartition, int breakMax, Custo* custo);

#endif