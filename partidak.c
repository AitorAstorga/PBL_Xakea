#include <stdio.h>
#include "jokoa.h"
#include "ebentoak.h"
#include "text.h"
#include "imagen.h"
#include "irudiakEtaSoinuak.h"
#include <string.h>
#include "graphics.h"
#include "kalkuloak.h"
#include "partidak.h"

FILE *kargaFitx;

void errepikapenaGorde(char *partidaIzena) {
	FILE *errepikapena, *tmp;
	char str[128];
	char errepikapenaIzena[128];
	fopen_s(&tmp, "partidak//errepikapena.tmp", "r");
	if (tmp != NULL) {
		partidaIzena[strlen(partidaIzena) - 4] = '\0';
		sprintf_s(errepikapenaIzena, 128, "%s.errepikapena", partidaIzena);

		fopen_s(&errepikapena, errepikapenaIzena, "w");
		if (errepikapena != 0) {
			while (fgets(str, 128, tmp) != NULL) {//dammit
				fprintf(errepikapena, "%s", str);
			}
			fclose(errepikapena);
			fclose(tmp);
		}
	}
	else printf("Ez da partida honen errepikapena gordeko.\n");
}

void textuaJaso(char *textua, int x, int y, int sg) {
	int ebentuGorde;
	int letraKop = 0;
	do {
		ebentuGorde = ebentuaJasoGertatuBada();
		if (letraKop == 16) {
			//letraKopMaximoa popUp
		}
		else if (ebentuGorde >= 32 && ebentuGorde <= 126) {
			textua[letraKop] = ebentuGorde;
			letraKop++;
			textua[letraKop] = '\0';
			pantailaGarbitu(sg);
			irudiakMarraztu(sg);
			textuaIdatzi(x, y, textua, sg);
			pantailaBerriztu(sg);
		}
		else if (ebentuGorde == 8) {//EL 8 ES LA TECLA BACKSPACE(BORRAR)
			if (letraKop > 0) {
				letraKop--;
				textua[letraKop] = '\0';
				pantailaGarbitu(sg);
				irudiakMarraztu(sg);
				if (letraKop > 1) textuaIdatzi(x, y, textua, sg);
				pantailaBerriztu(sg);
			}
		}
	} while (ebentuGorde != SAGU_BOTOIA_EZKERRA || letraKop < 1);
	textua[letraKop] = '\0';
}

void partidaGorde(EGOERA partidaMota, LAUKIA *laukiak, PUNTUAKETA puntu, int turnoa) {
	FILE *partida, *partidaErregistroa;
	char partidaArtxiboa[128];
	char partidaIzena[123];
	int letraKop = 0;

	int imageIdIdatzi;

	imageIdIdatzi = irudiaKargatu(GORDE_IZENA, JOKOA);
	irudiaMugitu(imageIdIdatzi, 170, 140);
	irudiakMarraztu(JOKOA);
	pantailaBerriztu(JOKOA);

	textuaGaitu(30);
	textuaJaso(partidaIzena, 190, 160, JOKOA);
	sprintf_s(partidaArtxiboa, 128, "partidak//%s.txt", partidaIzena);
	fopen_s(&partida, partidaArtxiboa, "w");

	if (partida != NULL) {
		fprintf(partida, "PARTIDA_IZENA: %s\n\n", partidaIzena);
		fprintf(partida, "PARTIDA_MOTA: %i\n\n", partidaMota);
		fprintf(partida, "tableroPosizioa: %i\n\n", tableroPosizioa);
		fprintf(partida, "zuriPuntuaketa: %i\n", puntu.zuri);
		fprintf(partida, "beltzPuntuaketa: %i\n\n", puntu.beltz);
		fprintf(partida, "turnoa: %i\n", turnoa);
		for (int i = 0; i < LAUKI_KOP; i++) {
			fprintf(partida, "\n[id: %i / mota: %i / kolorea: %i / mugimenduKop: %i]",
				laukiak[i].id, laukiak[i].pieza.mota,
				laukiak[i].pieza.kolorea,
				laukiak[i].pieza.mugimenduKop);
		}
		fclose(partida);
	}

	fopen_s(&partidaErregistroa, "partidak//partidaErregistroa.txt", "a");
	if (partidaErregistroa != NULL) {
		fprintf(partidaErregistroa, "%s\n", partidaIzena);
		fclose(partidaErregistroa);
	}
	//errepikapenaren... izena.errepikapena.txt would work?
	irudiaKendu(imageIdIdatzi);
	errepikapenaGorde(partidaArtxiboa);
}

