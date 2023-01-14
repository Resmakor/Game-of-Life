# Game of Life
 Conway's Game of Life - made for C++ Project at Rzeszów University of Technology

#
# Sterowanie symulacją
- Aby zakończyć program należy zamknąć okno konsoli albo napisać ```STOP```.
- Aby zatrzymać symulację lub ją wznowić należy wcisnąć klawisz ```P``` na klawiaturze.
- Aby ożywić lub zabić komórkę należy nacisnąć na komórkę lewym przyciskiem myszy gdy symulacja jest wstrzymana.
- Aby zwiększyć opóźnienie między ruchami należy wcisnąć górną strzałkę na klawiaturze.
- Aby zmniejszyć opóźnienie między ruchami należy wcisnąć dolną strzałkę na klawiaturze.
- Aby wyjść z obecnej symulacji należy zamknąć okno symulacji. Po tym będzie możliwe zainicjalizowanie nowej symulacji z innymi parametrami.

#

# Klasa ```Simulation```

## Publiczne metody

```cpp
Simulation();
```
- Konstruktor domyślny.
```cpp
void Simulate();
```
- Wyświetla sterowanie i inicjalizuje symulację obiektem ```Board```.
#
## Prywatne metody

```cpp
void Get_correct_parameters();
```
- Pobiera poprawne parametry symulacji od użytkownika.

```cpp
void Load(int& parameter);
```
- Pomaga w pobieraniu poprawnych parametrów od użytkownika, ustawia poprawny parametr poprzez referencję.

```cpp
bool Just_digits(std::string& input)const;
```
- Zwraca ```true``` jeżeli napis podany na wejściu zawiera tylko cyfry, ```false``` w przeciwnym wypadku.

```cpp
int Suggested_cell_size(int how_many_cells)const;
```
- Zwraca najbardziej optymalny rozmiar pojedynczej komórki w pikselach dla podanej liczby komórek w rzędzie (```how_many_cells```).
```cpp
void Display_control()const;
```
- Wyświetla sterowanie symulacją.
#

## Prywatne pola

```cpp
int cell_size;
```
- Informacja o rozmiarze komórki w pikselach.
```cpp
int number_of_cells;
```
- Informacja o liczbie komórek.
```cpp
int cells_to_draw;
```
- Informacja o liczbie żyjących komórek do wylosowania.
```cpp
int delay;
```
- Informacja o opóźnieniu między ruchami.

#

# Klasa ```Board```

## Stałe
```cpp
#define CHANGE_OF_DELAY 50
```
- Zmiana opóźnienia o 50 ms.
```cpp
#define MAX_DELAY 2500
```
- Maksymalne opóźnienie (2500 ms).
```cpp
#define GRAY sf::Color(58, 58, 58)
```
- Kolor szary.
```cpp
#define BLACK sf::Color::Black
```
- Kolor czarny.
```cpp
#define GREEN sf::Color(0, 255, 127)
```
- Kolor zielony.
```cpp
#define OUTLINE_THICKNESS 1
```
- Grubość obramowania (1 piksel).
#


## Publiczne metody
```cpp
Board(int how_many_cells=15, int what_size_cell=30, int delay=1);
```
- Konstruktor domyślny - inicjalizuje odpowiednie zmienne i tablice dwuwymiarowe. W argumentach przyjmuję liczbę komórek w rzędzie (domyślnie 15), rozmiar komórki (w pikselach, domyślnie 30) oraz opóźnienie między ruchami (domyślnie 1 ms).
```cpp
~Board();
```
- Destruktor - zwalnia z pamięci wcześniej zainicjalizowane tablice dwuwymiarowe.
```cpp
void Choose_random_fields(int fields);
```
- Wybiera ```fields``` komórek, które początkowo będą żyć.
```cpp
void Initialize();
```
- Główna metoda, zajmuje się całą logiką i oknem symulacji.

#

## Prywatne metody
```cpp
void Show_population(sf::RenderWindow& window)const;
```
- Wyświetla populację w oknie.
```cpp
void Update();
```
- Tworzy planszę, która będzie wyświetlona w kolejnym kroku symulacji.
```cpp
void Copy_population();
```
- Kopiuje planszę stworzoną w metodzie ```Update``` do obecnie wyświetlanej w oknie.
```cpp
sf::RectangleShape Return_cell(int x, int y)const;
```
- Zwraca komórkę o współrzędnych ```x```, ```y``` typu ```sf::RectangleShape``` z ustawionymi już atrybutami.
```cpp
int Number_of_neighbors(int x, int y)const;
```
- Zwraca liczbę żyjących sąsiadów komórki o współrzędnych ```x```, ```y```.
#


## Prywatne pola
```cpp
const int number_of_cells;
```
- Informacja o liczbie komórek w rzędzie.
```cpp
const int cell_size;
```
- Informacja o rozmiarze pojedynczej komórki w pikselach.
```cpp
int delay;
```
- Informacja o opóźnieniu między ruchami.
```cpp
bool paused;
```
- Informacja o tym czy symulacja jest wstrzymana.
```cpp
bool **current_population;
```
- Dynamiczna tablica dwuwymiarowa przechowująca informację o komórkach.
```cpp
bool **next_population;
```
- Dynamiczna tablica dwuwymiarowa potrzebna by stworzyć planszę, która zostanie wyświetlona w kolejnym kroku symulacji.

```cpp
sf::Vector2f vector;
```
- Używane, by ustawić rozmiar komórki w oknie symulacji.

#