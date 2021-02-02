#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "defendiendo_torres.h"

#define FIN				"\033[0m"
#define ROJO 			"\033[1m\033[31m"
#define VERDE 			"\033[1m\033[32m"
#define AMARILLO		"\033[1m\033[33m"
#define MAGENTA 		"\033[1m\033[35m"
#define MAX_FILAS 30
#define MAX_COLUMNAS 30
#define MAX_LONGITUD_CAMINO 200
#define MAX_ENEMIGOS 500
#define MAX_DEFENSORES 50

static const char MAL_ANIMO = 'M';
static const char REGULAR_ANIMO = 'R';
static const char BUEN_ANIMO = 'B';

static const int DEFAULT = -1;
const char TORRE = 'T';
const char ENTRADA = 'E';
const char TIERRA = '~';
const char CAMINO = ' ';

const int RESISTENCIA_INICIAL = 600;
const int ENANOS_EXTRA_INICIAL = 10;
const int ELFOS_EXTRA_INICIAL= 10;

static const int NO_PUEDE_COLOCARSE = -1;
static const int PUEDE_COLOCARSE = 0;
static const int JUGANDO = 0;
static const int PERDIDO = -1;
static const int GANADO = 1;

static const int PRIMER_NIVEL = 1;
static const int SEGUNDO_NIVEL = 2;
static const int TERCER_NIVEL = 3;
static const int CUARTO_NIVEL = 4;

const int CRITICO_MINIMO = 0;
const int CRITICO_MEDIO = 10;
const int CRITICO_MAXIMO = 25;

const int PRIMER_CAMINO = 1;
const int SEGUNDO_CAMINO = 2;
static const int MAX_TABLERO_CHICO = 15;
static const int MAX_TABLERO_GRANDE = 20;


static const char ENANO = 'G';
const int GOLPE_ENANO = 60;
const int GOLPE_CRITICO_ENANO = 100;

static const char ELFO = 'L';
const int GOLPE_ELFO = 30;
const int GOLPE_CRITICO_ELFO = 70;

static const char ORCO = 'O';
const int VIDA_INICIAL_ORCO = 200;
const int INICIO = 0;
const int SIN_FUERZA = 0;
const int SIN_VIDA = 0;
const int SIN_RESISTENCIA = 0;

//PRE:  recibirá un cracter que representa el estado de animo de Legolas o Gimli (M malo, R regular, B buenio).
//POST: devolverá el porcentaje de golpes de cada tipo de defensor que seran criticos (ENANOS dependen del animo Gimli, ELFOS dependen del animo de Legolas).
int ataque_critico(char animo){
	int criticidad = 0;
	if (animo == MAL_ANIMO){
		criticidad = CRITICO_MINIMO;
	}else if(animo == REGULAR_ANIMO){
		criticidad = CRITICO_MEDIO;
	}else if (animo == BUEN_ANIMO){
		criticidad = CRITICO_MAXIMO;
	}
	return criticidad;
}

//PRE:  recibirá las condiciones del clima (velocidad del viento o porcentaje de humedad).
//POST: devolverá el porcentaje de golpes de cada tipo de defensor que fallaran (ENANOS dependen de la humedad, ELFOS dependen del viento).
int porcentaje_fallo(int clima){
	return (clima/2);
}

/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
 * NO inicializará el primer nivel.
 */
