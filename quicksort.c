#include "quicksort.h"

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