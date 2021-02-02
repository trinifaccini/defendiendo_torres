#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "juego.h"
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"


#define TOTAL_CAMINOS 6
#define MAX_NIVELES 4


static const int DEFAULT = -1;
static const float DEFAULT_FLOAT = -1;
static const float VELOCIDAD_DEFAULT = 0.2f;
static const char AFIRMATIVO = 'S';
static const char NEGATIVO = 'N';
static const int PRIMER_NIVEL = 1;
static const int SEGUNDO_NIVEL = 2;
static const int TERCER_NIVEL = 3;
static const int CUARTO_NIVEL = 4;
static const int PRIMER_TOPE_ENANOS = 5;
static const int SEGUNDO_TOPE_ENANOS = 0;
static const int TERCER_TOPE_ENANOS = 3;
static const int CUARTO_TOPE_ENANOS = 4;
static const int PRIMER_TOPE_ELFOS = 0;
static const int SEGUNDO_TOPE_ELFOS = 5;
static const int TERCER_TOPE_ELFOS = 3;
static const int CUARTO_TOPE_ELFOS = 4;
static const int MAX_TABLERO_CHICO = 15;
static const int MAX_TABLERO_GRANDE = 20;
const char ENANO = 'G';
const char ELFO = 'L';
const int RESISTENCIA_DEFENSOR_EXTRA = 50;
const int SIN_DEFENSORES = 0;
static const int JUGANDO = 0;
static const int PERDIDO = -1;
static const int GANADO = 1;
const int NUMERO_BASURA = 0;
const char CARACTER_BASURA = ' ';
const int PRIMER_MAX_ENEMIGOS = 100;
const int SEGUNDO_MAX_ENEMIGOS = 200;
const int TERCER_MAX_ENEMIGOS = 150;
const int CUARTO_MAX_ENEMIGOS = 250;


////HECHO
//PRE:  recibirá un juego con todas sus estructuras válidas.
//POST: devuelve la cantidad de orcos con la cual contara la horda que entrara por cada camino en ese determinado nivel.
//----> Nivel 1: 100
//----> Nivel 2: 200 
//----> Nivel 3: 150
//----> Nivel 4: 250
int maximo_enemigos_por_nivel(juego_t juego){
	if (juego.nivel_actual == PRIMER_NIVEL){
		return PRIMER_MAX_ENEMIGOS;
	}else if (juego.nivel_actual == SEGUNDO_NIVEL){
		return SEGUNDO_MAX_ENEMIGOS;
	}else if (juego.nivel_actual == TERCER_NIVEL){
		return TERCER_MAX_ENEMIGOS;
	}else{
		return CUARTO_MAX_ENEMIGOS;
	}

}

//HECHO
//PRE: 	recibirá un juego con todas sus estructuras válidas.
//POST:	devolverá el tamanio del tablero segun el nivel.
//----> Nivel 1 y 2: 15x15.
//----> Nivel 3 y 4: 20x20.
int tamanio_tablero(juego_t juego){

	if (juego.nivel_actual == PRIMER_NIVEL || juego.nivel_actual == SEGUNDO_NIVEL){
		return MAX_TABLERO_CHICO;
	} 
	else 
		return MAX_TABLERO_GRANDE;
}


//PRE: 
//POST:
int defensores_totales( configuracion_t configuracion, ranking_t* enanos, ranking_t* elfos){

	if (configuracion.enanos.nivel_1 != DEFAULT){
		enanos->nivel_1 = configuracion.enanos.nivel_1;
	}else{
		enanos->nivel_1 = PRIMER_TOPE_ENANOS;
	}

	if (configuracion.enanos.nivel_2 != DEFAULT){
		enanos->nivel_2 = configuracion.enanos.nivel_2;
	}else{
		enanos->nivel_2 = SEGUNDO_TOPE_ENANOS;
	}

	if (configuracion.enanos.nivel_3 != DEFAULT){
		enanos->nivel_3 = configuracion.enanos.nivel_3;
	}else{
		enanos->nivel_3 = TERCER_TOPE_ENANOS;
	}

	if (configuracion.enanos.nivel_4!= DEFAULT){
		enanos->nivel_4 = configuracion.enanos.nivel_4;
	}else{
		enanos->nivel_4 = CUARTO_TOPE_ENANOS;
	}

	if (configuracion.elfos.nivel_1 != DEFAULT){
		elfos->nivel_1 = configuracion.elfos.nivel_1;
	}else{
		elfos->nivel_1 = PRIMER_TOPE_ELFOS;
	}

	if (configuracion.elfos.nivel_2 != DEFAULT){
		elfos->nivel_2 = configuracion.elfos.nivel_2;
	}else{
		elfos->nivel_2 = SEGUNDO_TOPE_ELFOS;
	}

	if (configuracion.elfos.nivel_3 != DEFAULT){
		elfos->nivel_3 = configuracion.elfos.nivel_3;
	}else{
		elfos->nivel_3 = TERCER_TOPE_ELFOS;
	}

	if (configuracion.elfos.nivel_4!= DEFAULT){
		elfos->nivel_4 = configuracion.elfos.nivel_4;
	}else{
		elfos->nivel_4 = CUARTO_TOPE_ELFOS;
	}

	return (elfos->nivel_1 + elfos->nivel_2 + elfos->nivel_3 + elfos->nivel_4 + enanos->nivel_1 + enanos->nivel_2 + enanos->nivel_3 + enanos->nivel_4);
}