void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli, configuracion_t configuracion){

	if (configuracion.resistencia_torre_1 != DEFAULT){
		juego->torres.resistencia_torre_1 = configuracion.resistencia_torre_1;
	}else{
		juego->torres.resistencia_torre_1 = RESISTENCIA_INICIAL;
	}

	if (configuracion.resistencia_torre_2 != DEFAULT){
		juego->torres.resistencia_torre_2 = configuracion.resistencia_torre_2;
	}else{
		juego->torres.resistencia_torre_2 = RESISTENCIA_INICIAL;
	}
	
	if (configuracion.enanos.extras != DEFAULT){
		juego->torres.enanos_extra = configuracion.enanos.extras;
	}else{
		juego->torres.enanos_extra = ENANOS_EXTRA_INICIAL;
	}

	if (configuracion.elfos.extras != DEFAULT){
		juego->torres.elfos_extra = configuracion.elfos.extras;
	}else{
		juego->torres.elfos_extra = ELFOS_EXTRA_INICIAL;
	}

	if (configuracion.animos.critico_gimli != DEFAULT){
		juego->critico_gimli = configuracion.animos.critico_gimli;
	}else{
		juego->critico_gimli = ataque_critico(animo_gimli);
	}

	if (configuracion.animos.critico_legolas != DEFAULT){
		juego->critico_legolas = configuracion.animos.critico_legolas;
	}else{
    	juego->critico_legolas = ataque_critico(animo_legolas);
  	}

  	if (configuracion.animos.fallo_gimli != DEFAULT){
		juego->fallo_gimli = configuracion.animos.fallo_gimli;
	}else{
    	juego->fallo_gimli = porcentaje_fallo (humedad);
  	}

  	if (configuracion.animos.fallo_legolas!= DEFAULT){
		juego->fallo_legolas = configuracion.animos.fallo_legolas;
	}else{
    	juego->fallo_legolas = porcentaje_fallo(viento);
  	}

    printf(MAGENTA "===================================================\n" FIN);
 	printf("||DATOS||DE||SU||JUEGO||\n");
	printf("La velocidad del viento el dia de hoy es %i km/h\nEl porcentaje de humedad el dia de hoy es %i\n", viento, humedad);
	printf("El animo de Legolas es %c\nEl animo de Gimli es %c\n", animo_legolas, animo_gimli);
	printf(MAGENTA "===================================================\n" FIN);
}

/*
 * Recibe un juego con todas sus estructuras válidas. 
 * El juego se dará por ganado si el juego está en el ultimo nivel y éste ha sido terminado.
 * El juego se dará por perdido, si alguna de las torres llega a 0 en su resistencia.
 * Devolverá:
 * >  0 si el estado es jugando.
 * > -1 si el estado es perdido.
 * >  1 si el estado es ganado.
 */
int estado_juego(juego_t juego){

	if (juego.torres.resistencia_torre_1 <= SIN_RESISTENCIA || juego.torres.resistencia_torre_2 <= SIN_RESISTENCIA){
		return PERDIDO;
	}else if (juego.nivel_actual == CUARTO_NIVEL && estado_nivel(juego.nivel) == GANADO){
		return GANADO;
	}else{
		return JUGANDO;
	}
}

//PRE: recibirá un nivel con todas sus estructuras válidas. 
//POST: devolverá la cantidad de orcos muertos actuales.

int cantidad_orcos_muertos(nivel_t nivel){

	int orcos_muertos = 0;

	for(int i = 0; i < nivel.tope_enemigos; i++){
		if (nivel.enemigos[i].vida <= SIN_VIDA){
			orcos_muertos++;
		}
	}
	return orcos_muertos;
}

/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel){ 

	int orcos_muertos = cantidad_orcos_muertos(nivel);

	if (orcos_muertos == nivel.max_enemigos_nivel){
		return GANADO;
	}else{
		return JUGANDO;
	}
}


//PRE:  recibirá un caracter correspondiente a un de defensor válido (G si es enano, L si es elfo).
//POST: devolverá cual es la fuerza de su golpe base dependiendo del tipo de caracter recibido como parametro (60 si es ENANO, 30 si es ELFO).
int fuerza_base_segun_tipo(char tipo){

	int fuerza = 0;
	if (tipo == ENANO){
		fuerza = GOLPE_ENANO;
	}
	else{
		fuerza = GOLPE_ELFO;
	}

	return fuerza;
}

