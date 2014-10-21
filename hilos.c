#include "hilos.h"

int Tomar_Tiempo()
{
	struct timeval t;     /* usado para tomar los tiempos */
	int dt;
	gettimeofday ( &t, (struct timezone*)0 );
	dt = (t.tv_sec)*1000000 + t.tv_usec;
	return dt;
}


void* hoja (void *param)
{
	int Tiempo_Inicial,Tiempo_Final;
	Tiempo_Inicial = Tomar_Tiempo();
	datos_hilos *datos = (datos_hilos *) param;	
	quicksort_rec(datos->arreglo,datos->inicio,datos->cantidad-1+datos->inicio);
	Tiempo_Final = Tomar_Tiempo();
	printf("Hilo hoja. Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000);
	return 0;
}

void* rama (void *param)
{
	int Tiempo_Inicial,Tiempo_Final;
	Tiempo_Inicial = Tomar_Tiempo();
	datos_hilos* datos = (datos_hilos *) param;
	pthread_t hiloIzq, hiloDer;
	int ini,cant;
	ini = datos->inicio;
	cant = datos->cantidad;
	datos_hilos *datosIzq = malloc(sizeof(datos_hilos));
	datos_hilos *datosDer = malloc(sizeof(datos_hilos));
	datosIzq->arreglo = datos->arreglo;
	datosIzq->inicio = ini;
	datosIzq->cantidad = cant/2;
	datosIzq->capas = datos->capas - 1;
	datosDer->arreglo = datos->arreglo;
	datosDer->inicio = cant/2 + ini;
	datosDer->cantidad = cant - cant/2;
	datosDer->capas = datos->capas - 1;
	if (datos->capas == 2) // Si son dos capas, ya vienen las hojas
	{
		pthread_create(&hiloIzq, NULL, &hoja,(void *)datosIzq);
		pthread_create(&hiloDer, NULL, &hoja,(void *)datosDer);
	} else { // Sino, se procesan como ramas
		pthread_create(&hiloIzq, NULL, &rama,(void *)datosIzq);
		pthread_create(&hiloDer, NULL, &rama,(void *)datosDer);
	}
	// Esperamos a los hijos
	pthread_join(hiloIzq,NULL);
	pthread_join(hiloDer,NULL);
	int *auxiliar = merge_h(datos->arreglo,ini,cant/2 + ini,ini+cant);
	int i;
	// Copiamos el auxiliar al arreglo original
	for (i = 0; i < cant; ++i)
	{
		datos->arreglo[ini+i] = auxiliar[i];
	}
	free(datosIzq);
	free(datosDer);
	free(auxiliar);
	Tiempo_Final = Tomar_Tiempo();
	printf("Hilo rama. Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000);
	return 0;
}



int main(int argc, char const *argv[])
{
	if (argc!=5)
	{
		printf("Uso: %s NumEnteros NumNiveles ArchivoEnterosDesordenado ",argv[0]);
		printf("ArchivoEnterosOrdenado\n");
		exit(1);
	}

	char const *archEntrada = argv[3];
	char const *archSalida = argv[4];
	int capas,n;
	int Tiempo_Inicial,Tiempo_Final;

	errno = 0;
	n = (int) strtol(argv[1],NULL,10);
		
	// Verificacion de parametros

	if (errno)
	{
		perror("Error leyendo el numero de enteros");
		exit(1);
	}
	errno = 0;
	capas = (int) strtol(argv[2],NULL,10);
	if (errno)
	{
		perror("Error leyendo el numero de niveles");
		exit(1);
	}

	if ( pow(2,capas-1) > n )
	{
		printf("ERROR: Hay mas hojas que enteros a ordenar.\n");
		exit(1);
	}
	if (capas < 1 || n < 1)
	{
		printf("ERROR: Argumentos invalidos. NumEnteros y NumNiveles deben ser");
		printf(" mayores que 0.\n");
		exit(1);
	}

	// Fin de verificacion
	
	Tiempo_Inicial = Tomar_Tiempo();
	FILE *fp;
	// Creamos el arreglo
	int arreglo[n];
	if ((fp = fopen(archEntrada, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	// Leemos el arreglo
	if (fread(&arreglo[0], sizeof(int), n, fp) == 0) {
		perror("fread");
		exit(1);
	}
	fclose(fp);
	if (capas == 1) // Si es solo una capa todo lo procesa el main.
	{
		// Ordenamos el archivo
		quicksort(arreglo, n);
		// Escribimos el archivo
		if ((fp = fopen(archSalida, "w+")) == NULL) {
			perror("fopen");
			exit(1);
		}
		int i;
		for (i = 0; i < n; ++i)
		{
			fprintf(fp, "%d ",arreglo[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
	} else { // Si es mas de una capa lo procesamos con hilos
		pthread_t hiloIzq, hiloDer;
		datos_hilos *datosIzq = malloc(sizeof(datos_hilos));
		datos_hilos *datosDer= malloc(sizeof(datos_hilos));
		datosIzq->arreglo = arreglo;
		datosIzq->inicio = 0;
		datosIzq->cantidad = n/2;
		datosIzq->capas = capas - 1;
		datosDer->arreglo = arreglo;
		datosDer->inicio = n/2;
		datosDer->cantidad = n - n/2;
		datosDer->capas = capas - 1;
		if (capas == 2) // Si son dos capas, ya vienen las hojas
		{
			pthread_create(&hiloIzq, NULL, &hoja,(void *)datosIzq);
			pthread_create(&hiloDer, NULL, &hoja,(void *)datosDer);
		} else { // Sino, se procesan como ramas
			pthread_create(&hiloIzq, NULL, &rama,(void *)datosIzq);
			pthread_create(&hiloDer, NULL, &rama,(void *)datosDer);
		}
		// Esperamos a los hijos
		pthread_join(hiloIzq,NULL);
		pthread_join(hiloDer,NULL);
		int * auxiliar = merge_h(arreglo,0,n/2,n);
		// Escribimos el arreglo final al archivo
		int i;
		if ((fp = fopen(archSalida, "w+")) == NULL) {
			perror("fopen");
			exit(1);
		}
		for (i = 0; i < n; ++i)
		{
			fprintf(fp, "%d ",auxiliar[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
		free(datosIzq);
		free(datosDer);
		// Libero al arreglo
		free(auxiliar);
	}
	Tiempo_Final = Tomar_Tiempo();
	printf("Main. Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000);

	return 0;
}