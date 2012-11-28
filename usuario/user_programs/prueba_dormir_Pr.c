/*
 * Programa de usuario que realiza una prueba de la llamada dormir incluyendo prioridades
 */

#include "servicios.h"

int main(){

	printf("prueba_dormir_Pr: comienza\n");

	if (crear_proceso_alta_prioridad("dormilon_Pr")<0)
		printf("Error creando dormilon_Pr\n");
	
	if (crear_proceso("yosoy")<0)
		printf("Error creando yosoy\n");

	printf("prueba_dormir_Pr: termina\n");

	return 0; 
}
