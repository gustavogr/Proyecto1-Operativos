#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int cant = (int)strtol(argv[2], (char **)NULL, 10);
	int i,num[cant],num1[cant];
	FILE *fp;
	srand(time(NULL));
	for (i = 0; i < cant; ++i)
	{
		num[i] = rand();
	}


	// char *mensaje = "Error en los argumentos. Use generador [nombre_archivo] [cantidad de numeros]."
	if ((fp = fopen(argv[1], "w")) == NULL)
		perror("fopen:");
	if (fwrite(&num[0], sizeof(int), cant, fp) == 0)
		perror("fwrite:");
	fclose(fp);
	
	// Probando el archivo 

	if ((fp = fopen(argv[1], "r")) == NULL) {
		perror("**fopen:");
		exit(0);
	}
	if (fread(&num1[0], sizeof(int), cant, fp) == 0) {
		perror("fread:");
		exit(0);
	}
	fclose(fp);

	for (i = 0; i < cant; ++i)
	{
		printf("%d ",num1[i]);
	}
	printf("\n");
	return 0;
}
