#pragma once
#include "Plansza.h"
#include <string>
#include <locale.h>

class Symulacja
{
	int rozmiar_komorki;
	int liczba_komorek;
	int komorki_do_wylosowania;
	int opoznienie_miedzy_ruchami;
public:
	Symulacja();
	bool Czy_same_cyfry(std::string& wejscie)const;
	void Pobierz_poprawne_parametry();
	void Wczytaj(int& parametr);
	int Zalecany_rozmiar_komorki(int liczba_komorek)const;
	void Wyswietl_sterowanie()const;
	void Symuluj();
};