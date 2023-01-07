#include "Symulacja.h"

Symulacja::Symulacja()
{
	setlocale(LC_CTYPE, "Polish");
	Pobierz_poprawne_parametry();
}

/* Metoda pobiera poprawne parametry symulacji od u¿ytkownika */
void Symulacja::Pobierz_poprawne_parametry()
{	
	system("cls");
	std::cout << "========================================= GRA W ¯YCIE =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "				WPISZ 'STOP' ABY ZAKOÑCZYÆ PROGRAM " << std::endl;
	std::cout << std::endl;

	std::cout << "	PODAJ LICZBÊ KOMÓREK W RZÊDZIE (ZALECANA LICZBA 3 - 200): ";
	Wczytaj(liczba_komorek);
	while (liczba_komorek < 2 || Zalecany_rozmiar_komorki(liczba_komorek) < 2)
	{
		std::cout << "	B£¥D! PODAJ INN¥ WARTOŒÆ: ";
		Wczytaj(liczba_komorek);
	}
	rozmiar_komorki = Zalecany_rozmiar_komorki(liczba_komorek);

	std::cout << "	PODAJ ILE ¯YJ¥CYCH KOMOREK WYLOSOWAÆ (0 - " << liczba_komorek * liczba_komorek << "): ";
	Wczytaj(komorki_do_wylosowania);
	while (komorki_do_wylosowania < 0 || komorki_do_wylosowania > liczba_komorek * liczba_komorek)
	{
		std::cout << "	B£¥D! PODAJ INN¥ WARTOŒÆ: ";
		Wczytaj(liczba_komorek);
	}

	std::cout << "	PODAJ OPÓZNIENIE MIÊDZY KOLEJNYMI RUCHAMI (1 - " <<  MAKS_OPOZNIENIE << " ms): ";
	Wczytaj(opoznienie_miedzy_ruchami);
	while (opoznienie_miedzy_ruchami < 1 || opoznienie_miedzy_ruchami > MAKS_OPOZNIENIE)
	{
		std::cout << "	B£¥D! PODAJ INN¥ WARTOŒÆ: ";
		Wczytaj(opoznienie_miedzy_ruchami);
	}
}

/* Metoda wczytuje poprawne dane wejœciowe tj. liczbê */
void Symulacja::Wczytaj(int& parametr)
{
	while (true)
	{
		std::string wejscie;
		std::getline(std::cin, wejscie);
		transform(wejscie.begin(), wejscie.end(), wejscie.begin(), ::toupper);
		if (wejscie == "STOP") exit(0);
		else if (Czy_same_cyfry(wejscie))
		{
			parametr = std::stoi(wejscie);
			break;
		}
		else
		{
			std::cout << "	B£¥D! PODAJ INN¥ WARTOŒÆ: ";
		}
	}
}

/* Metoda zwraca czy w zmiennej typu string znajduj¹ siê same cyfry */
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

/* Metoda zwraca optymalny rozmiar pojedynczej komórki (px) */
int Symulacja::Zalecany_rozmiar_komorki(int liczba_komorek)const
{
	if (liczba_komorek < 2) return 0;
	int min = std::min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	min *= 0.9;
	return  min / liczba_komorek;
}

/* Metoda wyœwietla w jaki sposób sterowaæ symulacj¹ */
void Symulacja::Wyswietl_sterowanie()const
{
	system("cls");
	std::cout << "========================================= STEROWANIE =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	ABY ZAKOÑCZYÆ OBECN¥ SYMULACJÊ ZAMKNIJ OKNO SYMULACJI" << std::endl;
	std::cout << "	ABY O¯YWIÆ/ZABIÆ KOMÓRKÊ NACIŒNIJ NA NI¥ LEWYM PRZYCISKIEM MYSZY W CZASIE PAUZY" << std::endl;
	std::cout << "	ABY ZATRZYMAÆ/WZNOWIÆ SYMULACJÊ WCIŒNIJ KLAWISZ 'P'" << std::endl;
	std::cout << "	ABY ZWIÊKSZYÆ/ZMNIEJSZYÆ OPÓZNIENIE WCIŒNIJ KLAWISZ STRZA£KA GÓRNA/DOLNA" << std::endl;
	std::cout << std::endl;
	std::cout << "==============================================================================================" << std::endl;
}

/* Metoda wyœwietla sterowanie, a nastêpnie rozpoczyna symulacjê */
void Symulacja::Symuluj()
{
	Wyswietl_sterowanie();
	Plansza plansza(liczba_komorek, rozmiar_komorki, opoznienie_miedzy_ruchami);
	plansza.Wybierz_i_losowych_pol(komorki_do_wylosowania);
	plansza.Inicjalizuj();
}
