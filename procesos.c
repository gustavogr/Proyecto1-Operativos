#include "procesos.h"

int main(int argc, char const *argv[])
{
	char *archEntrada = argv[3];
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
	if (2^(capas-1)<n)
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

		if (fread(&arreglo[0], sizeof(int), n, fp) == 0) {
			perror("fread");
			return 1;
		}
		fclose(fp);

	}






	return 0;
}