int partidakAurkitu(FILE *partidaErregistroa, char partidaIzenak[][128], char *fitxIzena, int *imageIdPartida, int sg) {
	EGOERA egoera;
	LAUKIA laukia[LAUKI_KOP];
	PUNTUAKETA puntu;
	int turno;
	int partidaKop = 0;
	char aux[128];
	
	textuaGaitu(16);
	if (partidaErregistroa == NULL) {
		perror("Ezin da partidaErregistroa.txt ireki");
		//ez daude partidarik gorde
	}
	else {
		do {
			fgets(partidaIzenak[partidaKop], sizeof(*partidaIzenak), partidaErregistroa);
			if (feof(partidaErregistroa)) {
				break;
			}
			imageIdPartida[partidaKop] = irudiaKargatu(KARGATU_PARTIDA_IRUDIA, sg);
			irudiaMugitu(imageIdPartida[partidaKop], 71, 21 + (96 * partidaKop));
			partidaKop++;
		} while (partidaKop < 5);
		irudiakMarraztu(sg);

		for (int i = 0; i < partidaKop; i++) {
			partidaIzenak[i][strlen(partidaIzenak[i]) - 1] = '\0';
			sprintf_s(fitxIzena, 128, "partidak//%s.txt", partidaIzenak[i]);
			fopen_s(&kargaFitx, fitxIzena, "r");
			if (kargaFitx != NULL) {
				egoera = partidaKargatu(laukia, &puntu, &turno);
				fclose(kargaFitx);
			}
			textuaIdatzi(100, 38 + (96 * i), partidaIzenak[i], sg);
			sprintf_s(aux, 128, "Zuri / Beltz: %i - %i", puntu.zuri, puntu.beltz);
			textuaIdatzi(250, 38 + (96 * i), aux, sg);
			if (turno == ZURI) {
				textuaIdatzi(440, 38 + (96 * i), "turnoa: ZURI", sg);
			}
			else if (turno == BELTZ) {
				textuaIdatzi(440, 38 + (96 * i), "turnoa: BELTZ", sg);
			}
		}
		printf("\nPartidaKop: %i", partidaKop);
		fclose(kargaFitx);
		kargaFitx = NULL;
		for (int i = 0; i < partidaKop; i++) irudiaKendu(imageIdPartida[i]);
		pantailaBerriztu(sg);
	}
	return partidaKop;
}

char *partidaAukeratu(int sg) {
	EGOERA egoera = -1;
	POSIZIOA pos;
	FILE *partidaErregistroa;
	char partidaIzenak[5][128];
	char *partidaAukeratua = NULL;
	char fitxIzena[128];
	int ebentuKargatu = 0;
	int partidaKop = 0;
	int imageIdPartida[5];
	int imageIdFondoa;

	imageIdFondoa = irudiaKargatu(KARGATU_IRUDIA, sg);
	irudiakMarraztu(sg);
	pantailaBerriztu(sg);

	fopen_s(&partidaErregistroa, "partidak//partidaErregistroa.txt", "r");
	partidaKop = partidakAurkitu(partidaErregistroa, partidaIzenak, fitxIzena, imageIdPartida, sg);
	egoera = -1;
	do {
		ebentuKargatu = ebentuaJasoGertatuBada();
		pos = saguarenPosizioa();
		if (ebentuKargatu == TECLA_ESCAPE) egoera = MENU;
		else if (ebentuKargatu == SAGU_BOTOIA_EZKERRA) {
			if (pos.y > 20 && pos.y < 76 && partidaKop >= 1) {
				partidaAukeratua = partidaIzenak[0];
				egoera = KARGATU;
			}
			else if (pos.y > 116 && pos.y < 173 && partidaKop >= 2) {
				partidaAukeratua = partidaIzenak[1];
				egoera = KARGATU;
			}
			else if (pos.y > 212 && pos.y < 269 && partidaKop >= 3) {
				partidaAukeratua = partidaIzenak[2];
				egoera = KARGATU;
			}
			else if (pos.y > 308 && pos.y < 364 && partidaKop >= 4) {
				partidaAukeratua = partidaIzenak[3];
				egoera = KARGATU;
			}
			else if (pos.y > 404 && pos.y < 461 && partidaKop >= 5) {
				partidaAukeratua = partidaIzenak[4];
				egoera = KARGATU;
			}
		}
	} while (ebentuKargatu != TECLA_ESCAPE && egoera == -1);

	if (egoera == KARGATU) {
		sprintf_s(fitxIzena, 128, "partidak//%s.txt", partidaAukeratua);
		fopen_s(&kargaFitx, fitxIzena, "r");
	}
	if (partidaErregistroa != NULL) fclose(partidaErregistroa);
	irudiaKendu(imageIdFondoa);
	if (egoera == KARGATU) return partidaAukeratua;
	else return "\0";
}

