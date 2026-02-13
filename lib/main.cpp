#include <iostream>
#include <cstdlib>
#include "../Headers/Puzzle.hpp"
#include "../Headers/Solver.hpp"

using namespace std;

int main()
{
	int userInput;

	while (true)
	{
		Puzzle game;
		MainMenu:
		cout << "Welcome to 8-Puzzle Solver!" << endl
					<< "1. To play a random puzzle" << endl
					<< "2. To create your own puzzle" << endl
					<< "3. Quit" << endl
					<< "Choice (from here on out enter number ): ";
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			game.shufflePuzzle(31);
			break;
		case 2:{
			unsigned const int PUZZLESIZE = 3;
			vector<vector<int>> rowList(PUZZLESIZE);
			vector<int> incomingInts(PUZZLESIZE);
			cout << "Enter your puzzle, using a zero to represent the empty square. Please only enter valid 8-puzzles."<<endl
					 << "Enter the puzzle demilimiting the numbers with a space. Type  RETURN only when" << endl
					 << "finished." <<endl;
			for(unsigned int i = 1; i<=rowList.size(); i++){
				cout << "Enter row "<<i<<": ";
				for (unsigned int j = 0; j < incomingInts.size(); j++)
				{
					cin >> userInput;
					incomingInts.at(j) = userInput;
				}
				cout<<endl;
			}
			game = rowList;
			}break;
		case 3:
			return 0;
		default:
			cout<<"Incorrect Character!"<<endl<<endl;
			goto MainMenu;
		}
		
		cout << "Who is solving?" << endl
				 << "1. Play Yourself" << endl
				 << "2. Let AI Solve" << endl
				 << "3. Quit" << endl
				 << "Choice: ";
		cin >> userInput;

		if (userInput == 3)
			return 0;

		if (userInput == 1)
		{
			while (!game.isGoal())
			{
				game.printBoard();
				//I chose these numbers since it corresponded to the numpad
				cout << "Move: Up (8), Down (2), Left (4), Right (6), Quit to Menu (0): ";
				cin >> userInput;

				bool moved = false;
				
				switch (userInput)
				{
				case 8:
					moved = game.moveUp();
					break;
				case 2:
					moved = game.moveDown();
					break;
				case 4:
					moved = game.moveLeft();
					break;
				case 6:
					moved = game.moveRight();
					break;
				case 0:
					goto end_game;
				default:
					cout << "Invalid input." << endl;
				}

				if (!moved && userInput != 0)
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
		else if (userInput == 2)
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
				cout << "Invalid algorithm selection. Returning to Main Menu..." << endl;
				goto MainMenu;
			}
			
			cout << "Initial Random State:" << endl;
			game.printBoard();

			solveAI(game, algoChoice);
		}
		else
		{
			cout << "Invalid selection." << endl;
			continue;
		}

	end_game:
		cout << "\nPress 1 to return to menu, or 0 to quit: ";
		cin >> userInput;
		if (userInput == 0)
			return 0;
		
	}
	return 0;
}