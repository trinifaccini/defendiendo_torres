#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "funciones.h"
#include "utiles.h"

#define FIN				"\033[0m"
#define VERDE 			"\033[1m\033[32m"

static const int PRIMER_NIVEL = 1;
static const int SEGUNDO_NIVEL = 2;
static const int TERCER_NIVEL = 3;
static const int CUARTO_NIVEL = 4;
static const int MAX_NIVELES = 5;
static const int RESISTENCIA_MINIMA = 0;
static const int RESISTENCIA_DEFAULT = -1;
static const int DEFENSORES_DEFAULT = -1;
static const int DEFENSORES_MINIMO = 0;
static const int DEFENSORES_MAXIMO = 50;
static const int DEFAULT = -1;
static const float DEFAULT_FLOAT = -1;
static const char AFIRMATIVO = 'S';
static const int INICIO = 0;
static const char TORRE = 'T';
static const char ENTRADA = 'E';
static const char TIERRA = '~';
static const char CAMINO = ' ';
const int NO_PUEDE_COLOCARSE = -1;
const int PUEDE_COLOCARSE = 0;
static const int MAX_TABLERO_CHICO = 15;
static const int MAX_TABLERO_GRANDE = 20;


//HECHO
//POST: devulve true si el entero recibido como parametro esta dentro del rango de resistencia valida (mayor a 0) 
//      o es igual a -1(default).
bool es_resistencia_valida (int resistencia){

	return (resistencia == RESISTENCIA_DEFAULT || resistencia > RESISTENCIA_MINIMA);
}

//HECHO
//PRE:  recibe dos enteros como pametros (por referencia).
//POST: asignara a las torres la resistencia elegida por el usuario.
void pedir_resistencia_torres(int* resistencia_1, int* resistencia_2){
	printf("RESISTENCIA TORRE 1:\n");
	scanf(" %i", resistencia_1);
	while (!es_resistencia_valida(*resistencia_1)){
		printf("INGRESA UNA RESISTENCIA VALIDA!\n");
		printf("RESISTENCIA TORRE 1:\n");
		scanf(" %i", resistencia_1);
	}

	printf("RESISTENCIA TORRE 2:\n");
	scanf(" %i", resistencia_2);
	while (!es_resistencia_valida(*resistencia_2)){
		printf("INGRESA UNA RESISTENCIA VALIDA!\n");
		printf("RESISTENCIA TORRE 2:\n");
		scanf(" %i", resistencia_2);
	}
}

//HECHO
//POST: devolverá true si el entero recibido como parametro esta dentro del rango de defesores validos(mayor a 0) 
// 		o es igual a -1(default).
bool son_defensores_validos(int defensores_inicio){	

	if (defensores_inicio == DEFENSORES_DEFAULT){
		return true;
	}else if (defensores_inicio <= DEFENSORES_MAXIMO && defensores_inicio > DEFENSORES_MINIMO){
		return true;
	}else
		return false;
}

//HECHO
//PRE:  recibira un tipo de dato enanos_t por referencia.
//POST: asignará la cantidad de enanos disponibles para cada nivel, elegidos por el usuario.
void pedir_enanos_iniciales(enanos_t* enanos){

	printf("INGRESA LA CANTIDAD DE ENANOS INICIALES PARA EL NIVEL 1: \n");
	scanf("%i", &(enanos->nivel_1));
	while (!son_defensores_validos(enanos->nivel_1)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(enanos->nivel_1));
	}

	printf("INGRESA LA CANTIDAD DE ENANOS INICIALES PARA EL NIVEL 2: \n");
	scanf("%i", &(enanos->nivel_2));
	while (!son_defensores_validos(enanos->nivel_2)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(enanos->nivel_2));
	}

	printf("INGRESA LA CANTIDAD DE ENANOS INICIALES PARA EL NIVEL 3: \n");
	scanf("%i", &(enanos->nivel_3));
	while (!son_defensores_validos(enanos->nivel_3)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(enanos->nivel_3));
	}

	printf("INGRESA LA CANTIDAD DE ENANOS INICIALES PARA EL NIVEL 4: \n");
	scanf("%i", &(enanos->nivel_4));
	while (!son_defensores_validos(enanos->nivel_4)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(enanos->nivel_4));
	}
}

