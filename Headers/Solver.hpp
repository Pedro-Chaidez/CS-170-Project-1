#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.hpp"
#include <string>
#include <vector>

// Node structure for A* Search
struct Node
{
	std::vector<std::vector<int>> state;
	int g;						// Cost from start (depth)
	int h;						// Heuristic (estimated cost to goal)
	std::string path; // Moves taken to get here

	// Priority Queue comparator (lowest f = g + h has highest priority)
	bool operator>(const Node &other) const
	{
		return (g + h) > (other.g + other.h);
	}
};

// Main AI solver function
void solveAI(Puzzle &initialPuzzle);

#endif