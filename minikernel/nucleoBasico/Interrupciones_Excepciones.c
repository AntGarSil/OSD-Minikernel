/*
 *  Interrupciones_Excepciones.c
 *  
 *
 *  Created by Javier Fernandez Muñoz on 08/12/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "minikernel.h"


/***************************************************************
 * VARIABLES GLOBALES
 ***************************************************************/

/*
 * Variable global que representa el buffer de tareas pendientes de la 
 * interrupcion software.
 */

TipoListaTareas listaTareasPend;

/*
 * Variable global que contabiliza las interrupciones de reloj desde el inicio
 */
unsigned int ticks = 0;

/***************************************************************
 * FUNCIONES PUBLICAS
 ***************************************************************/

/*---------------------------------------------------------------------*
 * Funciones para gestionar la lista de tareas pendientes de la int. SW
 *---------------------------------------------------------------------*/

/*
 * Inicializar el buffer de tareas pendientes
 * de la interrupciÛn  software.
 */
void iniciarTareasPend(TipoListaTareas *lista)
{
	lista->primero = 0;
	lista->ultimo = 0;
}
/*
 * Inserta una tarea al final del buffer de tareas pendientes
 * de la interrupciÛn  software.
 */
void insertarUltimaTareaPend(TipoListaTareas *lista, void (*funcion)(void *), void *datos)
{
	if (lista->primero == (lista->ultimo+1) % MAX_TAREAS) { 
		/* si el buffer esta lleno, error */
		printk("-> ERROR: LISTA TAREAS PENDIENTE LLENA, SE DESCARTA\n");
	} else { 
		/* cargar la entrada y apuntar que hay uno mas */
		lista->tablaTareas[lista->ultimo].tarea.funcionTareaPend = funcion;
		lista->tablaTareas[lista->ultimo].datos = datos;
		lista->ultimo = (lista->ultimo+1) % MAX_TAREAS;
	}
}

/*
 * Obtener una tarea del principio de la lista de tareas pendientes
 * de la interrupcion  software.
 */
void obtenerPrimeraTareaPend(TipoListaTareas *lista, void (**funcion)(void *), void **datos)
{
	if (lista->primero == lista->ultimo) { 
		/* si el buffer esta vacio, error */
		printk("-> ERROR: LISTA TAREAS PENDIENTE VACIA\n");
	} else { 
		/* obtener la entrada y apuntar que hay uno menos */
		(*funcion) = lista->tablaTareas[lista->primero].tarea.funcionTareaPend;
		(*datos) = lista->tablaTareas[lista->primero].datos;
		lista->primero = (lista->primero+1) % MAX_TAREAS;
	}
}

/* 
 * Devuelve TRUE si hay tareas pendientes
 */
int hayTareasPend(TipoListaTareas *lista)
{
	return (lista->primero != lista->ultimo);
}

/*------------------------------------------------*
 * Manejadores de las interrupciones y excepciones
 *------------------------------------------------*/

/*
 * Tratamiento de interrupciuones software
 */
void interrupcionSoftware()
{
	void (*funcion)(void *);
	void *datos = NULL;

	//printk("-> TRATANDO INT. SW\n");
	while (hayTareasPend(&(listaTareasPend)) ) {

		/* mientras haya tareas en el buffer, ejecutarlas */
		obtenerPrimeraTareaPend(&(listaTareasPend), &(funcion), &(datos));
		//printk("LLEGGGGGOOOOOOOOOO\n");
		funcion (datos);
	}	
	return;
}


/*
 * Espera a que se produzca una interrupcion
 */
void esperaInterrupcion()
{
	int nivel;

	//printk("-> NO HAY LISTOS. ESPERA INT\n");

	/* Baja al mÌnimo el nivel de interrupciÛn mientras espera */
	nivel=fijar_nivel_int(NIVEL_1);
	/* 
	 * Como no se pueden desinhibir totalmente las int 
	 * si hay alguna int. sw. pendiente la hacemos en lugar de parar
	 */
	if (hayTareasPend(&(listaTareasPend)) ) {
		interrupcionSoftware();
	} else {
		//printk("-> EJECUTANDO HALT\n");
		halt();
	}
	fijar_nivel_int(nivel);
}


