#include "ordenamiento.h"

int * merge(int arreglo1[], int arreglo2[], int tam1, int tam2)
{
    int *auxiliar =(int *)malloc(sizeof(int)*(tam1+tam2));
    int i = 0, j = 0, k = 0;
    while ((i < tam1) && (j < tam2)) {
        if (arreglo1[i] <= arreglo2[j]) {
            auxiliar[k++] = arreglo1[i++];
        } else {
            auxiliar[k++] = arreglo2[j++];
        }
    }
    while (i < tam1)
        auxiliar[k++] = arreglo1[i++];  
    while (j < tam2)
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

int * merge_h(int arreglo[], int ini, int med, int fin)
{
    int *auxiliar = (int *)malloc(sizeof(int)*(fin-ini));
    int i = ini, j = med, k = 0;
    while ((i < med) && (j < fin)) {
        if (arreglo[i] <= arreglo[j]) {
            auxiliar[k++] = arreglo[i++];
        } else {
            auxiliar[k++] = arreglo[j++];
        }
    }
    while (i < med)
        auxiliar[k++] = arreglo[i++];  
    while (j < fin)
        auxiliar[k++] = arreglo[j++];
    return auxiliar;
}


/*int main(int argc, const char * argv[])
{
    int lista1[] = {1, 3, 5 , 7, 9};
    int lista2[] = {0, 2, 4 , 6, 8, 8, 8, 8, 10, 12};
    int lista3[] = {2, 4, 6, -47, -1, 3};
    int lista4[] = {5, 48, 39, 72 ,1435 ,13548};
    int t1 = sizeof(lista1)/sizeof(int);
    int t2 = sizeof(lista2)/sizeof(int);
    int t3 = sizeof(lista3)/sizeof(int);
    int t4 = sizeof(lista4)/sizeof(int);

    int *arreglo = merge(lista1, lista2, t1, t2);
    int *arreglo1 = merge_h(lista3, 0, 3, 6);
    quicksort_rec(lista4, 0, t4 -1);
    //quicksort(lista4, t4);

    int g;
    printf("Merge procesos:\n");  
    for (g = 0; g < t1+t2; g++){
        printf("%d ", arreglo[g]);
    }
    printf("\n");
    printf("Merge hilos:\n");  
    for (g = 0; g < t3; g++){
        printf("%d ", arreglo1[g]);
    }
    printf("\n");
    printf("quicksort hilos (recursivo):\n");  
    for (g = 0; g < t4; g++){
        printf("%d ", lista4[g]);
    }
    printf("\n");*/
    /*printf("quicksort procesos:\n");      
    for (g = 0; g < t4; g++){
        printf("%d ", lista4[g]);
    }
    printf("\n");
}*/