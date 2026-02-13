#include "../Headers/Solver.hpp"
#include <queue>
#include <set>
#include <cmath>
#include <iostream>
#include <algorithm> // for std::max
#include <chrono>		 // Added for timer

using namespace std;

// --- Heuristic Functions ---

// 1. Manhattan Distance (Sum of distances of tiles to their goal positions)
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

// 2. Misplaced Tile Heuristic (Count of tiles not in correct position)
int calculateMisplaced(const vector<vector<int>> &state)
{
	int misplaced = 0;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int value = state[r][c];
			if (value != 0)
			{ // Don't count the blank tile (0)
				// Correct value for this position should be (r*3 + c + 1)
				// Exception: The last cell (2,2) should be 0, but we skip 0 checks anyway.
				int targetR = (value - 1) / 3;
				int targetC = (value - 1) % 3;

				// If the tile is not where it belongs, increment cost
				if (r != targetR || c != targetC)
				{
					misplaced++;
				}
			}
		}
	}
	return misplaced;
}

// Helper to switch between heuristics based on user choice
int getHeuristic(const vector<vector<int>> &state, int choice)
{
	if (choice == UNIFORM_COST)
	{
		return 0; // UCS is just A* with h(n) = 0
	}
	else if (choice == MISPLACED_TILE)
	{
		return calculateMisplaced(state);
	}
	else
	{
		return calculateManhattan(state);
	}
}

// --- General Search Algorithm ---
void solveAI(Puzzle &initialPuzzle, int algorithmChoice)
{
	cout << "AI is thinking..." << endl;

	// Start the timer
	auto startTime = chrono::high_resolution_clock::now();

	// Priority queue stores nodes to visit, ordered by lowest f(n) = g(n) + h(n)
	priority_queue<Node, vector<Node>, greater<Node>> frontier;

	// Set to keep track of visited states to prevent loops
	set<vector<vector<int>>> visited;

	// Statistics
	int nodesExpanded = 0;
	size_t maxQueueSize = 0;

	// Initial Node
	Node startNode;
	startNode.state = initialPuzzle.getState();
	startNode.g = 0;
	startNode.h = getHeuristic(startNode.state, algorithmChoice);
	startNode.path = "";

	frontier.push(startNode);
	visited.insert(startNode.state);
	maxQueueSize = max(maxQueueSize, frontier.size());

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
			// Stop the timer and calculate duration
			auto endTime = chrono::high_resolution_clock::now();
			chrono::duration<double> elapsed = endTime - startTime;

			cout << "AI Solved it!" << endl;
			cout << "Time Taken: " << elapsed.count() << " seconds" << endl;
			cout << "Nodes Expanded: " << nodesExpanded << endl;
			cout << "Max Queue Size: " << maxQueueSize << endl;
			cout << "Solution Depth: " << current.g << endl;
			cout << "Path: " << current.path << endl;

			// Show the final state
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
					neighbor.h = getHeuristic(newState, algorithmChoice);
					neighbor.path = current.path + moveName + " ";

					visited.insert(newState);
					frontier.push(neighbor);

					// Update max queue size
					maxQueueSize = max(maxQueueSize, frontier.size());
				}
			}
		};

		tryMove("U");
		tryMove("D");
		tryMove("L");
		tryMove("R");
	}

	cout << "Failure: Could not find solution." << endl;
	cout << "Nodes Expanded: " << nodesExpanded << endl;
	cout << "Max Queue Size: " << maxQueueSize << endl;
}