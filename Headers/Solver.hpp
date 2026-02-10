#ifndef SOLVER_H
#define SOLVER_H

#include "Puzzle.hpp"
#include <string>
#include <vector>

// Algorithm Options
enum Algorithm
{
	UNIFORM_COST = 1,
	MISPLACED_TILE = 2,
	MANHATTAN = 3
};

// Node structure for A* Search
struct Node
{
	std::vector<std::vector<int>> state;
	int g;						// Cost from start (depth)
	int h;						// Heuristic (estimated cost to goal)
	std::string path; // Moves taken to get here

	// Priority Queue comparator (lowest f = g + h has highest priority)
	// For Uniform Cost Search, h will be 0, so it sorts purely by g (Dijkstra)
	bool operator>(const Node &other) const
	{
		return (g + h) > (other.g + other.h);
	}
};

// Main AI solver function (now takes algorithm choice)
void solveAI(Puzzle &initialPuzzle, int algorithmChoice);

#endif