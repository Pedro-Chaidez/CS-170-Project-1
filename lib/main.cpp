#include <iostream>
#include <cstdlib>
#include "../Headers/Puzzle.hpp"
#include "../Headers/Solver.hpp"

using namespace std;

// Helper function to clear console
void clearScreen()
{
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

int main()
{
	char userInput;

	while (true)
	{
		// Setup new game
		Puzzle game({{0,7,2},{4,6,1},{3,5,8}});

		cout << "8-Puzzle Solver Main Menu" << endl
				 << "1. Play Yourself (p)" << endl
				 << "2. Let AI Solve (a)" << endl
				 << "3. Quit (q)" << endl
				 << "Choice: ";
		cin >> userInput;

		if (userInput == 'q')
			return 0;

		// Shuffle board (25 moves to ensure it's solvable but not too easy)
		game.shufflePuzzle(31);

		if (userInput == 'p')
		{
			clearScreen();
			while (!game.isGoal())
			{
				game.printBoard();
				cout << "Move: Up (u), Down (d), Left (l), Right (r), Quit to Menu (q): ";
				cin >> userInput;

				bool moved = false;
				clearScreen();

				switch (userInput)
				{
				case 'u':
					moved = game.moveUp();
					break;
				case 'd':
					moved = game.moveDown();
					break;
				case 'l':
					moved = game.moveLeft();
					break;
				case 'r':
					moved = game.moveRight();
					break;
				case 'q':
					goto end_game;
				default:
					cout << "Invalid input." << endl;
				}

				if (!moved && userInput != 'q')
				{
					cout << "Cannot move that way!" << endl;
				}
			}
			if (game.isGoal())
			{
				game.printBoard();
				cout << "\nCONGRATULATIONS! You solved the puzzle!\n";
			}
		}
		else if (userInput == 'a')
		{
			// Algorithm Selection Menu
			int algoChoice;
			cout << "\nSelect Algorithm:" << endl;
			cout << "1. Uniform Cost Search" << endl;
			cout << "2. A* with Misplaced Tile Heuristic" << endl;
			cout << "3. A* with Manhattan Distance Heuristic" << endl;
			cout << "Choice (1-3): ";
			cin >> algoChoice;

			if (algoChoice < 1 || algoChoice > 3)
			{
				cout << "Invalid algorithm selection. Defaulting to Manhattan." << endl;
				algoChoice = 3;
			}

			clearScreen();
			cout << "Initial Random State:" << endl;
			game.printBoard();

			solveAI(game, algoChoice);
		}
		else
		{
			clearScreen();
			cout << "Invalid selection." << endl;
			continue;
		}

	end_game:
		cout << "\nPress 'y' to return to menu, or 'q' to quit: ";
		cin >> userInput;
		if (userInput == 'q')
			return 0;
		clearScreen();
	}
	return 0;
}