/*
 * usuario/yosoy.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/*
 * Programa de usuario que simplemente imprime su identificador
 */

#include "servicios.h"

#define TOT_ITER 5000	/* ponga las que considere oportuno */

int main(){
	int i;

	for (i=0; i<TOT_ITER; i++)
		printf("yosoy (%d): i=%d, time=%d\n", obtener_id_proceso(), i, obtener_tiempo());
	printf("yosoy (%d): termina\n", obtener_id_proceso());
	return 0;
}

