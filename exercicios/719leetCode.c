#include <stdio.h>
#include <stdlib.h>
#define swap(a,b) {int t; t = a; a = b; b = t;}

int sum_n_int(int n)
{
    return (n * (n + 1))/2;
}

int insertionSort(int *f, int l, int r)
{
    int i = l, j = 0;
    while (i < r)
    {   
        j = i + 1;
        while(j - 1 >= l && f[j]< f[j - 1])
        {
            swap(f[j], f[j - 1]);
            j--;
        }
        i++;
    }

    int tam = r - l + 1;
    int mediana;
    if(tam % 2 == 0) mediana = (tam/2) + l - 1;
    else mediana = (tam/2) + l;

    return f[mediana];
}

int MoM(int *f, int l, int r)
{
    int tam = (r - l + 1);

    if(tam <= 5)
    {
        return insertionSort(f,l,r);
    }

    tam = (tam % 5 == 0) ? tam/5 : tam/5 + 1;
    int *aux = malloc((tam) * sizeof(int));
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

int parcialSorted(int *f, int pivo, int l, int r)
{

    int tam = (r - l + 1);
    int *new = malloc(sizeof(int) * tam );
    int begin = 0, end = tam - 1;
    int pivoFound = 0;
    for(int i = l; i <= r; i++)
    {   
       
        if(f[i] == pivo && !pivoFound)
        {
            pivoFound = 1;
        }
        else if(f[i] <= pivo)
        {
            new[begin++] = f[i];
        }
        else 
        {
            new[end--] = f[i];
        }

    }
    new[begin] =  pivo;
    
    int aux = l;
    for(int i = 0; i < tam; i++)
    {
        f[aux++] = new[i];
      
    }
    // printf("\n\n");
    free(new);
    return begin + l;
}

int kthFracSmallest(int *f, int l, int r, int k)
{
    int pivo = MoM(f, l, r);
    int attemptOracle = parcialSorted(f, pivo, l, r);
    
    if(attemptOracle == k)
        return f[k];
    
    if(attemptOracle < k)
        return kthFracSmallest(f, attemptOracle + 1, r, k);
        
    else
        return kthFracSmallest(f, l, attemptOracle - 1, k);
        
}

int smallestDistancePair(int* nums, int numsSize, int k) 
{   
    int tam = sum_n_int(numsSize - 1);
    int *vet = malloc(sizeof(int) * tam);

    int aux = 0;
    for(int i = 0; i < numsSize; i++)
    { 
        for(int j = i + 1; j < numsSize; j++)
            vet[aux++] = abs(nums[i] - nums[j]);
    }

    int answer = kthFracSmallest(vet, 0, tam-1, k - 1);
    return answer;

}

int main()
{
    int num[] =  {};
    int size = 10;
    int k = 2;
    smallestDistancePair(num,size,k);
    return 0;
}