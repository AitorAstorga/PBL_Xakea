#include "graphics.h"
#include "imagen.h"
#include "ebentoak.h"
#include <stdio.h>
#include "ourTypes.h"
#include "jokoa.h"
#include "menu.h"

/*
MENU -> (BERRIA / KARGATU / ERREPIKAPENAK) [MUSIKA / SOINUA]
	BERRIA -> (1 VS 1 / PVE)
		PVE -> (SIMETRIKO / INTERCAMBIO / IA / LUCKY_BLOCK)
	KARGATU -> (PARTIDA 1 / PARTIDA 2 / PARTIDA 3) {Rename option for slots xD}
	ERREPIKAPENAK -> (PARTIDA 1 / PARTIDA 2 / PARTIDA 3)

*/

int main() {
  int jarraitu = 0;
  EGOERA egoera;

  egoera = menu();
  sgItxi(MENU);

  if (egoera == JOKOA) {
	  if (sgHasieratu(JOKOA, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN) == -1)
	  {
		  fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		  return 1;
	  }
	  do
	  {
		  jokoa();
	  } while (jarraitu);
	  sgItxi(JOKOA);
  }
  return 0;
}
