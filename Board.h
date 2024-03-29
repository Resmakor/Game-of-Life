#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>

#define CHANGE_OF_DELAY 50
#define MAX_DELAY 2500
#define GRAY sf::Color(58, 58, 58)
#define BLACK sf::Color::Black
#define GREEN sf::Color(0, 255, 127)
#define OUTLINE_THICKNESS 1

class Board
{
	const int number_of_cells;
	const int cell_size;
	int delay;
	bool paused;
	bool **current_population;
	bool **next_population;
	sf::Vector2f vector;
	void Show_population(sf::RenderWindow& window)const;
	void Update();
	void Copy_population();
	sf::RectangleShape Return_cell(int x, int y)const;
	int Number_of_neighbors(int x, int y)const;
public:
	Board(int how_many_cells=15, int what_size_cell=30, int delay=1);
	~Board();
	void Choose_random_fields(int fields);
	void Initialize();
	
};

