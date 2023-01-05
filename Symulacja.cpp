#include "Symulacja.h"


bool Symulacja::Sprawdz_rozdzielczosc(int liczba, int rozmiar)const
{
	int szerokosc = sf::VideoMode::getDesktopMode().width;
	int wysokosc = sf::VideoMode::getDesktopMode().height;
	int pomnozone = liczba * rozmiar;
	return pomnozone < szerokosc && pomnozone < wysokosc;
}

int Symulacja::Zalecany_rozmiar_komorki(int liczba_komorek)const
{
	int min = std::min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	min *= 0.9;
	return  min / liczba_komorek;
}

Symulacja::Symulacja()
{
	std::cout << "================================= GRA W ZYCIE =================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	Podaj liczbe komorek w rzedzie (zalecana liczba 3 - 200): ";
	std::cin >> liczba_komorek;
	rozmiar_komorki = Zalecany_rozmiar_komorki(liczba_komorek);
	if (this->Sprawdz_rozdzielczosc(liczba_komorek, rozmiar_komorki) && rozmiar_komorki > 1)
	{
		std::cout << "	Podaj ile zyjacych komorek wylosowac: (0 - " << liczba_komorek * liczba_komorek << "): ";
		std::cin >> komorki_do_wylosowania;
		std::cout << "	Podaj opoznienie miedzy kolejnymi ruchami (domyslnie 100 ms): ";
		std::cin >> opoznienie_miedzy_ruchami;
		system("cls");
		std::cout << "================================= STEROWANIE =================================" << std::endl;
		std::cout << std::endl;
		std::cout << "	ABY OZYWIC/ZABIC KOMORKE NACISNIJ NA NIA LEWYM PRZYCISKIEM MYSZY W CZASIE PAUZY" << std::endl;
		std::cout << "	ABY ZATRZYMAC/WZNOWIC SYMULACJE WCISNIJ KLAWISZ 'P'" << std::endl;
		std::cout << "	ABY ZWIEKSZYC/ZMNIEJSZYC OPOZNIENIE WCISNIJ KLAWISZ STRZALKA GORNA/DOLNA" << std::endl;
		std::cout << "===============================================================================" << std::endl;
	}
	
}

void Symulacja::Symuluj()
{
	Plansza plansza(liczba_komorek, rozmiar_komorki, opoznienie_miedzy_ruchami);
	plansza.Wybierz_i_losowych_pol(komorki_do_wylosowania);
	plansza.Inicjalizuj();		
}