/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */
int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){

	int puede_colocarse = PUEDE_COLOCARSE;

	for (int i = 0; i < nivel->tope_camino_1; i++){
		if (posicion.fil == (*nivel).camino_1[i].fil && posicion.col == (*nivel).camino_1[i].col)
			puede_colocarse = NO_PUEDE_COLOCARSE;
	}

	for (int i = 0; i < nivel->tope_camino_2; i++){
		if (posicion.fil == (*nivel).camino_2[i].fil && posicion.col == (*nivel).camino_2[i].col)
			puede_colocarse = NO_PUEDE_COLOCARSE;
	}

	for (int i = 0; i < nivel->tope_defensores; i++){
		if (posicion.fil == (*nivel).defensores[i].posicion.fil && posicion.col ==(*nivel).defensores[i].posicion.col)
			puede_colocarse = NO_PUEDE_COLOCARSE;
	}

	if (puede_colocarse == PUEDE_COLOCARSE){
		(*nivel).defensores[nivel->tope_defensores].posicion = posicion;
		(*nivel).defensores[nivel->tope_defensores].tipo = tipo;
		(*nivel).defensores[nivel->tope_defensores].fuerza_ataque = fuerza_base_segun_tipo(tipo);
		(*nivel).tope_defensores ++;
	}
	return puede_colocarse;
}

//PRE:  recibirá  un nivel con todas sus estructuras válidas y un numero de un camino valido (1 para el primer camino, 2 para el segundo camino).
//POST: creara un enemigo (orco) en el camino recibido como parametro, le asignara una vida inicial (que estara entre 200 y 300) y lo posicionara 
//      en el inicio del camino. 
void crear_orco (nivel_t* nivel, int camino){

	if (nivel->tope_enemigos < nivel->max_enemigos_nivel){
			nivel->enemigos[nivel->tope_enemigos].vida = (VIDA_INICIAL_ORCO + rand() % 101);
			nivel->enemigos[nivel->tope_enemigos].camino = camino;
			nivel->enemigos[nivel->tope_enemigos].pos_en_camino = INICIO;
			nivel->tope_enemigos++;
	}
}

//PRE:  recibe juego con todas sus estructuras válidas.
//POST: (si la vida del orco es mayor a 0) avanzara al orco una posicion dentro de su camino, en el caso que este se encuentre en la ultima posicicion del camino 
//      restara tanta resistencia a la torre como vida tenga. Una vez alli, cambia su vida a 0. 
void accion_orcos (juego_t* juego){

	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
		if (juego->nivel.enemigos[i].camino == PRIMER_CAMINO){
			if (juego->nivel.enemigos[i].pos_en_camino < (juego->nivel.tope_camino_1 - 2) && juego->nivel.enemigos[i].vida > SIN_VIDA){
				juego->nivel.enemigos[i].pos_en_camino++;
			} else if (juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_1 - 2 && juego->nivel.enemigos[i].vida > SIN_VIDA){
				if (juego->nivel_actual == SEGUNDO_NIVEL){
					juego->torres.resistencia_torre_2 = juego->torres.resistencia_torre_2 - juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = SIN_VIDA;

				}else{
					juego->torres.resistencia_torre_1 = juego->torres.resistencia_torre_1 - juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = SIN_VIDA;
				}
			}
		}
	}

	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
		if (juego->nivel.enemigos[i].camino == SEGUNDO_CAMINO){
			if (juego->nivel.enemigos[i].pos_en_camino < (juego->nivel.tope_camino_2 - 2) && juego->nivel.enemigos[i].vida > SIN_VIDA){
				juego->nivel.enemigos[i].pos_en_camino++;
			} else if (juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_2 - 2 && juego->nivel.enemigos[i].vida > SIN_VIDA){
				juego->torres.resistencia_torre_2 = juego->torres.resistencia_torre_2 - juego->nivel.enemigos[i].vida;
				juego->nivel.enemigos[i].vida = SIN_VIDA;
			}
		}
	}
}

