#include "imagen.h"
#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>
#include <windows.h>
#include "irudiakEtaSoinuak.h"
#include "jokoa.h"
#include "piezaMugimenduak.h"

NEURRIAK neurria = {50, SCREEN_WIDTH, 47};
//hau erabiliz fullscreen etc garatuko duuuut :)


void resetClickatua(LAUKIA *clickatua) {
	clickatua->id = -1;
	clickatua->pieza.mota = HUTS;
	clickatua->pieza.kolorea = HUTS;
}

int clickatutakoZutabea(float xKoord) {
		
	int zutabea = 0;
	if (xKoord < neurria.margenLuzera) zutabea = 0;
	else if (xKoord > neurria.screenWidth - neurria.margenLuzera) zutabea = 9;
	else {
		while (xKoord >= neurria.margenLuzera && xKoord <= neurria.screenWidth - neurria.margenLuzera) {
			xKoord -= LAUKI_X;//tengo que hacer una calculadora de LAUKI_X...
			zutabea++;
		}
	}
	return zutabea;
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

LAUKIA clickatutakoLaukia(int ebentu, LAUKIA laukiak[]) {
	POSIZIOA posizioa;
	int clickLekua = -1;
	
	posizioa = saguarenPosizioa();

					//En que columna se ha hecho click
	int zutabea = clickatutakoZutabea(posizioa.x);

					//En que fila se ha hecho click
	int ilara = clickatutakoIlara(posizioa.y);

	if((ilara > 0 && ilara < 9) && (zutabea > 0 && zutabea < 9)) clickLekua = 8 * (ilara - 1) + (zutabea - 1);
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

void laukiClickatuaMarkatu(LAUKIA clickatua) {
	int ilara = ilaraKalkulatu(clickatua.id);
	int zutabea = zutabeaKalkulatu(clickatua.id);
	arkatzKoloreaEzarri(0, 255, 0);
	zuzenaMarraztu((zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50, JOKOA);
	zuzenaMarraztu((zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50 + LAUKI_Y, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50 + LAUKI_Y, JOKOA);
	zuzenaMarraztu((zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50 + LAUKI_Y, JOKOA);
	zuzenaMarraztu((zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50 + LAUKI_Y, JOKOA);
	pantailaBerriztu(JOKOA);
}

void laukiClickatuaDesmarkatu(LAUKIA clickatua) {
	int ilara = ilaraKalkulatu(clickatua.id);
	int zutabea = zutabeaKalkulatu(clickatua.id);
	
	SDL_SetRenderDrawColor(gRenderer[JOKOA], 0, 0, 0, 0);
	SDL_RenderDrawLine(gRenderer[JOKOA], (zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50);
	SDL_RenderDrawLine(gRenderer[JOKOA], (zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50 + LAUKI_Y, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50 + LAUKI_Y);
	SDL_RenderDrawLine(gRenderer[JOKOA], (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50 + LAUKI_X, (ilara*LAUKI_Y) + 50 + LAUKI_Y);
	SDL_RenderDrawLine(gRenderer[JOKOA], (zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50, (zutabea*LAUKI_X) + 50, (ilara*LAUKI_Y) + 50 + LAUKI_Y);

	pantailaBerriztu(JOKOA);
}

void laukiakHasieratu(LAUKIA *laukiak) {
	int koordX = 0;
	int koordY = 0;
	//Laukiak "garbitu"
	for (int i = 0; i < LAUKI_KOP; i++) {
		laukiak[i].id = i;
		laukiak[i].pieza.mota = HUTS;
		laukiak[i].pieza.kolorea = HUTS;
		laukiak[i].pieza.mugimenduKop = 0;
		laukiak[i].pieza.imageId = 0;
	}
	//DORREAK
	for (int i = A1; i <= H1; i += H1) {
		koordX = LAUKI_X * zutabeaKalkulatu(i) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i) + MARGEN_LUZERA;
		laukiak[i].pieza.mota = DORRE;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i].pieza.imageId = irudiaKargatu(DORRE_ZURI, JOKOA);
		irudiaMugitu(laukiak[i].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(i + 7) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i + 7) + MARGEN_LUZERA;
		laukiak[i + 7].pieza.mota = DORRE;
		laukiak[i + 7].pieza.kolorea = BELTZ;
		laukiak[i + 7].pieza.imageId = irudiaKargatu(DORRE_BELTZ, JOKOA);
		irudiaMugitu(laukiak[i + 7].pieza.imageId, koordX, koordY);
	}
	//ZALDUNAK
	for (int i = B1; i <= G1; i += G1 - B1) {
		koordX = LAUKI_X * zutabeaKalkulatu(i) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i) + MARGEN_LUZERA;
		laukiak[i].pieza.mota = ZALDUN;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i].pieza.imageId = irudiaKargatu(ZALDUN_ZURI, JOKOA);
		irudiaMugitu(laukiak[i].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(i + 7) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i + 7) + MARGEN_LUZERA;
		laukiak[i + 7].pieza.mota = ZALDUN;
		laukiak[i + 7].pieza.kolorea = BELTZ;
		laukiak[i + 7].pieza.imageId = irudiaKargatu(ZALDUN_BELTZ, JOKOA);
		irudiaMugitu(laukiak[i + 7].pieza.imageId, koordX, koordY);
	}
	//ALFILAK
	for (int i = C1; i <= F1; i += F1 - C1) {
		koordX = LAUKI_X * zutabeaKalkulatu(i) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i) + MARGEN_LUZERA;
		laukiak[i].pieza.mota = ALFIL;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i].pieza.imageId = irudiaKargatu(ALFIL_ZURI, JOKOA);
		irudiaMugitu(laukiak[i].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(i + 7) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i + 7) + MARGEN_LUZERA;
		laukiak[i + 7].pieza.mota = ALFIL;
		laukiak[i + 7].pieza.kolorea = BELTZ;
		laukiak[i + 7].pieza.imageId = irudiaKargatu(ALFIL_BELTZ, JOKOA);
		irudiaMugitu(laukiak[i + 7].pieza.imageId, koordX, koordY);
	}
	//ANDREAK
	if ("kodeaOrdenatutaGeratzeko" == "kodeaOrdenatutaGeratzeko") {
		koordX = LAUKI_X * zutabeaKalkulatu(D1) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(D1) + MARGEN_LUZERA;
		laukiak[D1].pieza.mota = ANDRE;
		laukiak[D1].pieza.kolorea = ZURI;
		laukiak[D1].pieza.imageId = irudiaKargatu(ANDRE_ZURI, JOKOA);
		irudiaMugitu(laukiak[D1].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(D8) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(D8) + MARGEN_LUZERA;
		laukiak[D8].pieza.mota = ANDRE;
		laukiak[D8].pieza.kolorea = BELTZ;
		laukiak[D8].pieza.imageId = irudiaKargatu(ANDRE_BELTZ, JOKOA);
		irudiaMugitu(laukiak[D8].pieza.imageId, koordX, koordY);
	}
	//ERREGEA
	if ("kodeaOrdenatutaGeratzeko" == "kodeaOrdenatutaGeratzeko") {
		koordX = LAUKI_X * zutabeaKalkulatu(E1) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(E1) + MARGEN_LUZERA;
		laukiak[E1].pieza.mota = ERREGE;
		laukiak[E1].pieza.kolorea = ZURI;
		laukiak[E1].pieza.imageId = irudiaKargatu(ERREGE_ZURI, JOKOA);
		irudiaMugitu(laukiak[E1].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(E8) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(E8) + MARGEN_LUZERA;
		laukiak[E8].pieza.mota = ERREGE;
		laukiak[E8].pieza.kolorea = BELTZ;
		laukiak[E8].pieza.imageId = irudiaKargatu(ERREGE_BELTZ, JOKOA);
		irudiaMugitu(laukiak[E8].pieza.imageId, koordX, koordY);
	}
	//PEOIAK
	for (int i = A1; i < H8; i += 8) {
		koordX = LAUKI_X * zutabeaKalkulatu(i + 1) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i + 1) + MARGEN_LUZERA;
		laukiak[i + 1].pieza.mota = PEOI;
		laukiak[i + 1].pieza.kolorea = ZURI;
		laukiak[i + 1].pieza.imageId = irudiaKargatu(PEOI_ZURI, JOKOA);
		irudiaMugitu(laukiak[i + 1].pieza.imageId, koordX, koordY);

		koordX = LAUKI_X * zutabeaKalkulatu(i + 6) + MARGEN_LUZERA;
		koordY = LAUKI_Y * ilaraKalkulatu(i + 6) + MARGEN_LUZERA;
		laukiak[i + 6].pieza.mota = PEOI;
		laukiak[i + 6].pieza.kolorea = BELTZ;
		laukiak[i + 6].pieza.imageId = irudiaKargatu(PEOI_BELTZ, JOKOA);
		irudiaMugitu(laukiak[i + 6].pieza.imageId, koordX, koordY);
	}
	irudiakMarraztu(JOKOA);
}

void mugituPieza(LAUKIA *laukiak, LAUKIA laukia, int lauki2, int turnoa) {
	int koordX = 0;
	int koordY = 0;

	koordX = LAUKI_X * zutabeaKalkulatu(lauki2) + MARGEN_LUZERA;
	koordY = LAUKI_Y * ilaraKalkulatu(lauki2) + MARGEN_LUZERA;

	laukiak[laukia.id].pieza.mota = HUTS;
	laukiak[laukia.id].pieza.kolorea = HUTS;
	irudiaMugitu(laukiak[laukia.id].pieza.imageId, koordX, koordY);
	laukiak[lauki2].pieza.mugimenduKop++;
	laukiak[lauki2].pieza.mota = laukia.pieza.mota;
	laukiak[lauki2].pieza.kolorea = turnoa;
	laukiak[lauki2].pieza.imageId = laukia.pieza.imageId;

	pantailaGarbitu(JOKOA);
	irudiakMarraztu(JOKOA);
}

int posizioaTaulan(LAUKIA *clickatua) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);

	//Zutabe berdina
	if (zutabe0 == zutabe1) return ZUTABE_BERDIN;
	//Ilara berdina
	if (ilara0 == ilara1) return ILARA_BERDIN;

	//Eskuinean, behean
	if (zutabe0 < zutabe1 && ilara0 < ilara1) return BEHE_ESKUIN;
	//Ezkerrean, behean
	if (zutabe0 > zutabe1 && ilara0 < ilara1) return BEHE_EZKER;
	//Eskuinean, gainean
	if (zutabe0 < zutabe1 && ilara0 > ilara1) return GOI_ESKUIN;
	//Ezkerrean, gainean
	if (zutabe0 > zutabe1 && ilara0 > ilara1) return GOI_EZKER;
}

int mugituEdoJanPieza(LAUKIA *clickatua, LAUKIA *laukiak, int turnoa) {
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

int taulaBiratu(LAUKIA *laukiak, int id) {
	LAUKIA aux[64];
	
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			aux[(9 - i) * j].id = laukiak[(i - 1) * 8 + j].id;
			aux[(9 - i) * j].pieza.imageId = laukiak[(i - 1) * 8 + j].pieza.imageId;
			aux[8].pieza.kolorea = laukiak[8].pieza.kolorea;
			aux[(9 - i) * j].pieza.mota = laukiak[(i - 1) * 8 + j].pieza.mota;
			aux[(9 - i) * j].pieza.mugimenduKop = laukiak[(i - 1) * 8 + j].pieza.mugimenduKop;
		}
	}
	
	irudiaKendu(id);
	id = irudiaKargatu(CHESS_IMG_BIRATU, JOKOA);
	irudiaMugitu(id, 0, 0);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);
	return id;
}
//Menu//
void jokoa(void) {
	LAUKIA laukiak[64];
	LAUKIA clickatua[2];
	int clickatuMota;
	int puntuaketaAux = 0;
	int zuriPuntuaketa = 0;
	int beltzPuntuaketa = 0;
	int clickEzkerKop = 0;
	int turnoa = 1;
	int eragiketa;
	int ebentuJoko = 0;
	int imageIdTurnoBeltz = 0;
	int imageIdTurnoZuri = irudiaKargatu(TURNOA_ZURI, JOKOA);
	int imageIdFondoa = irudiaKargatu(CHESS_IMG, JOKOA);
	//aukeratutakoFondoa comingSOON :)
	laukiakHasieratu(&laukiak);
	irudiaMugitu(imageIdFondoa, 0, 0);
	irudiaMugitu(imageIdTurnoZuri, 50, 0);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);
	
	do {
		ebentuJoko = ebentuaJasoGertatuBada();
	
		if (ebentuJoko == SAGU_BOTOIA_EZKERRA && clickEzkerKop < 2) {
			clickatua[clickEzkerKop] = clickatutakoLaukia(ebentuJoko, laukiak);
			//CLICK 1
			if (clickEzkerKop == 0 && clickatua[clickEzkerKop].id >= 0 && clickatua[clickEzkerKop].pieza.mota > HUTS && clickatua[clickEzkerKop].pieza.kolorea == turnoa) {
				//if: lehenengo click da && click egin da && pieza bat click egin da && clickatutako pieza kolore berdinekoa da
				laukiClickatuaMarkatu(clickatua[clickEzkerKop]);
				clickEzkerKop++;
			}
			//CLICK 2
			if (clickEzkerKop == 1 && clickatua[clickEzkerKop].pieza.kolorea != turnoa && clickatua[1].id >= 0) {
				//if: bigarren click da && clickatutako pieza kolore berdinekoa ez bada && click egin da
				laukiClickatuaMarkatu(clickatua[clickEzkerKop]);
				clickatuMota = clickatua[1].pieza.mota;
				clickEzkerKop++;
				eragiketa = mugituEdoJanPieza(clickatua, laukiak, turnoa);
				if (eragiketa == EZINEZKOA || eragiketa == OZTOPOA) {
					laukiClickatuaDesmarkatu(clickatua[1]);
					clickEzkerKop--;
					//mugimenduEzOnartua-Ezinezkoa
				}
				else if (eragiketa == MUGITU || eragiketa == JAN) {
					mugituPieza(laukiak, clickatua[0], clickatua[1].id, turnoa);
					if (eragiketa == JAN) {
						switch (clickatuMota) {
							case PEOI:
								printf("PEOIA JAN");
								puntuaketaAux++;
								break;
							case DORRE:
								printf("DORREA JAN");
								puntuaketaAux = 5;
								break;
							case ZALDUN:
								printf("ZALDUNA JAN");
								puntuaketaAux = 3;
								break;
							case ALFIL:
								printf("ALFILA JAN");
								puntuaketaAux = 3;
								break;
							case ANDRE:
								printf("ANDREA JAN");
								puntuaketaAux = 9;
								break;
							case ERREGE:
								printf("ERREGEA LOL JAN");
								break;
						}
						if (turnoa == BELTZ) beltzPuntuaketa += puntuaketaAux;
						if (turnoa == ZURI) zuriPuntuaketa += puntuaketaAux;
					}
				}
			}
			if (clickEzkerKop == 2) {
				laukiClickatuaDesmarkatu(clickatua[0]);
				laukiClickatuaDesmarkatu(clickatua[1]);
				resetClickatua(&clickatua[0]);
				resetClickatua(&clickatua[1]);
				clickEzkerKop = 0;
				turnoa *= -1;
				if (turnoa == BELTZ) {
					imageIdTurnoBeltz = irudiaKargatu(TURNOA_BELTZ, JOKOA);
					irudiaKendu(imageIdTurnoZuri);
					irudiaMugitu(imageIdTurnoBeltz, 50 + 6 * LAUKI_X, JOKOA);
				}
				if (turnoa == ZURI) {
					imageIdTurnoZuri = irudiaKargatu(TURNOA_ZURI, JOKOA);
					irudiaKendu(imageIdTurnoBeltz);
					irudiaMugitu(imageIdTurnoZuri, 50, 0);
				}
				pantailaGarbitu(JOKOA);
				irudiakMarraztu(JOKOA);
				pantailaBerriztu(JOKOA);
			}
		}
		if (ebentuJoko == SAGU_BOTOIA_ESKUMA && clickEzkerKop > 0) {
			clickEzkerKop--;
			laukiClickatuaDesmarkatu(clickatua[clickEzkerKop]);
			resetClickatua(&clickatua[0]);
			resetClickatua(&clickatua[1]);
		}
		if (ebentuJoko == TECLA_p) {			
			sgHasieratu(PAUSA, 300, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
			int aukera = 0;
			int imagePausa = irudiaKargatu(PAUSA_BELTZ, PAUSA);
			irudiakMarraztu(PAUSA);
			pantailaBerriztu(PAUSA);
			while (aukera != TECLA_p) {
				aukera = ebentuaJasoGertatuBada();
				//if (aukera == 'f') imageIdFondoa = taulaBiratu(laukiak, imageIdFondoa);
				//ERROR, excepcion kolorea ¿?
			}
			irudiaKendu(imagePausa);
			sgItxi(PAUSA);
		}
	} while (ebentuJoko != TECLA_RETURN);

	//fitxategietan partida gorde.................. COMING MAYBE SOON DUNNOLKASJRJBGLKAHJDSBR

	irudiaKendu(imageIdFondoa);
	pantailaGarbitu(JOKOA);
	pantailaBerriztu(JOKOA);
	sgItxi(JOKOA);
}
