#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*Programa que simula el funcionamiento del comando echo. recibe dos enteros N, L y opcionalmente palabras a imprimir.
Donde N es las n ultimas palabras y L las l primeras letras.*/

void
printstr(char *str, int l)
{
	int i;

	for (i = 0; i < strlen(str) && i < l; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

int
main(int argc, char *argv[])
{
	/*Variables locales */
	int n;
	int l;
	int first;
	int i;

	/*Si se reciben menos de 3 argumentos -> error */
	if (argc < 3) {
		fprintf(stderr, "usage: %s N L [word ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*comprueba que n y l son enteros positivos o 0 */
	char *endptr;

	n = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0' || n < 0) {
		fprintf(stderr, "error: bad value %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	l = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0' || l < 0) {
		fprintf(stderr, "error: bad value %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	/*Encuentra la primera palabra a imprimir por salida estandar */
	first = argc - n;
	if (first < 3) {
		first = 3;
	}

	/*Salir si no hay nada que imprimir n o l = 0 */

	for (i = first; i <= argc - 1; i++) {
		printstr(argv[i], l);
	}

	exit(EXIT_SUCCESS);
}