//HECHO
//PRE:  recibirá un juego y un tipo de dato ranking correspondiente a enanos.
//POST:	devolverá la cantidad de enanos iniciales que el usuario podra posicionar en ese determinado nivel. Si el 
//		usario eligio la configuracion default, devolverá:
//----> Nivel 1: 5 enanos.
//----> Nivel 2: 0 enanos.
//----> Nivel 3: 3 enanos.
//----> Nivel 4: 4 enanos.
int tope_enanos_por_nivel (juego_t juego, ranking_t enanos){
	int tope_enanos;

	if (juego.nivel_actual == PRIMER_NIVEL){
		tope_enanos = enanos.nivel_1;
	}else if (juego.nivel_actual == SEGUNDO_NIVEL){
		tope_enanos = enanos.nivel_2;
	}else if (juego.nivel_actual == TERCER_NIVEL){
		tope_enanos = enanos.nivel_3;
	}else{
		tope_enanos = enanos.nivel_4;
	}

	return tope_enanos;
}

//HECHO
//PRE:  recibirá un juego y un tipo de dado ranking correspondiente a elfos.
//POST:	devolverá la cantidad de elfos iniciales que el usuario podra posicionar en ese determinado nivel.Si el 
//		usario eligio la config default, devolverá:
//----> Nivel 1: 0 elfos.
//----> Nivel 2: 5 elfos.
//----> Nivel 3: 3 elfos.
//----> Nivel 4: 4 elfos.
int tope_elfos_por_nivel (juego_t juego, ranking_t elfos){
	int tope_elfos;

	if (juego.nivel_actual == PRIMER_NIVEL){
		tope_elfos = elfos.nivel_1;
	}else if (juego.nivel_actual == SEGUNDO_NIVEL){
		tope_elfos = elfos.nivel_2;
	}else if (juego.nivel_actual == TERCER_NIVEL){
		tope_elfos = elfos.nivel_3;
	}else{
		tope_elfos = elfos.nivel_4;
	}

	return tope_elfos;
}

//PRE: 	recibirá un juego con todas sus estructuras válidas y la coordenada que eligio el usuario para su defensor.
//POST: devolverá true si la coordenada recibida como parámetro esta dentro del tablero de juego.
bool es_coordenada_valida(juego_t juego, coordenada_t posicion_defensor){

	int tablero = tamanio_tablero(juego);
	if ((posicion_defensor.fil < 0) || (posicion_defensor.fil >= tablero) || (posicion_defensor.col < 0) || (posicion_defensor.col >= tablero)){
		return false;
	}else
		return true;
}


//HECHO
//PRE:  recibirá un juego (por referencia) y un tipo de dato ranking correspondiente a enanos. 
//POST: posicionará a los enanos iniciales disponibles para cada nivel en las casillas determinadas por la coordenada que el usuario haya elegido.
void pedir_posicion_enanos(juego_t* juego, ranking_t enanos){

	int tope_actual = tope_enanos_por_nivel(*juego, enanos);
	coordenada_t posicion_defensor;

	printf("Posiciona tus ENANOS!\nRECORDATORIO: No debes posicionarlos dentro del camino, fuera del terreno y cada uno debe estar en una distinta posicion.\n");
	for (int i = 0; i < tope_actual; i++){
		printf("INGRESA LA FILA Y LUEGO LA COLUMNA DEL ENANO NUMERO %i: \n", i+1);
		scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
		while (es_coordenada_valida(*juego, posicion_defensor) == false || agregar_defensor(&(juego->nivel), posicion_defensor, ENANO) == -1){
			printf("LA POSICION DE TU DEFENSOR NO ES VALIDA, POR FAVOR VUELVE A INGRESARLA.\n");
			printf("INGRESA LA FILA Y LUEGO LA COLUMNA DEL ENANO NUMERO %i: \n", i+1);
			scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
		}
		mostrar_juego(*juego);
	}
}

//HECHO
//PRE:  recibirá un jueg (por referencia) y un tipo de dato ranking correspondiente a elfos.
//POST: posicionará a los elfos iniciales disponibles para cada nivel en las casillas determinadas por la coordenada que el usuario haya elegido.
void pedir_posicion_elfos(juego_t* juego, ranking_t elfos){

	int tope_actual = tope_elfos_por_nivel(*juego, elfos);
	coordenada_t posicion_defensor;

	printf("Posiciona tus ELFOS!\nRECORDATORIO: No debes posicionarlos dentro del camino, fuera del terreno y cada uno debe estar en una distinta posicion.\n");
	for (int i = 0; i < tope_actual; i++){
		printf("INGRESA LA FILA Y LUEGO LA COLUMNA DEL ELFO NUMERO %i\n", i+1);
		scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
		while (es_coordenada_valida(*juego, posicion_defensor) == false || agregar_defensor(&(juego->nivel), posicion_defensor, ELFO) == -1){
			printf("LA POSICION DE TU DEFENSOR NO ES VALIDA, POR FAVOR VUELVE A INGRESARLA\n");
			printf("INGRESA LA FILA Y LUEGO LA COLUMNA DEL ELFO NUMERO %i\n", i+1);
			scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
		}
		mostrar_juego(*juego);
	}
} 