//HECHO
//PRE:  recibira un tipo de dato elfos_t por referencia.
//POST: asignará la cantidad de enanos disponibles para cada nivel, elegidos por el usuario.
void pedir_elfos_iniciales(elfos_t* elfos){

	printf("INGRESA LA CANTIDAD DE ELFOOS INICIALES PARA EL NIVEL 1: \n");
	scanf("%i", &(elfos->nivel_1));
	while (!son_defensores_validos(elfos->nivel_1)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(elfos->nivel_1));
	}

	printf("INGRESA LA CANTIDAD DE ELFOS INICIALES PARA EL NIVEL 2: \n");
	scanf("%i", &(elfos->nivel_2));
	while (!son_defensores_validos(elfos->nivel_2)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(elfos->nivel_2));
	}

	printf("INGRESA LA CANTIDAD DE ELFOS INICIALES PARA EL NIVEL 3: \n");
	scanf("%i", &(elfos->nivel_3));
	while (!son_defensores_validos(elfos->nivel_3)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(elfos->nivel_3));
	}

	printf("INGRESA LA CANTIDAD DE ELFOS INICIALES PARA EL NIVEL 4: \n");
	scanf("%i", &(elfos->nivel_4));
	while (!son_defensores_validos(elfos->nivel_4)){
		printf("INGRESA UNA CANTIDAD VALIDA: \n");
		scanf(" %i", &(elfos->nivel_4));
	}
}


//PRE:	recibe un tipo de dato enanos_t (por referencia) y uno de elfos_t (por referencia).
//POST:	asignara la cantidad de enanos y elfos extra que estaran disponibles durante el juego, elegidos por el usuario.
void pedir_defensores_extra (enanos_t* enanos, elfos_t* elfos){

	printf("INGRESA LA CANTIDAD DE ENANOS EXTRA: \n");
	scanf("%i", &(enanos->extras));
	while(enanos->extras < DEFENSORES_DEFAULT){
		printf("INGRESA UNA CANTIDAD VALIDA DE ENANOS EXTRA: \n");
		scanf("%i", &(enanos->extras));
	}

	printf("INGRESA LA CANTIDAD DE ELFOS EXTRA: \n");
	scanf("%i", &(elfos->extras));
	while(elfos->extras < DEFENSORES_DEFAULT){
		printf("INGRESA UNA CANTIDAD VALIDA DE ENANOS EXTRA: \n");
		scanf("%i", &(elfos->extras));
	}
	
}


//PRE:	recibira un tipo de dato animos_t (por referencia).
//POST:	asignara que porcentaje de golpes fallaran y que porcentaje de golpes seran criticos (para ambos tipos de defensores).
void determinar_animos (animos_t* animos){
	printf("INGRESA EL PORCENTAJE DE GOLPES CRITICOS Y DE GOLPES FALLIDOS QUE TENDRAN LOS ENANOS: \n");
	scanf(" %i %i", &(animos->critico_gimli), &(animos->fallo_gimli));
	while (animos->critico_gimli < DEFAULT || animos->fallo_gimli < DEFAULT){
		printf("POR FAVOR, INGRESA PORCENTAJES VALIDOS\n");
		printf("INGRESA EL PORCENTAJE DE GOLPES CRITICOS Y DE GOLPES FALLIDOS QUE TENDRAN LOS ENANOS: \n");
		scanf(" %i %i", &(animos->critico_gimli), &(animos->fallo_gimli));
	}

	printf("INGRESA EL PORCENTAJE DE GOLPES CRITICOS Y DE GOLPES FALLIDOS QUE TENDRAN LOS ELFOS: \n");
	scanf(" %i %i", &(animos->critico_legolas), &(animos->fallo_legolas));
	while (animos->critico_legolas < DEFAULT || animos->fallo_legolas< DEFAULT){
		printf("POR FAVOR, INGRESA PORCENTAJES VALIDOS\n");
		printf("INGRESA EL PORCENTAJE DE GOLPES CRITICOS Y DE GOLPES FALLIDOS QUE TENDRAN LOS ELFOS: \n");
		scanf(" %i %i", &(animos->critico_legolas), &(animos->fallo_legolas));
	}
}


//PRE:	recibira por referencia un float.
//POST:	asignara 
void pedir_velocidad(float* velocidad){
	printf("INGRESE A QUE VELOCIDAD QUIERE QUE FUNCIONE SU JUEGO (float): \n");
	scanf("%f", velocidad);
	while(*velocidad < DEFAULT_FLOAT){
		printf("INGRESA UNA VELOCIDAD VALIDA (float): \n");
		scanf("%f", velocidad);
	}
}


