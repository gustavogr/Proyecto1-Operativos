#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include "ordenamiento.h"

int Tomar_Tiempo();

void* hoja (void *datos);

void* rama (void *datos);

typedef struct datos_hilos {
	int *arreglo;
	int inicio;
	int cantidad;
	int capas;
}datos_hilos;
