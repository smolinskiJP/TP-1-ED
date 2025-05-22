#include "optimizer.h"


//Função que calcula o número otimizado de quebras para o vetor
int defineBreakLimit(int* A, int tam, ArrayParameters* ap, int MPS){
    //A nossa faixa inicial vai de 1-quebra até "metade do tamanho do vetor"-quebras
    int minLQ = 1, maxLQ = tam / 2;
    int stepLQ = (maxLQ - minLQ) / 5;
    if(stepLQ == 0) stepLQ++;

    //A variável limBreak guardará o número mais otimizado de quebras para a faixa calculada (Onde a diferença do Quick pro Insertion é menor)
    //A variável numLQ conta a quantidade de testes que foram feitos na faixa
    int limBreak, numLQ;

    //A variável diffCusto guarda a distância de custo entre o novo valor máximo e mínimo de faixa
    float diffCusto;

    //Os dois vetores guardam o custo (resultado da função do enunciado) do Quick e do Insertion respectivamente
    double *custosQ, *custosI;

    custosQ = (double*)malloc(10 * sizeof(double));
    //Tratamento de erro para alocacao
    if(!custosQ){
        printf("Erro de memória");
        return MEM_ERROR_OPT;
    }
    custosI = (double*)malloc(10 * sizeof(double));
    //Tratamento de erro para alocacao
    if(!custosI){
        printf("Erro de memória");
        free(custosQ);
        return MEM_ERROR_OPT;
    }

    //Variáveis do TAD custo que conta a quantidade de vezes que cada parâmetro analisado (move, cmp, call) foi chamado
    Custo *custoQuick, *custoInsertion;

    custoQuick = newCusto();
    //Tratamento de erro para alocacao
    if(!custoQuick){
        printf("Erro de memória");
        free(custosQ);
        free(custosI);
        return MEM_ERROR_OPT;
    }
    
    custoInsertion = newCusto();
    //Tratamento de erro para alocacao
    if(!custoInsertion){
        printf("Erro de memória");
        deleteCusto(custoQuick);
        free(custosQ);
        free(custosI);
        return MEM_ERROR_OPT;
    }

    resetCusto(custoQuick);
    resetCusto(custoInsertion);

    //Variável de iteração usada somente para a saída
    int iter = 0;

    do{
        printf("\niter %d\n", iter);
        numLQ = 0;
        //Caminharemos do início ao fim da faixa com o passo calculado
        for(int t = minLQ; t <= maxLQ; t += stepLQ){

            //Essa função vai escrever o custo de cada um dos dois algoritmos para um número específico de quebras
            int flag = OrdenadorUniversalBreakOptimizer(A, tam, t, custoQuick, custoInsertion, MPS, ap->seed);
            if(flag != TEST_SUCCESS) {
                free(custosQ);
                free(custosI);
                deleteCusto(custoQuick);
                deleteCusto(custoInsertion);
                return flag;
            }

            //quickSort estatísticas
            custosQ[numLQ] = calcCusto(custoQuick, ap->a, ap->b, ap->c);
            printf("qs lq %d cost %.9lf cmp %d move %d calls %d\n", t, custosQ[numLQ], custoQuick->compare, custoQuick->moves, custoQuick->calls);
            resetCusto(custoQuick);

            //insertionSort estatísticas
            custosI[numLQ] = calcCusto(custoInsertion, ap->a, ap->b, ap->c);
            printf("in lq %d cost %.9lf cmp %d move %d calls %d\n", t, custosI[numLQ], custoInsertion->compare, custoInsertion->moves, custoInsertion->calls);
            resetCusto(custoInsertion);

            numLQ++;
        }

        //Calculamos a posição onde houve menor diferença entre o quick e o insertion
        int minIndex = menorCustoDiff(custosI, custosQ, numLQ);
        //Pegamos o número de quebras correspondente
        limBreak = getValueByStep(minIndex, minLQ, stepLQ);

        //Por padrão, o limite superior da nova faixa deve ser próximo passo ao que teve menor diferença
        int maxLim = minIndex + 1;
        //Se a menor diferença se deu no primeiro, é a posição 2
        if(minIndex == 0) maxLim = minIndex + 2;
        //Se a menor diferença se deu no último, é a última posição
        else if(minIndex == numLQ - 1) maxLim = minIndex;

        //Calculamos a nova faixa do número de quebras para a próxima iteração
        calculaNovaFaixa(minIndex, &minLQ, &maxLQ, numLQ, &stepLQ);
        //Calculamos também a diferença de custo entre o limite inferior e superior da nova faixa
        diffCusto = absolute(custosI[maxLim - 2] - custosI[maxLim]);

        //imprimimos conforme a saída
        printf("numlq %d limQuebras %d lqdiff %f\n", numLQ, limBreak, diffCusto);

        iter++;

        //A condição de parada é que o custo seja menor do que o custo otimizado esperado, ou que tenham sido feitos menos de 5 testes na faixa
    }while((diffCusto > ap->limiarCusto) && (numLQ >= 5));

    //Liberando toda a memória alocada
    free(custosQ);
    free(custosI);
    deleteCusto(custoQuick);
    deleteCusto(custoInsertion);
    return limBreak;
}

