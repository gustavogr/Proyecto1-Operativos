#include "procesos.h"

int main(int argc, char const *argv[])
{
	char const *archEntrada = argv[3];
	char const *archSalida = argv[4];
	int capas,n;
	errno = 0;
	n = (int) strtol(argv[1],NULL,10);
		
	// Verificacion de parametros

	if (errno)
	{
		perror("Error leyendo el numero de enteros");
		return 1;
	}
	errno = 0;
	capas = (int) strtol(argv[2],NULL,10);
	if (errno)
	{
		perror("Error leyendo el numero de niveles");
		return 1;
	}

	if ( pow(2,capas-1) > n )
	{
		printf("ERROR: Hay mas hojas que enteros a ordenar.\n");
		return 1;
	}
	if (capas < 1 || n < 1)
	{
		printf("ERROR: Argumentos invalidos. NumEnteros y NumNiveles deben ser");
		printf(" mayores que 0.\n");
		return 1;
	}

	// Fin de verificacion

	if (capas == 1) // Si es solo una capa todo lo procesa el proceso raiz.
	{
		FILE *fp;
		int arreglo[n];
		if ((fp = fopen(archEntrada, "r")) == NULL) {
			perror("fopen");
			return 1;
		}
		// Leemos el arreglo
		if (fread(&arreglo[0], sizeof(int), n, fp) == 0) {
			perror("fread");
			return 1;
		}
		fclose(fp);
		// Ordenamos el archivo
		quicksort(arreglo, n);
		// Escribimos el archivo
		if ((fp = fopen(archSalida, "w+")) == NULL) {
			perror("fopen");
			return 1;
		}
		int i;
		for (i = 0; i < n; ++i)
		{
			fprintf(fp, "%d ",arreglo[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);

	}
	else if (capas == 2) // Si son dos capas, los hijos inmediatos son hojas.
	{
		int iniIzq,iniDer,nIzq,nDer,pidI,pidD,status;
		char inicio[10],cantidad[10];
		iniIzq = 0;
		iniDer = n/2;
		nDer = n/2;
		nIzq = n - nDer;
		pidI = fork();
		if (pidI == 0)
		{
			sprintf(inicio, "%d", iniIzq);
			sprintf(cantidad, "%d", nIzq);
			execl("./hoja","./hoja",archEntrada,inicio,cantidad,(char *)0);
			perror("No deberias estar aqui. exec");
		}
		pidD = fork();
		if (pidD == 0)
		{
			sprintf(inicio, "%d", iniDer);
			sprintf(cantidad, "%d", nDer);
			execl("./hoja","./hoja",archEntrada,inicio,cantidad,(char *)0);
			perror("No deberias estar aqui. exec"); 
		}
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo izquierdo PID %d fallo.\n",pidI);
		}
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo izquierdo PID %d fallo.\n",pidI);
		}
		
	} else { // Mas de dos capas ya existen nodos intermedios

		int iniIzq,iniDer,nIzq,nDer,pidI,pidD,status;
		char inicio[10],cantidad[10];
		iniIzq = 0;
		iniDer = n/2;
		nDer = n/2;
		nIzq = n - nDer;
		pidI = fork();
		if (pidI == 0)
		{
			sprintf(inicio, "%d", iniIzq);
			sprintf(cantidad, "%d", nIzq);
			execl("./rama","./rama",archEntrada,inicio,cantidad,(char *)0);
			perror("No deberias estar aqui. exec");
		}
		pidD = fork();
		if (pidD == 0)
		{
			sprintf(inicio, "%d", iniDer);
			sprintf(cantidad, "%d", nDer);
			execl("./rama","./rama",archEntrada,inicio,cantidad,(char *)0);
			perror("No deberias estar aqui. exec"); 
		}
		wait(&status);
		wait(&status);

	}






	return 0;
}