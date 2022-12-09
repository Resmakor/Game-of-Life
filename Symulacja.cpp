#include "Symulacja.h"
#include <Windows.h>
bool Symulacja::Sprawdz_rozdzielczosc(int liczba, int rozmiar)
{
	int szerokosc = sf::VideoMode::getDesktopMode().width;
	int wysokosc = sf::VideoMode::getDesktopMode().height;
	int pomnozone = liczba * rozmiar;
	return pomnozone < szerokosc && pomnozone < wysokosc && pomnozone > 200;
}
void Symulacja::Symuluj()
{
	while (true)
	{
		int rozmiar_komorki, liczba_komorek;
		std::cout << "Podaj liczbe komorek: ";
		std::cin >> liczba_komorek;
		std::cout << "Podaj rozmiar komorki: ";
		std::cin >> rozmiar_komorki;
		if (this->Sprawdz_rozdzielczosc(liczba_komorek, rozmiar_komorki))
		{
			Plansza plansza(liczba_komorek, rozmiar_komorki);
			plansza.Inicjalizuj();
			break;
		}
		system("cls");
		std::cout << "Okno dla poprzednich parametrow jest zbyt duze/male!" << std::endl;
		
	}
}
