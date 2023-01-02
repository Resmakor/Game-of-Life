#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>

#define ZMIANA_OPOZNIENIA 50
#define SZARY sf::Color(58, 58, 58)
#define CZARNY sf::Color::Black
#define ZIELONY sf::Color(0, 255, 127)
#define BIALY sf::Color(255, 250, 250)
#define OUTLINE_THICKNESS 1

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
	int Ile_sasiadow(int x, int y)const;
	sf::RectangleShape Zwroc_komorke(int x, int y)const;
	void Wyswietl_populacje(sf::RenderWindow& okno)const;
	void Inicjalizuj();
	void Aktualizuj();
	void Kopiuj_populacje();
};

