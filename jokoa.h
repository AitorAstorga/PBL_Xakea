#ifndef JOKOA_H
#define JOKOA_H

#include "ourTypes.h"

#define MARGEN_LUZERA 50
#define ZUTABE_KOP 8
#define ILARA_KOP 8
#define LAUKI_KOP 64
#define ZURI 1
#define BELTZ -1
#define JAKE 1

#define LAUKI_X 67
#define LAUKI_Y 47

typedef enum laukia_zenb {
	A1, A2, A3, A4, A5, A6, A7, A8,
	B1, B2, B3, B4, B5, B6, B7, B8,
	C1, C2, C3, C4, C5, C6, C7, C8,
	D1, D2, D3, D4, D5, D6, D7, D8,
	E1, E2, E3, E4, E5, E6, E7, E8,
	F1, F2, F3, F4, F5, F6, F7, F8,
	G1, G2, G3, G4, G5, G6, G7, G8,
	H1, H2, H3, H4, H5, H6, H7, H8
} LAUKIA_ZENB;

int tableroPosizioa;
typedef enum zurien_noranzkoa { ESKUIN, BEHE, EZKER, GORA } ZURIEN_NORANZKOA;
typedef enum mota { HUTS, PEOI, DORRE, ZALDUN, ALFIL, ANDRE, ERREGE } MOTA;
typedef enum emaitzak { MUGITU, JAN, OZTOPOA, EZINEZKOA, PROMOZIOA} EMAITZAK;
typedef enum posizioak_laukian { GOI_ESKUIN, GOI_EZKER, BEHE_ESKUIN, BEHE_EZKER, ZUTABE_BERDIN, ILARA_BERDIN } POSIZIOAK_LAUKIAN;

typedef struct pieza {
	MOTA mota;
	int kolorea;
	int mugimenduKop;
} PIEZA;

typedef struct laukia {
	LAUKIA_ZENB id;
	PIEZA pieza;
} LAUKIA;

typedef struct neurriak {
	int margenLuzera;
	int screenWidth;
	int screenHeight;
} NEURRIAK;

typedef struct puntuaketa {
	int zuri;
	int beltz;
} PUNTUAKETA;

EGOERA jokoa(EGOERA egoera);

void laukiClickatuaMarkatu(LAUKIA clickatua);
void laukiClickatuaDesmarkatu(LAUKIA clickatua);
void laukiakHasieratu(LAUKIA *laukiak);
void mugituPieza(LAUKIA *laukiak, int org, int lauki2);
void puntuaketaPantailaratu(PUNTUAKETA puntu, int sg);
void piezakKargatu(LAUKIA* laukiak, int* imageIdPieza, int sg);
int turnoIrudiaKargatu(int turnoa, int imageIdTurno, int sg);

#endif