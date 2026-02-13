#include "../Headers/Puzzle.hpp"
#include <algorithm> // for std::swap
#include <cstdlib>	 // for rand, srand
#include <ctime>		 // for time

using namespace std;

void Puzzle::updateZeroPosition()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (state[r][c] == 0)
			{
				zeroRow = r;
				zeroCol = c;
				return;
			}
		}
	}
}

// Rule of Three
Puzzle::Puzzle()
{
	state = goalState;
	updateZeroPosition();
}
Puzzle::Puzzle(const Puzzle &other)
	:state(other.state),
	zeroRow(other.zeroRow),
	zeroCol(other.zeroCol)
{}
Puzzle& Puzzle::operator=(const Puzzle &other){
	if (this != &other) {
		state = other.state;
		zeroRow = other.zeroRow;
		zeroCol = other.zeroCol;
	}
	return *this;
}
// Sets a new puzzle with vector
Puzzle &Puzzle::operator=(const vector<vector<int>> &s)
{
	state = s;
	updateZeroPosition();
	return *this;
}
// Constructs a Puzzle with vector
Puzzle::Puzzle(vector<vector<int>> s) : state(s)
{
	updateZeroPosition();
}

vector<vector<int>> Puzzle::getState() const
{
	return state;
}

bool Puzzle::isGoal() const
{
	return state == goalState;
}

void Puzzle::printBoard() const
{
	cout << "-------------" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "| ";
		for (int j = 0; j < 3; j++)
		{
			if (state[i][j] == 0)
				cout << "  | ";
			else
				cout << state[i][j] << " | ";
		}
		cout << endl
				 << "-------------" << endl;
	}
}

bool Puzzle::moveUp()
{
	if (zeroRow > 0)
	{
		swap(state[zeroRow][zeroCol], state[zeroRow - 1][zeroCol]);
		zeroRow--;
		return true;
	}
	return false;
}

bool Puzzle::moveDown()
{
	if (zeroRow < 2)
	{
		swap(state[zeroRow][zeroCol], state[zeroRow + 1][zeroCol]);
		zeroRow++;
		return true;
	}
	return false;
}

bool Puzzle::moveLeft()
{
	if (zeroCol > 0)
	{
		swap(state[zeroRow][zeroCol], state[zeroRow][zeroCol - 1]);
		zeroCol--;
		return true;
	}
	return false;
}

bool Puzzle::moveRight()
{
	if (zeroCol < 2)
	{
		swap(state[zeroRow][zeroCol], state[zeroRow][zeroCol + 1]);
		zeroCol++;
		return true;
	}
	return false;
}

void Puzzle::shufflePuzzle(int moves)
{
	if (moves <= 0)
		return;

	srand(time(0));
	for (int i = 0; i < moves; i++)
	{
		int r = rand() % 4;
		switch (r)
		{
		case 0:
			moveUp();
			break;
		case 1:
			moveDown();
			break;
		case 2:
			moveLeft();
			break;
		case 3:
			moveRight();
			break;
		}
	}
}