//Função que calcula o número otimizado de quebras para o vetor
int definePartitionSize(int* A, int tam, ArrayParameters* ap) {
    //A nossa faixa inicial vai de tamanho 2 até tamanho do vetor
    int minMPS = 2, maxMPS = tam;
    int stepMPS = (maxMPS - minMPS) / 5;
    if(stepMPS == 0) stepMPS++;
    
    //A variável limParticao guardará tamanho mais otimizado de particao para a faixa calculada (Menor custo)
    //A variável numMPSconta a quantidade de testes que foram feitos na faixa
    int limParticao, numMPS;
    
    //A variável diffCusto guarda a distância de custo entre o novo valor máximo e mínimo de faixa
    float diffCusto;

    //O vetor guarda o custo de cada teste (valor retornado pela função do enunciado)
    double* custos = (double*)malloc(10 * sizeof(double));

    //Tratamento de erro para alocacao
    if(!custos){
        printf("Erro de memória");
        return MEM_ERROR_OPT;
    }

    //Variável que conta o número de operações do teste (cmp, move e calls)
    Custo* custo = newCusto();

    //Tratamento de erro para alocacao
    if(!custo){
        printf("Erro de memória");
        free(custos);
        return MEM_ERROR_OPT;
    }

    resetCusto(custo);

    //Usada somente para a saída
    int iter = 0;

    do {
        printf("\niter %d\n", iter);
        numMPS = 0;
        //Caminharemos do início ao fim da faixa com o passo calculado
        for (int t = minMPS; t <= maxMPS; t += stepMPS) {

            //Essa função vai escrever o custo do teste com o tamanho de partição atual
            int flag = OrdenadorUniversalPartitionOptimizer(A, tam, t, custo);
            if(flag != TEST_SUCCESS){
                free(custos);
                deleteCusto(custo);
                return flag;
            }

            //Manipulando os valores adquiridos pelo teste
            custos[numMPS] = calcCusto(custo, ap->a, ap->b, ap->c);
            printf("mps %d cost %.9lf cmp %d move %d calls %d\n", t, custos[numMPS], custo->compare, custo->moves, custo->calls);
            numMPS++;
            resetCusto(custo);
        }

        //Calculamos a posição onde houve menor custo
        int minIndex = menorCusto(custos, numMPS);
        //Pegamos o tamanho de partição correspondente
        limParticao = getValueByStep(minIndex, minMPS, stepMPS);

        //O máximo é por padrão, um passo a mais que o ótimo
        int maxLim = minIndex + 1;
        //Caso o ótimo seja o primeiro, é a posição 2
        if(minIndex == 0) maxLim = minIndex + 2;
        //Caso o ótimo seja o último, é a última posição
        else if(minIndex == numMPS - 1) maxLim = minIndex;

        //Calculamos a nova faixa de valores a serem testados com base no menor custo que encontramos
        calculaNovaFaixa(minIndex, &minMPS, &maxMPS, numMPS, &stepMPS);
        //Também calculamos a diferença entre o custo do limite superior e inferior da nova faixa
        diffCusto = (float)absolute(custos[maxLim - 2] - custos[maxLim]);
        
        //imprimimos conforme a saída
        printf("nummps %d limParticao %d mpsdiff %f\n", numMPS, limParticao, diffCusto);

        iter++;

        //A condição de parada é que o custo seja menor do que o custo otimizado esperado, ou que tenham sido feitos menos de 5 testes na faixa
    } while ((diffCusto > ap->limiarCusto) && (numMPS >= 5));

    //Liberando toda a memória alocada
    free(custos);
    deleteCusto(custo);
    return limParticao;
}

//Função que calcula uma nova faixa de valores a serem testados de acordo com o menor encontrado
void calculaNovaFaixa(int lim, int* min, int* max, int num, int* step) {
    int newMin, newMax;
    //Caso o menor seja o primeiro, a faixa é [0, 2]
    if (lim == 0) {
        newMin = 0;
        newMax = 2;
    }
    //Caso o menor seja o último a faixa é [tam - 3, tam - 1]
    else if (lim == num - 1) {
        newMin = num - 3;
        newMax = num - 1;
    }
    //Caso padrão, a faixa é [menor - 1, menor + 1]
    else {
        newMin = lim - 1;
        newMax = lim + 1;
    }
    //Pegamos os valores correspondentes a posição
    (*max) = getValueByStep(newMax, *min, *step);
    (*min) = getValueByStep(newMin, *min, *step);
    (*step) = (int)(*max - *min) / 5;
    //Valor mínimo de passo é 1.
    if ((*step) == 0) (*step)++;
}

//Retorna o valor correspondente ao com base no passo, quantidade de passos e início
int getValueByStep(int index, int start, int step){
    return start + index * step;
}

//Função que retorna a posição com o menor valor em um vetor de double
int menorCusto(double* A, int size) {
    int min = 0;
    for (int i = 1; i < size; i++) if (A[min] > A[i]) min = i;
    return min;
}

//Função que retorna a posição de menor diferença entre dois vetores de double
int menorCustoDiff(double* A, double* B, int size){
    int min = 0;
    for (int i = 1; i < size; i ++) if (absolute(A[min] - B[min]) > absolute(A[i] - B[i])) min = i;
    return min;
}

//Cálculo de valor absoluto entre dois doubles
float absolute(double d){
    if(d < 0) return -1.0 * d;
    return d;
}
