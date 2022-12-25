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
			int komorki_do_wylosowania = 0, opoznienie_miedzy_ruchami = 0;
			std::cout << "Podaj ile zyjacych komorek wylosowac: ";
			std::cin >> komorki_do_wylosowania;
			std::cout << "Podaj opoznienie miedzy kolejnymi ruchami (domyslnie 100 ms): ";
			std::cin >> opoznienie_miedzy_ruchami;
			Plansza plansza(liczba_komorek, rozmiar_komorki, opoznienie_miedzy_ruchami);
			plansza.Wybierz_i_losowych_pol(komorki_do_wylosowania);
			plansza.Inicjalizuj();
			break;
		}
		system("cls");
		std::cout << "Okno dla poprzednich parametrow jest zbyt duze/male!" << std::endl;
		
	}
}