//PRE:	recibira un string.
//POST:	asignara a ese string el nombre del archivo donde el usurio guardo sus caminos.
void pedir_archivo_camino (char arch_camino[MAX_NOMBRE]){
	printf("INGRESA EL ARCHIVO DONDE SE ENCUENTRAN SUS CAMINOS ELEGIDOS: \n");
	scanf(" %[^\n]", arch_camino);
}


//PRE:	recibira una configuracion y un archivo de texto en donde guardarla (por referencia).
//POST:	copiara los datos de la configuracion en el archivo.
void pedir_configuracion(configuracion_t* configuracion, FILE** arch_config){

	pedir_resistencia_torres(&(configuracion->resistencia_torre_1), &(configuracion->resistencia_torre_2));
	pedir_enanos_iniciales(&(configuracion->enanos));
	pedir_elfos_iniciales(&(configuracion->elfos));
	pedir_defensores_extra(&(configuracion->enanos), &(configuracion->elfos));
	determinar_animos(&(configuracion->animos));
	pedir_velocidad(&(configuracion->velocidad_juego));
	pedir_archivo_camino(configuracion->archivo_camino);

	fprintf(*arch_config, "RESISTENCIA_TORRES=%i,%i\n", configuracion->resistencia_torre_1, configuracion->resistencia_torre_2);
	fprintf(*arch_config, "ENANOS_INICIO=%i,%i,%i,%i\n", configuracion->enanos.nivel_1, configuracion->enanos.nivel_2, configuracion->enanos.nivel_3, configuracion->enanos.nivel_4);
	fprintf(*arch_config, "ELFOS_INICIO=%i,%i,%i,%i\n", configuracion->elfos.nivel_1, configuracion->elfos.nivel_2, configuracion->elfos.nivel_3, configuracion->elfos.nivel_4);
	fprintf(*arch_config, "ENANOS_EXTRA=%i\n", configuracion->enanos.extras);
	fprintf(*arch_config, "ELFOS_EXTRA=%i\n", configuracion->elfos.extras);
	fprintf(*arch_config, "ENANOS_ANIMO=%i,%i\n", configuracion->animos.critico_gimli, configuracion->animos.fallo_gimli);
	fprintf(*arch_config, "ELFOS_ANIMO=%i,%i\n", configuracion->animos.critico_legolas, configuracion->animos.fallo_legolas);
	fprintf(*arch_config, "VELOCIDAD=%f\n", configuracion->velocidad_juego);
	fprintf(*arch_config, "CAMINOS=%s", configuracion->archivo_camino);

}

//PRE: 	recibira un entero que representa al nivel actual.
//POST:	devolverá el tamanio del tablero segun el nivel.
//----> Nivel 1 y 2: 15x15.
//----> Nivel 3 y 4: 20x20. 
int tam_tablero(int nivel_actual){

	if (nivel_actual == PRIMER_NIVEL || nivel_actual == SEGUNDO_NIVEL){
		return MAX_TABLERO_CHICO;
	}else{
		return MAX_TABLERO_GRANDE;
	}
}


//PRE:	recibe el nivel actual, el camino a ser mostrado y el tope de este.
//POST: le mostrara al usario el tablero de juego al momento de armar sus caminos.
void mostrar_tablero(int nivel_actual, coordenada_t* camino, int tope_camino, bool terminado){

	system("clear");
	int max_tablero = tam_tablero(nivel_actual);
	char tablero[MAX_FILAS][MAX_COLUMNAS];

	printf(VERDE "                       1 1 1 1 1 1 1 1 1 1\n" FIN);
	printf(VERDE "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n" FIN);
	printf(VERDE "   ═══════════════════════════════════════\n" FIN);

	for (int i = 0; i < max_tablero; i++){
		for (int j = 0; j < max_tablero; j++){
			tablero[i][j] = TIERRA;
		}
	}

	if (nivel_actual == PRIMER_NIVEL || nivel_actual == SEGUNDO_NIVEL || nivel_actual == TERCER_NIVEL || nivel_actual == CUARTO_NIVEL){
		for (int i = 0; i < tope_camino; i++){
			tablero[camino[i].fil][camino[i].col] = CAMINO;
		}

		tablero[camino[INICIO].fil][camino[INICIO].col] = ENTRADA;

		if (terminado == true){
			tablero[camino[tope_camino-1].fil][camino[tope_camino-1].col] = TORRE;
		}
	}


	for (int i = 0; i < max_tablero; i++){
		printf(VERDE "%2i║" FIN, i);
		for (int j=0; j < max_tablero; j++){
			printf("%c ", tablero[i][j]);
		}
		printf("\n");
	}

}


