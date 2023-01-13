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
	void Get_correct_parameters();
	void Load(int& parameter);
	void Display_control()const;
	void Simulate();
	bool Just_digits(std::string& input)const;
	int Suggested_cell_size(int number_of_cells)const;
};