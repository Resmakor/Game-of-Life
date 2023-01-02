#include "Plansza.h"

Plansza::Plansza(int ile_komorek, int jaki_rozmiar_komorki, int opoznienie) : liczba_komorek(ile_komorek), rozmiar_komorki(jaki_rozmiar_komorki)
{
   this->opoznienie = opoznienie;
   vector.x = rozmiar_komorki - OUTLINE_THICKNESS;
   vector.y = rozmiar_komorki - OUTLINE_THICKNESS;
   populacja_obecna = new bool* [liczba_komorek];
   populacja_nastepna = new bool* [liczba_komorek];
   czy_zapauzowano = true;
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
    if (i == 0)
    {
        return;
    }
    else if (i > liczba_komorek * liczba_komorek || i < 0)
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

int Plansza::Ile_sasiadow(int x, int y)const
{
    int sasiedzi = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < liczba_komorek && j >= 0 && j < liczba_komorek)
            {
                sasiedzi += int(populacja_obecna[i][j]);
            }
        }
    }
    return sasiedzi - int(populacja_obecna[x][y]);
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
            else if ((liczba_sasiadow == 2 || liczba_sasiadow == 3) && populacja_obecna[i][j])
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
        std::memcpy(populacja_obecna[i], populacja_nastepna[i], sizeof(bool) * liczba_komorek);
    }
}

sf::RectangleShape Plansza::Zwroc_komorke(int x, int y)const
{
    sf::RectangleShape komorka;
    komorka.setPosition(x * rozmiar_komorki, y * rozmiar_komorki);
    komorka.setSize(vector);
    komorka.setOutlineThickness(OUTLINE_THICKNESS);
    komorka.setOutlineColor(CZARNY);
    komorka.setFillColor(ZIELONY);
    return komorka;
}

void Plansza::Wyswietl_populacje(sf::RenderWindow& okno)const
{
    for (int i = 0; i < liczba_komorek; i++)
    {
        for (int j = 0; j < liczba_komorek; j++)
        {
            if (populacja_obecna[i][j])
            {
                okno.draw(Zwroc_komorke(i, j));
            }
        }
    }
}

void Plansza::Inicjalizuj()
{
    sf::RenderWindow okno(sf::VideoMode(rozmiar_komorki * liczba_komorek, rozmiar_komorki * liczba_komorek), "Gra w Zycie - zapauzowano " + std::to_string(opoznienie) + " ms opoznienia", sf::Style::Titlebar | sf::Style::Close);
    while (okno.isOpen())
    {
        sf::Event event;
        while (okno.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                okno.close();
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

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                czy_zapauzowano = !czy_zapauzowano;
            }

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                opoznienie += ZMIANA_OPOZNIENIA;
            }

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                if (opoznienie > ZMIANA_OPOZNIENIA)
                {
                    opoznienie -= ZMIANA_OPOZNIENIA;
                }

                else
                {
                    opoznienie = 1;
                }
            }
        }

        okno.clear(SZARY);
        Wyswietl_populacje(okno);
        if (!czy_zapauzowano)
        {
            Aktualizuj();
            Kopiuj_populacje();
            okno.setTitle("Gra w Zycie " + std::to_string(opoznienie) + " ms opoznienia");
            okno.display();
            sf::sleep(sf::milliseconds(opoznienie));
        }

        else
        {
            okno.setTitle("Gra w Zycie - zapauzowano " + std::to_string(opoznienie) + " ms opoznienia");
            okno.display();
        }
    }
}

