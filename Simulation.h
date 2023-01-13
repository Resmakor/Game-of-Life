#pragma once
#include "Board.h"
#include <string>
#include <locale.h>

class Simulation
{
	int cell_size;
	int number_of_cells;
	int cells_to_draw;
	int delay;
public:
	Simulation();
	bool Just_digits(std::string& input)const;
	void Get_correct_parameters();
	void Load(int& parameter);
	int Suggested_cell_size(int number_of_cells)const;
	void Display_control()const;
	void Simulate();
};