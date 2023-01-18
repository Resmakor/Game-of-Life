# Game of Life

Conway's Game of Life - made for C++ Project at Rzeszow University of Technology.

#
# Simulation control
- To exit the program, close the console window or write ``STOP``.
- To pause the simulation or resume it, press the ``P`` key on the keyboard.
- To revive or kill a cell, press the ```left mouse button``` on the cell when the simulation is paused.
- To increase the delay between moves, press the ```upper arrow``` on the keyboard.
- To decrease the delay between moves, press the ```down arrow``` on the keyboard.
- To exit the current simulation, close the simulation window. After that it will be possible to initialize a new simulation with different parameters.

![](https://github.com/Resmakor/Game-of-Life/blob/main/example.gif)
#

# Class ```Simulation```

## Public methods

```cpp
Simulation();
```
- The default constructor.
```cpp
void Simulate();
```
- Displays the control and initializes the simulation with the ``Board`` object.
#
## Private methods

```cpp
void Get_correct_parameters();
```
- Gets the correct simulation parameters from the user.

```cpp
void Load(int& parameter);
```
- Helps to get the correct parameters from the user, sets the correct parameter by reference.

```cpp
bool Just_digits(std::string& input)const;
```
- Returns ``true`` if the text given in the input contains only digits, ``false`` otherwise.

```cpp
int Suggested_cell_size(int how_many_cells)const;
```
- Returns the most optimal single cell size in pixels for the given number of cells in a row (``how_many_cells``).
```cpp
void Display_control()const;
```
- Displays simulation control.
#

## Private members

```cpp
int cell_size;
```
- Information about the size of the cell in pixels.
```cpp
int number_of_cells;
```
- Information about the number of cells.
```cpp
int cells_to_draw;
```
- Information about the number of living cells to be drawn.
```cpp
int delay;
```
- Information about the delay between movements.

#

# Class ```Board```

## Constants
```cpp
#define CHANGE_OF_DELAY 50
```
- Change in delay by 50 ms.
```cpp
#define MAX_DELAY 2500
```
- Maximum delay (2500 ms).
```cpp
#define GRAY sf::Color(58, 58, 58)
```
- Gray color.
```cpp
#define BLACK sf::Color::Black
```
- Black color.
```cpp
#define GREEN sf::Color(0, 255, 127)
```
- Green color.
```cpp
#define OUTLINE_THICKNESS 1
```
- Outline thickness (1 pixel).
#


## Public methods
```cpp
Board(int how_many_cells=15, int what_size_cell=30, int delay=1);
```
- The default constructor - initializes the appropriate variables and two-dimensional arrays. In its arguments, it takes the number of cells in a row (15 by default), the size of the cell (in pixels, 30 by default) and the delay between moves (1 ms by default).
```cpp
~Board();
```
- Destructor - releases previously initialized two-dimensional arrays from memory.
```cpp
void Choose_random_fields(int fields);
```
- Selects ``fields`` of cells that will initially live.
```cpp
void Initialize();
```
- The main method, takes care of all the logic and the simulation window.

#

## Private methods
```cpp
void Show_population(sf::RenderWindow& window)const;
```
- Displays the population in the window.
```cpp
void Update();
```
- Creates a board that will be displayed in the next step of the simulation.
```cpp
void Copy_population();
```
- Copies the board created in the ``Update`` method to the one currently displayed in the window.
```cpp
sf::RectangleShape Return_cell(int x, int y)const;
```
- Returns a cell with ```x```, ```y``` coordinates of type ``sf::RectangleShape`` with attributes already set.
```cpp
int Number_of_neighbors(int x, int y)const;
```
- Returns the number of living neighbors of the cell with coordinates ```x```, ```y```.
#


## Private members
```cpp
const int number_of_cells;
```
- Information about the number of cells in a row.
```cpp
const int cell_size;
```
- Information about the size of a single cell in pixels.
```cpp
int delay;
```
- Information about the delay between movements.
```cpp
bool paused;
```
- Information on whether the simulation is paused.
```cpp
bool **current_population;
```
- A dynamic two-dimensional array that stores cell information.
```cpp
bool **next_population;
```
- A dynamic two-dimensional array needed to create the board that will be displayed in the next step of the simulation.

```cpp
sf::Vector2f vector;
```
- Used to set the cell size in the simulation window.

#
