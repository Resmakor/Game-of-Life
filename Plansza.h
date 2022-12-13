#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
class Plansza
{
	const int liczba_komorek = { 15 };
	const int rozmiar_komorki = { 30 };
	sf::Vector2f vector;
	bool **populacja_obecna;
	bool **populacja_nastepna;
public:
	Plansza(int ile_komorek, int jaki_rozmiar_komorki);
	~Plansza();
	void Wybierz_i_losowych_pol(int i);
	sf::RectangleShape Zwroc_komorke(int x, int y);
	void Inicjalizuj();

};

