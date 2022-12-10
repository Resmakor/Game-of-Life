#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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
	void Wyswietl_komorke(int x, int y);
	void Wyswietl_komorki();
	void Inicjalizuj();

};

