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
	bool isPlaying = 0;
	int zeroPosition = -1;
	vector<vector<int>> InitialState = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 0, 8}};
	vector<vector<int>> GoalState = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}};
	int findZeroLocation()
	{
		for (unsigned int row = 0; row < InitialState.size(); row++)
		{
			for (unsigned int column = 0; column < InitialState.at(0).size(); column++)
			{
				if (InitialState[row][column] == 0)
				{
					return row * 3 + column;
				}
			}
		}
	}
	void winChecker()
	{
		if (InitialState == GoalState)
		{
			isPlaying = 0;
		}
		else
		{
			isPlaying = 1;
		}
	}
	void squareSwapper(const int position1, const int position2)
	{
		/* positions
		0/1/2
		3/4/5
		6/7/8*/
		if (position1 < 0 || 9 <= position1)
		{
			throw out_of_range("Position 1 out of range");
		}
		if (position2 < 0 || 9 <= position2)
		{
			throw out_of_range("Position 2 out of range");
		}
		int tempValue = -1;
		tempValue = InitialState[position1 / 3][position1 % 3];
		InitialState[position1 / 3][position1 % 3] = InitialState[position2 / 3][position2 % 3];
		InitialState[position2 / 3][position2 % 3] = tempValue;
		winChecker();
		zeroPosition = findZeroLocation();
	}
	public:
		Puzzle() : 
			isPlaying(1), 
			zeroPosition(findZeroLocation())
		{}
		void PuzzlePrinter() const
		{
			for (unsigned int row = 0; row < InitialState.size(); row++)
			{
				for (unsigned int column = 0; column < InitialState.at(0).size(); column++)
				{
					cout << "" << InitialState[row][column] << " ";
				}
				cout << endl;
			}
		}
		void moveBlankSquareUp()
		{
			if (zeroPosition % 3 == 0)
			{
				throw out_of_range("Can't move a blank past the first row");
			}
			else
			{
				squareSwapper(zeroPosition, zeroPosition-3);
			}
		}
		void moveBlankSquareLeft()
		{
			if (zeroPosition / 3 == 0)
			{
				throw out_of_range("Can't move a blank past the first row");
			}
			else
			{
				squareSwapper(zeroPosition, zeroPosition - 1);
			}
		}
		void moveBlankSquareDown()
		{
			if (zeroPosition % 3 == 2)
			{
				throw out_of_range("Can't move a blank past the first row");
			}
			else
			{
				squareSwapper(zeroPosition, zeroPosition + 3);
			}
		}
		void moveBlankSquareRight()
		{
			if (zeroPosition / 3 == 0)
			{
				throw out_of_range("Can't move a blank past the first row");
			}
			else
			{
				squareSwapper(zeroPosition, zeroPosition - 3);
			}
		}
		bool getIsPlaying() const{
			return isPlaying;
		}
};

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
		cout << "8's Puzzle!!! Wanna play (p) or want an ai to complete one (a)? or quit (q): ";
		cin >> userInput;
		if (userInput == 'p')
		{
			clearScreen();
			while(puzzleInstance.getIsPlaying()){
				puzzleInstance.PuzzlePrinter();
				cout<<endl<<"Where would to you like to slide the white tile?: Up (u), Down(d), Left (l), Right (r), or Quit (q): ";
				cin>>userInput;
				clearScreen();
				switch (userInput)
				{
				case 'u':
					puzzleInstance.moveBlankSquareUp();
					break;
				case 'd':
					puzzleInstance.moveBlankSquareDown();
					break;
				case 'l':
					puzzleInstance.moveBlankSquareLeft();
					break;
				case 'r':
					puzzleInstance.moveBlankSquareRight();
					break;
				case 'q':
					return 0;
				default:
					cout << "Wrong Input, please try again!" << endl;
				}
			}
		}
		else if (userInput == 'a')
		{
			cout << "AI playing game.\n";
		}
		else if (userInput == 'q'){
			return 0;
		}
		else
		{
			clearScreen();
			cout << "Wrong input, try again!\n";
			continue;
		}		
		while (true){
			cout << "Game Finished! Want to return to main menu? Yes (y) or Quit (q): ";
			cin >> userInput;
			cout<<endl;
			if (userInput == 'y')
			{
				clearScreen();
				break;
			}
			else if (userInput == 'q')
			{
				return 0;
			}
			else{
				clearScreen();
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