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
    sf::RenderWindow window(sf::VideoMode(cell_size * number_of_cells, cell_size * number_of_cells), "Game of Life - paused " + std::to_string(delay) + " ms delay", sf::Style::Titlebar | sf::Style::Close);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (paused && event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
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
        }

        window.clear(GRAY);
        Show_population(window);
        if (!paused)
        {
            Update();
            Copy_population();
            window.setTitle("Game of Life " + std::to_string(delay) + " ms delay");
            window.display();
            sf::sleep(sf::milliseconds(delay));
        }
        else
        {
            window.setTitle("Game of Life - paused " + std::to_string(delay) + " ms delay");
            window.display();
        }
    }
}

