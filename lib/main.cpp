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
		Puzzle game;

		cout << "8-Puzzle Solver Main Menu" << endl
				 << "1. Play Yourself (p)" << endl
				 << "2. Let AI Solve (a)" << endl
				 << "3. Quit (q)" << endl
				 << "Choice: ";
		cin >> userInput;

		if (userInput == 'q')
			return 0;

		// Shuffle board (25 moves to ensure it's solvable but not too easy)
		// Pass 0 if you want to test the goal state immediately
		game.shufflePuzzle(25);

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
			clearScreen();
			cout << "Initial Random State:" << endl;
			game.printBoard();
			solveAI(game);
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