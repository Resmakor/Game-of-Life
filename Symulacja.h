#pragma once
#include "Plansza.h"

class Symulacja
{
	int rozmiar_komorki;
	int liczba_komorek;
	int komorki_do_wylosowania;
	int opoznienie_miedzy_ruchami;
public:
	bool Sprawdz_rozdzielczosc(int liczba, int rozmiar)const;
	int Zalecany_rozmiar_komorki(int liczba_komorek)const;
	void Symuluj();
	Symulacja();
};