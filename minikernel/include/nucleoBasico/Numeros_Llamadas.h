/*
 *  minikernel/kernel/include/llamsis.h
 *
 *  Minikernel. Versión 1.0
 *
 *  Fernando Pérez Costoya
 *
 */

/*
 *
 * Fichero de cabecera que contiene el numero asociado a cada llamada
 *
 * 	SE DEBE MODIFICAR PARA INCLUIR NUEVAS LLAMADAS
 *
 */

#ifndef _NUMEROS_LLAMADAS_H_
#define _NUMEROS_LLAMADAS_H_

/* Numero de llamadas disponibles */
#define NUMERO_SERVICIOS 14

#define CREAR_PROCESO 0
#define CREAR_PROCESO_ALTA_PRIORIDAD 1
#define TERMINAR_PROCESO 2
#define ABRIR 3
#define LEER 4
#define ESCRIBIR 5
#define BUSCAR 6
#define CERRAR 7
#define MONTAR 8
#define SINCRONIZAR 9
#define DESMONTAR 10
#define OBTENER_ID_PROCESO 11
#define OBTENER_TIEMPO 12
#define DORMIR 13

#endif /* _NUMEROS_LLAMADAS_H_ */


