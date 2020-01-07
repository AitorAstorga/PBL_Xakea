#ifndef PIEZAMUGIMENDUAK_H
#define PIEZAMUGIMENDUAK_H

#include "jokoa.h"

int promozioaPosible(LAUKIA* clickatua, int turnoa);
void promozionatu(LAUKIA *laukiak, LAUKIA* clickatua, int turnoa);

int mugimenduPeoi(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int mugimenduDorre(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int mugimenduZaldun(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int mugimenduAlfil(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int mugimenduAndre(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);
int mugimenduErrege(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa);

#endif