/*
 *
 * Manejadores de interrupciones y excepciones genericas
 *	
 */

/*
 * Manejador de excepciones aritmeticas
 */
void excepcionAritmetica()
{
	if (!viene_de_modo_usuario())
		panico("excepcion aritmetica cuando estaba dentro del kernel");


	printk("-> EXCEPCION ARITMETICA EN PROC %d\n", procesoActual->id);
	liberarProceso();

        return; /* no deberÌa llegar aqui */
}

/*
 * Manejador de excepciones en el acceso a memoria
 */
void excepcionMemoria(){

	if (!viene_de_modo_usuario())
		panico("excepcion de memoria cuando estaba dentro del kernel");


	//printk("-> EXCEPCION DE MEMORIA EN PROC %d\n", procesoActual->id);
	liberarProceso();

        return; /* no deberÌa llegar aqui */
}

/*
 * Manejador de interrupciones para toda la tabla de dispositivos
 */
void interrupcionDispositivos()
{
	int i;

	//printk("-> INTERRUPCION DE DISPOSITIVOS\n");
	for (i=0; i<MAX_TABLA_DISPOSITIVOS; i++) {
		if  ( (TRUE == tablaDispositivos[i].ocupado) && 
			  (NULL != tablaDispositivos[i].interrupcionHW) ) {
			tablaDispositivos[i].interrupcionHW(i);
		}
	}
	return;
}


/*
 * Manejador de interrupciones de reloj
 */
void interrupcionReloj()
{
	int nivel;

	//printk("-> TRATANDO INT. DE RELOJ\n");

	/*Establecemos el nivel de interrupcion e incrementamos el numero de ticks*/
	nivel=fijar_nivel_int(NIVEL_3);
	ticks = ticks + 1;

	/*Insertamos las tareas en la lista de tareas pendientes*/
	insertarUltimaTareaPend(&listaTareasPend, despertar_Dormidos, NULL);
	insertarUltimaTareaPend(&listaTareasPend, planificar_Rodaja, NULL);
	
	/*Generamos una interrupcion software */
	activar_int_SW();
	fijar_nivel_int(nivel);

    return;
}

/*
 * Tarea que despierta procesos dormidos
 */
void despertar_Dormidos(void *p)
{
	TipoBCP * procesoAux;	

	/* Comprobamos que haya procesos dormidos y que su despertarEnTicks sea menor que el numero actual de ticks*/
	procesoAux = primeroListaBCP(&listaDormidos);
	while ((procesoAux != NULL) && procesoAux->despertarEnTicks < ticks){

	/*Cambiamos el estado del proceso, lo eliminamos de la lista de dormidos y lo insertamos en la de listos */		
		procesoAux->estado = LISTO;
		eliminarPrimeroListaBCP(&listaDormidos);
		insertarConPrioridad(procesoAux);

	/*Obtenemos el siguiente proceso dormido*/
		procesoAux = primeroListaBCP(&listaDormidos);
	}
	return;		
}

/* 
 * Tarea que implementa la planificacion Round-Robin 
 */
void planificar_Rodaja(void *p)
{
	TipoBCP * procesoAnterior = NULL;

	if(procesoActual != NULL){
	/*Decrementamos el valor de la rodaja del proceso*/
		procesoActual->rodaja = procesoActual->rodaja -1;
	/*Si la rodaja del proceso es 0 o menor reiniciamos su valor al de la constante TICKS_PRO_RODAJA*/
		if(procesoActual->rodaja <= 0){

			procesoActual->rodaja = TICKS_POR_RODAJA;
	/*Cambiamos el estado del proceso y lo insertamos en la lista correspondiente*/
			procesoActual->estado = LISTO;
			insertarConPrioridad(procesoActual);
	/*Obtenemos un nuevo proceso o esperamos hasta que lo obtengamos*/
			procesoAnterior = procesoActual;
			procesoActual = planificador();
			while(procesoActual==NULL)
			{
				esperaInterrupcion();
				procesoActual=planificador();
			}
	/*Cambiamos el estado del proceso y realizamos el cambio de contexto*/
			procesoActual->estado = EJECUCION;
			cambio_contexto(&(procesoAnterior->contextoRegs), &(procesoActual->contextoRegs));
		}

	}
	return;
}


