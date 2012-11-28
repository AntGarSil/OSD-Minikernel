/*
 * usuario/init.c
 *
 *  Minikernel. Versi�n 1.0
 *
 *  Fernando P�rez Costoya
 *
 */

/* Programa inicial que arranca el S.O. S�lo se ejecutar�n los programas
   que se incluyan aqu�, que, evidentemente, pueden ejecutar otros
   programas...
*/

/*
 *
 * Contiene las mismas pruebas que se realizan para evaluar la pr�ctica.
 * Para llevar a cabo cada prueba, comente y descomente
 * las l�neas correspondientes. En la versi�n inicial, la parte descomentada
 * se corresponde con funcionalidad ya implementada en el material de apoyo.
 *
 */

#include "servicios.h"

int main(){
int num;
int i;


    printf("init: comienza\n");

	printf("Menu de pruebas\n\n");
	
	printf("1.- Prueba simple\n");
	printf("2.- Excepcion aritmetica\n");
	printf("3.- Excepcion memoria\n");
	printf("4.- Nuevas llamadas\n");
	printf("5.- Dormir procesos\n");
	printf("6.- Planificacion Round-Robin\n");
	printf("7.- Mostrar disco\n");
	printf("8.- Mostrar fichero\n");
	printf("9.- Copiar disco\n");
	printf("10.-Copiar fichero\n");
	printf("11.-Planificacion Round-Robin Avanzada\n");
	printf("12.-Dormir avanzado\n");
	printf("13.-Dormir con prioridades\n");
	printf("\nIntroduzca su opcion:");
	scanf("%d",&num);


	switch (num) {
	case 1:
		/* PRUEBA CREAR PROCESO QUE NO EXISTE */
		if (crear_proceso("noexiste")<0)
			printf("Error creando noexiste\n");

		/* PRUEBA CREAR PROCESO SIMPLE */
		if (crear_proceso("simplon")<0)
			printf("Error creando simplon\n");
		break;
	case 2:
		/* PRUEBA PROVOCAR EXCEPCION ARITMETICA */
		if (crear_proceso("excep_arit")<0)
			printf("Error creando excep_arit\n");
		break;
	case 3:
		/* PRUEBA PROVOCAR EXCEPCION MEMORIA */
		if (crear_proceso("excep_mem")<0)
			printf("Error creando excep_mem\n");
		break;
	case 4:
		/* PRUEBA DE LAS NUEVAS LLAMADAS */
		for (i=1; i<=2; i++) {
			if (crear_proceso("yosoy")<0)
				printf("Error creando yosoy\n");
		}
		break;
	case 5:
		/* PRUEBA DE LA LLAMADA DORMIR */
		if (crear_proceso("prueba_dormir")<0)
			printf("Error creando prueba_dormir\n");
		break;
	case 6:
		/* PRIMERA PRUEBA DE ROUND-ROBIN */
		if (crear_proceso("prueba_RR")<0)
			printf("Error creando prueba_RR\n");
		break;
	case 7:
		/* PRUEBA DEL DRIVER DE CDROM */
		if (crear_proceso("mostrar_disco")<0)
			printf("Error creando mostrar_disco\n");
		break;
	case 8:
		/* PRUEBA DEL SISTEMA DE FICHEROS SOLO LECTURA */	
		if (crear_proceso("mostrar_fichero")<0)
			printf("Error creando mostrar_fichero\n");
		break;
	case 9:
		/* PRUEBA DEL DRIVER DE DISCO */
		if (crear_proceso("copiar_disco")<0)
			printf("Error creando copiar_disco\n");
		break;
	case 10:
		/* PRUEBA DEL SISTEMA DE FICHEROS LECTURA/ESCRITURA */	
		if (crear_proceso("copiar_fichero")<0)
			printf("Error creando copiar_fichero\n");
		break;
	case 11:
		/* PRUEBA DE ROUND-ROBIN CON PRIORIDADES */	
		if (crear_proceso("prueba_RR_Av")<0)
			printf("Error creando prueba_RR_Av\n");
		break;
	case 12:
		/* PRUEBA AVANZADA DE DORMIR */	
		if (crear_proceso("prueba_dormir_Av")<0)
			printf("Error creando prueba_dormir_Av\n");
		break;
	case 13:
		/* PRUEBA DORMIR CON PRIORIDADES */	
		if (crear_proceso("prueba_dormir_Pr")<0)
			printf("Error creando prueba_dormir_Pr\n");
		break;
	}

    printf("init: fin\n");

	return (0);
}