//HECHO
//PRE: recibira el nombre del archivo donde el usuario guardo sus caminos (-1 si es default) y un vector auxiliar de caminos.
//POST: cargará las coordenadas del camino creado por el usuario al vector de caminos.  
bool cargar_camino(char archivo_camino[MAX_ARCHIVO], caminos_aux_t aux[TOTAL_CAMINOS]){

	char linea[MAX];
	char token[MAX];
	char flag[MAX];
	int nivel = 0, camino = 0;
	
	FILE* arch_caminos = fopen(archivo_camino, "r");

	if (!arch_caminos){
		printf(ROJO "ERROR AL INTENTAR LEER EL ARCHIVO O ESE ARCHIVO NO EXISTE\n" FIN);
		return false;
	}

	int leidos = fscanf(arch_caminos, "%[^\n]\n", linea);

	while(leidos == 1){
		sscanf(linea, "%[^=]=%s",flag, token);

		if(strcmp(flag, "NIVEL") == 0){
			nivel = atoi(token);
			leidos = fscanf(arch_caminos, "%[^\n]\n", linea);

		}else if(strcmp(flag, "CAMINO") == 0){

			int indice;
			camino = atoi(token);

			if(nivel == PRIMER_NIVEL || nivel == SEGUNDO_NIVEL){
				indice = (nivel - 1);
			}else if (nivel == TERCER_NIVEL){
				indice = (camino + 1);
			}else{
				indice = (camino + 3);
			}
			
			aux[indice].tope = 0;
			leidos = fscanf(arch_caminos, "%[^\n]\n", linea);
			int leidos2 = 0;
			while (leidos == 1 && leidos2 != 2){

				sscanf(linea, "%i;%i\n", &(aux[indice].camino[aux[indice].tope].fil), &(aux[indice].camino[aux[indice].tope].col));

				leidos = fscanf(arch_caminos, "%[^\n]\n", linea);
				leidos2 = sscanf(linea, "%[^=]=%s", flag, token);
				(aux[indice].tope)++;
			}
		}
	}

	fclose(arch_caminos);
	return true;
}

//HECHO
//PRE: recibira un vector de coordenadas_t de origen, uno de destino y el tope correspondiende al camino de origen.
//POST: cargara las coordenadas del camino de origen al de destino.
void igualar_camino(coordenada_t destino[MAX_LONGITUD_CAMINO], coordenada_t origen[MAX_LONGITUD_CAMINO], int tope){

	for(int i = 0; i < tope; i++){
		destino[i].fil = origen[i].fil;
		destino[i].col = origen[i].col;
	}
}


//PRE:  recibe un juego por referencia, un vector de caminos auxiliar, y un tipo de dato bool.
//POST: inicializara el camino del nivel 1.
//---> si personalizados = true, se creara el camino que el usuario haya elegido, que estará guardado en aux[0].camino.
//---> si personalizados = false, se creara el camino configurado por defecto.
void inicializar_nivel_1(juego_t* juego, caminos_aux_t aux[TOTAL_CAMINOS], bool personalizados){

	if(personalizados == true){

		igualar_camino((*juego).nivel.camino_1, aux[0].camino, aux[0].tope);
		juego->nivel.tope_camino_1 = aux[0].tope;

	}else{

		coordenada_t entrada;
		entrada.fil = 5;
		entrada.col =14;

		coordenada_t torre;
		torre.fil = 3;
		torre.col = 0;

		obtener_camino(juego->nivel.camino_1, (&(juego->nivel.tope_camino_1)), entrada, torre);
	}

}


//PRE:  recibe un juego por referencia, un vector de caminos auxiliar, y un tipo de dato bool.
//POST: inicializara el camino del nivel 2.
//---> si personalizados = true, se creara el camino que el usuario haya elegido, que estará guardado en aux[1].camino.
//---> si personalizados = false, se creara el camino configurado por defecto.:
void inicializar_nivel_2(juego_t* juego, caminos_aux_t aux[TOTAL_CAMINOS], bool personalizados){

	if(personalizados == true){
		igualar_camino((*juego).nivel.camino_1, aux[1].camino, aux[1].tope);
		juego->nivel.tope_camino_1 = aux[1].tope;

	}else{

		coordenada_t entrada;
		entrada.fil = 3;
		entrada.col = 0;

		coordenada_t torre;
		torre.fil = 5;
		torre.col = 14;

		obtener_camino(juego->nivel.camino_1, (&(juego->nivel.tope_camino_1)), entrada, torre);
	}
}


