#include "Simulation.h"

Simulation::Simulation()
{
	Get_correct_parameters();
}

/* The method gets correct simulation parameters from user */
void Simulation::Get_correct_parameters()
{	
	system("cls");
	std::cout << "========================================= Game of Life =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "				TYPE 'STOP' TO END THE PROGRAM " << std::endl;
	std::cout << std::endl;

	std::cout << "	ENTER THE NUMBER OF CELLS IN A ROW (RECOMMENDED NUMBER 3 - 200): ";
	Load(number_of_cells);
	while (number_of_cells < 2 || Suggested_cell_size(number_of_cells) < 2)
	{
		std::cout << "	ERROR! ENTER ANOTHER VALUE: ";
		Load(number_of_cells);
	}
	cell_size = Suggested_cell_size(number_of_cells);

	std::cout << "	ENTER HOW MANY LIVING CELLS TO DRAW (0 - " << number_of_cells * number_of_cells << "): ";
	Load(cells_to_draw);
	while (cells_to_draw < 0 || cells_to_draw > number_of_cells * number_of_cells)
	{
		std::cout << "	ERROR! ENTER ANOTHER VALUE: ";
		Load(cells_to_draw);
	}

	std::cout << "	ENTER THE DELAY BETWEEN MOVES (1 - " <<  MAX_DELAY << " ms): ";
	Load(delay);
	while (delay < 1 || delay > MAX_DELAY)
	{
		std::cout << "	ERROR! ENTER ANOTHER VALUE: ";
		Load(delay);
	}
}

/* The method loads the correct input data (int) */
void Simulation::Load(int& parameter)
{
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (input == "STOP")
		{
			exit(0);
		}
		else if (Just_digits(input))
		{
			parameter = std::stoi(input);
			break;
		}
		else
		{
			std::cout << "	ERROR! ENTER ANOTHER VALUE: ";
		}
	}
}

/* The method returns whether there are digits alone in a variable of type string */
bool Simulation::Just_digits(std::string& input)const
{
	int input_size = input.size();
	if (input_size == 0 || input_size > 8)
	{
		return false;
	}
	for (int i = 0; i < input_size; i++)
	{
		if (input[i] < '0' || input[i] > '9')
		{
			return false;
		}
	}
	return true;
}

/* The method returns the optimal size of a single cell (px) */
int Simulation::Suggested_cell_size(int how_many_cells)const
{
	if (how_many_cells < 2)
	{
		return 0;
	}
	int minimal = std::min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	minimal *= 0.9;
	return  minimal / how_many_cells;
}

/* The method displays how to control the simulation */
void Simulation::Display_control()const
{
	system("cls");
	std::cout << "========================================= CONTROL =========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "	TO EXIT THE CURRENT SIMULATION CLOSE THE SIMULATION WINDOW" << std::endl;
	std::cout << "	TO REVIVE/KILL A CELL PRESS THE LEFT MOUSE BUTTON ON IT WHILE PAUSED" << std::endl;
	std::cout << "	TO PAUSE/RESUME SIMULATION PRESS 'P' KEY" << std::endl;
	std::cout << "	TO INCREASE/DECREASE THE DELAY PRESS THE UP/DOWN ARROW KEY" << std::endl;
	std::cout << std::endl;
	std::cout << "===========================================================================================" << std::endl;
}

/* The method displays the control and then starts the simulation */
void Simulation::Simulate()
{
	Display_control();
	Board board(number_of_cells, cell_size, delay);
	board.Choose_random_fields(cells_to_draw);
	board.Initialize();
}
