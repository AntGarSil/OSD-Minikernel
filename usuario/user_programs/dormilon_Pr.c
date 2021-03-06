/*
 * Programa de usuario que parecido al yosoy, pero durmiendo a un proceso en un determinado momento
 */

#include "servicios.h"

#define ITER 5000	/* ponga las que considere oportuno */
#define DUERME 250	/* indica la iteracion en la que se mandara dormir al proceso */

int main(){
	int i, id;

	id=obtener_id_proceso();
	printf("dormilon_Pr (%d): comienza\n", id);
	for (i=0; i<ITER; i++){
		printf("yosoy (%d): i=%d, time=%d\n", id, i, obtener_tiempo());
		if(i == DUERME){
			printf("(%d) duerme 2 segundos\n", id);
			dormir(2);
		}
	}
	printf("dormilon_Pr (%d): termina\n", id);
	return 0;
}
	