//PRE:  recibe un juego por referencia, un vector de caminos auxiliar, y un tipo de dato bool.
//POST: inicializara los caminos del nivel 3.
//---> si personalizados = true, se crearan los caminos que el usuario haya elegido, que estará guardados en aux[2].camino y en aux[3].camino.
//---> si personalizados = false, se creara el camino configurado por defecto.
void inicializar_nivel_3(juego_t* juego, caminos_aux_t aux[TOTAL_CAMINOS], bool personalizados){

	if(personalizados == true){

		igualar_camino((*juego).nivel.camino_1, aux[2].camino, aux[3].tope);
		juego->nivel.tope_camino_1 = aux[2].tope;
		igualar_camino((*juego).nivel.camino_1, aux[3].camino, aux[3].tope);
		juego->nivel.tope_camino_2 = aux[3].tope;

	}else{

		coordenada_t primer_entrada;
		primer_entrada.fil = 0;
		primer_entrada.col = 3;

		coordenada_t primer_torre;
		primer_torre.fil = 19;
		primer_torre.col = 8;

		obtener_camino(juego->nivel.camino_1, (&(juego->nivel.tope_camino_1)), primer_entrada, primer_torre);

		coordenada_t segunda_entrada;
		segunda_entrada.fil = 0;
		segunda_entrada.col = 16;

		coordenada_t segunda_torre;
		segunda_torre.fil = 19;
		segunda_torre.col = 11;

		obtener_camino(juego->nivel.camino_2, (&(juego->nivel.tope_camino_2)), segunda_entrada, segunda_torre);
	}
}


//PRE:  recibe un juego por referencia, un vector de caminos auxiliar, y un tipo de dato bool.
//POST: inicializara los caminos del nivel 4.
//---> si personalizados = true, se crearan los caminos que el usuario haya elegido, que estará guardados en aux[4].camino y en aux[5].camino.
//---> si personalizados = false, se creara el camino configurado por defecto.
void inicializar_nivel_4(juego_t* juego, caminos_aux_t aux[TOTAL_CAMINOS], bool personalizados){

	if(personalizados == true){
		igualar_camino((*juego).nivel.camino_1, aux[4].camino, aux[4].tope);
		juego->nivel.tope_camino_1 = aux[4].tope;
		igualar_camino((*juego).nivel.camino_1, aux[5].camino, aux[5].tope);
		juego->nivel.tope_camino_2 = aux[5].tope;

	}else{

		coordenada_t primer_entrada;
		primer_entrada.fil = 19;
		primer_entrada.col = 8;

		coordenada_t primer_torre;
		primer_torre.fil = 0;
		primer_torre.col = 3;

		obtener_camino(juego->nivel.camino_1, (&(juego->nivel.tope_camino_1)), primer_entrada, primer_torre);

		coordenada_t segunda_entrada;
		segunda_entrada.fil = 19;
		segunda_entrada.col = 11;

		coordenada_t segunda_torre;
		segunda_torre.fil = 0;
		segunda_torre.col = 16;

		obtener_camino(juego->nivel.camino_2, (&(juego->nivel.tope_camino_2)), segunda_entrada, segunda_torre);
	}
}


//PRE:  recibirá un juego (por referencia), una configuracion con todas sus estructuras válidas, un tipo de dato ranking correspondiente a enanos y uno correspondiente a elfos.
//POST:	inicializará cada nivel. (obtendra el/los camino/s de cada uno y pedira al usuario las coordenadas en donde posicionar los defensores en cada nivel).
void inicializar_niveles(juego_t* juego, configuracion_t configuracion, ranking_t enanos, ranking_t elfos){

	(*juego).nivel.max_enemigos_nivel = maximo_enemigos_por_nivel(*juego);
	juego->nivel.tope_defensores = 0;
	juego->nivel.tope_enemigos = 0;

	caminos_aux_t aux[TOTAL_CAMINOS];

	bool personalizados = cargar_camino(configuracion.archivo_camino, aux);

	if ((juego->nivel_actual) == PRIMER_NIVEL){

		inicializar_nivel_1(juego, aux, personalizados);
	}

	else if ((juego->nivel_actual) == SEGUNDO_NIVEL){

		inicializar_nivel_2(juego, aux, personalizados);
	}

	else if ((juego->nivel_actual) == TERCER_NIVEL){

		inicializar_nivel_3(juego, aux, personalizados);
	}

	else if ((juego->nivel_actual) == CUARTO_NIVEL){

		inicializar_nivel_4(juego, aux, personalizados);
	}

	mostrar_juego(*juego);
	pedir_posicion_enanos(juego, enanos);
	pedir_posicion_elfos(juego, elfos);

	detener_el_tiempo(2);
	mostrar_juego(*juego);
}	

