#include <stdio.h>
#include "SDL_video.h"
#include "irudiakEtaSoinuak.h"
#include "graphics.h"
#include "imagen.h"
#include "ebentoak.h"
#include "OurTypes.h"

EGOERA menu() {
	EGOERA aukera = -1;
	int imageIdFondoa;
	int ebentuMenu = 0;

	if (sgHasieratu(MENU, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1)
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		return 1;
	}
	
	imageIdFondoa = irudiaKargatu(MENU_FONDO, MENU);
	irudiaMugitu(imageIdFondoa, 0, 0);
	irudiakMarraztu(MENU);
	pantailaBerriztu(MENU);

	/*
	Dimensiones de los botones: (x0, y0), (x1, y1)

		Partida berria: (160, 80), (480, 140)
		Kargatu: (160, 160), (480, 220)
		Errepikapenak: (160, 240), (480, 300)
		Itxi: (160, 320), (480, 380)
		Musika: (520, 420), (560, 460)
		Soinua: (580, 420), (620, 460)
	*/
	
	do {
		ebentuMenu = ebentuaJasoGertatuBada();
		switch (ebentuMenu) {
			case 'e':
				aukera = BERRIA;
				aukera = berria();
				printf("berria");
				break;
			case 'r':
				aukera = KARGATU;
				printf("kargatu");
				break;
			case 't':
				aukera = ERREPIKAPENAK;
				printf("errepikapenak");
				break;
			case 'y':
				aukera = ITXI;
				printf("itxi");
				break;
		}
	} while (aukera == -1);
	
	return aukera;
}

EGOERA berria() {
	EGOERA aukera = -1;
	int imageIdFondoa;
	int ebentuMenu = 0;

	if (sgHasieratu(BERRIA, 300, 200, SDL_WINDOW_SHOWN) == -1)
	{
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		return 1;
	}
	
	imageIdFondoa = irudiaKargatu(MENU_JOKATU, BERRIA);
	irudiaMugitu(imageIdFondoa, 0, 0);
	irudiakMarraztu(BERRIA);
	pantailaBerriztu(BERRIA);

	do {
		ebentuMenu = ebentuaJasoGertatuBada();
		if (ebentuMenu == 'a') aukera = JOKOA;
	} while (aukera == -1);

	return aukera;
}
