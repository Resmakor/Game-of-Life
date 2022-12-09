#include "Plansza.h"
Plansza::Plansza(int ile_komorek, int jaki_rozmiar_komorki) : liczba_komorek(ile_komorek), rozmiar_komorki(jaki_rozmiar_komorki)
{
   vector.x = rozmiar_komorki;
   vector.y = rozmiar_komorki;
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

