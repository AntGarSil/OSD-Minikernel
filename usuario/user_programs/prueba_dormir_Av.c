/*
 * Programa de usuario que realiza una prueba de la llamada dormir, durmiendo un proceso mientras se ejecuta el otro
 */

#include "servicios.h"

int main(){

	printf("prueba_dormir_Av: comienza\n");

	if (crear_proceso("dormilon_Av")<0)
		printf("Error creando dormilon_Av\n");
	
	if (crear_proceso("yosoy")<0)
		printf("Error creando yosoy\n");

	printf("prueba_dormir_Av: termina\n");

	return 0; 
}
