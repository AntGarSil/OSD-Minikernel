/*
 * Programa de usuario que realiza una prueba del round-robin usando
 * procesos con distintas prioridades, que hacen muchas llamadas al sistema.
 */

#include "servicios.h"

int main(){
	int i;

	printf("prueba_RR_Avanzada: comienza\n");

	for (i=1; i<=3; i++){
		if (crear_proceso("yosoy")<0)
			printf("Error creando yosoy\n");
		if (crear_proceso_alta_prioridad("yosoy")<0)
			printf("Error creando yosoy\n");
	}
	printf("prueba_RR_ Avanzada: termina\n");
	return 0; 
}