//PRE:  recibirá  un nivel con todas sus estructuras válidas, un determinado orco y la coordenada de un enano.
//POST: devolverá true si el orco se encuentra dentro del rango de ataque del enano.
bool esta_rango_enanos(nivel_t* nivel, int j, coordenada_t posicion_defensor){

	coordenada_t posicion_orco;

	if (nivel->enemigos[j].camino == PRIMER_CAMINO){
		posicion_orco = nivel->camino_1[nivel->enemigos[j].pos_en_camino];
	}else if (nivel->enemigos[j].camino == SEGUNDO_CAMINO){
		posicion_orco = nivel->camino_2[nivel->enemigos[j].pos_en_camino];
	}

	if(posicion_defensor.fil+1 == posicion_orco.fil && posicion_defensor.col == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil+1 == posicion_orco.fil && posicion_defensor.col+1 == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil+1 == posicion_orco.fil && posicion_defensor.col-1 == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil == posicion_orco.fil && posicion_defensor.col+1 == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil == posicion_orco.fil && posicion_defensor.col-1 == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil-1 == posicion_orco.fil && posicion_defensor.col == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil-1 == posicion_orco.fil && posicion_defensor.col+1 == posicion_orco.col){
		return true;
	}else if(posicion_defensor.fil-1 == posicion_orco.fil && posicion_defensor.col-1 == posicion_orco.col){
		return true;
	}else{
		return false;
	}
}


//PRE: recibirá  un nivel con todas sus estructuras válidas, un determinado orco y la coordenada de un elfo.
//POST: devolvera true si el orco se encuentra dentro del rango de ataque del elfo.
bool esta_rango_elfos(nivel_t* nivel, int j, coordenada_t posicion_defensor){

	coordenada_t posicion_orco;

	if (nivel->enemigos[j].camino == PRIMER_CAMINO){
		posicion_orco = nivel->camino_1[nivel->enemigos[j].pos_en_camino];
	}else if (nivel->enemigos[j].camino == SEGUNDO_CAMINO){
		posicion_orco = nivel->camino_2[nivel->enemigos[j].pos_en_camino];
	}

	int distancia_fil = abs (posicion_defensor.fil - posicion_orco.fil);
	int distancia_col = abs (posicion_defensor.col - posicion_orco.col);

	return ((distancia_fil + distancia_col) <= 3 && nivel->enemigos[j].vida > SIN_VIDA);

}

//PRE:  recibirá el valor de criticidad de Gimli y el porcentaje de fallo de Gimli.
//POST: devolvera la fuerza del golpe del enano (60 si el golpe es basico, 100 si el golpe es critico, 0 si el golpe es fallido).
int fuerza_enano(int critico_gimli, int fallo_gimli){

	int numero = rand() % 100;
	int fallo = rand() % 100;
	int fuerza;

	if (numero < critico_gimli){
		fuerza = GOLPE_CRITICO_ENANO;
	}else{
		fuerza = GOLPE_ENANO;
	}

	if (fallo < fallo_gimli){
		fuerza = SIN_FUERZA;
	}

	return fuerza;
}

//PRE:  recibirá el valor de criticidad de Legolas y el porcentaje de fallo de Legolas.
//POST: devolverá la fuerza de la flecha del elfo (30 si el golpe es basico, 70 si el golpe es critico, 0 si el golpe es fallido).
int fuerza_elfo(int critico_legolas, int fallo_legolas){

	int numero = rand() % 100;
	int fallo = rand() % 100;
	int fuerza;

	if (numero < critico_legolas){
		fuerza = GOLPE_CRITICO_ELFO;
	}else{
		fuerza = GOLPE_ELFO;
	}

	if (fallo < fallo_legolas){
		fuerza = SIN_FUERZA;
	}

	return fuerza;
}

//PRE:  recibirá un juego con todas sus estructuras válidas, un caracter valido correspondiente al defensor(G si es ENANO, L si es ELFO) y un numero que corresponde a un orco especifico.
//POST: modificará la vida del orco (permanecera igual si la fuerza del golpe del defenor es 0 o disminuira).
void resta_vida_orco(juego_t* juego, char tipo, int j){

	int fuerza_ataque;

	if (tipo == ENANO){
		fuerza_ataque = fuerza_enano(juego->critico_gimli, juego->fallo_gimli);
	}
	else{
		fuerza_ataque = fuerza_elfo(juego->critico_legolas, juego->fallo_legolas);
	}

	juego->nivel.enemigos[j].vida = juego->nivel.enemigos[j].vida - fuerza_ataque;
}