EGOERA partidaKargatu(LAUKIA *laukiak, PUNTUAKETA *puntu, int *turnoa) {
	int partidaMota;
	int ignoraErrorPlz = 0;//ahora que hdp, ya no me pondras nervioso
	ignoraErrorPlz = fscanf_s(kargaFitx, "PARTIDA_IZENA: %*s\n\nPARTIDA_MOTA: %i[^\n]", &partidaMota);
	ignoraErrorPlz = fscanf_s(kargaFitx, "\ntableroPosizioa: %i[^\n]", &tableroPosizioa);
	ignoraErrorPlz = fscanf_s(kargaFitx, "\nzuriPuntuaketa: %i[^\n]", &puntu->zuri);
	ignoraErrorPlz = fscanf_s(kargaFitx, "\nbeltzPuntuaketa: %i[^\n]", &puntu->beltz);
	ignoraErrorPlz = fscanf_s(kargaFitx, "\nturnoa: %i[^\n]", turnoa);
	for (int i = 0; i < LAUKI_KOP; i++) {
		ignoraErrorPlz = fscanf_s(kargaFitx, "\n[id: %i / mota: %i / kolorea: %i / mugimenduKop: %i][^\n]", &laukiak[i].id, &laukiak[i].pieza.mota, &laukiak[i].pieza.kolorea, &laukiak[i].pieza.mugimenduKop);
	}
	fclose(kargaFitx);
	return partidaMota;
}

void errepikapenaTmp(LAUKIA laukia, int lauki2) {
	FILE *tmp;
	fopen_s(&tmp, "partidak//errepikapena.tmp", "a");
	if (tmp != NULL) {
		fprintf(tmp, "[%i -> %i]\n", laukia.id, lauki2);
		fclose(tmp);
	}
}

void errepikapenaTmpBiratu() {
	FILE *tmp;
	fopen_s(&tmp, "partidak//errepikapena.tmp", "a");
	if (tmp != NULL) {
		fprintf(tmp, "biratuDa\n");
		fclose(tmp);
	}
}

void errepikapenaPantailaratu() {
	char partidaAukeratua[128];

	strcpy_s(partidaAukeratua, 128, partidaAukeratu(ERREPIKAPENAK));
	if (strcmp(partidaAukeratua, "\0") != 0) {
		FILE* errepikapena;
		LAUKIA laukiak[LAUKI_KOP];
		LAUKIA clickatua[2] = { -1, {-1, 0, 0} };
		PUNTUAKETA puntu = { 0, 0 };
		int turnoa = ZURI;
		int eragiketa;
		int errepikapenEbentua;
		char fitxIzena[128];

		int imageIdFondoa;
		int imageIdTurno;
		int imageIdPieza[32];
		char str[128];

		laukiakHasieratu(laukiak);
		imageIdFondoa = irudiaKargatu(CHESS_IMG, ERREPIKAPENAK);
		imageIdTurno = irudiaKargatu(TURNOA_ZURI, ERREPIKAPENAK);
		piezakKargatu(laukiak, imageIdPieza, ERREPIKAPENAK);
		imageIdTurno = turnoIrudiaKargatu(turnoa, imageIdTurno, ERREPIKAPENAK);

		irudiakMarraztu(ERREPIKAPENAK);
		puntuaketaPantailaratu(puntu, ERREPIKAPENAK);
		pantailaBerriztu(ERREPIKAPENAK);
		sprintf_s(fitxIzena, 128, "partidak//%s.errepikapena", partidaAukeratua);
		fopen_s(&errepikapena, fitxIzena, "r");
		if (errepikapena != NULL) {
			while (fgets(str, 128, errepikapena) != NULL) {
				do {
					errepikapenEbentua = ebentuaJasoGertatuBada();
				} while (errepikapenEbentua != TECLA_RETURN);
				if (strcmp(str, "biratuDa") == 1) {
					imageIdFondoa = taulaBiratu(laukiak, imageIdFondoa, imageIdPieza, ERREPIKAPENAK);
					imageIdTurno = turnoIrudiaKargatu(turnoa, imageIdTurno, ERREPIKAPENAK);
					puntuaketaPantailaratu(puntu, ERREPIKAPENAK);
					pantailaBerriztu(ERREPIKAPENAK);
				}
				else {
					sscanf_s(str, "[%i -> %i]", &(int*)clickatua[0].id, &(int*)clickatua[1].id);
					eragiketa = mugituEdoJanPieza(clickatua, laukiak, turnoa);
					mugituPieza(laukiak, clickatua[0].id, clickatua[1].id);
					piezakKargatu(laukiak, imageIdPieza, ERREPIKAPENAK);
					if (eragiketa == JAN) {
						if (turnoa == BELTZ) puntu.beltz += puntuaketa(clickatua[1].pieza.mota);
						if (turnoa == ZURI) puntu.zuri += puntuaketa(clickatua[1].pieza.mota);
					}
					puntuaketaPantailaratu(puntu, ERREPIKAPENAK);
					pantailaBerriztu(ERREPIKAPENAK);
				}
			}
		}
	}
}