#include "universalsort.h"

//Troca de dois valores
void swap(int* a, int* b, Custo* c){

    increaseMoves(c);
    int temp = *a;

    increaseMoves(c);
    *a = *b;

    increaseMoves(c);
    *b = temp;
}

//Ordenacao baseada no algoritmo de QuickSort com Insertion para pequenas particoes e mediana de 3
void quickSort3Ins(int * A, int l, int r, Custo* custo, int minSizePartition){
    if (l >= r) return; //Caso base: Particao com menos de 2 elementos
    if(r - l < minSizePartition) { //Se a particao e menor que o tamanho minimo, ordena com Insertion
        insertionSort(A, l, r, custo);
        return;
    }
    //Passo recursivo

    //Incrementa o numero de chamadas
    increaseCalls(custo);
    int i, j;

    //Particiona o vetor
    partition3(A, l, r, &i, &j, custo);

    //Chama recursivamente para cada uma das particoes
    quickSort3Ins(A, l, j, custo, minSizePartition);
    quickSort3Ins(A, i, r, custo, minSizePartition);
}

//Particionamento de um vetor em dois menores e separados por um pivo
void partition3(int * A, int l, int r, int *i, int *j, Custo* custo){
    //Incrementa o numero de chamadas
    increaseCalls(custo);
    
    (*i) = l;
    (*j) = r;
    //Calcula o pivo como mediana do primeiro, ultimo e valor do meio para evitar o caso O(n^2)
    int pivot = median(A[l], A[r], A[(l + r) / 2]);
    
    do{
        increaseCompare(custo); //Conta as comparacoes
        while(pivot > A[*i]){ //Avanca o ponteiro da esqueda ate encontrar um elemento maior ou igual ao pivo
            increaseCompare(custo);
            (*i)++;
        }
        
        increaseCompare(custo); //Conta as comparacoes
        while(pivot < A[*j]){ //Retrocede o ponteiro da direita ate encontrar um elemento menor ou igual ao pivo
            increaseCompare(custo);
            (*j)--;
        } 

      if((*i) <= (*j)){ //Se o ponteiro da esquerda esta a esquerda do ponteiro da direita troca seus valores e incrementa cada um deles
        swap(&A[*i], &A[*j], custo);
        (*i)++;
        (*j)--;
      }

    //Executa enquanto o ponteiro da esquerda estiver a esquerda do ponteiro da direita
    }while(*i <= *j);
}

//Ordenacao baseada no algoritmo de InsertionSort
void insertionSort(int v[], int l, int r, Custo* custo){
    //Incrementa o numero de chamadas
    increaseCalls(custo);

    //Inicia a partir do segundo elemento
    l++;
    int aux, j;
    for(; l <= r; l++){
        aux = v[l]; //Elemento a ser inserido no vetor ordenado
        increaseMoves(custo); //Conta movimentacoes

        j = l - 1;

        increaseCompare(custo); //Conta comparacoes
        while((j >= 0) && aux < v[j]){ //Desloca para a direita elementos maiores que aux
            increaseCompare(custo);

            //Conta movimentacoes
            v[j + 1] = v[j];
            increaseMoves(custo);

            j--;
        }

        //Insere aux na posicao em aberto
        v[j + 1] = aux;
        increaseMoves(custo);
    }
}

//Mediana de 3 numeros
int median(int a, int b, int c){
    if(b <= a){ // _ b _ a _
        if(c <= b) return b; // c b a
        if(c <= a) return c; // b c a
        return a; // b a c
    } // _ a _ b _
    if(c <= a) return a; // c a b
    if(c <= b) return c; // a c b
    return b; // a b c
}

//Ordenador que escolhe o algoritmo com base no quao desordenado o vetor esta e seu tamanho, calcula o custo e armazena na variavel custo
void universalSort(int * A, int tam, int minSizePartition, int breakMax, Custo* custo){
    int breakCount = countBreak(A, 0, tam);
    if(breakCount < breakMax) insertionSort(A, 0, tam - 1, custo); //Chama Insertion se a quantidade de quebras for menor do que o maximo
    else if(tam > minSizePartition) quickSort3Ins(A, 0, tam - 1, custo, minSizePartition); //Chama Quick se o tamanho for maior do que o minimo
    else insertionSort(A, 0, tam - 1, custo); //Chama Insertion se o tamanho for menor ou igual ao otimo
}

//Conta a quantidade de quebras em um vetor
int countBreak(int * A, int l, int tam){
    int count = 0;
    for(int i = l; i < tam - 1; i++) if(A[i] > A[i + 1]) count++;
    return count;
}

//Calcula os testes para um tamanho especifico de particao e armazena em custo
int OrdenadorUniversalPartitionOptimizer(int * A, int tam, int minSizePartition, Custo* custo){
    //Cria um vetor copiado do original que servira para o teste
    int* B = (int*)malloc(tam * sizeof(int));
    //Tratamento de erro para alocacao
    if(!B){
        printf("Erro de memória");
        return MEM_ERROR_SORT;
    }
    arrayCopy(A, B, tam);

    //Inicialmente ja verificamos se o tamanho do vetor permite a chamada do Insertion
    if(tam > minSizePartition) quickSort3Ins(B, 0, tam - 1, custo, minSizePartition);
    else insertionSort(B, 0, tam - 1, custo);

    //Libera o vetor de teste
    free(B);
    return TEST_SUCCESS;
}

//Calcula os testes para um numero especifico de quebras e armazena em custoQuick e custoInsertion
int OrdenadorUniversalBreakOptimizer(int* A, int tam, int breakMax, Custo* custoQuick, Custo* custoInsertion, int MPS, unsigned int seed){
    //Cria um vetor copiado do original que servira para o teste
    int* B = (int*)malloc(tam * sizeof(int));
    //Tratamento de erro para alocacao
    if(!B){
        printf("Erro de memória");
        return MEM_ERROR_SORT;
    }
    arrayCopy(A, B, tam);

    //Ordena o vetor teste
    quickSort3Ins(B, 0, tam - 1, custoQuick, MPS);
    resetCusto(custoQuick);

    //Use Srand para Windows e Srand48 para Linux
    srand(seed);
    //srand48(seed);

    //Embaralha o vetor e logo ordena com o Insertion
    arrayShuffler(B, tam, breakMax);
    insertionSort(B, 0, tam - 1, custoInsertion);


    //Use Srand para Windows e Srand48 para Linux
    srand(seed);
    //srand48(seed);


    //Embaralha e ordena com o Quick
    arrayShuffler(B, tam, breakMax);
    quickSort3Ins(B, 0, tam - 1, custoQuick, MPS);

    //Libera o vetor de teste
    free(B);
    return TEST_SUCCESS;
}

//Bagunça um vetor um número de vezes igual a totalBreaks
void arrayShuffler(int* A, int tam, int totalBreaks){
    for(int i = 0; i < totalBreaks; i++){
        int i1 = 0, i2 = 0;
        while(i1 == i2){
            //Para usuarios de Windows (descomentar um e comentar o outro)
            i1 = (rand() % tam);
            i2 = (rand() % tam);

            //Para usuarios de Linux (descomentar um e comentar o outro)
            //i1 = (int)(drand48() * tam);
            //i2 = (int)(drand48() * tam);
        }

        //Troca as posicoes sorteadas
        int temp = A[i1];
        A[i1] = A[i2];
        A[i2] = temp;
    }
}

//Copia o primeiro vetor no segundo
void arrayCopy(int* A, int* B, int tam){
    for(int i = 0; i < tam; i++) B[i] = A[i];
}