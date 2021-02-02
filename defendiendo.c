#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

int main (int argc, char *argv[]){

	char ruta_archivo[MAX_ARCHIVO];
	char ruta_grabacion[MAX_ARCHIVO];
	char flag[MAX_ARCHIVO];
	char ruta[MAX_ARCHIVO];
	char auxiliar[MAX_ARCHIVO];

	FILE* arch_config;
	FILE* arch_caminos;	
	FILE* arch_ranking;
	FILE* arch_grabacion;

	if((strcmp(argv[1], "crear_configuracion") == 0) && (argc >= 3)){

		strcpy (ruta_archivo, argv[2]);
		arch_config = fopen(ruta_archivo, "w");

		if (!arch_config){

			printf(ROJO "ERROR AL INTENTAR CREAR EL ARCHIVO\n" FIN);
			return -1;

		}else{

			configuracion_t configuracion;
			pedir_configuracion(&configuracion, &arch_config);
			fclose(arch_config);

		}

	}else if((strcmp(argv[1], "crear_camino") == 0) && (argc >= 3)){

		strcpy (ruta_archivo, argv[2]);
		arch_caminos = fopen(ruta_archivo, "w");

		if (!arch_caminos){
			printf(ROJO "ERROR AL INTENTAR CREAR EL ARCHIVO\n" FIN);
			return -1;

		} else {

			pedir_caminos(&arch_caminos);
			fclose(arch_caminos);
		}

	}else if((strcmp(argv[1], "ranking") == 0) && (argc >= 2)){

		int listados;
		bool hay_listados = false;
		char nombre_archivo_ranking[MAX_ARCHIVO];

		for (int i = 2; i < argc; i++){
			sscanf(argv[i], "%[^=]=%s", flag, auxiliar);

			if(strcmp(flag, "listar") == 0){
				hay_listados = true;
				listados = atoi(auxiliar);

			}else if(strcmp(flag, "config") == 0){
				strcpy(ruta_archivo, auxiliar);
			}
		}

		if(ruta_archivo[0] == '\0'){

			strcpy(nombre_archivo_ranking, "ranking.csv");

		}else{

			strcpy(nombre_archivo_ranking, "ranking_");
			strcat(nombre_archivo_ranking, ruta_archivo);
			strcat(nombre_archivo_ranking, ".csv");
		}

		arch_ranking = fopen(nombre_archivo_ranking, "r");

		if (!arch_ranking){
			printf(ROJO "ERROR AL INTENTAR LEER EL ARCHIVO O ESE ARCHIVO NO EXISTE\n" FIN);
			return -1;

		} else {

			mostrar_ranking(arch_ranking, hay_listados, listados);

		}

	}else if((strcmp(argv[1], "jugar") == 0) && (argc >= 2)){

		strcpy(ruta_archivo, "\0");
		bool hay_config = false;
		strcpy(ruta_grabacion, "\0");
		configuracion_t configuracion;

		for (int i = 2; i < argc; i++){
			sscanf(argv[i], "%[^=]=%s", flag, ruta);
			if(strcmp(flag, "config") == 0){
				strcpy(ruta_archivo, ruta);
				hay_config = true;
			}else if(strcmp(flag, "grabacion") == 0){
				strcpy(ruta_grabacion, ruta);
			}
		}

		if (hay_config == true){

			arch_config = fopen(ruta_archivo, "r");

			if (!arch_config){
				printf(ROJO "ERROR AL INTENTAR LEER EL ARCHIVO O ESE ARCHIVO NO EXISTE\n" FIN);
				return -1;
		
			}else{

				guardar_configuracion(&configuracion, arch_config, ruta_archivo);
				jugar_juego(configuracion, ruta_grabacion);
			}

		}else{

			guardar_configuracion_default(&configuracion);
			jugar_juego(configuracion, ruta_grabacion);

		}
		

	} else if((strcmp(argv[1], "poneme_la_repe") == 0) && (argc >= 3)){

		float velocidad = 0.2f;

		for (int i = 2; i < argc; i++){
			sscanf(argv[i], "%[^=]=%s", flag, auxiliar);
			if(strcmp(flag, "velocidad") == 0){
				velocidad = (float) atof(auxiliar);
			}else if(strcmp(flag, "grabacion") == 0){
				strcpy(ruta_grabacion, auxiliar);
			}
		}

		arch_grabacion = fopen(ruta_grabacion, "r");

		if (!arch_grabacion){
			printf(ROJO "ERROR AL INTENTAR LEER EL ARCHIVO O ESE ARCHIVO NO EXISTE\n" FIN);
			return -1;
		
		} else {

			mostrar_grabacion(arch_grabacion, velocidad); 

		}

	}

	return 0;
}