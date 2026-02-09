#include "../Headers/Solver.hpp"
#include <queue>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;

// Heuristic: Manhattan Distance
// (Kept internal to this file as it's a helper for the solver)
int calculateManhattan(const vector<vector<int>> &state)
{
	int distance = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int value = state[r][c];
			if (value != 0)
			{
				// Expected position of value (1 at 0,0; 2 at 0,1; etc.)
				int targetR = (value - 1) / 3;
				int targetC = (value - 1) % 3;
				distance += abs(r - targetR) + abs(c - targetC);
			}
		}
	}
	return distance;
}

void solveAI(Puzzle &initialPuzzle)
{
	cout << "AI is thinking..." << endl;

	// Priority queue stores nodes to visit, ordered by lowest cost
	priority_queue<Node, vector<Node>, greater<Node>> frontier;

	// Set to keep track of visited states to prevent loops
	set<vector<vector<int>>> visited;

	// Initial Node
	Node startNode;
	startNode.state = initialPuzzle.getState();
	startNode.g = 0;
	startNode.h = calculateManhattan(startNode.state);
	startNode.path = "";

	frontier.push(startNode);
	visited.insert(startNode.state);

	int nodesExpanded = 0;

	while (!frontier.empty())
	{
		// Pop the best node
		Node current = frontier.top();
		frontier.pop();
		nodesExpanded++;

		// Goal Test
		Puzzle p(current.state);
		if (p.isGoal())
		{
			cout << "AI Solved it!" << endl;
			cout << "Nodes Expanded: " << nodesExpanded << endl;
			cout << "Solution Depth: " << current.g << endl;
			cout << "Path: " << current.path << endl;

			// Show the result
			cout << "\nFinal State:" << endl;
			p.printBoard();
			return;
		}

		// Expand Neighbors (Up, Down, Left, Right)
		auto tryMove = [&](string moveName)
		{
			Puzzle tempP(current.state);
			bool valid = false;

			if (moveName == "U")
				valid = tempP.moveUp();
			else if (moveName == "D")
				valid = tempP.moveDown();
			else if (moveName == "L")
				valid = tempP.moveLeft();
			else if (moveName == "R")
				valid = tempP.moveRight();

			if (valid)
			{
				vector<vector<int>> newState = tempP.getState();
				if (visited.find(newState) == visited.end())
				{
					Node neighbor;
					neighbor.state = newState;
					neighbor.g = current.g + 1;
					neighbor.h = calculateManhattan(newState);
					neighbor.path = current.path + moveName + " ";

					visited.insert(newState);
					frontier.push(neighbor);
				}
			}
		};

		tryMove("U");
		tryMove("D");
		tryMove("L");
		tryMove("R");
	}

	cout << "Failure: Could not find solution." << endl;
}