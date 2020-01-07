#include <stdio.h>
#include "SDL_video.h"
#include "irudiakEtaSoinuak.h"
#include "graphics.h"
#include "imagen.h"
#include "ebentoak.h"
#include "OurTypes.h"

#include "text.h"
#include <Windows.h>

#include "partidak.h"
#include "menu.h"

int musika;
int soinua;

EGOERA menu() {
	EGOERA aukera = MENU;
	POSIZIOA pos;
	int imageIdMenu;
	int ebentuMenu = 0;

	if (sgHasieratu(MENU, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1)
	{
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return ERROREA;
	}

	imageIdMenu = irudiaKargatu(MENU_FONDO, MENU);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	do {
		ebentuMenu = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuMenu == SAGU_BOTOIA_EZKERRA) {
			if (pos.x > 160 && pos.x < 480) {
				if (pos.y > 80 && pos.y < 140) {
					aukera = BERRIA;
					aukera = berria();
				}
				else if (pos.y > 160 && pos.y < 220) {
					aukera = KARGATU;
					aukera = kargatu();
				}
				else if (pos.y > 240 && pos.y < 300) {
					aukera = ERREPIKAPENAK;
					aukera = errepikapenak();
				}
				else if (pos.y > 320 && pos.y < 380) {
					aukera = ITXI;
					aukera = itxi();
				}
			}
		}
		else if (pos.y > 420 && pos.y < 460) {
			if (pos.x > 580 && pos.x < 560) {
				musika *= -1;
			}
			else if (pos.x > 580 && pos.x < 620) {
				soinua *= -1;
			}
		}
	} while (aukera == MENU);
	irudiaKendu(imageIdMenu);
	sgItxi(MENU);
	return aukera;
}

EGOERA berria() {
	EGOERA aukera = -1;
	POSIZIOA pos;
	int imageIdBerria;
	int ebentuBerria = 0;
	
	imageIdBerria = irudiaKargatu(MENU_JOKATU, MENU);
	irudiaMugitu(imageIdBerria, 170, 140);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	do {
		ebentuBerria = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuBerria == SAGU_BOTOIA_EZKERRA) {
			if (pos.x > 170 && pos.x < 470) {
				if (pos.y > 140 && pos.y < 240) aukera = JOKOA;
				else if (pos.y > 240 && pos.y < 340) aukera = bots();//COMING SOON, (bots)
				else aukera = MENU;
			}
			else aukera = MENU;
		}
	} while (aukera == -1);
	irudiaKendu(imageIdBerria);
	pantailaGarbitu(MENU);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	return aukera;
}

EGOERA kargatu() {
	EGOERA aukera;
	int partida = -1;

	if (sgHasieratu(KARGATU, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1)
	{
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return ERROREA;
	}

	if (partidaAukeratu(KARGATU) != "\0") aukera = KARGATU;
	else aukera = MENU;

	sgItxi(KARGATU);
	return aukera;
}

EGOERA errepikapenak() {
	int ebentuErrepikapenak = 0;

	if (sgHasieratu(ERREPIKAPENAK, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1)
	{
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return ERROREA;
	}
	
	errepikapenaPantailaratu();

	sgItxi(ERREPIKAPENAK);
	return MENU;
}

EGOERA itxi() {
	POSIZIOA pos;
	int imageIdFondoa;
	int ebentuItxi = 0;

	if (sgHasieratu(ITXI, 300, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1)
	{
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", 300, 200, SDL_GetError());
		return ERROREA;
	}

	imageIdFondoa = irudiaKargatu(MENU_ITXI, ITXI);
	irudiaMugitu(imageIdFondoa, 0, 0);
	irudiakMarraztu(ITXI);
	pantailaBerriztu(ITXI);

	do {
		ebentuItxi = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuItxi == SAGU_BOTOIA_EZKERRA) {
			if (pos.x < 170 || pos.x > 470 || pos.y < 140 || pos.y > 240) return MENU;
		}
	} while (ebentuItxi != TECLA_RETURN);

	return ITXI;
}

EGOERA bots() {
	EGOERA aukera = -1;
	POSIZIOA pos;
	int imageIdBots;
	int ebentuBots = 0;

	imageIdBots = irudiaKargatu(MENU_BOTS, MENU);
	irudiaMugitu(imageIdBots, 0, 0);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	do {
		ebentuBots = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuBots == SAGU_BOTOIA_EZKERRA) {
			if (pos.x > 0 && pos.x < 320) {
				if (pos.y > 0 && pos.y < 240) aukera = IA;
				else if (pos.y > 240 && pos.y < 480) aukera = INTERCAMBIO;
			}
			else if (pos.x > 320 && pos.x < 640) {
				if (pos.y > 0 && pos.y < 240) aukera = SIMETRIKO;
				else if (pos.y > 240 && pos.y < 480) aukera = LUCKY_BLOCK;
			}
		}
		else if (ebentuBots == TECLA_ESCAPE) aukera = MENU;
	} while (aukera == -1);
	irudiaKendu(imageIdBots);
	pantailaGarbitu(MENU);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	return aukera;
}

EGOERA menuPausa(EGOERA partidaMota) {
	EGOERA aukera = PAUSA;
	POSIZIOA pos;
	int ebentuPausa = 0;
	int imageIdPausa;

	imageIdPausa = irudiaKargatu(MENU_PAUSA, JOKOA);
	irudiaMugitu(imageIdPausa, 170, 140);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);

	do {
		ebentuPausa = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuPausa == SAGU_BOTOIA_EZKERRA) {
			if (pos.y > 140 && pos.y < 340 && pos.x > 170 && pos.x < 470) {
				if (pos.y > 149 && pos.y < 182) {
					if (pos.x > 358 && pos.x < 391) {
						aukera = MUSIKA;
						musika *= -1;
					}
					else if (pos.x > 418 && pos.x < 451) {
						aukera = SOINUA;
						soinua *= -1;
					}
				}
				else if (pos.y > 224 && pos.y < 251 && pos.x > 195 && pos.x < 446) {
					aukera = GORDE;
					//partidaGorde();
				}
				else if (pos.y > 274 && pos.y < 301 && pos.x > 275 && pos.x < 362) {
					aukera = MENU;
				}
			}
			else aukera = partidaMota;
		}
		else if (ebentuPausa == TECLA_p) aukera = partidaMota;
		//if (aukera == 'f') imageIdFondoa = taulaBiratu(laukiak, imageIdFondoa);
	} while (aukera == PAUSA && ebentuPausa != TECLA_p);

	irudiaKendu(imageIdPausa);
	pantailaGarbitu(JOKOA);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);

	return aukera;
}

void popUpEzinezkoa() {
	int imageIdEzinezkoa = irudiaKargatu(COMING_SOON, JOKOA);
	irudiaMugitu(imageIdEzinezkoa, 170, 140);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);
	Sleep(1000);
	irudiaKendu(imageIdEzinezkoa);
	pantailaGarbitu(JOKOA);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);
}