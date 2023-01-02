#pragma once
#include "Plansza.h"

class Symulacja
{
public:
	bool Sprawdz_rozdzielczosc(int liczba, int rozmiar)const;
	int Zalecany_rozmiar_komorki(int liczba_komorek)const;
	void Symuluj();
};