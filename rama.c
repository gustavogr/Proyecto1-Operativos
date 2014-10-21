#include "rama.h"

int Tomar_Tiempo()
{
	struct timeval t;     /* usado para tomar los tiempos */
	int dt;
	gettimeofday ( &t, (struct timezone*)0 );
	dt = (t.tv_sec)*1000000 + t.tv_usec;
	return dt;
}

int main(int argc, char *argv[]){
	// Se almacenan los parametros.
	int Tiempo_Inicial,Tiempo_Final;
	Tiempo_Inicial = Tomar_Tiempo();
	int pos_ini = atoi(argv[2]);
	int cant_elem = atoi(argv[3]);
	int capas_rest = atoi(argv[4]);
	// Se asignan los limites y las cantidades a pasar a los hijos.
	int izq_ini = pos_ini;
	int izq_cant = cant_elem/2;
	int der_ini = pos_ini + cant_elem/2;
	int der_cant = cant_elem - izq_cant;
	char inicio[10], cantidad[10], capas[2];
	int status;
	// 
	pid_t pid_izq, pid_der;
	if ((pid_izq = fork()) == 0) {
		sprintf(cantidad, "%d", izq_cant);
		sprintf(inicio, "%d", izq_ini);
		sprintf(capas, "%d", capas_rest -1);
		if (capas_rest > 1) {
			execl("./rama", "./rama", argv[1], inicio, cantidad, capas, (char *) 0);
		} else {
			execl("./hoja", "./hoja", argv[1], inicio, cantidad, (char *) 0);
		}
	}
	if ((pid_der = fork()) == 0) {
		sprintf(cantidad, "%d", der_cant);
		sprintf(inicio, "%d", der_ini);
		sprintf(capas, "%d", capas_rest -1);
		if (capas_rest > 1) {
			execl("./rama", "./rama", argv[1], inicio, cantidad, capas, (char *) 0);
		} else {
			execl("./hoja", "./hoja", argv[1], inicio, cantidad, (char *) 0);
		}
	}
	// Codigo realizado por el padre
	
	wait(&status);
	if (status)
	{
		printf("ERROR: hijo %d fallo.\n",pid_izq);
	}
	wait(&status);
	if (status)
	{
		printf("ERROR: hijo %d fallo.\n",pid_der);
	}
	// Despues de que los hijos terminan
	char arch_izq[10], arch_der[10], arch_propio[10];
	sprintf(arch_izq, "%d.txt", pid_izq);
	sprintf(arch_der, "%d.txt", pid_der);
	sprintf(arch_propio, "%d.txt", getpid());
	int arregloi[cant_elem], arreglod[cant_elem];
	// Se abren los archivos generados por los hijos y se almacena su contenido
	// en arreglos.
	FILE *fp;
	// Archivo izquierdo:
	if ((fp = fopen(arch_izq, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	if (fread(&arregloi[0], sizeof(int), izq_cant, fp) == 0) {
		perror("fread1");
		exit(1);
	}
	fclose(fp);
	// Archivo derecho:
	if ((fp = fopen(arch_der, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	if (fread(&arreglod[0], sizeof(int), der_cant, fp) == 0) {
		perror("fread2");
		exit(1);
	}
	fclose(fp);
	// Se hace merge de los arreglos y se guarda en el arreglo propio:
	int *arreglo = merge(arregloi, arreglod, izq_cant, der_cant);
	// Se escribe dicho arreglo en el archivo propio:

	if ((fp = fopen(arch_propio, "w+")) == NULL) {
		perror("fopen");
		exit(1);
	}
	if (fwrite(&arreglo[0], sizeof(int), cant_elem, fp) == 0)
		perror("fwrite");
	fclose(fp);
	free(arreglo);
	remove(arch_izq);
	remove(arch_der);
	Tiempo_Final = Tomar_Tiempo();
	printf("Nodo Rama PID %d. ",getpid());
	printf("Tiempo de ejecucion: %f ms.\n",(double)(Tiempo_Final - Tiempo_Inicial)/1000 );
	exit(0);
}