//HECHO
//PRE:  recibirá un juego con todas sus estructuras válidas (por referencia) y un caracter correspondiente a un tipo de defensor (G para ENANO, L para ELFO).
//POST:	disminuirá la resistencia de la torre 1 50 puntos si se trata de un ENANO y 50 puntos la de la torre 2  si se trata de un ELFO.
void quitar_resistencia_torres(juego_t* juego, char tipo){

	if (tipo == ENANO){
		juego->torres.enanos_extra -= 1; //ver de transformar en cte
		juego->torres.resistencia_torre_1 = juego->torres.resistencia_torre_1 - RESISTENCIA_DEFENSOR_EXTRA;
	}else if (tipo == ELFO){
		juego->torres.elfos_extra -= 1;
		juego->torres.resistencia_torre_2 = juego->torres.resistencia_torre_2- RESISTENCIA_DEFENSOR_EXTRA;
	}
}


//POST: devolvera true si el caracter recibido como parámetro es una S (SI) o una N (NO).
bool es_respuesta_valida(char respuesta){

	return (respuesta == AFIRMATIVO || respuesta == NEGATIVO);
}


//HECHO
//PRE:  recibirá un juego con todas sus estructuras válidas y un caracter corresponidente a un tipo de defensor vàlido (G si es ENANO, L si es ELFO).
//POST: devolvera true si es posible agregar el tipo de defensor recibido como parámetro, dependiendo el nivel:
//----> Nivel 1: si el tipo es ENANO.
//----> Nivel 2: si el tipo es ELFO.
//----> Nivel 3 y 4: si el tipo es ENANO y la cantidad de enanos extras es mayor a 0.
//----> Nivel 3 y 4: si el tipo es ELFOS y la cantidad de elfos extras es mayor a 0.
bool es_defensor_valido(juego_t juego, char tipo){

	if (juego.nivel_actual == PRIMER_NIVEL && tipo == ENANO){
		return true;
	}else if (juego.nivel_actual == SEGUNDO_NIVEL && tipo == ELFO){
		return true;
	}else if (juego.nivel_actual == TERCER_NIVEL && juego.torres.enanos_extra > 0 && tipo == ENANO){
		return true;
	}else if (juego.nivel_actual == TERCER_NIVEL && juego.torres.elfos_extra > 0 && tipo == ELFO){
		return true;
	}else if (juego.nivel_actual == CUARTO_NIVEL && juego.torres.enanos_extra > 0 && tipo == ENANO){
		return true;
	}else if (juego.nivel_actual == CUARTO_NIVEL && juego.torres.elfos_extra > 0 && tipo == ELFO){
		return true;
	}else
		return false;
}

//HECHO
//PRE:  recibirá un juego con todas sus estructuras válidas.
//POST: devolverá true si el usuario esta habilitado para agregar un defensor extra, con condiciones específicas para cada nivel:
//----> Nivel 1: cada 25 orcos, si la resistencia de la torre 1 es mayor a 0 y la cantidad de enanos extras disponibles es mayor a 0.
//----> Nivel 2: cada 50 orcos, si la resistencia de la torre 2 es mayor a 0 y la cantidad de elfos extras disponibles es mayor a 0.
//----> Nivel 3 y 4: cada 50 orcos, si la resistencia de la torre 1 es mayor a 0 y la cantidad de enanos extras disponibles es mayor a 0.
//----> Nivel 3 y 4: cada 50 orcos, si la resistencia de la torre 2 es mayor a 0 y la cantidad de elfos extras disponibles es mayor a 0.
bool puede_agregar_defensor_extra(juego_t juego){

	if ((juego.nivel_actual == PRIMER_NIVEL) && (juego.nivel.tope_enemigos % 25 == 0) && (juego.torres.enanos_extra > SIN_DEFENSORES) && (juego.torres.resistencia_torre_1 > RESISTENCIA_DEFENSOR_EXTRA)){
		return true;
	}else if ((juego.nivel_actual == SEGUNDO_NIVEL) && (juego.nivel.tope_enemigos % 50 == 0) && (juego.torres.elfos_extra > SIN_DEFENSORES) && (juego.torres.resistencia_torre_2 > RESISTENCIA_DEFENSOR_EXTRA)){
		return true;
	}else if (juego.nivel_actual == TERCER_NIVEL && juego.nivel.tope_enemigos % 50 == 0){
		return(juego.torres.enanos_extra > 0 || juego.torres.elfos_extra > SIN_DEFENSORES);	
	}else if ((juego.nivel_actual == CUARTO_NIVEL) && (juego.nivel.tope_enemigos % 50 == 0)){
		return ((juego.torres.enanos_extra > 0) || (juego.torres.elfos_extra > SIN_DEFENSORES));
	}else
		return false;
}

//HECHO
//PRE: 	recibirá un juego con todas sus estructuras válidas y un contador (correspondiente a la cantidad de defensores extras).
//POST:	devolverá la cantidad máxima de defensores extra que el usuario podrá agregar dependiendo el nivel:
//----> Nivel 1 y 2: 4 defensores.
//----> Nivel 3: 6 defensores.
//----> Nivel 4: 10 defensores.
int maximo_defensores_extra(juego_t juego, int contador){

	if (juego.nivel_actual == TERCER_NIVEL){
		return 6;
	}else if (juego.nivel_actual == CUARTO_NIVEL){
		return 10;
	}else 
		return 4;
}

