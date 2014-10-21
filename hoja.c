#include "hoja.h"

int main(int argc, char const *argv[])
{
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
		exit(0);
	}

	if (fseek(fp,inicio*sizeof(int),SEEK_SET))
	{
		perror("fseek");
		exit(0);
	}

	if (fread(&arreglo[0], sizeof(int), cantidad, fp) == 0) {
		perror("fread3");
		exit(0);
	}
	fclose(fp);
	
	quicksort(arreglo,cantidad);

	if ((fp = fopen(archivoS, "w+")) == NULL) {
		perror("fopen");
		exit(0);
	}
	if (fwrite(&arreglo[0], sizeof(int), cantidad, fp) == 0)
		perror("fwrite");
	fclose(fp);
	return 0;
}