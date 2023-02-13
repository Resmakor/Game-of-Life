#include "Board.h"

Board::Board(int how_many_cells, int what_size_cell, int delay) : number_of_cells(how_many_cells), cell_size(what_size_cell)
{
   this->delay = delay;
   paused = true;
   vector.x = cell_size - OUTLINE_THICKNESS;
   vector.y = cell_size - OUTLINE_THICKNESS;
   current_population = new bool* [number_of_cells];
   next_population = new bool* [number_of_cells];
   for (int i = 0; i < number_of_cells; i++)
   {
       current_population[i] = new bool[number_of_cells];
       memset(current_population[i], false, number_of_cells * sizeof(bool));
       next_population[i] = new bool[number_of_cells];
       memset(next_population[i], false, number_of_cells * sizeof(bool));
   }
}

Board::~Board()
{
    for (int i = 0; i < number_of_cells; i++)
    {
        delete[] current_population[i];
        delete[] next_population[i];
    }
    delete[] current_population;
    delete[] next_population;
}

/* Method chooses how many random fields at the start will live */
void Board::Choose_random_fields(int fields)
{
    if (fields == 0 || fields > number_of_cells * number_of_cells) return;
    srand(time(0));
    int living_cells_counter = 0, temp_x, temp_y;
    while (living_cells_counter != fields)
    {
        temp_x = rand() % number_of_cells;
        temp_y = rand() % number_of_cells;
        if (temp_x >= 0 && temp_y >= 0 && temp_x < number_of_cells && temp_y < number_of_cells)
        {
            if (current_population[temp_x][temp_y] == false)
            {
                current_population[temp_x][temp_y] = true;
                living_cells_counter++;
            }
        }
    }
}

/* Method returns how many living neighbors a cell has */
int Board::Number_of_neighbors(int x, int y)const
{
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < number_of_cells && j >= 0 && j < number_of_cells)
            {
                neighbors += int(current_population[i][j]);
            }
        }
    }
    return neighbors - int(current_population[x][y]);
}

/* Method returns number of living cells */
int Board::Number_of_living_cells()const
{
    int alive = 0;
    for (int x = 0; x < number_of_cells; x++)
    {
        for (int y = 0; y < number_of_cells; y++)
        {
            if (current_population[x][y])
                alive++;
        }
    }
    return alive;
}


/* The method is used to update the board according to the given rules */
void Board::Update()
{
    for (int x = 0; x < number_of_cells; x++)
    {
        for (int y = 0; y < number_of_cells; y++)
        {
            int neighbors = Number_of_neighbors(x, y);
            if (neighbors == 3 && current_population[x][y] == false)
            {
                next_population[x][y] = true;
            }
            else if ((neighbors == 2 || neighbors == 3) && current_population[x][y])
            {
                next_population[x][y] = true;
            }
            else
            {
                next_population[x][y] = false;
            }
        }
    }
}

/* The method copies the updated population */
void Board::Copy_population()
{
    for (int i = 0; i < number_of_cells; i++)
    {
        std::memcpy(current_population[i], next_population[i], sizeof(bool) * number_of_cells);
    }
}

/* Method returns a cell with attributes already set */
sf::RectangleShape Board::Return_cell(int x, int y)const
{
    sf::RectangleShape cell;
    cell.setPosition(x * cell_size, y * cell_size);
    cell.setSize(vector);
    cell.setOutlineThickness(OUTLINE_THICKNESS);
    cell.setOutlineColor(BLACK);
    cell.setFillColor(GREEN);
    return cell;
}

/* The method displays the population */
void Board::Show_population(sf::RenderWindow& window)const
{
    for (int x = 0; x < number_of_cells; x++)
    {
        for (int y = 0; y < number_of_cells; y++)
        {
            if (current_population[x][y])
            {
                window.draw(Return_cell(x, y));
            }
        }
    }
}

