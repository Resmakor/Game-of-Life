#include "Symulacja.h"

void Symulacja::Sprawdz_rozdzielczosc(int liczba, int rozmiar)
{
	int szerokosc = sf::VideoMode::getDesktopMode().width;
	int wysokosc = sf::VideoMode::getDesktopMode().height;
}
void Symulacja::Symuluj()
{
		int rozmiar_komorki, liczba_komorek;
		std::cout << "Podaj liczbe komorek: ";
		std::cin >> liczba_komorek;
		std::cout << "Podaj rozmiar komorki: ";
		std::cin >> rozmiar_komorki;
		Plansza plansza(liczba_komorek, rozmiar_komorki);
		plansza.Inicjalizuj();
}