//HECHO
//PRE:  recibirá un juego con todas sus estructuras válidas
//POST:	(si es posible) posicionará un defensor extra en el caso de que el usuario lo desee.
void agregar_defensor_extra(juego_t* juego){

	char respuesta, tipo;
	coordenada_t posicion_defensor;
	
	printf("SI LO CREE NECESARIO, PUEDE AGREGAR UN DEFENSOR EXTRA. RECORDA QUE ESTO LE QUITARA RESISTENCIA A TUS TORRES.\nSi coloca un ENANO, le quitara 50 puntos a la Torre 1, si coloca un ELFO le quitara 50 puntos a la Torre 2.\nIngrese S si quisiera agregarlo o N si quiere seguir con el juego: \n");

	scanf(" %c", &respuesta);
	while (!es_respuesta_valida(respuesta)){
			printf("Por favor, ingrese S si lo desea, N si quiere continuar: ");
			scanf(" %c", &respuesta);
	}

	if (respuesta == AFIRMATIVO){
		if (juego->nivel_actual == PRIMER_NIVEL){
			printf("En este nivel puede agregar un ENANO ingresando G: \n");
			scanf(" %c", &tipo);
			while (!es_defensor_valido(*juego, tipo)){
				printf("Por favor, ingrese G: \n");
				scanf(" %c", &tipo);
			}
		}else if (juego->nivel_actual == SEGUNDO_NIVEL){
			printf("En este nivel puede agregar un ELFO ingresando L: \n");
			scanf(" %c", &tipo);
			while (!es_defensor_valido(*juego, tipo)){
				printf("Por favor, ingrese L: \n");
				scanf(" %c", &tipo);
			}
		}else{
			printf("Si desea agregar un ENANO, ingrese G. Si desea agregar un elfo, ingrese L\nRECORDA: si la resistencia de la torre es menor o igual a 50 o el tipo de defensor que quiere agregar no esta disponible, no podra agregarlo!: ");
			scanf(" %c", &tipo);
			while (!es_defensor_valido(*juego, tipo)){
				printf("Por favor, ingrese un defensor valido y disponible! G si es ENANO, L si es ELFO: \n");
				scanf(" %c", &tipo);
			}
		}
			
		quitar_resistencia_torres(juego, tipo);
		printf("ELEGIR FILA Y COLUMNA DEL DEFENSOR EXTRA: \n");
		scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
			while (es_coordenada_valida(*juego, posicion_defensor) == false || agregar_defensor(&(juego->nivel), posicion_defensor, tipo) == -1){
				printf("LA POSICION DE TU DEFENSOR NO ES VALIDA, POR FAVOR VUELVE A INGRESARLA.\n");
				printf("ELEGIR FILA Y COLUMNA DEL DEFENSOR EXTRA: ");
				scanf ("%i %i", &posicion_defensor.fil, &posicion_defensor.col);
			}

	}
}


//PRE: recibira la cantidad total de orcos muertos en esa partida, la cantitad total de defensores iniciales con la que el usuari contó, la resistencia
//	   inicial de ambas torres y la cantidad de enanos y elfos extras que el usuario tenia disponibles.
//POST:	devolvera el puntaje obtenido por el usuario en su partida actual, la cual dependera de todos los datos recibidos.
int puntos_totales(int orcos_muertos, int def_totales, int resistencia_1, int resistencia_2, int enanos_extra, int elfos_extra){

	return (orcos_muertos * 1000) / (def_totales + resistencia_1 + resistencia_2 + enanos_extra + elfos_extra);
}

