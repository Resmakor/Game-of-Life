#pragma once
#include "Board.h"
#include <string>

class Simulation
{
	int cell_size;
	int number_of_cells;
	int cells_to_draw;
	int delay;
	void Get_correct_parameters();
	void Load(int& parameter);
	bool Just_digits(std::string& input)const;
	int Suggested_cell_size(int how_many_cells)const;
	void Display_control()const;
public:
	Simulation();
	void Simulate();
};