#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include "ordenamiento.h"

int Tomar_Tiempo();

typedef struct datos_hilo {
	int *arreglo;
	int inicio;
	int cantidad;
	int capas;
} datos_hilo;
