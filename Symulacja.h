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
	void Wyswietl_sterowanie()const;
	void Wczytaj(int &parametr);
	bool Sprawdz_rozdzielczosc(int liczba, int rozmiar)const;
	int Zalecany_rozmiar_komorki(int liczba_komorek)const;
	void Symuluj();
};