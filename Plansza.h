#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <algorithm>
class Plansza
{
	const int liczba_komorek = { 15 };
	const int rozmiar_komorki = { 30 };
	int opoznienie = { 100 };
	sf::Vector2f vector;
	bool **populacja_obecna;
	bool **populacja_nastepna;
	bool czy_zapauzowano;
public:
	Plansza(int ile_komorek, int jaki_rozmiar_komorki, int opoznienie_miedzy_ruchami);
	~Plansza();
	void Wybierz_i_losowych_pol(int i);
	int Ile_sasiadow(int x, int y);
	sf::RectangleShape Zwroc_komorke(int x, int y);
	void Wyswietl_populacje(sf::RenderWindow& okno);
	void Inicjalizuj();
	void Aktualizuj();
	void Kopiuj_populacje();

};

