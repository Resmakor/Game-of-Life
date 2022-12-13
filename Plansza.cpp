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

void Plansza::Wybierz_i_losowych_pol(int i)
{
    if (i > liczba_komorek * liczba_komorek || i < 1)
    {
        std::cout << "Nieprawidlowa wartosc pol do wylosowania!" << std::endl;
        return;
    }
    srand(time(0));
    int licznik_zywych_pol = 0;
    int temp_x, temp_y;
    while (licznik_zywych_pol != i)
    {
        temp_x = rand() % liczba_komorek;
        temp_y = rand() % liczba_komorek;
        if (temp_x > 0 && temp_y > 0 && temp_x < liczba_komorek + 1 && temp_y < liczba_komorek + 1)
        {
            if (populacja_obecna[temp_x][temp_y] == false)
            {
                populacja_obecna[temp_x][temp_y] = true;
                licznik_zywych_pol++;
            }
        }
    }
}


sf::RectangleShape Plansza::Zwroc_komorke(int x, int y)
{
    sf::RectangleShape cell;
    cell.setPosition(x * rozmiar_komorki, y * rozmiar_komorki);
    cell.setSize(vector);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Green);
    if (populacja_obecna[x][y] == 1)
    {
        cell.setFillColor(sf::Color::Black);
    }
        
    else
    {
        cell.setFillColor(sf::Color::White);
    }
    return cell;
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
        for (int i = 0; i < liczba_komorek; i++)
        {
            for (int j = 0; j < liczba_komorek; j++)
            {
                sf::RectangleShape cell = Zwroc_komorke(i, j);
                window.draw(cell);
            }
        }
        window.display();
    }
}

