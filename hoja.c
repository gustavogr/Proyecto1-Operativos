#include "hoja.h"

int Tomar_Tiempo()
{
	struct timeval t;     /* usado para tomar los tiempos */
	int dt;
	gettimeofday ( &t, (struct timezone*)0 );
	dt = (t.tv_sec)*1000000 + t.tv_usec;
	return dt;
}

int main(int argc, char const *argv[])
{
	
	if (argc != 4)
	{
		printf("ERROR: error en el numero de argumentos de %s.\n",argv[0]);
		exit(1);
	}

	int Tiempo_Inicial,Tiempo_Final;
	Tiempo_Inicial = Tomar_Tiempo();

	char const *archivoE;
	char archivoS[10];
	int inicio,cantidad;
	FILE *fp;

	archivoE = argv[1];
	sprintf(archivoS,"%d.txt",getpid());
	inicio = atoi(argv[2]);
	cantidad = atoi(argv[3]);	
	int arreglo[cantidad];

	if ((fp = fopen(archivoE, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}

	if (fseek(fp,inicio*sizeof(int),SEEK_SET))
	{
		perror("fseek");
		exit(1);
	}
	int c;
	if ((c = fread(&arreglo[0], sizeof(int), cantidad, fp)) < cantidad) {
		if (c == 0)
		{
			perror("fread3");
		} else {
			printf("ERROR: el archivo especificado no tiene suficientes enteros.\n");
		}
		exit(1);
	}
	fclose(fp);
	
	quicksort(arreglo,cantidad);

	if ((fp = fopen(archivoS, "w+")) == NULL) {
		perror("fopen");
		exit(1);
	}
	if (fwrite(&arreglo[0], sizeof(int), cantidad, fp) == 0)
		perror("fwrite");
	fclose(fp);
	Tiempo_Final = Tomar_Tiempo();
	printf("Nodo Hoja PID %d. ",getpid());
	printf("Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000);
	return 0;
}