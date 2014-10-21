#include "procesos.h"

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
	if (capas == 1) // Si es solo una capa todo lo procesa el proceso raiz.
	{
		FILE *fp;
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

	}
	else if (capas == 2) // Si son dos capas, los hijos inmediatos son hojas.
	{
		int iniIzq,iniDer,nIzq,nDer,pidI,pidD,status;
		char inicio[10],cantidad[10];
		iniIzq = 0;
		iniDer = n/2;
		nIzq = n/2;
		nDer = n - nIzq;
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

		// Esperamos a los hijos, verificamos que no hayn fallado.
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo PID %d fallo.\n",pidI);
			exit(1);
		}
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo PID %d fallo.\n",pidD);
			exit(1);
		}

		// Inicializamos arreglos auxiliares

		int arregloI[nIzq],arregloD[nDer];
		char archIzq[10],archDer[10];
		sprintf(archIzq,"%d.txt",pidI);
		sprintf(archDer,"%d.txt",pidD);
		FILE *fp;
		// Leemos archivo del primer hijo		
		if ((fp = fopen(archIzq, "r")) == NULL) {
			perror("fopen");
			exit(1);
		}
		if (fread(&arregloI[0], sizeof(int), nIzq, fp) == 0) {
			perror("fread");
			exit(1);
		}
		fclose(fp);
		// Leemos archivo del segundo hijo
		if ((fp = fopen(archDer, "r")) == NULL) {
			perror("fopen");
			exit(1);
		}
		if (fread(&arregloD[0], sizeof(int), nDer, fp) == 0) {
			perror("fread");
			exit(1);
		}
		fclose(fp);
		// Merge de los dos arreglos
		int *arregloF = merge(arregloI,arregloD,nIzq,nDer);
		// Escribo el archivo de Salida
		int i;
		if ((fp = fopen(archSalida, "w+")) == NULL) {
			perror("fopen");
			exit(1);
		}
		for (i = 0; i < n; ++i)
		{
			fprintf(fp, "%d ",arregloF[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
		// Libero al arreglo y elimino los .txt
		free(arregloF);
		remove(archIzq);
		remove(archDer);

	} else { // Mas de dos capas ya existen nodos intermedios

		int iniIzq,iniDer,nIzq,nDer,pidI,pidD,status;
		char inicio[10],cantidad[10],capasH[3];
		iniIzq = 0;
		iniDer = n/2;
		nIzq = n/2;
		nDer = n - nIzq;
		pidI = fork();
		if (pidI == 0)
		{
			sprintf(inicio, "%d", iniIzq);
			sprintf(cantidad, "%d", nIzq);
			sprintf(capasH, "%d",capas-2);
			execl("./rama","./rama",archEntrada,inicio,cantidad,capasH,(char *)0);
		}
		pidD = fork();
		if (pidD == 0)
		{
			sprintf(inicio, "%d", iniDer);
			sprintf(capasH, "%d",capas-2);
			sprintf(cantidad, "%d", nDer);
			execl("./rama","./rama",archEntrada,inicio,cantidad,capasH,(char *)0);
		}
		// Esperamos a los hijos, verificamos que no hayn fallado.
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo fallo. Devolvio %d \n",status);
			exit(status);
		}
		wait(&status);
		if (status)
		{
			printf("ERROR: hijo PID %d fallo.\n",pidD);
			exit(status);
		}

		// Inicializamos arreglos auxiliares

		int arregloI[nIzq],arregloD[nDer];
		char archIzq[10],archDer[10];
		sprintf(archIzq,"%d.txt",pidI);
		sprintf(archDer,"%d.txt",pidD);
		FILE *fp;
		// Leemos archivo del primer hijo		
		if ((fp = fopen(archIzq, "r")) == NULL) {
			perror("fopen");
			exit(1);
		}
		if (fread(&arregloI[0], sizeof(int), nIzq, fp) == 0) {
			perror("fread");
			exit(1);
		}
		fclose(fp);
		// Leemos archivo del segundo hijo
		if ((fp = fopen(archDer, "r")) == NULL) {
			perror("fopen");
			exit(1);
		}
		if (fread(&arregloD[0], sizeof(int), nDer, fp) == 0) {
			perror("fread");
			exit(1);
		}
		fclose(fp);
		// Merge de los dos arreglos
		int *arregloF = merge(arregloI,arregloD,nIzq,nDer);
		// Escribo el archivo de Salida
		int i;
		if ((fp = fopen(archSalida, "w+")) == NULL) {
			perror("fopen");
			exit(1);
		}
		for (i = 0; i < n; ++i)
		{
			fprintf(fp, "%d ",arregloF[i]);
		}
		fprintf(fp, "\n");
		fclose(fp);
		// Libero al arreglo y elimino los .txt
		free(arregloF);
		remove(archIzq);
		remove(archDer);
	}

	Tiempo_Final = Tomar_Tiempo();
	printf("Nodo Raiz. Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000);

	exit(0);
}