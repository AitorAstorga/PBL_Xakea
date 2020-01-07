#include "jokoa.h"
#include "irudiakEtaSoinuak.h"
#include "ebentoak.h"
#include "imagen.h"
#include "kalkuloak.h"
#include "graphics.h"

int promozioaPosible(LAUKIA* clickatua, int turnoa) {
	int posible = 0;
	if (turnoa == ZURI) {
		for (int i = A8; i < H8; i += 8) {
			if (clickatua[1].id == i) posible = 1;
		}
	}
	else if (turnoa == BELTZ) {
		for (int i = A1; i < H1; i += 8) {
			if (clickatua[1].id == i) posible = 1;
		}
	}
	return posible;
}

void promozionatu(LAUKIA *laukiak, LAUKIA *clickatua, int turnoa) {
	int ebentua = 0;
	int aukera = HUTS;
	int imageIdAldatu;
	sgHasieratu(ALDATU, 505, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	imageIdAldatu = irudiaKargatu(ALDATU_TXURI, ALDATU);
	irudiakMarraztu(ALDATU);
	pantailaBerriztu(ALDATU);
	do {
		ebentua = ebentuaJasoGertatuBada();
		POSIZIOA posizioa = saguarenPosizioa();
		if (ebentua == SAGU_BOTOIA_EZKERRA) {
			if ((posizioa.x >= 42 && posizioa.x < 113) && (posizioa.y <= 143 && posizioa.y >= 64)) {
				aukera = ALFIL;
			}
			else if ((posizioa.x >= 150 && posizioa.x < 221) && (posizioa.y <= 143 && posizioa.y >= 64)) {
				aukera = ANDRE;
			}
			else if ((posizioa.x >= 258 && posizioa.x < 329) && (posizioa.y <= 143 && posizioa.y >= 60)) {
				aukera = ZALDUN;
			}
			else if ((posizioa.x >= 368 && posizioa.x < 439) && (posizioa.y <= 143 && posizioa.y >= 62)) {
				aukera = DORRE;
			}
		}
	} while (aukera == HUTS);
	laukiak[clickatua[1].id].pieza.mota = aukera;
	
	irudiaKendu(imageIdAldatu);
	sgItxi(ALDATU);
}

int mugimenduPeoi(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int emaitza = -1;
	if (tableroPosizioa == ESKUIN) {
		if ((clickatua[0].id + turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS) {
			emaitza = MUGITU;
		}
		else if ((clickatua[0].id + 2 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS && laukiak[clickatua[0].id + turnoa].pieza.mota == HUTS && clickatua[0].pieza.mugimenduKop == 0) {
			emaitza = MUGITU;
		}
		else if (((clickatua[0].id + ZUTABE_KOP + turnoa == clickatua[1].id) ||
			(clickatua[0].id - ZUTABE_KOP + turnoa == clickatua[1].id)) && clickatua[1].pieza.mota > HUTS && clickatua[1].pieza.kolorea != turnoa) {
			emaitza = JAN;
		}
		else emaitza = EZINEZKOA;
	}
	else if (tableroPosizioa == EZKER) {
		if ((clickatua[0].id - turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS) {
			emaitza = MUGITU;
		}
		else if ((clickatua[0].id - 2 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS && laukiak[clickatua[0].id - turnoa].pieza.mota == HUTS && clickatua[0].pieza.mugimenduKop == 0) {
			emaitza = MUGITU;
		}
		else if (((clickatua[0].id + ZUTABE_KOP - turnoa == clickatua[1].id) ||
			(clickatua[0].id - ZUTABE_KOP - turnoa == clickatua[1].id)) && clickatua[1].pieza.mota > HUTS && clickatua[1].pieza.kolorea != turnoa) {
			emaitza = JAN;
		}
		else emaitza = EZINEZKOA;
	}
	else if (tableroPosizioa == GORA) {
		if ((clickatua[0].id - 8 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS) {
			emaitza = MUGITU;
		}
		else if ((clickatua[0].id - 16 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS && laukiak[clickatua[0].id - 8 * turnoa].pieza.mota == HUTS && clickatua[0].pieza.mugimenduKop == 0) {
			emaitza = MUGITU;
		}
		else if (((clickatua[0].id - ZUTABE_KOP * turnoa + turnoa == clickatua[1].id) ||
			(clickatua[0].id - ZUTABE_KOP * turnoa - turnoa == clickatua[1].id)) && clickatua[1].pieza.mota > HUTS && clickatua[1].pieza.kolorea != turnoa) {
			emaitza = JAN;
		}
		else emaitza = EZINEZKOA;
	}
	else if (tableroPosizioa == BEHE) {
		if ((clickatua[0].id + 8 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS) {
			emaitza = MUGITU;
		}
		else if ((clickatua[0].id + 16 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS && laukiak[clickatua[0].id + 8 * turnoa].pieza.mota == HUTS && clickatua[0].pieza.mugimenduKop == 0) {
			emaitza = MUGITU;
		}
		else if (((clickatua[0].id + ZUTABE_KOP * turnoa + turnoa == clickatua[1].id) ||
			(clickatua[0].id + ZUTABE_KOP * turnoa - turnoa == clickatua[1].id)) && clickatua[1].pieza.mota > HUTS&& clickatua[1].pieza.kolorea != turnoa) {
			emaitza = JAN;
		}
		else emaitza = EZINEZKOA;
	}

	if (emaitza != EZINEZKOA && promozioaPosible(clickatua, turnoa) == 1) {
		emaitza = PROMOZIOA;
	}
	
	return emaitza;
}

int mugimenduDorre(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);
	int posizioa = posizioaTaulan(clickatua);

	int zerbaitErdian = 0;
	//DORRE
	if (posizioa == ZUTABE_BERDIN || posizioa == ILARA_BERDIN) {
		//Mugimendu horizontala
		if (posizioa == ILARA_BERDIN) {
			//Eskuinerantz
			if (zutabe0 < zutabe1) {
				for (int i = clickatua[0].id + 1; i <= clickatua[1].id; i++) {
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
			//Ezkerrerantz
			if (zutabe0 > zutabe1) {
				for (int i = clickatua[0].id - 1; i >= clickatua[1].id; i--) {
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
		}
		//mugimendu bertikala
		else if (posizioa == ZUTABE_BERDIN) {
			//Beherantz
			if (ilara0 < ilara1) {
				for (int i = clickatua[0].id + ZUTABE_KOP; i <= clickatua[1].id; i += ZUTABE_KOP) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
			//Gorantz
			if (ilara0 > ilara1) {
				for (int i = clickatua[0].id - ZUTABE_KOP; i >= clickatua[1].id; i -= ZUTABE_KOP) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
		}
		//Kasu honetan "erdian" dagoena aukeratutako pieza bada
		if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;

		if (zerbaitErdian == MUGITU) {
			return MUGITU;
		}
		else if (zerbaitErdian == JAN) {
			//Pieza aurkaria bada
			if (clickatua[1].pieza.kolorea != turnoa) {
				return JAN;
			}
			else return OZTOPOA;
		}
		else return OZTOPOA;
	}
	else return EZINEZKOA;
}

int mugimenduZaldun(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int posizioa = posizioaTaulan(clickatua);
	int zerbaitErdian = -1;

	//Eskuinean, behean
	if (posizioa == BEHE_ESKUIN) {
		if ((clickatua[0].id + 17 == clickatua[1].id) || (clickatua[0].id + 10 == clickatua[1].id)) {
			if (clickatua[1].pieza.mota > HUTS) zerbaitErdian = JAN;
			else zerbaitErdian = MUGITU;
		}
	}
	//Eskuinean, gainean
	if (posizioa == GOI_ESKUIN) {
		if ((clickatua[0].id - 15 == clickatua[1].id) || (clickatua[0].id - 6 == clickatua[1].id)) {
			if (clickatua[1].pieza.mota > HUTS) zerbaitErdian = JAN;
			else zerbaitErdian = MUGITU;
		}
	}
	//Ezkerrean, behean
	if (posizioa == BEHE_EZKER) {
		if ((clickatua[0].id + 15 == clickatua[1].id) || (clickatua[0].id + 6 == clickatua[1].id)) {
			if (clickatua[1].pieza.mota > HUTS) zerbaitErdian = JAN;
			else zerbaitErdian = MUGITU;
		}
	}
	//Ezkerrean, gainean
	if (posizioa == GOI_EZKER) {
		if ((clickatua[0].id - 17 == clickatua[1].id) || (clickatua[0].id - 10 == clickatua[1].id)) {
			if (clickatua[1].pieza.mota > HUTS) zerbaitErdian = JAN;
			else zerbaitErdian = MUGITU;
		}
	}

	if (zerbaitErdian == MUGITU) {
		return MUGITU;
	}
	else if (zerbaitErdian == JAN) {
		if (clickatua[1].pieza.kolorea != turnoa) {
			return JAN;
		}
		else return OZTOPOA;
	}
	else return EZINEZKOA;
}

int mugimenduAlfil(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);
	int posizioa = posizioaTaulan(clickatua);

	int zerbaitErdian = 0;
	int laukiPosibleak[8];
	int posibleKop = 0;
	int mugimenduPosiblea = EZINEZKOA;

	if (posizioa != ZUTABE_BERDIN && posizioa != ILARA_BERDIN) {
		//Eskuinean, behean
		if (posizioa == BEHE_ESKUIN) {
			int laukiPosible = clickatua[0].id + ZUTABE_KOP + 1;//

			for (int i = 0; i < ilara1 - ilara0; i++) {//
				laukiPosibleak[i] = laukiPosible;
				laukiPosible = laukiPosible + ZUTABE_KOP + 1;//
				posibleKop++;
			}
		}
		//Eskuinean, gainean
		if (posizioa == GOI_ESKUIN) {
			int laukiPosible = clickatua[0].id - ZUTABE_KOP + 1;//

			for (int i = 0; i < ilara0 - ilara1; i++) {//
				laukiPosibleak[i] = laukiPosible;
				laukiPosible = laukiPosible - ZUTABE_KOP + 1;//
				posibleKop++;
			}
		}
		//Ezkerrean, behean
		if (posizioa == BEHE_EZKER) {
			int laukiPosible = clickatua[0].id + ZUTABE_KOP - 1;//

			for (int i = 0; i < ilara1 - ilara0; i++) {//
				laukiPosibleak[i] = laukiPosible;
				laukiPosible = laukiPosible + ZUTABE_KOP - 1;//
				posibleKop++;
			}
		}
		//Ezkerrean, gainean
		if (posizioa == GOI_EZKER) {
			int laukiPosible = clickatua[0].id - ZUTABE_KOP - 1;//

			for (int i = 0; i < ilara0 - ilara1; i++) {//
				laukiPosibleak[i] = laukiPosible;
				laukiPosible = laukiPosible - ZUTABE_KOP - 1;//
				posibleKop++;
			}
		}

		//Mugimendua lauki posible batean dagoen
		for (int i = 0; i < posibleKop; i++) {
			if (clickatua[1].id == laukiak[laukiPosibleak[i]].id) mugimenduPosiblea = 1;
		}
		//Laukia onartuta badago, oztopoak bitartean dauden
		if (mugimenduPosiblea == 1) {
			for (int i = 0; i < posibleKop; i++) {
				if (laukiak[laukiPosibleak[i]].pieza.mota > HUTS) zerbaitErdian++;
			}
			if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;

			if (zerbaitErdian == MUGITU) {
				return MUGITU;
			}
			else if (zerbaitErdian == JAN) {
				if (clickatua[1].pieza.kolorea != turnoa) {
					return JAN;
				}
				else return OZTOPOA;
			}
			else return OZTOPOA;
		}
		else return OZTOPOA;
	}
	else return EZINEZKOA;
}

int mugimenduAndre(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int posizioa = posizioaTaulan(clickatua);
	if (posizioa == ZUTABE_BERDIN || posizioa == ILARA_BERDIN) {
		return mugimenduDorre(clickatua, laukiak, turnoa);
	}
	else {
		return mugimenduAlfil(clickatua, laukiak, turnoa);
	}
}

int mugimenduErrege(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);

	if (zutabe1 - zutabe0 == 1 || zutabe1 - zutabe0 == -1 || ilara1 - ilara0 == 1 || ilara1 - ilara0 == -1) {
		if (clickatua[1].pieza.mota == HUTS) {
			return MUGITU;
		}
		else if (clickatua[0].pieza.kolorea != clickatua[1].pieza.kolorea) {
			return JAN;
		}
		else return EZINEZKOA;
	}
	else return EZINEZKOA;
}