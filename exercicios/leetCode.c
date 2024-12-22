#include <stdio.h>
#include <stdlib.h>
# define swap(a,b) {frac t; t = a; a = b; b = t;}

typedef struct fractions frac;
struct fractions 
{
    int numerator;
    int denominator;
    float fraction;
};
 
int sum_n_int(int n)
{
    return (n * (n + 1))/2;
}

frac insertionSort(frac *f, int l, int r)
{
    int i = l, j;
    while (i < r)
    {   
        j = i + 1;
        while(j - 1 >= l && f[j].fraction < f[j - 1].fraction)
        {
            swap(f[j], f[j - 1]);
            j--;
        }
        i++;
    }

    // Calcula a mediana
    int tam = r - l + 1;
    int mediana;
    if(tam % 2 == 0) mediana = (tam/2) + l;
    else mediana = (tam/2) + l + 1;

    return f[mediana];
}

frac MoM(frac *f, int l, int r)
{
    int tam = (r - l + 1)/5;

    if(tam <= 5)
    {
        return insertionSort(f,l,r);
    }

    frac *aux = malloc(tam * sizeof(frac));
    int k = 0;
    int pos = l;
    while( pos <= r)
    {
        if( pos + 4 <= r)
        {
            aux[k++] = insertionSort(f, pos, pos + 4);
        }
        else
        {
            aux[k++] = insertionSort(f, pos, r);
        }
        pos += 5;
    }

    return MoM(aux,0, k - 1);
}

int parcialSorted(frac *f, float pivo, int l, int r)
{
    // // Coloca o pivo na posicao final 
    // frac aux = f[pivo];
    // f[pivo] = f[r];
    // f[r] = aux;
    
    // // Inicia o partition
    // int i = l - 1;
    // int j = r;

    // while (i < j)
    // {
    //    while(f[++i].fraction < f[pivo].fraction);
    //    while(f[--j].fraction >= f[pivo].fraction && j > l);
    //    if(i < j) swap(f[i], f[j]);
    // }
    
    // swap (f[i] ,f[r]);

    // return i;
    int tam = (r - l + 1);
    frac *new = malloc(sizeof(frac) * tam );
    int begin = l, end = r;
    for(int i = 0; i < tam; i++)
    {
        if(f[i].fraction <= pivo)
            new[begin++] = f[i];
        else
            new[end--] =f[i];
    }

    // Copia o vetor
    for(int i = 0; i < tam; i++)
    {
        f[i] = new[i];
    }

    free(new);
    return begin;
}

frac kthFracSmallest(frac *f, int l, int r, int k)
{
    frac pivo = MoM(f, l, r);
    int attemptOracle = parcialSorted(f, pivo.fraction, l, r);
    
    if(attemptOracle == k)
        return f[k];
    
    if(attemptOracle < k)
        return kthFracSmallest(f, l, attemptOracle - 1, k);
    else
        return kthFracSmallest(f, attemptOracle + 1, r, k);
}

int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize)
{   
    frac *f = malloc(sum_n_int(arrSize - 1) * sizeof(frac *));

    int actual = 0;
    
    for(int i = 0; i < arrSize - 1 ; i++)
    {
        for(int j = i + 1; j < arrSize; j++)
        {
            f[actual].numerator = arr[i];
            f[actual].denominator = arr[j];
            f[actual].fraction = arr[i] / arr[j];
        }
    }
    frac anwser = kthFracSmallest(f, 0, arrSize - 1, k);

    free(f);

    // int numDen[2] = {anwser.numerator, anwser.denominator};
    returnSize[1] = anwser.numerator;
    returnSize[2] = anwser.denominator;

    return returnSize;
}

int main()
{
    int arr[4] = {1,2,3,5};
    int arrSize = 4;
    int k = 3;
    int *returnSize = malloc(sizeof(int) * 2);

    returnSize = kthSmallestPrimeFraction(arr, arrSize, k, returnSize);
    return 0;
}