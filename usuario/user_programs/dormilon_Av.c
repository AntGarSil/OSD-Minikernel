/*
 * Programa de usuario que duerme un proceso 2 segundos.
 */

#include "servicios.h"

int main(){
	int id;

	id=obtener_id_proceso();
	printf("dormilon_AV (%d): comienza\n", id);

	printf("dormilon_Av (%d) duerme 2 segundos\n", id);
	dormir(2);

	printf("dormilon_Av (%d): termina\n", id);
	return 0;
}
