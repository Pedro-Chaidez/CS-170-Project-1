#include <string>
#include <vector>
#include <iostream>
#include "../Headers/8PuzzleAIAlgorithm.h++"
using namespace std;

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
class puzzle{
	vector<vector<int>> builder(int size); /*user inputs a size of puzzle and outputs a vector of vector of ints 
	where rows is the x axis and y is the columns. 
	valid inputs are any integer in this postive expression 2^n -1 besides n=0,1. It builds the 2d vector with values
	from 0-(n-1), n-1 being the size of the array. values are assigned randomly. 0 will be the empty square.*/
	string outputCurrentState(); //outputs a string of the current state of vector<vector<node>>
	
};

class UIBuilder{//This class should take in a string and output it in the terminal in a Certain format
	void clearTerminal(); //This should clear terminal everytime a new screen is prompted

};

int main(){
	/* 
	Main should ask the user to play or for an AI to solve it or to quit puzzle.
	for both user and AI, build a random puzzle. For user,
	Ask what move of the 4 potential ones that the blank square can go while displaying the current
	state of the puzzle. Once selected,
	swap the blank square with the square in the selected direction. Repeat. For AI, it will run
	the general search algorithm and display how fast it was able to be solved in seconds.
	For both when they reach the goal state, ask to return to main menu or quit puzzle.*/
	char userInput;
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