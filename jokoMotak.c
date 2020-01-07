#include "jokoa.h"
#include "kalkuloak.h"
#include <stdlib.h>
#include <time.h>
/*Ejemplo de errores. Problemas a tope con stack overflows y diversos bakuretsus aquí y allá
*/
void mugimenduAleatorio(LAUKIA* laukiak) {
	LAUKIA aux[2];
	int mugiDaiteke[16] = { 0 };//las piezas negras. luego lo reutilizo para... oh igual ahí peta?
	int mugiKop = 0;
	int eragiketaB;
	srand((unsigned int)time(NULL));
	int aleatorio = rand();
	for (int i = 0; i < LAUKI_KOP; i++) {
		aux[0].id = laukiak[i].id;
		aux[0].pieza.kolorea = laukiak[i].pieza.kolorea;//y asi
		aux[0].pieza.mota = laukiak[i].pieza.mota;//moar
		aux[0].pieza.mugimenduKop = laukiak[i].pieza.mugimenduKop;//all of it
		if (laukiak[aux[0].id].pieza.kolorea == BELTZ) {
			for (int j = 0; j < LAUKI_KOP; j++) {
				aux[1].id = laukiak[j].id;//
				aux[1].pieza.kolorea = laukiak[j].pieza.kolorea;//
				aux[1].pieza.mota = laukiak[j].pieza.mota;//
				aux[1].pieza.mugimenduKop = laukiak[j].pieza.mugimenduKop;//
				eragiketaB = mugituEdoJanPieza(aux, laukiak, BELTZ);
				if (eragiketaB != EZINEZKOA && eragiketaB != -1) {
					mugiDaiteke[mugiKop] = aux[0].id;
					mugiKop++;
					break;
				}
			}
		}
	}
	aleatorio = rand() % (mugiKop);
	aux[0].id = laukiak[mugiDaiteke[aleatorio]].id;//
	aux[0].pieza.kolorea = laukiak[mugiDaiteke[aleatorio]].pieza.kolorea;//
	aux[0].pieza.mota = laukiak[mugiDaiteke[aleatorio]].pieza.mota;//
	aux[0].pieza.mugimenduKop = laukiak[mugiDaiteke[aleatorio]].pieza.mugimenduKop;//
	mugiKop = 0;
	for (int i = 0; i < 16; i++) mugiDaiteke[i] = -1;
	for (int i = 0; i < LAUKI_KOP; i++) {
		aux[1].id = laukiak[i].id;//
		aux[1].pieza.kolorea = laukiak[i].pieza.kolorea;///
		aux[1].pieza.mota = laukiak[i].pieza.mota;//
		aux[1].pieza.mugimenduKop = laukiak[i].pieza.mugimenduKop;//
		eragiketaB = mugituEdoJanPieza(aux, laukiak, BELTZ);
		if (eragiketaB != EZINEZKOA && eragiketaB != -1) {
			mugiDaiteke[mugiKop] = aux[1].id;
			mugiKop++;

		}
	}
	aleatorio = rand() % (mugiKop);
	aux[1].id = laukiak[mugiDaiteke[aleatorio]].id;
	aux[1].pieza.kolorea = laukiak[mugiDaiteke[aleatorio]].pieza.kolorea;
	aux[1].pieza.mota = laukiak[mugiDaiteke[aleatorio]].pieza.mota;
	aux[1].pieza.mugimenduKop = laukiak[mugiDaiteke[aleatorio]].pieza.mugimenduKop;

	if (mugituEdoJanPieza(aux, laukiak, BELTZ) != EZINEZKOA) {
		mugituPieza(laukiak, aux[0].id, aux[1].id);
	}
}

void botSimetriko(LAUKIA *clickatua, LAUKIA *laukiak, int *beltzPuntuaketa) {
	LAUKIA botClickatua[2];
	int eragiketa = 0;
	
	int piezaMota = clickatua[0].pieza.mota;
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe0 = ZUTABE_KOP - zutabeaKalkulatu(clickatua[0].id) - 1;
	int ilara1 = ilaraKalkulatu(clickatua[1].id);
	int zutabe1 = ZUTABE_KOP - zutabeaKalkulatu(clickatua[1].id) - 1;

	botClickatua[0].id = 8 * ilara0 + zutabe0;
	botClickatua[1].id = 8 * ilara1 + zutabe1;
	botClickatua[0].pieza.kolorea = laukiak[botClickatua[0].id].pieza.kolorea;
	botClickatua[1].pieza.kolorea = laukiak[botClickatua[1].id].pieza.kolorea;
	botClickatua[0].pieza.mota = laukiak[botClickatua[0].id].pieza.mota;
	botClickatua[1].pieza.mota = laukiak[botClickatua[1].id].pieza.mota;
	botClickatua[0].pieza.mugimenduKop = laukiak[botClickatua[0].id].pieza.mugimenduKop;
	botClickatua[1].pieza.mugimenduKop = laukiak[botClickatua[1].id].pieza.mugimenduKop;

	if (botClickatua[0].pieza.kolorea != BELTZ) {
		mugimenduAleatorio(laukiak);
	}
	else {
		eragiketa = mugituEdoJanPieza(botClickatua, laukiak, BELTZ);

		mugituPieza(laukiak, botClickatua[0].id, botClickatua[1].id);
	}
	//if (eragiketa == PROMOZIOA)
	if (eragiketa == JAN) beltzPuntuaketa += puntuaketa(piezaMota);
	//int movimiento = (clickatua[1].id - clickatua[0].id) * -1;
}