//POST: devolvera true si la coordenada se encuentra dentro del tablero de juego.
bool esta_dentro_tablero(coordenada_t camino, int nivel_actual){

	int tablero = tam_tablero(nivel_actual);

	if ((camino.fil < 0) || (camino.fil >= tablero) || (camino.col < 0) || (camino.col >= tablero)){
		return false;
	}else{
		return true;
	}
}


//POST: devolvera true si la coordenada puede ser parte del camino.
bool es_valido_camino(coordenada_t actual, coordenada_t anterior){

	if(anterior.fil+1 == actual.fil && anterior.col == actual.col){
		return true;
	}else if(anterior.fil == actual.fil && anterior.col+1 == actual.col){
		return true;
	}else if(anterior.fil == actual.fil && anterior.col-1 == actual.col){
		return true;
	}else if(anterior.fil-1 == actual.fil && anterior.col == actual.col){
		return true;
	}else{
		return false;
	}
}


//POST: devolvera true si en la posicion de la coordenada puede ser posicionada la entrada del camino.
bool es_entrada_valida(coordenada_t entrada, int nivel_actual){

	if (nivel_actual == PRIMER_NIVEL){
		return (entrada.col == 14);
	}else if (nivel_actual == SEGUNDO_NIVEL){
		return (entrada.col == 0);
	}else if (nivel_actual == TERCER_NIVEL){
		return (entrada.fil == 0);
	}else if (nivel_actual == CUARTO_NIVEL){
		return(entrada.fil == 19);
	}else{
		return false;
	}
}

