#include "jokoa.h"
#include "graphics.h"
#include "OurTypes.h"
#include "ebentoak.h"
#include "irudiakEtaSoinuak.h"
#include "piezaMugimenduak.h"
#include "kalkuloak.h"
#include <stdio.h>
#include "imagen.h"

NEURRIAK neurria = { 50, SCREEN_WIDTH, 47 };

void resetClickatua(LAUKIA* clickatua) {
	clickatua->id = -1;
	clickatua->pieza.mota = HUTS;
	clickatua->pieza.kolorea = HUTS;
}

int clickatutakoIlara(float yKoord) {
	int ilara = 0;
	if (yKoord < MARGEN_LUZERA) ilara = 0;
	else if (yKoord > SCREEN_WIDTH - MARGEN_LUZERA) ilara = 9;
	else {
		while (yKoord >= MARGEN_LUZERA && yKoord <= SCREEN_HEIGHT - MARGEN_LUZERA) {
			yKoord -= LAUKI_Y;
			ilara++;
		}
	}
	return ilara;
}

int clickatutakoZutabea(float xKoord) {

	int zutabea = 0;
	if (xKoord < neurria.margenLuzera) zutabea = 0;
	else if (xKoord > neurria.screenWidth - neurria.margenLuzera) zutabea = 9;
	else {
		while (xKoord >= neurria.margenLuzera && xKoord <= neurria.screenWidth - neurria.margenLuzera) {
			xKoord -= LAUKI_X;
			zutabea++;
		}
	}
	return zutabea;
}

LAUKIA clickatutakoLaukia(int ebentu, LAUKIA laukiak[]) {
	POSIZIOA posizioa;
	int zutabea;
	int ilara;
	int clickLekua = -1;

	posizioa = saguarenPosizioa();
	zutabea = clickatutakoZutabea(posizioa.x);
	ilara = clickatutakoIlara(posizioa.y);

	if ((ilara > 0 && ilara < 9) && (zutabea > 0 && zutabea < 9)) {
		clickLekua = 8 * (ilara - 1) + (zutabea - 1);
	}
	else resetClickatua(&laukiak[clickLekua]);
	return laukiak[clickLekua];
}

int ilaraKalkulatu(int id) {
	int ilara = 0;
	while (id + 1 - ZUTABE_KOP > 0) {
		id -= ZUTABE_KOP;
		ilara++;
	}
	return ilara;
}

int zutabeaKalkulatu(int id) {
	int ilara = ilaraKalkulatu(id);
	int zutabea = id - ilara * ZUTABE_KOP;
	return zutabea;
}

int posizioaTaulan(LAUKIA* clickatua) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);

	if (zutabe0 == zutabe1) return ZUTABE_BERDIN;
	else if (ilara0 == ilara1) return ILARA_BERDIN;
	else if (zutabe0 < zutabe1 && ilara0 < ilara1) return BEHE_ESKUIN;
	else if (zutabe0 > zutabe1&& ilara0 < ilara1) return BEHE_EZKER;
	else if (zutabe0 < zutabe1 && ilara0 > ilara1) return GOI_ESKUIN;
	else if (zutabe0 > zutabe1&& ilara0 > ilara1) return GOI_EZKER;
	else return -1;
}

LAUKIA erregeaBilatu(LAUKIA* laukiak, int turnoa) {
	LAUKIA erregea = { -1, {-1, 0, 0} };
	for (int i = 0; i < LAUKI_KOP; i++) {
		if (laukiak[i].pieza.mota == ERREGE && laukiak[i].pieza.kolorea != turnoa) {
			erregea = laukiak[i];
		}
	}
	return erregea;
}

int puntuaketa(MOTA clickatuMota) {
	int puntuak = 0;
	switch (clickatuMota) {
	case PEOI:
		printf("PEOIA JAN");
		puntuak++;
		break;
	case DORRE:
		printf("DORREA JAN");
		puntuak = 5;
		break;
	case ZALDUN:
		printf("ZALDUNA JAN");
		puntuak = 3;
		break;
	case ALFIL:
		printf("ALFILA JAN");
		puntuak = 3;
		break;
	case ANDRE:
		printf("ANDREA JAN");
		puntuak = 9;
		break;
	case ERREGE:
		printf("ERREGEA LOL JAN");
		break;
	}
	return puntuak;
}

int jakeAlDa(int id, LAUKIA* laukiak, int turnoa) {
	LAUKIA clickatua[2];
	clickatua[0] = laukiak[id];
	clickatua[1] = erregeaBilatu(laukiak, turnoa);
	int posible = mugituEdoJanPieza(clickatua, laukiak, turnoa);
	if (posible == JAN) return JAKE;
	else return 0;
}

int mugituEdoJanPieza(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	switch (clickatua[0].pieza.mota) {
	default: return -1;
	case PEOI:
		return mugimenduPeoi(clickatua, laukiak, turnoa);
		break;
	case DORRE:
		return mugimenduDorre(clickatua, laukiak, turnoa);
		break;
	case ZALDUN:
		return mugimenduZaldun(clickatua, laukiak, turnoa);
		break;
	case ALFIL:
		return mugimenduAlfil(clickatua, laukiak, turnoa);
		break;
	case ANDRE:
		return mugimenduAndre(clickatua, laukiak, turnoa);
		break;
	case ERREGE:
		return mugimenduErrege(clickatua, laukiak, turnoa);
		break;
	}
}

int taulaBiratu(LAUKIA* laukiak, int id, int* imageIdPieza, int sg) {
	LAUKIA transposatua[8][8];
	LAUKIA ilara[8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			transposatua[j][i] = laukiak[(i * 8) + j];
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			ilara[j] = transposatua[i][j];
		}
		for (int j = 0; j < 8; j++) {
			transposatua[i][j] = ilara[7 - j];
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			laukiak[(i * 8) + j].pieza.kolorea = transposatua[i][j].pieza.kolorea;
			laukiak[(i * 8) + j].pieza.mota = transposatua[i][j].pieza.mota;
			laukiak[(i * 8) + j].pieza.mugimenduKop = transposatua[i][j].pieza.mugimenduKop;
		}
	}

	if (tableroPosizioa == GORA) tableroPosizioa = ESKUIN;
	else tableroPosizioa++;
	if (tableroPosizioa == GORA || tableroPosizioa == BEHE) {
		irudiaKendu(id);
		id = irudiaKargatu(CHESS_IMG_BIRATU, sg);
	}
	else {
		irudiaKendu(id);
		id = irudiaKargatu(CHESS_IMG, sg);
	}

	piezakKargatu(laukiak, imageIdPieza, sg);

	return id;
}