//PRE:  recibira un string correspondiente al nombre del archivo en donde el usuario guardo su configuracion y el puntaje total otenido por este.
//POST:	cargara a un archivo de texto el nombre del usuario y su puntaje.
//---> si el usuario no eligio la configracion default, el archivo de texto en donde se guardara se llamara "rankig_"nombre del archivo de config".csv"
//---> si el usuario eligio la configuracion default, el archivo de texto en donde e guardara se llamara "rankig.csv"
void cargar_rankings(char nombre_archivo_configuracion[MAX_ARCHIVO], int puntaje){

	char nombre_archivo_ranking[MAX_ARCHIVO];
	usuario_t usuario;
	usuario.puntos = puntaje;
	FILE* arch_ranking_previo;
	FILE* arch_ranking;

	printf(VERDE "SU PUNTAJE TOTAL ES: %i\n" FIN, puntaje);
	printf("POR FAVOR, INGRESE SU NOMBRE: \n");
	scanf (" %s", usuario.nombre);


	if(nombre_archivo_configuracion[0] == '\0'){
		strcpy(nombre_archivo_ranking, "ranking.csv");
	}else{
		strcpy(nombre_archivo_ranking, "ranking_");
		strcat(nombre_archivo_ranking, nombre_archivo_configuracion);
		strcat(nombre_archivo_ranking, ".csv");
	}

	arch_ranking_previo = fopen(nombre_archivo_ranking, "r");  
	if (!arch_ranking_previo){
		printf("SE CREARA UN NUEVO ARCHIVO DE RANKING CON ESTA CONFIGURACION\n");
	} 

	if(arch_ranking_previo){

		arch_ranking = fopen("ranking_auxiliar.csv", "w");
		if(!arch_ranking){
			fclose(arch_ranking_previo);
			printf("ERROR AL INTENTAR CREAR EL ARCHIVO DE RANKING AUXILIAR\n");
		
		}

	}else{ 

		arch_ranking = fopen(nombre_archivo_ranking, "w");
		if(!arch_ranking){
			printf("ERROR AL INTENTAR CREAR EL ARCHIVO DE RANKING\n");
		}
	}

	if(!arch_ranking_previo && arch_ranking){ 

		fprintf(arch_ranking, FORMATO_SALIDA_RANKING, usuario.nombre, usuario.puntos);
		fclose(arch_ranking);

	}else{ 

		char nombre_comparacion[MAX_NOMBRE];
		int puntos_comparacion;
		bool nombre_escrito = false;
		int leidos = fscanf(arch_ranking_previo, FORMATO_LECTURA_RANKING, nombre_comparacion, &puntos_comparacion );
		
		while(leidos == 2){

			if(nombre_escrito == false){

				if(puntos_comparacion > usuario.puntos){ 

					fprintf(arch_ranking, FORMATO_SALIDA_RANKING, nombre_comparacion, puntos_comparacion);

				}else if(puntos_comparacion == usuario.puntos){ 

					if(strcmp(nombre_comparacion, usuario.nombre) >= 0){ 

						fprintf(arch_ranking, FORMATO_SALIDA_RANKING, usuario.nombre, usuario.puntos);
						fprintf(arch_ranking, FORMATO_SALIDA_RANKING, nombre_comparacion, puntos_comparacion);
						nombre_escrito = true;
					
					}else{

						fprintf(arch_ranking, FORMATO_SALIDA_RANKING, nombre_comparacion, puntos_comparacion);
					}

				}else{ 

					fprintf(arch_ranking, FORMATO_SALIDA_RANKING, usuario.nombre, usuario.puntos);
					fprintf(arch_ranking, FORMATO_SALIDA_RANKING,nombre_comparacion, puntos_comparacion);
					nombre_escrito = true;
				}

			}else{

				fprintf(arch_ranking, FORMATO_SALIDA_RANKING, nombre_comparacion, puntos_comparacion);
			}

			leidos = fscanf(arch_ranking_previo, FORMATO_LECTURA_RANKING, nombre_comparacion, &puntos_comparacion);
		}

		if(nombre_escrito == false){
			fprintf(arch_ranking, FORMATO_SALIDA_RANKING, usuario.nombre, usuario.puntos);
		}

		fclose(arch_ranking_previo);
		fclose(arch_ranking);
		rename("ranking_auxiliar.csv", nombre_archivo_ranking);
	}
}

