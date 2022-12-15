#include "Symulacja.h"
#include <Windows.h>
bool Symulacja::Sprawdz_rozdzielczosc(int liczba, int rozmiar)
{
	int szerokosc = sf::VideoMode::getDesktopMode().width;
	int wysokosc = sf::VideoMode::getDesktopMode().height;
	int pomnozone = liczba * rozmiar;
	return pomnozone < szerokosc && pomnozone < wysokosc;
}

int Symulacja::Zalecany_rozmiar_komorki(int liczba_komorek)
{
	int min = std::min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	min *= 0.9;
	return  min / liczba_komorek;
}

void Symulacja::Symuluj()
{
	while (true)
	{
		int rozmiar_komorki, liczba_komorek;
		std::cout << "Podaj liczbe komorek w rzedzie (zalecana liczba 3 - 400): ";
		std::cin >> liczba_komorek;
		int zalecany_rozmiar = Zalecany_rozmiar_komorki(liczba_komorek);
		std::cout << "Podaj rozmiar komorki (zalecany rozmiar to " << zalecany_rozmiar << " px): ";
		std::cin >> rozmiar_komorki;
		if (this->Sprawdz_rozdzielczosc(liczba_komorek, rozmiar_komorki) && zalecany_rozmiar > 1)
		{
			Plansza plansza(liczba_komorek, rozmiar_komorki);
			plansza.Wybierz_i_losowych_pol(5000);
			plansza.Inicjalizuj();
			break;
		}
		system("cls");
		std::cout << "Okno dla poprzednich parametrow jest zbyt duze/male!" << std::endl;
		
	}
}