//PRE:	recibe un archivo de texto correspondiente a una configuracion (por referencia).
//POST:	copiara las coordenadas del camino en el archivo 
void pedir_caminos(FILE** arch_caminos){

	coordenada_t camino[MAX_LONGITUD_CAMINO];

	char respuesta;
	int nivel_actual = 1;
	bool camino_finalizado = false;
	int tope_camino = 0;
	
	while (nivel_actual < MAX_NIVELES){

		int max_caminos_nivel = 0;
		int camino_actual = 0;
		tope_camino = 0;
		camino_finalizado = false;
		coordenada_t entrada_anterior;
		coordenada_t salida_anterior;

		printf("INGRESA LAS COORDENADAS DE LOS CAMINOS PARA EL NIVEL %i\n", nivel_actual);
		fprintf(*arch_caminos,"NIVEL=%i\n",nivel_actual);

		if ((nivel_actual) == PRIMER_NIVEL || (nivel_actual) == SEGUNDO_NIVEL){
			max_caminos_nivel = 1;
		}else{
			max_caminos_nivel = 2;
		}

		entrada_anterior.fil = 100;
		entrada_anterior.col = 100;
		salida_anterior.fil = 100;
		salida_anterior.col = 100;

		while (camino_actual < max_caminos_nivel){
			tope_camino = 0;
			camino_finalizado = false;			
			int i = 0;

			printf("INGRESALAS PARA EL CAMINO %i\n", camino_actual+1);
			fprintf(*arch_caminos, "CAMINO=%i\n", camino_actual+1);

			while(camino_finalizado == false  && i < MAX_LONGITUD_CAMINO){
				
				if (i == 0){
					printf("POSICIONA LA ENTRADA\n");
					if (entrada_anterior.fil < 25 && entrada_anterior.col < 25){
						printf("ENTRADA ANTERIOR, FILA: %i COLUMNA: %i\n", entrada_anterior.fil, entrada_anterior.col);
					}
		
					printf("PRIMERO INGRESA LA FILA Y LUEGO LA COLUMNA\n");
					scanf(" %i %i", &camino[i].fil, &camino[i].col);
					while(es_entrada_valida(camino[i], nivel_actual) == false || (camino[i].col == entrada_anterior.col && camino[i].fil == entrada_anterior.fil)){
						printf("LA COORDENADA NO ES VALIDA, VUELVE A INGRESARLA\n");
						scanf ("%i %i",&camino[i].fil, &camino[i].col);
					}
					entrada_anterior.fil = camino[0].fil;
					entrada_anterior.col = camino[0].col;

				}else{
					printf("INGRESA LA COORDENADA %i DE TU CAMINO\n", i);
					printf("PRIMERO INGRESA LA FILA Y LUEGO LA COLUMNA\n");
					scanf(" %i %i", &camino[i].fil, &camino[i].col);
					while (esta_dentro_tablero(camino[i], nivel_actual) == false || es_valido_camino(camino[i], camino[i-1]) == false ){
						printf("LA COORDENADA NO ES VALIDA, VUELVE A INGRESARLA\n");
						printf("INGRESA LA COORDENADA %i DE TU CAMINO\n", i);
						scanf ("%i %i", &camino[i].fil, &camino[i].col);
					}
					
					if ((nivel_actual == PRIMER_NIVEL && camino[i].col == 0)  || (nivel_actual == SEGUNDO_NIVEL && camino[i].col == 14) || (nivel_actual == TERCER_NIVEL && camino[i].fil == 19) || (nivel_actual == CUARTO_NIVEL && camino[i].fil == 0)){
						printf("POSICIONAR AQUI LA TORRE?\n");
						if (salida_anterior.fil < 25 && salida_anterior.col < 25){
							printf("RECORDA NO POSICIONARLA EN EL LUGAR DONDE POSICIONASTE LA TORRE 1, CUYA FILA ES: %i Y COLUMNA ES: %i \n", salida_anterior.fil, salida_anterior.col);
						}
						printf("INGRESA S SI LO DESEAS, CUALQUIER OTRO CARACTER SI QUIERES CONTINUAR: \n");
						scanf(" %c", &respuesta);
						if (respuesta == AFIRMATIVO && (camino[tope_camino].fil == salida_anterior.fil && camino[tope_camino].col == salida_anterior.col)){
							printf("NO PUEDES POSICIONAR AQUI LA TORRE\n");
							camino_finalizado = false;
						}else if (respuesta == AFIRMATIVO && (camino[tope_camino].fil != salida_anterior.fil || camino[tope_camino].col != salida_anterior.col)){
							camino_finalizado = true;
							salida_anterior.fil = camino[tope_camino].fil;
							salida_anterior.col = camino[tope_camino].col;
						}
					}
				}

				fprintf(*arch_caminos, "%i;%i\n", camino[i].fil, camino[i].col);
				tope_camino++;
				mostrar_tablero(nivel_actual, camino, tope_camino, camino_finalizado);
				i++;
			}
			camino_actual++;
		}
		nivel_actual++;
	}
}

//PRE:	recibe una configuracion (por referencia) y un archivo de configuracion.
//POST:	asignara al struct configuracion todos los datos que posee el archivo.
void guardar_configuracion(configuracion_t* configuracion, FILE* arch_config, char nombre_archivo_configuracion[MAX_NOMBRE]){

	char etiqueta[MAX_NOMBRE];
	int leidos = fscanf (arch_config, "%[^=]=", etiqueta);
	strcpy(configuracion->archivo_configuracion, nombre_archivo_configuracion);

	while (leidos != EOF){

		if(strcmp(etiqueta, "RESISTENCIA_TORRES") == 0){
			leidos = fscanf(arch_config, "%i,%i\n", &(configuracion->resistencia_torre_1), &(configuracion->resistencia_torre_2));
		}else if(strcmp(etiqueta, "ENANOS_INICIO") == 0){
			leidos = fscanf(arch_config, "%i,%i,%i,%i\n", &(configuracion->enanos.nivel_1), &(configuracion->enanos.nivel_2), &(configuracion->enanos.nivel_3),&(configuracion->enanos.nivel_4));
		}else if(strcmp(etiqueta, "ELFOS_INICIO") == 0){
			leidos = fscanf(arch_config, "%i,%i,%i,%i\n", &(configuracion->elfos.nivel_1), &(configuracion->elfos.nivel_2), &(configuracion->elfos.nivel_3), &(configuracion->elfos.nivel_4));
		}else if(strcmp(etiqueta, "ENANOS_EXTRA") == 0){
			leidos = fscanf(arch_config, "%i\n", &(configuracion->enanos.extras));
		}else if(strcmp(etiqueta, "ELFOS_EXTRA") == 0){
			leidos = fscanf(arch_config, "%i\n", &(configuracion->elfos.extras));
		}else if(strcmp(etiqueta, "ENANOS_ANIMO") == 0){
			leidos = fscanf(arch_config, "%i,%i\n", &(configuracion->animos.fallo_gimli), &(configuracion->animos.critico_gimli));
		}else if(strcmp(etiqueta, "ELFOS_ANIMO") == 0){
			leidos = fscanf(arch_config, "%i,%i\n", &(configuracion->animos.fallo_legolas), &(configuracion->animos.critico_legolas));
		}else if(strcmp(etiqueta, "VELOCIDAD") == 0){
			leidos = fscanf(arch_config, "%f\n", &(configuracion->velocidad_juego));
		}else if(strcmp(etiqueta, "CAMINOS") == 0){
			leidos = fscanf(arch_config, "%s\n", configuracion->archivo_camino);
		}

		leidos = fscanf (arch_config, "%[^=]=", etiqueta);
	}

	fclose(arch_config);
}