//POST: devolverá true si el caracter recibido como parámetro es una E (ENANO).
bool es_enano(char tipo){
	return (tipo == ENANO);
}

//PRE:  recibirá un juego con todas sus estructuras válidas. 
//POST: si el orco se encuentra dentro del rango del enano, este ejecturará el ataque, disminuyendo su vida dependiendo su golpe.
void ataque_de_enano(juego_t* juego){

	coordenada_t posicion_defensor;
	int i = 0, j = 0;
	char tipo;
	bool enano_ataco;

	while (i < juego->nivel.tope_defensores){
		posicion_defensor = juego->nivel.defensores[i].posicion;
		tipo = juego->nivel.defensores[i].tipo;
		enano_ataco = false;
		j=0;
		while(j < juego->nivel.tope_enemigos && enano_ataco == false){
			if (es_enano(tipo) == true && esta_rango_enanos(&((*juego).nivel), j, posicion_defensor) == true && juego->nivel.enemigos[j].vida > SIN_VIDA){
				resta_vida_orco(juego, ENANO, j);
				enano_ataco = true;
			}
			j++;
		}
		i++;	
	}
}

//POST: devolverá true si el caracter recibido como parámetro es una L (ELFO).
bool es_elfo(char tipo){
	return (tipo == ELFO);
}

//PRE:  recibirá un juego con todas sus estructuras válidas (por referencia).
//POST: si el orco se encuentra dentro del rango del elfo, este ejecturará el ataque, disminuyendo su vida dependiendo su golpe.
void ataque_de_elfo(juego_t* juego){

	coordenada_t posicion_defensor;
	int i = 0, j = 0;
	char tipo;
	
	for (i = 0; i < juego->nivel.tope_defensores; i++){
		tipo = juego->nivel.defensores[i].tipo;
		posicion_defensor = juego->nivel.defensores[i].posicion;
		for (j = 0; j< juego->nivel.tope_enemigos; j++){
			if (es_elfo(tipo) == true && esta_rango_elfos(&((*juego).nivel), j, posicion_defensor) == true && juego->nivel.enemigos[j].vida > SIN_VIDA){
				resta_vida_orco(juego, ELFO, j);
			}
		}
	}
}	

//PRE:  recibirá un juego con todas sus estructuras válidas (por referencia).
//POST: harán su jugada los enanos, luego los elfos.
void ataque_defensores (juego_t* juego){
	ataque_de_enano(juego);
	ataque_de_elfo(juego);
}


//PRE:  recibirá un juego con todas sus estructuras válidas (por referencia).
//POST: harán su jugada lor orcos.
void turno_orcos (juego_t* juego){

	if ((*juego).nivel_actual == PRIMER_NIVEL || (*juego).nivel_actual == SEGUNDO_NIVEL){
		accion_orcos(juego);
		crear_orco(&(juego->nivel), PRIMER_CAMINO);
	}else{
		accion_orcos(juego);
		crear_orco(&(juego->nivel), PRIMER_CAMINO);
		crear_orco (&(juego->nivel), SEGUNDO_CAMINO);
	}

}


/* Jugará un turno y dejará el juego en el estado correspondiente.
   Harán su jugada enanos, elfos y orcos en ese orden. */
void jugar_turno(juego_t* juego){

	ataque_defensores(juego);
	turno_orcos(juego);
}

//PRE: recibirá un juego con todas sus estructuras válidas (por referencia) y un valor que correspondara a un defensor especifico.
//POST: devolvera G si se trata de un ENANO, en otro caso, devolvera una L (de ELFO).
char defensor_segun_tipo (juego_t juego, int i){
	if (juego.nivel.defensores[i].tipo == ENANO)
		return ENANO;
	else{
		return ELFO;
	}
}

// Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
void mostrar_juego(juego_t juego){
	system("clear");
	int max_tablero;
	int orcos_muertos = cantidad_orcos_muertos(juego.nivel);

	if ((juego.nivel_actual) == PRIMER_NIVEL || juego.nivel_actual == SEGUNDO_NIVEL){
		max_tablero = MAX_TABLERO_CHICO;
	}else if (juego.nivel_actual == TERCER_NIVEL || juego.nivel_actual == CUARTO_NIVEL){
		max_tablero= MAX_TABLERO_GRANDE;
	}

	printf(MAGENTA "========================================================================================\n" FIN);
	printf("||DATOS||DE||SU||JUEGO||\n");
	printf("NIVEL ACTUAL: %i\n", juego.nivel_actual);
	printf("Un %i porciento de los golpes de los enanos seran criticos y un %i porciento fallaran.\n", juego.critico_gimli, juego.fallo_gimli);
	printf("Un %i porciento de los golpes de los elfos seran criticos y un %i porciento fallaran.\n", juego.critico_legolas, juego.fallo_legolas);
	printf("LA RESISTENCIA DE LA TORRE 1 ES: %i\n", juego.torres.resistencia_torre_1);
	printf("LA RESISTENCIA DE LA TORRE 2 ES: %i\n", juego.torres.resistencia_torre_2);
	printf("Has matado %i orcos de %i en este nivel\n", orcos_muertos, juego.nivel.max_enemigos_nivel);
	printf("Todavia puedes agregar %i enanos extra\n", juego.torres.enanos_extra);
	printf("Todavia puedes agregar %i elfos extra\n", juego.torres.elfos_extra);
	printf(MAGENTA "========================================================================================\n" FIN);
	printf("\n");

	printf(VERDE "                       1 1 1 1 1 1 1 1 1 1\n" FIN);
	printf(VERDE "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n" FIN);
	printf(VERDE "   ═══════════════════════════════════════\n" FIN);

	char tablero[MAX_FILAS][MAX_COLUMNAS];

	for (int i = 0; i < max_tablero; i++){
		for (int j = 0; j < max_tablero; j++){
			tablero[i][j] = TIERRA;
		}
	}

	
	for (int i = 0; i < juego.nivel.tope_camino_1; i++){
		tablero[juego.nivel.camino_1[i].fil][juego.nivel.camino_1[i].col] = CAMINO;
	}

	tablero[juego.nivel.camino_1[INICIO].fil][juego.nivel.camino_1[INICIO].col] = ENTRADA;
	tablero[juego.nivel.camino_1[juego.nivel.tope_camino_1-1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1-1].col] = TORRE;
	
	
	if (juego.nivel_actual == TERCER_NIVEL || juego.nivel_actual == CUARTO_NIVEL){
		for (int i = 0; i < juego.nivel.tope_camino_2; i++){
		tablero[juego.nivel.camino_2[i].fil][juego.nivel.camino_2[i].col] = CAMINO;
		}
		tablero[juego.nivel.camino_2[INICIO].fil][juego.nivel.camino_2[INICIO].col] = ENTRADA;
		tablero[juego.nivel.camino_2[juego.nivel.tope_camino_2-1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2-1].col] = TORRE;
	}


	for (int i = 0; i < juego.nivel.tope_defensores; i++){
		tablero[juego.nivel.defensores[i].posicion.fil][juego.nivel.defensores[i].posicion.col] = defensor_segun_tipo(juego, i);
	}

	for (int i = 0; i < juego.nivel.tope_enemigos; i++){
		if (juego.nivel.enemigos[i].camino == PRIMER_CAMINO && juego.nivel.enemigos[i].vida > SIN_VIDA){
			tablero[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCO;
		}
	}

	for (int i = 0; i < juego.nivel.tope_enemigos; i++){
		if (juego.nivel.enemigos[i].camino == SEGUNDO_CAMINO && juego.nivel.enemigos[i].vida > SIN_VIDA){
			tablero[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col] = ORCO;
		}
	}

	for (int i = 0; i < max_tablero; i++){
		printf(VERDE "%2i║" FIN, i);
		for (int j=0; j < max_tablero; j++){
			printf("%c ", tablero[i][j]);
		}
		printf("\n");
	}

	printf(VERDE "   ═══════════════════════════════════════\n" FIN);
}



