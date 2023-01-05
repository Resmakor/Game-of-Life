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
	if (liczba_komorek < 2)
	{
		return 0;
	}
	return  min / liczba_komorek;
}


void Symulacja::Wyswietl_sterowanie()const
{
	system("cls");
	std::cout << "================================= STEROWANIE =================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	ABY OZYWIC/ZABIC KOMORKE NACISNIJ NA NIA LEWYM PRZYCISKIEM MYSZY W CZASIE PAUZY" << std::endl;
	std::cout << "	ABY ZATRZYMAC/WZNOWIC SYMULACJE WCISNIJ KLAWISZ 'P'" << std::endl;
	std::cout << "	ABY ZWIEKSZYC/ZMNIEJSZYC OPOZNIENIE WCISNIJ KLAWISZ STRZALKA GORNA/DOLNA" << std::endl;
	std::cout << "===============================================================================" << std::endl;
}

void Symulacja::Wczytaj(int &parametr)
{
	while (!(std::cin >> parametr))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "	BLAD! PODAJ INNA WARTOSC: ";
	}
}

Symulacja::Symulacja()
{
	std::cout << "================================= GRA W ZYCIE =================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	PODAJ LICZBE KOMOREK W RZEDZIE (ZALECANA LICZBA 3 - 200): ";
	Wczytaj(liczba_komorek);
	std::cout << liczba_komorek << std::endl;
	while (liczba_komorek < 2 || Zalecany_rozmiar_komorki(liczba_komorek) < 2)
	{
		std::cout << "	BLAD! PODAJ INNA WARTOSC: ";
		Wczytaj(liczba_komorek);
	}
	rozmiar_komorki = Zalecany_rozmiar_komorki(liczba_komorek);
	std::cout << "	PODAJ ILE ZYJACYCH KOMOREK WYLOSOWAC (0 - " << liczba_komorek * liczba_komorek << "): ";
	Wczytaj(komorki_do_wylosowania);
	while (komorki_do_wylosowania < 0 || komorki_do_wylosowania > liczba_komorek * liczba_komorek)
	{
		std::cout << "	BLAD! PODAJ INNA WARTOSC: ";
		Wczytaj(liczba_komorek);
	}
	std::cout << "	PODAJ OPOZNIENIE MIEDZY KOLEJNYMI RUCHAMI (ms): ";
	Wczytaj(opoznienie_miedzy_ruchami);
	while (opoznienie_miedzy_ruchami < 0)
	{
		std::cout << "	BLAD! PODAJ INNA WARTOSC: ";
		Wczytaj(opoznienie_miedzy_ruchami);
	}
}

void Symulacja::Symuluj()
{
	Wyswietl_sterowanie();
	Plansza plansza(liczba_komorek, rozmiar_komorki, opoznienie_miedzy_ruchami);
	plansza.Wybierz_i_losowych_pol(komorki_do_wylosowania);
	plansza.Inicjalizuj();		
}
