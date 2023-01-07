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
	if (liczba_komorek < 2) return 0;
	int min = std::min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	min *= 0.9;
	return  min / liczba_komorek;
}

void Symulacja::Wyswietl_sterowanie()const
{
	system("cls");
	std::cout << "========================================= STEROWANIE =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	ABY ZAKO�CZY� OBECN� SYMULACJ� ZAMKNIJ OKNO SYMULACJI" << std::endl;
	std::cout << "	ABY O�YWI�/ZABI� KOM�RK� NACI�NIJ NA NI� LEWYM PRZYCISKIEM MYSZY W CZASIE PAUZY" << std::endl;
	std::cout << "	ABY ZATRZYMA�/WZNOWI� SYMULACJ� WCI�NIJ KLAWISZ 'P'" << std::endl;
	std::cout << "	ABY ZWI�KSZY�/ZMNIEJSZY� OP�ZNIENIE WCI�NIJ KLAWISZ STRZA�KA G�RNA/DOLNA" << std::endl;
	std::cout << std::endl;
	std::cout << "==============================================================================================" << std::endl;
}

bool Symulacja::Czy_same_cyfry(std::string& wejscie)const
{
	int dlugosc_wejscia = wejscie.size();
	if (dlugosc_wejscia == 0 || dlugosc_wejscia > 8) return false;
	for (int i = 0; i < dlugosc_wejscia; i++)
	{
		if (wejscie[i] < '0' || wejscie[i] > '9')
		{
			return false;
		}
	}
	return true;
}

void Symulacja::Wczytaj(int &parametr)
{
	while (true)
	{
		std::string wejscie;
		std::getline(std::cin, wejscie);
		if (wejscie == "STOP") exit(0);
		else if (Czy_same_cyfry(wejscie))
		{
			parametr = std::stoi(wejscie);
			break;
		}
		else
		{
			std::cout << "	B��D! PODAJ INN� WARTO��: ";
		}
	}
}

void Symulacja::Pobierz_poprawne_parametry()
{
	system("cls");
	std::cout << "========================================= GRA W �YCIE =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "				WPISZ 'STOP' ABY ZAKO�CZY� PROGRAM " << std::endl;
	std::cout << std::endl;

	std::cout << "	PODAJ LICZB� KOM�REK W RZ�DZIE (ZALECANA LICZBA 3 - 200): ";
	Wczytaj(liczba_komorek);
	while (liczba_komorek < 2 || Zalecany_rozmiar_komorki(liczba_komorek) < 2)
	{
		std::cout << "	B��D! PODAJ INN� WARTO��: ";
		Wczytaj(liczba_komorek);
	}
	rozmiar_komorki = Zalecany_rozmiar_komorki(liczba_komorek);

	std::cout << "	PODAJ ILE �YJ�CYCH KOMOREK WYLOSOWA� (0 - " << liczba_komorek * liczba_komorek << "): ";
	Wczytaj(komorki_do_wylosowania);
	while (komorki_do_wylosowania < 0 || komorki_do_wylosowania > liczba_komorek * liczba_komorek)
	{
		std::cout << "	B��D! PODAJ INN� WARTO��:";
		Wczytaj(liczba_komorek);
	}

	std::cout << "	PODAJ OP�ZNIENIE MI�DZY KOLEJNYMI RUCHAMI (ms): ";
	Wczytaj(opoznienie_miedzy_ruchami);
	while (opoznienie_miedzy_ruchami <= 0)
	{
		std::cout << "	B��D! PODAJ INN� WARTO��: ";
		Wczytaj(opoznienie_miedzy_ruchami);
	}
}

Symulacja::Symulacja()
{
	setlocale(LC_CTYPE, "Polish");
	Pobierz_poprawne_parametry();
}

void Symulacja::Symuluj()
{
	Wyswietl_sterowanie();
	Plansza plansza(liczba_komorek, rozmiar_komorki, opoznienie_miedzy_ruchami);
	plansza.Wybierz_i_losowych_pol(komorki_do_wylosowania);
	plansza.Inicjalizuj();
}
