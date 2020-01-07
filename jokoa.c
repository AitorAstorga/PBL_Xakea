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
#include <time.h>
#include "kalkuloak.h"
#include "partidak.h"
#include "jokoMotak.h"
#include "menu.h"

//hau erabiliz fullscreen etc garatuko duuuut :)

////////////////////////////////////////////////////////////////////////////////
//................................GRÁFICOS......................................
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

void puntuaketaPantailaratu(PUNTUAKETA puntu, int sg) {
	char txuria[128];
	char beltza[128];
	textuaGaitu(16);
	sprintf_s(txuria, 128, "PUNTUAKETA ZURIA: %i", puntu.zuri);
	sprintf_s(beltza, 128, "PUNTUAKETA BELTZA: %i", puntu.beltz);
	textuaIdatzi(50, 450, txuria, sg);
	textuaIdatzi(350, 450, beltza, sg);
}

void piezakKargatu(LAUKIA *laukiak, int *imageIdPieza, int sg) {
	int koordX, koordY;
	int imageKop = 0;

	for (int i = 0; i < LAUKI_KOP; i++) {
		if (laukiak[i].pieza.mota != HUTS) {
			if (imageIdPieza[imageKop] > 0) irudiaKendu(imageIdPieza[imageKop]);
			switch (laukiak[i].pieza.mota) {
				case PEOI:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(PEOI_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(PEOI_BELTZ, sg);
					break;
				case ALFIL:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(ALFIL_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(ALFIL_BELTZ, sg);
					break;
				case ANDRE:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(ANDRE_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(ANDRE_BELTZ, sg);
					break;
				case ERREGE:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(ERREGE_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(ERREGE_BELTZ, sg);
						break;
				case ZALDUN:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(ZALDUN_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(ZALDUN_BELTZ, sg);
					break;
				case DORRE:
					if (laukiak[i].pieza.kolorea == ZURI) {
						imageIdPieza[imageKop] = irudiaKargatu(DORRE_ZURI, sg);
					}
					else imageIdPieza[imageKop] = irudiaKargatu(DORRE_BELTZ, sg);
					break;
			}
			koordX = LAUKI_X * zutabeaKalkulatu(i) + MARGEN_LUZERA;
			koordY = LAUKI_Y * ilaraKalkulatu(i) + MARGEN_LUZERA;
			irudiaMugitu(imageIdPieza[imageKop], koordX, koordY);
			imageKop++;
		}
	}
	pantailaGarbitu(sg);
	irudiakMarraztu(sg);
	pantailaBerriztu(sg);
}

void laukiakHasieratu(LAUKIA* laukiak) {
	//Laukiak "garbitu"
	for (int i = 0; i < LAUKI_KOP; i++) {
		laukiak[i].id = i;
		laukiak[i].pieza.mota = HUTS;
		laukiak[i].pieza.kolorea = HUTS;
		laukiak[i].pieza.mugimenduKop = 0;
	}
	//DORREAK
	for (int i = A1; i <= H1; i += H1) {
		laukiak[i].pieza.mota = DORRE;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i + 7].pieza.mota = DORRE;
		laukiak[i + 7].pieza.kolorea = BELTZ;
	}
	//ZALDUNAK
	for (int i = B1; i <= G1; i += G1 - B1) {
		laukiak[i].pieza.mota = ZALDUN;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i + 7].pieza.mota = ZALDUN;
		laukiak[i + 7].pieza.kolorea = BELTZ;
	}
	//ALFILAK
	for (int i = C1; i <= F1; i += F1 - C1) {
		laukiak[i].pieza.mota = ALFIL;
		laukiak[i].pieza.kolorea = ZURI;
		laukiak[i + 7].pieza.mota = ALFIL;
		laukiak[i + 7].pieza.kolorea = BELTZ;
	}
	//ANDREAK
	laukiak[D1].pieza.mota = ANDRE;
	laukiak[D1].pieza.kolorea = ZURI;
	laukiak[D8].pieza.mota = ANDRE;
	laukiak[D8].pieza.kolorea = BELTZ;
	//ERREGEA
	laukiak[E1].pieza.mota = ERREGE;
	laukiak[E1].pieza.kolorea = ZURI;
	laukiak[E8].pieza.mota = ERREGE;
	laukiak[E8].pieza.kolorea = BELTZ;
	//PEOIAK
	for (int i = A1; i < H8; i += 8) {
		laukiak[i + 1].pieza.mota = PEOI;
		laukiak[i + 1].pieza.kolorea = ZURI;
		laukiak[i + 6].pieza.mota = PEOI;
		laukiak[i + 6].pieza.kolorea = BELTZ;
	}
}

void mugituPieza(LAUKIA* laukiak, int org, int dest) {
	laukiak[dest].pieza.mugimenduKop = laukiak[org].pieza.mugimenduKop + 1;
	laukiak[dest].pieza.mota = laukiak[org].pieza.mota;
	laukiak[dest].pieza.kolorea = laukiak[org].pieza.kolorea;
	laukiak[org].pieza.mota = HUTS;
	laukiak[org].pieza.kolorea = HUTS;
	laukiak[org].pieza.mugimenduKop = HUTS;
}

int turnoIrudiaKargatu(int turnoa, int imageIdTurno, int sg) {
	irudiaKendu(imageIdTurno);

	if (turnoa == BELTZ) {
		imageIdTurno = irudiaKargatu(TURNOA_BELTZ, sg);
		irudiaMugitu(imageIdTurno, 50 + 3 * LAUKI_X, 0);
	}
	else if (turnoa == ZURI) {
		imageIdTurno = irudiaKargatu(TURNOA_ZURI, sg);
		irudiaMugitu(imageIdTurno, 50 + 3 * LAUKI_X, 0);
	}
	irudiakMarraztu(sg);

	return imageIdTurno;
}

EGOERA jokoa(EGOERA egoera) {
	LAUKIA laukiak[LAUKI_KOP];
	LAUKIA clickatua[2];
	EGOERA partidaMota = egoera;
	PUNTUAKETA puntu = { 0, 0 };
	int clickEzkerKop = 0;
	int turnoa = ZURI;
	int eragiketa;
	int ebentuJoko;

	int imageIdFondoa;
	int imageIdTurno;
	int imageIdPieza[32];

	if (sgHasieratu(JOKOA, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) == -1)
	{
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return 1;
	}
	
	tableroPosizioa = ESKUIN;
	//aukeratutakoFondoa comingSOON :)
	if (egoera == KARGATU) {
		egoera = partidaMota = partidaKargatu(laukiak, &puntu, &turnoa);
	}
	else {
		if (egoera == LUCKY_BLOCK) luckyBlock(laukiak);
		else laukiakHasieratu(laukiak);
	}
	imageIdFondoa = irudiaKargatu(CHESS_IMG, JOKOA);
	imageIdTurno = irudiaKargatu(TURNOA_ZURI, JOKOA);
	piezakKargatu(laukiak, imageIdPieza, JOKOA);
	imageIdTurno = turnoIrudiaKargatu(turnoa, imageIdTurno, JOKOA);

	irudiakMarraztu(JOKOA);
	puntuaketaPantailaratu(puntu, JOKOA);
	pantailaBerriztu(JOKOA);

	do {
		ebentuJoko = ebentuaJasoGertatuBada();
		if (partidaMota == INTERCAMBIO) {
			if (intercambio(laukiak) == 1) {
				piezakKargatu(laukiak, imageIdPieza, JOKOA);
			}
		}
		if (turnoa == BELTZ && (partidaMota == SIMETRIKO || partidaMota == IA)) {
			switch (partidaMota) {
				case SIMETRIKO:
					botSimetriko(clickatua, laukiak, &puntu.beltz);
					break;
				case IA:

					break;
			}
			piezakKargatu(laukiak, imageIdPieza, JOKOA);
			clickEzkerKop = 2;
		}
		else if (ebentuJoko == SAGU_BOTOIA_EZKERRA && clickEzkerKop < 2) {
			clickatua[clickEzkerKop] = clickatutakoLaukia(ebentuJoko, laukiak);
			//CLICK 1
			if (clickEzkerKop == 0 && clickatua[clickEzkerKop].pieza.mota > HUTS && clickatua[clickEzkerKop].pieza.kolorea == turnoa) {
				laukiClickatuaMarkatu(clickatua[clickEzkerKop]);
				clickEzkerKop++;
			}
			//CLICK 2
			else if (clickEzkerKop == 1 && clickatua[clickEzkerKop].pieza.kolorea != turnoa) {				laukiClickatuaMarkatu(clickatua[clickEzkerKop]);
				clickEzkerKop++;
				eragiketa = mugituEdoJanPieza(clickatua, laukiak, turnoa);

				if (eragiketa == EZINEZKOA || eragiketa == OZTOPOA) {
					laukiClickatuaDesmarkatu(clickatua[1]);
					popUpEzinezkoa();
					clickEzkerKop--;
				}
				else if (eragiketa == MUGITU || eragiketa == JAN || eragiketa == PROMOZIOA) {
					mugituPieza(laukiak, clickatua[0].id, clickatua[1].id);
					errepikapenaTmp(clickatua[0], clickatua[1].id);
					if (eragiketa == PROMOZIOA) {
						promozionatu(laukiak, clickatua, turnoa);
					}
					piezakKargatu(laukiak, imageIdPieza, JOKOA);
					if (eragiketa == JAN) {
						if (turnoa == BELTZ) puntu.beltz += puntuaketa(clickatua[1].pieza.mota);
						if (turnoa == ZURI) puntu.zuri += puntuaketa(clickatua[1].pieza.mota);
					}
					if (clickatua[1].pieza.mota == ERREGE) printf("\n\nMATEEE");
					else if (jakeAlDa(clickatua[1].id, laukiak, turnoa) == JAKE) printf("\nJAKE DA (coming soon)");
				}
			}
		}
		if (ebentuJoko == SAGU_BOTOIA_ESKUMA && clickEzkerKop > 0) {
			clickEzkerKop--;
			laukiClickatuaDesmarkatu(clickatua[clickEzkerKop]);
		}
		if (ebentuJoko == TECLA_p) {			
			egoera = menuPausa(partidaMota);
			if (egoera == GORDE) {
				partidaGorde(partidaMota, laukiak, puntu, turnoa);
				egoera = menuPausa(partidaMota);
			}
			//Literalmente, tenía que ponerlo en algún sitio para testear
			//Próximamente un botoncico para rotar el tableroooooo~
			errepikapenaTmpBiratu();
			imageIdFondoa = taulaBiratu(laukiak, imageIdFondoa, imageIdPieza, JOKOA);
			imageIdTurno = turnoIrudiaKargatu(turnoa, imageIdTurno, JOKOA);
			puntuaketaPantailaratu(puntu, JOKOA);
			pantailaBerriztu(JOKOA);
		}
		if (clickEzkerKop == 2) {
			clickEzkerKop = 0;
			turnoa *= -1;
			imageIdTurno = turnoIrudiaKargatu(turnoa, imageIdTurno, JOKOA);
			puntuaketaPantailaratu(puntu, JOKOA);
			pantailaBerriztu(JOKOA);
		}
	} while (egoera == JOKOA || egoera == SIMETRIKO || egoera == INTERCAMBIO || egoera == IA || egoera == LUCKY_BLOCK);

	irudiaKendu(imageIdFondoa);
	irudiaKendu(imageIdTurno);
	for (int i = 0; i < 32; i++) irudiaKendu(imageIdPieza[i]);
	pantailaGarbitu(JOKOA);
	pantailaBerriztu(JOKOA);
	remove("partidak//errepikapena.tmp");
	sgItxi(JOKOA);

	return egoera;
}