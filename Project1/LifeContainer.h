#ifndef LIFE_CONTAINER_H_2_11_2020
#define	LIFE_CONTAINER_H_2_11_2020

#include <map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime>
#include <iostream>

// holding width and height of screen for calculations
static const int h = 500;
static const int w = 500;

// Frames Per Second
static int FPS = 2;

// Class holding and modifying all the cells currently in the game
class LifeContainer {
	// Holding contests of the each cell in the game
	std::map<int, bool> cells;

	// Holding the pending alive cells. Per rule 4) Any dead cell with exactly three live
	// neighbours becomes a live cell, as if by reproduction.
	// This map will hold the cell single dimentional index, and the number of neighbors it has.
	std::map<int, int> pendingAlive;

public:
	// Will generate a random set of cells placed around the grid
	LifeContainer();
	~LifeContainer();

		// MODIFIERS:

			// Adding cell at position x, y
	void addCell(int x, int y);

		// Adding pending alive cell at position x, y
	void addPendingAliveCell(int x, int y);

		// Removing cell at position x, y
	void removeCell(int x, int y);

		// Removing cell at single coord position
	void removeCell(int singleCoord);

		// Clearing contents of cells map
	void clearCells();

		// Clearing contents of penting alive cells map
	void clearPendingAlive();

		// clears contents of cells map and randomize
	void randomize();

		// ACCESSORS:
				// Returning copy of map storing cell data
	std::map<int, bool> copyMap();

	void printMap();

		// METHODS:
			// Evaluating N, E, S, W neighbors of the current cell and based on the rules,
			// to determine if the cell will live or die next step.
		void evaluateNeighbors();

	// Next Step will kill off any cells marked for death, and add any dead cells with exactly three neighbors
	void nextStep();

	// Converting 2D coords to 1D coord. Returning int
	int convertCoords(int x, int y);

	// Converting 1D coord to 2D coords. Returning x, y pair
	std::pair<int, int> convertCoords(int singleCoord);
};

#endif