/* Main method, takes care of all the logic and the simulation window */
void Board::Initialize()
{
    int living_cells = Number_of_living_cells();
    sf::RenderWindow window(sf::VideoMode(cell_size * number_of_cells, cell_size * number_of_cells), "Game of Life - paused " + std::to_string(delay) + " ms delay , living cells: " + std::to_string(living_cells), sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                int x = float(event.mouseButton.x) / cell_size;
                int y = float(event.mouseButton.y) / cell_size;
                if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
                {
                    current_population[x][y] = !(current_population[x][y]);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                paused = !paused;
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                if (delay + CHANGE_OF_DELAY <= MAX_DELAY)
                {
                    delay += CHANGE_OF_DELAY;
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                if (delay > CHANGE_OF_DELAY)
                {
                    delay -= CHANGE_OF_DELAY;
                }
                else
                {
                    delay = 1;
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_1(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_2(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_3(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_4(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_5(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_6(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num7)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_7(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_8(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num9)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_9(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0)
            {
                sf::Vector2i mousePositionRelative = sf::Mouse::getPosition(window);
                Show_pattern_0(mousePositionRelative.x / cell_size, mousePositionRelative.y / cell_size);
            }
        }

        window.clear(GRAY);
        Show_population(window);
        living_cells = Number_of_living_cells();
        if (living_cells == 0)
        {
            paused = true;
        }
        if (!paused)
        {
            Update();
            Copy_population();
            window.setTitle("Game of Life " + std::to_string(delay) + " ms delay, living cells: " + std::to_string(living_cells));
            window.display();
            sf::sleep(sf::milliseconds(delay));
        }
        else
        {
            window.setTitle("Game of Life - paused " + std::to_string(delay) + " ms delay, living cells: " + std::to_string(living_cells));
            window.display();
        }
    }
}


/* Square */
void Board::Show_pattern_1(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = true;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = true;
}

/* Glider */
void Board::Show_pattern_2(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = true;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = false;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = false;
}

/* LWSS */
void Board::Show_pattern_3(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = false;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = true;
    if (x >= 0 && x < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x][y + 3] = true;


    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 1][y + 3] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 2][y + 3] = true;

    if (x + 3 >= 0 && x + 3 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 3][y] = false;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 3][y + 1] = false;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 3][y + 2] = false;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 3][y + 3] = true;

    if (x + 4 >= 0 && x + 4 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 4][y] = true;
    if (x + 4 >= 0 && x + 4 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 4][y + 1] = false;
    if (x + 4 >= 0 && x + 4 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 4][y + 2] = true;
    if (x + 4 >= 0 && x + 4  < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 4][y + 3] = false;

}

/* Frog */
void Board::Show_pattern_4(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = false;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = true;
    
    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = true;

    if (x + 3 >= 0 && x + 3 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 3][y] = true;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 3][y + 1] = false;


}

/* Blinker */
void Board::Show_pattern_5(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = true;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = true;
}

/* Crocodile */
void Board::Show_pattern_6(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = true;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = true;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = true;

    if (x + 3 >= 0 && x + 3 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 3][y] = true;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 3][y + 1] = true;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 3][y + 2] = true;

    if (x + 4 >= 0 && x + 4 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 4][y] = true;
    if (x + 4 >= 0 && x + 4 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 4][y + 1] = true;
    if (x + 4 >= 0 && x + 4 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 4][y + 2] = true;

    if (x + 5 >= 0 && x + 5 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 5][y] = true;
    if (x + 5 >= 0 && x + 5 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 5][y + 1] = true;
    if (x + 5 >= 0 && x + 5 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 5][y + 2] = true;

    if (x + 6 >= 0 && x + 6 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 6][y] = true;
    if (x + 6 >= 0 && x + 6 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 6][y + 1] = false;
    if (x + 6 >= 0 && x + 6 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 6][y + 2] = true;

    if (x + 7 >= 0 && x + 7 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 7][y] = true;
    if (x + 7 >= 0 && x + 7 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 7][y + 1] = true;
    if (x + 7 >= 0 && x + 7 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 7][y + 2] = true;
}

/* Boat */
void Board::Show_pattern_7(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = true;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = false;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = false;
}


/* Loaf */
void Board::Show_pattern_8(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = false;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = true;
    if (x >= 0 && x < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x][y + 3] = false;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 1][y + 3] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 2][y + 3] = false;

    if (x + 3 >= 0 && x + 3 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 3][y] = false;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 3][y + 1] = true;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 3][y + 2] = false;
    if (x + 3 >= 0 && x + 3 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 3][y + 3] = false;
}

/* Crystal */
void Board::Show_pattern_9(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = false;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = true;
    if (x >= 0 && x < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x][y + 3] = false;


    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 1][y + 3] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 3 >= 0 && y + 3 < number_of_cells)
        current_population[x + 2][y + 3] = false;
}

/* Clover */
void Board::Show_pattern_0(int x, int y)
{
    if (x >= 0 && x < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x][y] = false;
    if (x >= 0 && x < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x][y + 1] = true;
    if (x >= 0 && x < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x][y + 2] = false;

    if (x + 1 >= 0 && x + 1 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 1][y] = true;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 1][y + 1] = false;
    if (x + 1 >= 0 && x + 1 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 1][y + 2] = true;

    if (x + 2 >= 0 && x + 2 < number_of_cells && y >= 0 && y < number_of_cells)
        current_population[x + 2][y] = false;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 1 >= 0 && y + 1 < number_of_cells)
        current_population[x + 2][y + 1] = true;
    if (x + 2 >= 0 && x + 2 < number_of_cells && y + 2 >= 0 && y + 2 < number_of_cells)
        current_population[x + 2][y + 2] = false;
}