#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "animos.h"

const int PRIM_DIA_RANGO_1 = 1;
const int ULT_DIA_RANGO_1 = 10;
const int PRIM_DIA_RANGO_2 = 11;
const int ULT_DIA_RANGO_2 = 20;
const int PRIM_DIA_RANGO_3 = 21;
const int ULT_DIA_RANGO_3 = 30;
const char MANIANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char ENSALADA = 'E';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char GUISO = 'G';
const int MIN_HORAS_RANGO_1 = 0;
const int MAX_HORAS_RANGO_1 = 4;
const int MIN_HORAS_RANGO_2 = 5;
const int MAX_HORAS_RANGO_2 = 8;
const int MIN_HORAS_RANGO_3 = 9;
const int MAX_HORAS_RANGO_3 = 12;
const char MAL_ANIMO = 'M';
const char REGULAR_ANIMO = 'R';
const char BUEN_ANIMO = 'B';
const int MIN_PUNTOS_MAL = 5;
const int MAX_PUNTOS_MAL = 20;
const int MIN_PUNTOS_REGU = 21;
const int MAX_PUNTOS_REGU = 35;
const int MIN_PUNTOS_BIEN = 36;
const int MAX_PUNTOS_BIEN = 50;
static const int VELOCIDAD_MEDIA = 50;
static const int VELOCIDAD_BAJA = 25;
static const int VELOCIDAD_MAXIMA = 75;
static const int HUMEDAD_MAXIMA = 75;
static const int HUMEDAD_MEDIA = 50;
static const int HUMEDAD_BAJA = 25;
static const char AFIRMATIVO = 'S';
static const char NEGATIVO = 'N';
const int PUNTOS_PIE_DERECHO = 10;
const int PUNTOS_PIE_IZQUIERDO = 0;
const int PUNTOS_ENSALADA = 20;
const int PUNTOS_HAMBURGUESA = 15;
const int PUNTOS_GUISO = 5;
const int PUNTOS_PIZZA = 10;
const int MIN_PUNTOS_SUENIO = 0;
const int MEDIO_PUNTOS_SUENIO = 10;
const int MAX_PUNTOS_SUENIO = 20;

//POST: devolvera true si el caracter recibido como parametro es una S (SI) o una N (NO).
bool es_valida(char respuesta){

	return (respuesta == AFIRMATIVO || respuesta == NEGATIVO);
} 


//POST: devolverá true cuando el valor recibido como parametro sea un numero entre el 1 y el 30.
bool es_dia_valido (int dia_del_mes){
		return ((dia_del_mes >= PRIM_DIA_RANGO_1) && (dia_del_mes <= ULT_DIA_RANGO_3));
}


//POST: devolverá el valor ingresado por el usuario (entre 1 y 30).
void preguntar_dia_del_mes (int *dia_del_mes){
		printf("¿En que dia del mes se encuentra? ");
		scanf (" %i", dia_del_mes);
		while(!es_dia_valido(*dia_del_mes)){
			printf("Por favor, ingrese un dia del mes valido! ");
			scanf(" %i", dia_del_mes);
		}
}

//POST: devolverá la velociad del viento respectivo al rango al que pertenezca el dia del mes.
//----> entre el 1 y el 10: 75 km/h
//----> entre el 11 y el 20: 50 km/h
//----> entre el 21 y el 30: 25 km/h
int velocidad_viento_segun_dia (int *dia_del_mes){
		int velocidad;
		if ((*dia_del_mes >= PRIM_DIA_RANGO_1) && (*dia_del_mes <= ULT_DIA_RANGO_1)){	
			velocidad = VELOCIDAD_MAXIMA;
		}else if ((*dia_del_mes >= PRIM_DIA_RANGO_2) && (*dia_del_mes <= ULT_DIA_RANGO_2)){
			velocidad = VELOCIDAD_MEDIA;
		}else if ((*dia_del_mes >= PRIM_DIA_RANGO_3) && (*dia_del_mes <= ULT_DIA_RANGO_3)){
			velocidad = VELOCIDAD_BAJA;
		}

		return velocidad;
}

//POST: devolverá true si el caracter recibido como parametro es una M (mañana), T (tarde) o N (noche).
bool es_hora_valida (char hora_del_dia){
		if ((hora_del_dia == MANIANA) || (hora_del_dia == TARDE) || (hora_del_dia == NOCHE)){
			return true;
		}else
			return false;
}


//POST: devolverá el caracter ingresado por el usuario: M (mañana), T (tarde) o N (noche).
void preguntar_hora_del_dia (char* hora_del_dia){
		printf("¿Cual es la hora actual? Maniana: M - Tarde: T - Noche: N : ");
		scanf(" %c", hora_del_dia);
		while(!es_hora_valida(*hora_del_dia)){
			printf("Por favor, ingrese una hora valida! Maniana: M - Tarde: T - Noche: N : ");
			scanf(" %c", hora_del_dia);
		}
}

