#ifndef __TP3_H__
#define __TP3_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "juego.h"


//PRE:	recibira una configuracion y un archivo de texto en donde guardarla (por referencia).
//POST:	copiara los datos de la configuracion en el archivo.
void pedir_configuracion(configuracion_t* configuracion, FILE** arch_config);

//PRE:	recibe un archivo de texto correspondiente a una configuracion (por referencia).
//POST:	copiara las coordenadas del camino en el archivo 
void pedir_caminos(FILE** arch_config);

//PRE:	recibe una configuracion (por referencia) y un archivo de configuracion.
//POST:	asignara al struct configuracion todos los datos que posee el archivo.
void guardar_configuracion(configuracion_t* configuracion, FILE* arch_config, char nombre_archivo_configuracion[MAX_NOMBRE]);

//PRE:	recibe una configuracion (por referencia)
//POST:	asignara a todos los campos del struct configuracion un "-1", para que el usuario juegue con la configuracion por defecto.
void guardar_configuracion_default(configuracion_t* configuracion);

//PRE: 	recibe un archivo binario correspondiente a una grabacion y un float que representa la velocidad en la que se reproducira.
//POST:	mostrará una grabacion del juego.
void mostrar_grabacion(FILE* arch_grabacion, float velocidad);

//PRE: recibe un archivo de texto correspondiente a un ranking, un tipo de dato bool y una cantidad de usuarios a listar.
//POST: mostrara por pantalla el archivo de ranking-
//---> si hay_listados = true, mostrara cierta cantidad de usuarios del archivo.
//---> si hay_listados = false, mostrara el archivo completo.
void mostrar_ranking(FILE* arch_ranking, bool hay_listados, int listados);




#endif /*__TP3_H__ */