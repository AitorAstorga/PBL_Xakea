#include "graphics.h"
#include "imagen.h"
#include "ebentoak.h"
#include <stdio.h>
#include "ourTypes.h"
#include "jokoa.h"
#include "menu.h"
#include "SDL.h"

/*
MENU -> (BERRIA / KARGATU / ERREPIKAPENAK) [MUSIKA / SOINUA]
	BERRIA -> (1 VS 1 / PVE)
		PVE -> (SIMETRIKO / INTERCAMBIO / IA / LUCKY_BLOCK)
	KARGATU -> (PARTIDA 1 / PARTIDA 2 / PARTIDA 3) {Rename option for slots xD}
	ERREPIKAPENAK -> (PARTIDA 1 / PARTIDA 2 / PARTIDA 3)

*/

int main(int argc, char* argv[]) {
  int jarraitu = 0;
  EGOERA egoera = MENU;

  musika = 1;
  soinua = 1;
  
  do {
	  if (egoera == MENU) {
		  egoera = menu();
	  }
	  if (egoera == KARGATU || egoera == JOKOA || egoera == SIMETRIKO || egoera == INTERCAMBIO || egoera == IA || egoera == LUCKY_BLOCK) {
		  egoera = jokoa(egoera);
	  }
  } while (egoera != ITXI);

  SDL_Quit();
  
  return 0;
}