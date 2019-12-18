#include "jokoa.h"
#include "irudiakEtaSoinuak.h"

int mugimenduPeoi(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int emaitza = -1;
	//PEOI+1
	if ((clickatua[0].id + turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS) {
		//if: peoia eta hurrengo laukia clickatu && hurrengo laukia hutsik
		emaitza = MUGITU;
	}
	//PEOI+2
	else if ((clickatua[0].id + 2 * turnoa == clickatua[1].id) && clickatua[1].pieza.mota == HUTS && laukiak[clickatua[0].id + turnoa].pieza.mota == HUTS && clickatua[0].pieza.mugimenduKop == 0) {
		//if: peoia eta hurrengo bigarren laukia clickatu && hurrengo bigarren laukia hutsik && piezaren lehenengo mugimendua
		emaitza = MUGITU;
	}
	//PEOI + diagonal1aurrera(jan)
	else if (((clickatua[0].id + ZUTABE_KOP + turnoa == clickatua[1].id) ||
		(clickatua[0].id - ZUTABE_KOP + turnoa == clickatua[1].id)) && clickatua[1].pieza.mota > HUTS&& clickatua[1].pieza.kolorea != turnoa) {
		//if: peoia eta diagonalean bere norabidean clickatu && bigarren clicka ez hutsik && bigarren clicka talde aurkakoa
		//jandakoaFuntzioa++deLaPiezaQueSeaaaa
		irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
		emaitza = JAN;
	}
	else emaitza = EZINEZKOA;

	if (emaitza != EZINEZKOA) {
		if (turnoa == ZURI) {
			for (int i = A8; i < H8; i += 8) {
				if (clickatua[1].id == i) {
					int x, y;
					x = LAUKI_X * zutabeaKalkulatu(clickatua[1].id) + MARGEN_LUZERA;
					y = LAUKI_Y * ilaraKalkulatu(clickatua[1].id) + MARGEN_LUZERA;
					clickatua[0].pieza.mota = DORRE;//piezaAukeraInterfaz();
					irudiaKendu(clickatua[0].pieza.imageId);
					clickatua[0].pieza.imageId = irudiaKargatu(DORRE_ZURI, JOKOA);
					irudiaMugitu(clickatua[0].pieza.imageId, x, y);
				}
			}
		}
		if (turnoa == BELTZ) {
			for (int i = A1; i < H1; i += 8) {
				if (clickatua[1].id == i) {
					int x, y;
					x = LAUKI_X * zutabeaKalkulatu(clickatua[1].id) + MARGEN_LUZERA;
					y = LAUKI_Y * ilaraKalkulatu(clickatua[1].id) + MARGEN_LUZERA;
					clickatua[0].pieza.mota = DORRE;//piezaAukeraInterfaz();
					irudiaKendu(clickatua[0].pieza.imageId);
					clickatua[0].pieza.imageId = irudiaKargatu(DORRE_BELTZ, JOKOA);
					irudiaMugitu(clickatua[0].pieza.imageId, x, y);
				}
			}
		}
	}
	return emaitza;
	//beste aldera ailegatzen bada DORRE, ZALDUN, ALFIL edo ANDRE bihur daiteke
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
			if (zutabe0 < zutabe1) {//
				for (int i = clickatua[0].id + 1; i <= clickatua[1].id; i++) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
			//Ezkerrerantz
			if (zutabe0 > zutabe1) {//
				for (int i = clickatua[0].id - 1; i >= clickatua[1].id; i--) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
		}
		//mugimendu bertikala
		else if (posizioa == ZUTABE_BERDIN) {
			//Beherantz
			if (ilara0 < ilara1) {//
				for (int i = clickatua[0].id + ZUTABE_KOP; i <= clickatua[1].id; i += ZUTABE_KOP) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
			//Gorantz
			if (ilara0 > ilara1) {//
				for (int i = clickatua[0].id - ZUTABE_KOP; i >= clickatua[1].id; i -= ZUTABE_KOP) {//
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
			}
		}
		//Kasu honetan "erdian" dagoena aukeratutako pieza bada
		if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;

		//Mugitu, ez jan
		if (zerbaitErdian == MUGITU) {
			return MUGITU;
		}
		//Mugitu eta jan
		else if (zerbaitErdian == JAN) {
			//Pieza aurkaria bada
			if (clickatua[1].pieza.kolorea != turnoa) {
				irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
				return JAN;
			}
		}
		//Bidean oztopoa 
		else return OZTOPOA;
	}
	//Bide ezinezkoa
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

	//Mugitu, ez jan
	if (zerbaitErdian == MUGITU) {
		return MUGITU;
	}
	//Mugitu eta jan
	else if (zerbaitErdian == JAN) {
		if (clickatua[1].pieza.kolorea != turnoa) {
			irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
			return JAN;
		}
	}
	//Bidean ezinezkoa
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

			//Mugitu, ez jan
			if (zerbaitErdian == MUGITU) {
				return MUGITU;
			}
			//Mugitu eta jan
			else if (zerbaitErdian == JAN) {
				if (clickatua[1].pieza.kolorea != turnoa) {
					irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
					return JAN;
				}
			}
			else return OZTOPOA;
		}
		//Bidean oztopoa 
		else return OZTOPOA;
	}
	//Bidea ezinezkoa
	else return EZINEZKOA;
}

int mugimenduAndre(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	int zutabe0 = zutabeaKalkulatu(clickatua[0].id);
	int ilara0 = ilaraKalkulatu(clickatua[0].id);
	int zutabe1 = zutabeaKalkulatu(clickatua[1].id);
	int ilara1 = ilaraKalkulatu(clickatua[1].id);
	int posizioa = posizioaTaulan(clickatua);
	int zerbaitErdian = 0;
	int mugimenduPosiblea = 0;
	//DORRE
	if (posizioa == ZUTABE_BERDIN || posizioa == ILARA_BERDIN) {
		//Mugimendu horizontala
		if (ilara0 == ilara1) {
			//Eskuinerantz
			if (zutabe0 < zutabe1) {
				for (int i = clickatua[0].id + 1; i <= clickatua[1].id; i++) {
					if (laukiak[i].pieza.mota > 0) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
				if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;
			}
			//Ezkerrerantz
			if (zutabe0 > zutabe1) {
				for (int i = clickatua[0].id - 1; i >= clickatua[1].id; i--) {
					if (laukiak[i].pieza.mota > 0) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
				if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;
			}
		}
		//mugimendu bertikala
		else if (zutabe0 == zutabe1) {
			//Beherantz
			if (ilara0 < ilara1) {
				for (int i = clickatua[0].id + ZUTABE_KOP; i <= clickatua[1].id; i += ZUTABE_KOP) {
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
				if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;
			}
			//Gorantz
			if (ilara0 > ilara1) {
				for (int i = clickatua[0].id - ZUTABE_KOP; i >= clickatua[1].id; i -= ZUTABE_KOP) {
					if (laukiak[i].pieza.mota > HUTS) zerbaitErdian++;
					if (zerbaitErdian > 1) break;
				}
				if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;
			}
		}
	}
	//ALFIL
	else {
		int laukiPosibleak[8];
		int posibleKop = 0;
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
		//Laukia onartuta badago oztopoak bitartean dauden
		if (mugimenduPosiblea == 1) {
			for (int i = 0; i < posibleKop; i++) {
				if (laukiak[laukiPosibleak[i]].pieza.mota > HUTS) zerbaitErdian++;
			}
			if (zerbaitErdian == 1 && clickatua[1].pieza.mota == HUTS) zerbaitErdian++;

			//Mugitu, ez jan
			if (zerbaitErdian == MUGITU) {
				mugituPieza(laukiak, clickatua[0], clickatua[1].id, turnoa);
				return MUGITU;
			}
			//Mugitu eta jan
			else if (zerbaitErdian == JAN) {
				if (clickatua[1].pieza.kolorea != turnoa) {
					irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
					mugituPieza(laukiak, clickatua[0], clickatua[1].id, turnoa);
					return JAN;
				}
			}
		}
		//Bidean oztopoa 
		else return OZTOPOA;
	}
	//Mugitu, ez jan
	if (zerbaitErdian == MUGITU) {
		return MUGITU;
	}
	//Mugitu eta jan
	else if (zerbaitErdian == JAN) {
		if (clickatua[1].pieza.kolorea != turnoa) {
			irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
			return JAN;
		}
	}
	//Bidean oztopoa 
	else return OZTOPOA;
	//Bidea ezinezkoa
	//return -1;
}

int mugimenduErrege(LAUKIA* clickatua, LAUKIA* laukiak, int turnoa) {
	if (clickatua[0].id - 9 == clickatua[1].id || clickatua[0].id - 8 == clickatua[1].id
		|| clickatua[0].id - 7 == clickatua[1].id || clickatua[0].id - 1 == clickatua[1].id
		|| clickatua[0].id + 1 == clickatua[1].id || clickatua[0].id + 7 == clickatua[1].id
		|| clickatua[0].id + 8 == clickatua[1].id || clickatua[0].id + 9 == clickatua[1].id) {
		if (clickatua[1].pieza.mota == HUTS) {
			return MUGITU;
		}
		else if (clickatua[0].pieza.kolorea != clickatua[1].pieza.kolorea) {
			irudiaKendu(laukiak[clickatua[1].id].pieza.imageId);
			return JAN;
		}
	}
	else return EZINEZKOA;
}
