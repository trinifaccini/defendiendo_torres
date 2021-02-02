#ifndef __TP2_H__
#define __TP2_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "defendiendo_torres.h"

#define FIN				"\033[0m"
#define ROJO 			"\033[1m\033[31m"
#define VERDE 			"\033[1m\033[32m"
#define AMARILLO		"\033[1m\033[33m"
#define MAGENTA 		"\033[1m\033[35m"

#define FORMATO_LECTURA_RANKING "%[^;];%i\n"
#define FORMATO_SALIDA_RANKING "%s;%i\n"

#define MAX_LONGITUD_CAMINO 200

typedef struct aux {
	coordenada_t camino[MAX_LONGITUD_CAMINO];
	int tope;
} caminos_aux_t;

typedef struct usuario {
	char nombre[MAX_NOMBRE];
	int puntos;
} usuario_t;

typedef struct ranking {
	int nivel_1;
	int nivel_2;
	int nivel_3;
	int nivel_4;	
} ranking_t;

//PRE:  recibira una configuracion con todas sus estructuras validas y un string correspondiente al nombre en donde el usuario querra guardar la grabacion
//  	de su juego.
//POST: jugara la partida. 
void jugar_juego(configuracion_t configuracion, char ruta_grabacion[MAX_ARCHIVO]);


#endif /*__TP2_H__ */