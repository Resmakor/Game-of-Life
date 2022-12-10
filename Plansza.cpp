#include "Plansza.h"
Plansza::Plansza(int ile_komorek, int jaki_rozmiar_komorki) : liczba_komorek(ile_komorek), rozmiar_komorki(jaki_rozmiar_komorki)
{
   vector.x = rozmiar_komorki;
   vector.y = rozmiar_komorki;
   populacja_obecna = new bool* [liczba_komorek];
   populacja_nastepna = new bool* [liczba_komorek];
   for (int i = 0; i < liczba_komorek; i++)
   {
       populacja_obecna[i] = new bool[liczba_komorek];
       memset(populacja_obecna[i], false, liczba_komorek * sizeof(bool));
       populacja_nastepna[i] = new bool[liczba_komorek];
       memset(populacja_nastepna[i], false, liczba_komorek * sizeof(bool));
   }
}

Plansza::~Plansza()
{
    for (int i = 0; i < liczba_komorek; i++)
    {
        delete[] populacja_obecna[i];
        delete[] populacja_nastepna[i];
    }
    delete[] populacja_obecna;
    delete[] populacja_nastepna;
}

void Plansza::Wyswietl_komorke(int x, int y)
{

}

void Plansza::Wyswietl_komorki()
{

}

void Plansza::Inicjalizuj()
{
    sf::RenderWindow window(sf::VideoMode(rozmiar_komorki * liczba_komorek, rozmiar_komorki * liczba_komorek), "Gra w Zycie");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.display();
    }
}

