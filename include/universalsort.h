#ifndef UNIVERSAL_SORT_HPP
#define UNIVERSAL_SORT_HPP

#include <stdlib.h>

void quickSort3Ins(int * A, int l, int r);
void partition3(int * A, int l, int r, int *i, int *j);
void insertionSort(int v[], int l, int r);
int median(int a, int b, int c);
void universalSort(int * A, int tam, int minSizePartition, int breakMax);
int countBreak(int * A, int tam);
int definePartitionSize(int * A, int tam, int limiarCusto);

#endif