//PRE:  recibira una configuracion con todas sus estructuras validas y un string correspondiente al nombre en donde el usuario querra guardar la grabacion
//  	de su juego.
//POST: jugara la partida con la configuracion elegida por el usuario.
void jugar_juego(configuracion_t configuracion, char ruta_grabacion[MAX_ARCHIVO]){

	char animo_legolas = CARACTER_BASURA, animo_gimli = CARACTER_BASURA;
	int viento = NUMERO_BASURA, humedad = NUMERO_BASURA;
	int puntaje = NUMERO_BASURA;
	int orcos_muertos = 0;
	float velocidad = VELOCIDAD_DEFAULT;
	ranking_t enanos, elfos;
	juego_t juego;

	int def_totales = defensores_totales(configuracion, &enanos, &elfos);

	srand((unsigned)time(NULL));

	if (configuracion.velocidad_juego != DEFAULT_FLOAT){
		velocidad = configuracion.velocidad_juego;
	}

	FILE* arch_grabacion = fopen(ruta_grabacion, "w");
	if (!arch_grabacion){
		printf(ROJO "ADEVERTENCIA: NO SE GRABARA SU JUEGO\n" FIN);
	} 

	printf(MAGENTA "╔╗ ╦╔═╗╔╗╔╦  ╦╔═╗╔╗╔╦╔╦╗╔═╗  ╔═╗  ╔╦╗╔═╗╔═╗╔═╗╔╗╔╔╦╗╦╔═╗╔╗╔╔╦╗╔═╗  ╔╦╗╔═╗╦═╗╦═╗╔═╗╔═╗\n" FIN);
	printf(MAGENTA "╠╩╗║║╣ ║║║╚╗╔╝║╣ ║║║║ ║║║ ║  ╠═╣   ║║║╣ ╠╣ ║╣ ║║║ ║║║║╣ ║║║ ║║║ ║   ║ ║ ║╠╦╝╠╦╝║╣ ╚═╗\n" FIN);
	printf(MAGENTA "╚═╝╩╚═╝╝╚╝ ╚╝ ╚═╝╝╚╝╩═╩╝╚═╝  ╩ ╩  ═╩╝╚═╝╚  ╚═╝╝╚╝═╩╝╩╚═╝╝╚╝═╩╝╚═╝   ╩ ╚═╝╩╚═╩╚═╚═╝╚═╝\n" FIN);
	
	animos (&viento, &humedad, &animo_legolas, &animo_gimli);
	system("clear");

	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli, configuracion);
	detener_el_tiempo(2);

	int resistencia_inicial_1 = juego.torres.resistencia_torre_1;
	int resistencia_inicial_2 = juego.torres.resistencia_torre_2;

	juego.nivel_actual = PRIMER_NIVEL;
	inicializar_niveles(&juego, configuracion, enanos, elfos);

	while (estado_juego(juego) == JUGANDO){
		int contador = 0;
		while(estado_juego(juego) == JUGANDO && estado_nivel(juego.nivel) == JUGANDO){
			jugar_turno(&juego);
			detener_el_tiempo(velocidad);
			mostrar_juego(juego);

			if (puede_agregar_defensor_extra(juego)== true && contador < maximo_defensores_extra(juego, contador)){
				agregar_defensor_extra(&juego);
				contador++;
			}
			if(arch_grabacion){
				fwrite(&juego, sizeof(juego_t), 1, arch_grabacion);
			}
		}

		if (estado_nivel(juego.nivel) == GANADO && juego.nivel_actual != CUARTO_NIVEL){
			orcos_muertos += cantidad_orcos_muertos(juego.nivel); 
			system ("clear");
			printf("FELICITACIONES, HAS PASADO EL NIVEL %i!\n", juego.nivel_actual);
			detener_el_tiempo(3);
			if (juego.nivel_actual < CUARTO_NIVEL){
				juego.nivel_actual++;
				inicializar_niveles(&juego, configuracion, enanos, elfos);
			}

		}
	}

	if (estado_juego(juego) == PERDIDO){
		printf(ROJO"╦ ╦╔═╗╔═╗  ╔═╗╔═╗╦═╗╔╦╗╦╔╦╗╔═╗  ╦╔╗╔╔╦╗╔═╗╔╗╔╔╦╗╔═╗╦  ╔═╗  ╔╗╔╦ ╦╔═╗╦  ╦╔═╗╔╦╗╔═╗╔╗╔╔╦╗╔═╗\n" FIN);
		printf(ROJO"╠═╣╠═╣╚═╗  ╠═╝║╣ ╠╦╝ ║║║ ║║║ ║  ║║║║ ║ ║╣ ║║║ ║ ╠═╣║  ║ ║  ║║║║ ║║╣ ╚╗╔╝╠═╣║║║║╣ ║║║ ║ ║╣\n"  FIN);
		printf(ROJO"╩ ╩╩ ╩╚═╝  ╩  ╚═╝╩╚══╩╝╩═╩╝╚═╝  ╩╝╚╝ ╩ ╚═╝╝╚╝ ╩ ╩ ╩╩═╝╚═╝  ╝╚╝╚═╝╚═╝ ╚╝ ╩ ╩╩ ╩╚═╝╝╚╝ ╩ ╚═╝\n" FIN);
		orcos_muertos += cantidad_orcos_muertos(juego.nivel);
		puntaje = puntos_totales(orcos_muertos, def_totales, resistencia_inicial_1, resistencia_inicial_2, juego.torres.enanos_extra, juego.torres.elfos_extra);
		
	} else if (estado_juego(juego) == GANADO){
		printf(AMARILLO"╔═╗╔═╗╦  ╦╔═╗╦╔╦╗╔═╗╔═╗╦╔═╗╔╗╔╔═╗╔═╗  ╦ ╦╔═╗╔═╗  ╔═╗╔═╗╔╗╔╔═╗╔╦╗╔═╗  ╔═╗╦     ╦╦ ╦╔═╗╔═╗╔═╗\n" FIN);
		printf(AMARILLO"╠╣ ║╣ ║  ║║  ║ ║ ╠═╣║  ║║ ║║║║║╣ ╚═╗  ╠═╣╠═╣╚═╗  ║ ╦╠═╣║║║╠═╣ ║║║ ║  ║╣ ║     ║║ ║║╣ ║ ╦║ ║\n" FIN);
		printf(AMARILLO"╚  ╚═╝╩═╝╩╚═╝╩ ╩ ╩ ╩╚═╝╩╚═╝╝╚╝╚═╝╚═╝  ╩ ╩╩ ╩╚═╝  ╚═╝╩ ╩╝╚╝╩ ╩═╩╝╚═╝  ╚═╝╩═╝  ╚╝╚═╝╚═╝╚═╝╚═╝\n" FIN);
		orcos_muertos += cantidad_orcos_muertos(juego.nivel);
		puntaje = puntos_totales(orcos_muertos, def_totales, resistencia_inicial_1, resistencia_inicial_2, juego.torres.enanos_extra, juego.torres.elfos_extra);

	}

	printf("ORCOS MUERTOS: %i\n", orcos_muertos);
	printf("DEFENSORES TOTALES: %i\n", def_totales);
	cargar_rankings(configuracion.archivo_configuracion, puntaje);

	return;
}

