//PRE:	recibe una configuracion (por referencia)
//POST:	asignara a todos los campos del struct configuracion un "-1", para que el usuario juegue con la configuracion por defecto.
void guardar_configuracion_default(configuracion_t* configuracion){

	configuracion->resistencia_torre_1 = RESISTENCIA_DEFAULT;
	configuracion->resistencia_torre_2 = RESISTENCIA_DEFAULT;
	configuracion->enanos.nivel_1 = DEFENSORES_DEFAULT;
	configuracion->enanos.nivel_2 = DEFENSORES_DEFAULT;
	configuracion->enanos.nivel_3 = DEFENSORES_DEFAULT;
	configuracion->enanos.nivel_4 = DEFENSORES_DEFAULT;
	configuracion->elfos.nivel_1 = DEFENSORES_DEFAULT;
	configuracion->elfos.nivel_2 = DEFENSORES_DEFAULT;
	configuracion->elfos.nivel_3 = DEFENSORES_DEFAULT;
	configuracion->elfos.nivel_4 = DEFENSORES_DEFAULT;
	configuracion->enanos.extras = DEFENSORES_DEFAULT;
	configuracion->elfos.extras = DEFENSORES_DEFAULT;
	configuracion->animos.fallo_gimli = DEFAULT;
	configuracion->animos.fallo_legolas = DEFAULT;
	configuracion->animos.critico_gimli = DEFAULT;
	configuracion->animos.critico_legolas = DEFAULT;
	configuracion->velocidad_juego = DEFAULT_FLOAT;
	strcpy(configuracion->archivo_camino, "-1");
	strcpy(configuracion->archivo_configuracion, "\0");

}


//PRE: 	recibe un archivo binario correspondiente a una grabacion y un float que representa la velocidad en la que se reproducira.
//POST:	mostrará una grabacion del juego.
void mostrar_grabacion(FILE* arch_grabacion, float velocidad){
	juego_t juego;

	while(!(feof(arch_grabacion))){

		fread(&juego, sizeof(juego_t), 1, arch_grabacion);
		detener_el_tiempo(velocidad);
		mostrar_juego(juego);
	}

	fclose(arch_grabacion);
}

//PRE: recibe un archivo de texto correspondiente a un ranking, un tipo de dato bool y una cantidad de usuarios a listar.
//POST: mostrara por pantalla el archivo de ranking-
//---> si hay_listados = true, mostrara cierta cantidad de usuarios del archivo.
//---> si hay_listados = false, mostrara el archivo completo.
void mostrar_ranking(FILE* arch_ranking, bool hay_listados, int listados){

	char nombre[MAX_NOMBRE];
	int puntos;
	int i = 0;

	int leidos = fscanf(arch_ranking, FORMATO_LECTURA_RANKING, nombre, &puntos);

	if (hay_listados == true){

		while(leidos == 2 && i < listados){

			printf("%s;%i\n", nombre, puntos);
			leidos = fscanf(arch_ranking, FORMATO_LECTURA_RANKING, nombre, &puntos);
			i++;
		}

	}else{

		while (leidos == 2){

			printf("%s;%i\n", nombre, puntos);
			leidos = fscanf(arch_ranking, FORMATO_LECTURA_RANKING, nombre, &puntos);

		}
	}
}





