#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Plansza
{
	const int liczba_komorek = { 15 };
	const int rozmiar_komorki = { 30 };
	sf::Vector2f vector;
public:
	Plansza(int ile_komorek, int jaki_rozmiar_komorki);
	void Inicjalizuj();
};

