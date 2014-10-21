#include "ordenamiento.h"

int * merge(int arreglo1[], int arreglo2[], int tam1, int tam2)
{
    int *auxiliar =(int *)malloc(sizeof(int)*(tam1+tam2));
    int i = 0, j = 0, k = 0;
    while ((i <= (tam1 - 1)) && (j <= (tam2 - 1))) {
        if (arreglo1[i] <= arreglo2[j]) {
            auxiliar[k++] = arreglo1[i++];
        } else {
            auxiliar[k++] = arreglo2[j++];
        }
    }
    while (i <= tam1 -1)
        auxiliar[k++] = arreglo1[i++];  
    while (j <= tam2 -1)
        auxiliar[k++] = arreglo2[j++];
    return auxiliar;
}

void quicksort_rec(int arreglo[], int lim_izq, int lim_der)
{
int izq, der, temp, piv;
    der = lim_der;
    izq = lim_izq;
    piv = arreglo[(izq + der)/2];
    do {
        while (arreglo[izq] < piv && izq < lim_der) izq++;
        while (piv < arreglo[der] && der > lim_izq) der--;
        if (izq <= der)
        {
            temp = arreglo[izq];
            arreglo[izq] = arreglo[der];
            arreglo[der] = temp;
            izq++;
            der--;
        }
    } while(izq <= der);
    if(lim_izq < der){quicksort_rec(arreglo, lim_izq, der);}
    if(lim_der > izq){quicksort_rec(arreglo, izq, lim_der);}
}

void quicksort(int arreglo[], int tam)
{
    quicksort_rec(arreglo, 0, tam-1);
}
  
/*int main(int argc, const char * argv[])
{
    int lista1[] = {1, 3, 5 , 7, 9};
    int lista2[] = {0, 2, 4 , 6, 8, 8, 8, 8, 10, 12};
    int t1 = sizeof(lista1)/sizeof(int);
    int t2 = sizeof(lista2)/sizeof(int);
    int *arreglo = merge(lista1, lista2, t1, t2);
    int g;
    for (g = 0; g < t1+t2; g++){
        printf("%d ", arreglo[g]);
    }
    printf("\n");
}*/