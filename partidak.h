#ifndef PARTIDAK_H
#define PARTIDAK_H

#include "jokoa.h"

FILE *kargaFitx;

void partidaGorde(EGOERA partidaMota, LAUKIA *laukiak, PUNTUAKETA puntu, int turnoa);
void textuaJaso(char *partidaIzena, int x, int y, int sg);
int partidakAurkitu(FILE *partidaErregistroa, char partidaIzenak[][128], char *fitxIzena, int* imageIdPartida, int sg);
char *partidaAukeratu(int sg);
EGOERA partidaKargatu(LAUKIA *laukiak, PUNTUAKETA *puntu, int *turnoa);
void errepikapenaTmp(LAUKIA laukia, int lauki2);
void errepikapenaTmpBiratu();
void errepikapenaGorde(char *partidaIzena);
void errepikapenaPantailaratu();

#endif