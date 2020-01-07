#ifndef KALKULOAK_H
#define KALKULOAK_H

#include "jokoa.h"

void resetClickatua(LAUKIA* clickatua);
int clickatutakoIlara(float yKoord);
int clickatutakoZutabea(float xKoord);
LAUKIA clickatutakoLaukia(int ebentu, LAUKIA laukiak[]);
int ilaraKalkulatu(int id);
int zutabeaKalkulatu(int id);
int posizioaTaulan(LAUKIA* clickatua);
LAUKIA erregeaBilatu(LAUKIA* laukiak, int turnoa);
int jakeAlDa(int id, LAUKIA* laukiak, int turnoa);
int puntuaketa(MOTA clickatuMota);
int mugituEdoJanPieza(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int taulaBiratu(LAUKIA* laukiak, int id, int* imageIdPieza, int sg);

#endif