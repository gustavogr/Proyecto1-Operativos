#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	
	if (argc != 3)
	{
		printf("Uso: %s archivoSalida cantNumeros\n",argv[0]);
		return 1;
	}

	int cant;
	errno = 0;
	cant = (int)strtol(argv[2], (char **)NULL, 10);
	if (errno)
	{
		perror("strtol");
	}	
		

	int i,num[cant];
	FILE *fp;
	srand(time(NULL));
	for (i = 0; i < cant; ++i)
	{
		num[i] = rand() % 1000;
	}


	if ((fp = fopen(argv[1], "w")) == NULL)
		perror("fopen:");
	if (fwrite(&num[0], sizeof(int), cant, fp) == 0)
		perror("fwrite");
	fclose(fp);

	return 0;
}
