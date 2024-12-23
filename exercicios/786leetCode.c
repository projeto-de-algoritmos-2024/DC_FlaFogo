/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {frac t; t = a; a = b; b = t;}

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
    int i = l, j = 0;
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
    if(tam % 2 == 0) mediana = (tam/2) + l - 1;
    else mediana = (tam/2) + l;

    return f[mediana];
}

frac MoM(frac *f, int l, int r)
{
    int tam = (r - l + 1);

    if(tam <= 5)
    {
        return insertionSort(f,l,r);
    }

    tam = (tam % 5 == 0) ? tam/5 : tam/5 + 1;
    frac *aux = malloc((tam) * sizeof(frac));
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

    int tam = (r - l + 1);
    frac *new = malloc(sizeof(frac) * tam );
    int begin = 0, end = tam - 1;
    frac newPivo;
    for(int i = l; i <= r; i++)
    {   
        if(f[i].fraction == pivo)
            newPivo = f[i];

        else if(f[i].fraction < pivo)
            new[begin++] = f[i];
        else 
            new[end--] =f[i];
    }
     
    new[begin] = newPivo;
    
    // Copia o vetor
    int aux = l;
    for(int i = 0; i < tam; i++)
    {
        f[aux++] = new[i];
    }

    free(new);
    return begin + l;
}

frac kthFracSmallest(frac *f, int l, int r, int k)
{
    frac pivo = MoM(f, l, r);
    int attemptOracle = parcialSorted(f, pivo.fraction, l, r);
    
    if(attemptOracle == k)
        return f[k];
    
    if(attemptOracle < k)
        return kthFracSmallest(f, attemptOracle + 1, r, k);
        
    else
        return kthFracSmallest(f, l, attemptOracle - 1, k);
        
}

int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize)
{   
    frac *f = malloc(sum_n_int(arrSize - 1) * sizeof(frac));
    int actual = 0;
    
    for(int i = 0; i < arrSize - 1 ; i++)
    {
        for(int j = i + 1; j < arrSize; j++)
        {
            f[actual].numerator = arr[i];
            f[actual].denominator = arr[j];
            f[actual].fraction = (float)arr[i] / arr[j];
            actual++;
        }
    }
    frac awnser = kthFracSmallest(f, 0, sum_n_int(arrSize - 1) - 1, k - 1);

    free(f);

    int *result = malloc(2 * sizeof(int)); // Aloca o array retornado
    result[0] = awnser.numerator;
    result[1] = awnser.denominator;

    *returnSize = 2; // Define o tamanho do array
    return result;
}

int main()
{
    int arr[] = {1,13,17,59};
    int arrSize = 4;
    int k = 6;
    int *returnSize = malloc(sizeof(int) * 2);

    returnSize = kthSmallestPrimeFraction(arr, arrSize, k, returnSize);
    printf("%d %d\n", returnSize[0], returnSize[1]);
    return 0;
}