/*Moar bugs yay*/
int intercambio(LAUKIA* laukiak) {
	int aldaketa = rand() % (5000);
	int aldaketa2 = rand() % (5000);
	if (aldaketa == 20 && aldaketa2 == 400) {
		for (int i = 0; i < LAUKI_KOP; i++) {
			if (laukiak[i].pieza.kolorea == ZURI) laukiak[i].pieza.kolorea = BELTZ;
			else if (laukiak[i].pieza.kolorea == BELTZ) laukiak[i].pieza.kolorea = ZURI;
		}
		printf("\nALDAKETA");
		return 1;
	}
	else return 0;
}

void botIA(LAUKIA* laukiak, int* beltzPuntuaketa) {
	/*
	Lee todas las piezas que tiene...
	Luego... Mira que movimientos pueden hacer...
	Y hace los que provoquen jaque en el siguiente. Si no, hace
	los que menos "riesgo" tengan. Resta el valor de lo que va a comer
	menos el valor de la pieza que mueve. De esos resultados hace la que mayor
	valor tenga.
	Y... nunca mueve una pieza que permitiera que le hicieran jaque supongo...?
	*/
	LAUKIA clickatua[2];
	int botPiezak[16];
	int piezaKop = 0;
	for (int i = 0; i < LAUKI_KOP; i++) {//1-
		if (laukiak[i].pieza.kolorea == BELTZ) {
			botPiezak[piezaKop] = i;
			piezaKop++;
		}
	}
	for (int i = 0; i < piezaKop; i++) {//2-
		for (int j = 0; j < LAUKI_KOP; j++) {
			clickatua[0] = laukiak[botPiezak[i]];
			clickatua[1] = laukiak[j];
			if (mugituEdoJanPieza(clickatua, laukiak, BELTZ) == JAN) {
				//botPiezak[i].mugimenduPosibleak[mugimenduKop[i]] = j;
				//botPiezak[i].mugimenduBalioak[mugimenduKop[i]] = mugimenduBalioa(laukiak, i, j);
				/*
				int mugimenduBalioa(LAUKIA *laukiak, int lauki1, int lauki2) {
					return (puntuaketa(laukiak[lauki2].pieza.mota) - puntuaketa(laukiak[lauki1].pieza.mota));
				}
				*/
				//mugimenduKop[i]++;
			}
			//botPiezak[i].mugimenduBalioak[mugimenduKop + 1] = EXIT;
		}
	}
	/*//Lista de movimientos con mayor valor
	int baliotsuenak[10];
	int balioKop = 0;
	for(int i = 0; i - piezaKop; i++) {
		for(int j = 0; j < mugimenduKop[i]; j++) {
			if (botPiezak[i].mugimenduBalioak[j] > botPiezak[i].mugimenduBalioak[j + 1]) {
				baliotsuena[balioKop] = botPiezak[i].mugimenduBalioak[j];
				balioKop++;
			}
			else if (botPiezak[i].mugimenduBalioak[j] == botPiezak[i].mugimenduBalioak[j + 1]) {
				baliotsuena[balioKop] = botPiezak[i].mugimenduBalioak[j];
				balioKop++;
			}
		}
	}
	*/
	
}

/*
1- La función examina todas las piezas que puede mover.
2- Analiza los movimientos y realiza el más barato.
3- Si hay varios al mismo precio, mueve virtualmente todas las piezas enemigas y
repite el examen para cada caso.
4- Si la cantidad de bloques recursivamente ejecutados llega a 0, elige aleatoriamente.
	1-
	2-
	3-
	4-

*/

void luckyBlock(LAUKIA* laukiak) {
	//Laukiak "garbitu"
	for (int i = 0; i < LAUKI_KOP; i++) {
		laukiak[i].id = i;
		laukiak[i].pieza.mota = HUTS;
		laukiak[i].pieza.kolorea = HUTS;
		laukiak[i].pieza.mugimenduKop = 0;
	}
	//ALEATORIO
	for (int i = 0; i <= 63; i += 8) {
		laukiak[i].pieza.mota = 1 + rand() % (5);
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i + 1].pieza.mota = 1 + rand() % (5);
		laukiak[i + 1].pieza.kolorea = ZURI;
		laukiak[i + 6].pieza.mota = 1 + rand() % (5);
		laukiak[i + 6].pieza.kolorea = BELTZ;
		laukiak[i + 7].pieza.mota = 1 + rand() % (5);
		laukiak[i + 7].pieza.kolorea = BELTZ;
	}
	//ERREGEA
	laukiak[E1].pieza.mota = ERREGE;
	laukiak[E1].pieza.kolorea = ZURI;
	laukiak[E8].pieza.mota = ERREGE;
	laukiak[E8].pieza.kolorea = BELTZ;
}