//PRE: char hora_del_dia: M (mañana), T (tarde) o N (noche).
//POST: devolverá el porcentaje de humedad que hay en ese momento del dia.
//----> Maniana: 75%.
//----> Tarde: 25%.
//----> Noche 50%.

int porcentaje_humedad_segun_hora(char* hora_del_dia){
		int porcentaje;
		if (*hora_del_dia == MANIANA){
			porcentaje = HUMEDAD_MAXIMA;
		}else if (*hora_del_dia == TARDE){
			porcentaje = HUMEDAD_BAJA;
		}else if (*hora_del_dia == NOCHE){
			porcentaje = HUMEDAD_MEDIA;
		}

		return porcentaje;

}

//POST: devolverá true si el caracter recibido como parametro es D (derecho) o I (izquierdo).
bool es_pie_valido (char pie_usado){
		return ((pie_usado == PIE_DERECHO) || (pie_usado == PIE_IZQUIERDO));
}


//POST: devolvera la inicial del pie ingresado por el usario: D (derecho) o I (izquierdo).
void preguntar_pie_levanto (char* pie_usado){
		printf("Indique el pie con el que se levanto: Pie derecho: D - Pie izquierdo: I : ");
		scanf(" %c", pie_usado);
		while (!es_pie_valido(*pie_usado)){
			printf("Por favor, ingrese un pie valido! Pie derecho: D - Pie izquierdo: I : ");
			scanf(" %c", pie_usado);
	}
}

//PRE: char pie_usado: D (derecho) o I (izquierdo).
//POST: devolvera la cantidad de puntos respectivos al pie ingresado.
//----> Derecho: 10.
//----> Izquierdo: 0.
int puntaje_segun_pie (char* pie_usado){
		preguntar_pie_levanto (pie_usado);
		int puntos_pie;
		if (*pie_usado == PIE_DERECHO){
			puntos_pie = PUNTOS_PIE_DERECHO;
		}else if (*pie_usado == PIE_IZQUIERDO){
			puntos_pie = PUNTOS_PIE_IZQUIERDO;
		}

		return puntos_pie;

}


//POST: devolverá true cuando el caracter recibido como parámetro sea E (ensalada), H (hamburguesa), P (pizza) o G (guiso).
bool es_cena_valida (char cena_dia_anterior){
		return ((cena_dia_anterior == ENSALADA) || (cena_dia_anterior == HAMBURGUESA) || (cena_dia_anterior == PIZZA) || (cena_dia_anterior == GUISO));
}

//POST: devolverá la inicial de la comida ingresada por el usuario.
void preguntar_cena_dia_anterior (char* cena_dia_anterior){
		printf("Ingrese la comida que ceno el dia anterior Ensalada: E - Hamburguesa: H - Pizza: P - Guiso: G : ");
		scanf(" %c", cena_dia_anterior);
		while (!es_cena_valida(*cena_dia_anterior)){
			printf("Por favor, ingrese bien lo que ceno anoche Ensalada: E - Hamburguesa: H - Pizza: P - Guiso: G : ");
			scanf(" %c", cena_dia_anterior);
	}
}

//PRE: char cena_dia_anterior:  E (ensalada), H (hamburguesa), P (pizza) o G (guiso).
//POST: devolverá la cantidad de puntos respectivos a la cena ingresada por el usuario:
//----> Ensalada: 20 puntos
//----> Hamburguesa: 15 puntos.
//----> Pizza: 10 puntos.
//----> Guiso: 5 puntos. 
int puntaje_segun_comida_cena (char* cena_dia_anterior){
		preguntar_cena_dia_anterior (cena_dia_anterior);
		int puntos_cena;
		if (*cena_dia_anterior == ENSALADA){
			puntos_cena = PUNTOS_ENSALADA;
		}else if (*cena_dia_anterior == HAMBURGUESA){
			puntos_cena = PUNTOS_HAMBURGUESA;
		}else if (*cena_dia_anterior == PIZZA){
			puntos_cena = PUNTOS_PIZZA;
		}else if (*cena_dia_anterior == GUISO){
			puntos_cena = PUNTOS_GUISO;
		}

		return puntos_cena;

}

//POST: devolverá true cuando el valor este dentro del rango valido de horas. (entre 0 y 12 horas).
bool son_horas_validas (int horas_dormidas){
		return ((horas_dormidas >= MIN_HORAS_RANGO_1) && (horas_dormidas <= MAX_HORAS_RANGO_3));
}


