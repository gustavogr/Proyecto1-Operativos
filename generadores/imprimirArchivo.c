#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	int cant,i;
	errno = 0;
	cant = (int)strtol(argv[2], (char **)NULL, 10);
	if (errno)
	{
		perror("strtol");
	}	
	FILE *fp;
	int num1[cant];
	if ((fp = fopen(argv[1], "r")) == NULL) {
		perror("**fopen");
		exit(0);
	}
	if (fread(&num1[0], sizeof(int), cant, fp) == 0) {
		perror("fread");
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