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
   czy_zapauzowano = false;
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
    int licznik_zywych_pol = 0, temp_x, temp_y;
    while (licznik_zywych_pol != i)
    {
        temp_x = rand() % liczba_komorek;
        temp_y = rand() % liczba_komorek;
        if (temp_x >= 0 && temp_y >= 0 && temp_x < liczba_komorek && temp_y < liczba_komorek)
        {
            if (populacja_obecna[temp_x][temp_y] == false)
            {
                populacja_obecna[temp_x][temp_y] = true;
                licznik_zywych_pol++;
            }
        }
    }
}

int Plansza::Ile_sasiadow(int x, int y)
{
    int sasiedzi = 0;
    if (x - 1 >= 0 && y - 1 >= 0)
        sasiedzi += int(populacja_obecna[x - 1][y - 1]);
    if (y - 1 >= 0)
        sasiedzi += int(populacja_obecna[x][y - 1]);
    if (x + 1 < liczba_komorek && y - 1 >= 0)
        sasiedzi += int(populacja_obecna[x + 1][y - 1]);
    if (x - 1 >= 0)
        sasiedzi += int(populacja_obecna[x - 1][y]);
    if (x + 1 < liczba_komorek)
        sasiedzi += int(populacja_obecna[x + 1][y]);
    if (x - 1 >= 0 && y + 1 < liczba_komorek)
        sasiedzi += int(populacja_obecna[x - 1][y + 1]);
    if (y + 1 < liczba_komorek)
        sasiedzi += int(populacja_obecna[x][y + 1]);
    if (x + 1 < liczba_komorek && y + 1 < liczba_komorek)
        sasiedzi += int(populacja_obecna[x + 1][y + 1]);
    return sasiedzi;
}


void Plansza::Aktualizuj()
{
    for (int i = 0; i < liczba_komorek; i++)
    {
        for (int j = 0; j < liczba_komorek; j++)
        {
            int liczba_sasiadow = Ile_sasiadow(i, j);
            if (liczba_sasiadow == 3 && populacja_obecna[i][j] == false)
            {
                populacja_nastepna[i][j] = true;
            }
            else if (liczba_sasiadow == 2 || liczba_sasiadow == 3 && populacja_obecna[i][j])
            {
                populacja_nastepna[i][j] = true;
            }
            else
            {
                populacja_nastepna[i][j] = false;
            }
        }
    }
}

void Plansza::Kopiuj_populacje()
{
    for (int i = 0; i < liczba_komorek; i++)
    {
        for (int j = 0; j < liczba_komorek; j++)
        {
            populacja_obecna[i][j] = populacja_nastepna[i][j];
        }
    }
}

sf::RectangleShape Plansza::Zwroc_komorke(int x, int y)
{
    sf::RectangleShape cell;
    cell.setPosition(x * rozmiar_komorki, y * rozmiar_komorki);
    cell.setSize(vector);
    cell.setOutlineThickness(2);
    cell.setOutlineColor(sf::Color::Green);
    if (populacja_obecna[x][y])
    {
        cell.setFillColor(sf::Color::Black);
    }
    else
    {
        cell.setFillColor(sf::Color::White);
    }
    return cell;
}

void Plansza::Wyswietl_populacje(sf::RenderWindow& window)
{
    for (int i = 0; i < liczba_komorek; i++)
    {
        for (int j = 0; j < liczba_komorek; j++)
        {
            window.draw(Zwroc_komorke(i, j));
        }
    }
}

void Plansza::Inicjalizuj()
{
    sf::RenderWindow window(sf::VideoMode(rozmiar_komorki * liczba_komorek, rozmiar_komorki * liczba_komorek), "Gra w Zycie");
    window.setFramerateLimit(75);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (czy_zapauzowano && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                int x = float(event.mouseButton.x) / rozmiar_komorki;
                int y = float(event.mouseButton.y) / rozmiar_komorki;
                if (x >= 0 && x < liczba_komorek && y >= 0 && y < liczba_komorek)
                {
                    this->populacja_obecna[x][y] = !(this->populacja_obecna[x][y]);
                }
            }    
        }
        window.clear(sf::Color::White);
        Wyswietl_populacje(window);
        if (czy_zapauzowano == false)
        {
            Aktualizuj();
            Kopiuj_populacje();
        }
        window.display();
        sf::sleep(sf::milliseconds(100));
    }
}