//POST: devolverá el valor de las horas ingresadas por el usuario.
void preguntar_cuanto_durmio (int* horas_dormidas){
		printf("¿Cuantas horas durmio anoche? (entre 1 y 12): ");
		scanf(" %i", horas_dormidas);
		while(!son_horas_validas(*horas_dormidas)){
			printf("Por favor, indique correctamente cuantas horas durmio (entre 1 y 12): ");
			scanf( " %i", horas_dormidas);
	}
}

//PRE:  int horas_dormidas: entre 0 y 12.
//POST: devolverá los puntos respectivos a las horas.
//----> Entre 0 y 4: 0 puntos.
//----> Etre 5 y 8: 10 puntos.
//----> Entre 8 y 12: 20 puntos.
int puntaje_segun_horas_dormidas (int* horas_dormidas){
		preguntar_cuanto_durmio (horas_dormidas);
		int puntos_suenio;
		if ((*horas_dormidas >= MIN_HORAS_RANGO_1) && (*horas_dormidas <= MAX_HORAS_RANGO_1)){
			puntos_suenio = MIN_PUNTOS_SUENIO;
		}else if ((*horas_dormidas >= MIN_HORAS_RANGO_2) && (*horas_dormidas <= MAX_HORAS_RANGO_2)){
			puntos_suenio = MEDIO_PUNTOS_SUENIO;
		}else if ((*horas_dormidas >= MIN_HORAS_RANGO_3) && (*horas_dormidas <= MAX_HORAS_RANGO_3)){
			puntos_suenio = MAX_PUNTOS_SUENIO;
		}

		return puntos_suenio;

}

//PRE:
//--> pie_usado: D (derecho) o I (izquierdo).
//--> cena_dia_anterior: E (ensalada), H (hamburguesa), P (pizza) o G (guiso).
//--> horas_dormidas: entre O y 12 
//POST: devolverá la cantidad de puntos que obtuvo correspondientes a los datos ingresados.

int puntaje_total_segun_datos (char *pie_usado, char* cena_dia_anterior, int* horas_dormidas){
		int puntos_pie = puntaje_segun_pie(pie_usado);
		int puntos_cena = puntaje_segun_comida_cena (cena_dia_anterior);
		int puntos_suenio = puntaje_segun_horas_dormidas (horas_dormidas);

		return puntos_pie + puntos_cena + puntos_suenio; 
}

//PRE:
//--> pie_usado: D (derecho) o I (izquierdo).
//--> cena_dia_anterior: E (ensalada), H (hamburguesa), P (pizza) o G (guiso).
//--> horas_dormidas: entre O y 12 
//POST: devolverá el animo que tiene el personaje (Gimli o Legolas) segun los puntos obtenidos segun los datos ingresados.

char animo_segun_puntaje_total (char *pie_usado, char* cena_dia_anterior, int* horas_dormidas){
		int puntos_totales = puntaje_total_segun_datos(pie_usado, cena_dia_anterior, horas_dormidas);
		char animo;
		if ((puntos_totales >= MIN_PUNTOS_MAL) && (puntos_totales <= MAX_PUNTOS_MAL)){
			animo = MAL_ANIMO;
		}else if ((puntos_totales >= MIN_PUNTOS_REGU) && (puntos_totales <= MAX_PUNTOS_REGU)){
			animo = REGULAR_ANIMO;
		}else if ((puntos_totales >= MIN_PUNTOS_BIEN) && (puntos_totales <= MAX_PUNTOS_BIEN)){
			animo = BUEN_ANIMO;
		}

		return animo;

}


void animos (int* viento, int *humedad, char* animo_legolas, char* animo_gimli){

	int dia_del_mes;
	char hora_del_dia;
	char pie_usado;
	char cena_dia_anterior;
	int horas_dormidas;
	char respuesta;

	printf("DESEA INGRESAR LOS DATOS DE SU JUEGO?\nSi la respuesta es SI ingrese S si la respuesta es NO ingrese N: ");
	scanf(" %c", &respuesta);

	if (respuesta == AFIRMATIVO){

	preguntar_dia_del_mes(&dia_del_mes);
	*viento = velocidad_viento_segun_dia(&dia_del_mes);
	preguntar_hora_del_dia(&hora_del_dia);
	*humedad = porcentaje_humedad_segun_hora(&hora_del_dia);
	printf ("A PARTIR DE AQUI INGRESE LOS DATOS DE LEGOLAS \n" );
	*animo_legolas = animo_segun_puntaje_total (&pie_usado, &cena_dia_anterior, &horas_dormidas);
	printf ("AHORA, INGRESE LOS DATOS DE GIMLI POR FAVOR \n" );
	*animo_gimli = animo_segun_puntaje_total(&pie_usado, &cena_dia_anterior, &horas_dormidas);
	}
	
	else{
		*viento =  25;
		*humedad = 25;
		*animo_legolas = BUEN_ANIMO;
		*animo_gimli = BUEN_ANIMO;
	}
}


