#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <cstdlib>
using namespace std;

void clearScreen()
{
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX (Linux/macOS)
	std::system("clear");
#endif
}
/*
class QueueingFunction{ // FIX THIS NEXT
	class nodes{

	};
	makeQueue
	public:
		vector<nodes> nodelist;
};

string generalSearch(vector<vector<int>> currentState) {// FIX THIS NEXT
	nodelist = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))  
	while(true){ 
		if EMPTY(nodes) return "failure"  
		node = REMOVE-FRONT(nodes)  
		if problem.GOAL-TEST(node.STATE) succeeds then return node 
		nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))   
	}
}
	*/
class Puzzle{
	vector<vector<int>> InitialState = {
			{1, 2, 3},
			{4, 5, 6},
			{7, 0, 8}};
	vector<vector<int>> GoalState = {
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 0}};
	vector<vector<int>> builder(int size); /*user inputs a size of Puzzle and outputs a vector of vector of ints 
	where rows is the x axis and y is the columns. 
	valid inputs are any integer in this postive expression 2^n -1 besides n=0,1. It builds the 2d vector with values
	from 0-(n-1), n-1 being the size of the array. values are assigned randomly. 0 will be the empty square.*/
	void PuzzlePrinter(const vector<vector<int>> &currentPuzzle)
	{
		for (int row = 0; row < currentPuzzle.size(); row++)
		{
			for (int column = 0; column < currentPuzzle.at(0).size(); column++)
			{
				cout << "" << currentPuzzle[row][column] << " ";
			}
			cout << endl;
		}
	}
};

void squareSwapper(vector<vector<int>>& currentPuzzle, const int position1, const int position2){
	/* positions
	0/1/2
	3/4/5
	6/7/8*/
	if (position1 < 0 || 9 <= position1){
		throw out_of_range("Position 1 out of range");
	}
	if (position2 < 0 || 9 <= position2){
		throw out_of_range("Position 2 out of range");
	}
	int tempValue = -1;
	tempValue = currentPuzzle[position1/3][position1%3];
	currentPuzzle[position1 / 3][position1 %3] = currentPuzzle[position2 / 3][position2 %3];
	currentPuzzle[position2 / 3][position2 %3] = tempValue;
}

int main()
{
	/* 
	Main should ask the user to play or for an AI to solve it or to quit Puzzle.
	for both user and AI, build a random Puzzle. For user,
	Ask what move of the 4 potential ones that the blank square can go while displaying the current
	state of the Puzzle. Once selected,
	swap the blank square with the square in the selected direction. Repeat. For AI, it will run
	the general search algorithm and display how fast it was able to be solved in seconds.
	For both when they reach the goal state, ask to return to main menu or quit Puzzle.*/
	char userInput;
	Puzzle puzzleInstance;
	while (true)
	{
		cout << "8's Puzzle!!! Wanna play (p) or want an ai to complete one (a)?: ";
		cin >> userInput;
		if (userInput == 'p')
		{
			cout << "Playing game.\n";
			cout << "{1,2,3}\n{4,5,6}\n{7,8,0}\n";
		}
		else if (userInput == 'a')
		{
			cout << "AI playing game.\n";
		}
		else
		{
			cout << "Wrong input, try again!\n";
			continue;
		}
		cout << "Want to return to main menu? Yes (y) or Quit (q): ";
		while (true){
			cin >> userInput;
			if (userInput == 'y')
			{
				break;
			}
			else if (userInput == 'q')
			{
				return 0;
			}
			else{
				cout<<"Wrong input, try again!\n";
				continue;
			}
		}
	}
	return 0;
}

/* This is the templete for my version of general search:
	function general-search(problem, QUEUEING-FUNCTION){
	nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))  
	loop do 
	if EMPTY(nodes) then return "failure"  
	node = REMOVE-FRONT(nodes)  
	if problem.GOAL-TEST(node.STATE) succeeds then return node 
	nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))   
	end
}*/