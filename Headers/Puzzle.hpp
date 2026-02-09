#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <iostream>

class Puzzle
{
private:
	std::vector<std::vector<int>> state;
	// Goal state definition
	const std::vector<std::vector<int>> goalState = {
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 0}};
	int zeroRow, zeroCol;

	// Helper to find the blank tile (0)
	void updateZeroPosition();

public:
	// Constructors
	Puzzle();
	Puzzle(std::vector<std::vector<int>> s);

	// Getters
	std::vector<std::vector<int>> getState() const;
	bool isGoal() const;

	// Display
	void printBoard() const;

	// Movement (returns true if valid)
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	// Randomization
	void shufflePuzzle(int moves = 20);
};

#endif