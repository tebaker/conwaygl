#include "LifeContainer.h"

// Will generate a random set of cells placed around the grid
LifeContainer::LifeContainer() {
	// Seeding rand
	srand(time(nullptr));

	randomize();

	// Making a glider
	/*addCell(250, 250);
	addCell(251, 251);
	addCell(251, 250);
	addCell(250, 249);
	addCell(249, 251);*/
}
LifeContainer::~LifeContainer() { cells.clear(); pendingAlive.clear(); }

// MODIFIERS:

// Adding cell at position x, y
void LifeContainer::addCell(int x, int y) {
	int heldCoords = convertCoords(x, y);
	cells.insert(std::pair<int, bool>(heldCoords, true));
}
// Adding pending alive cell at position x, y
void LifeContainer::addPendingAliveCell(int x, int y) {
	int heldCoords = convertCoords(x, y);
	// Holding converted coords and 0 to start the neighbor count.
	pendingAlive.insert(std::pair<int, bool>(heldCoords, 0));
}

// Removing cell at position x, y
void LifeContainer::removeCell(int x, int y) {
	int heldCoords = convertCoords(x, y);
	cells.erase(heldCoords);
}

// Removing cell at single coord position
void LifeContainer::removeCell(int singleCoord) {
	cells.erase(singleCoord);
}

// Clearing contents of cells map
void LifeContainer::clearCells() {
	cells.clear();
}

// Clearing contents of penting alive cells map
void LifeContainer::clearPendingAlive() {
	pendingAlive.clear();
}

// clears contents of cells map and randomize
void LifeContainer::randomize() {

	// Clearing cells map
	cells.clear();

	// Placing random cells in the grid
	for (int i = 0; i < 3000; ++i) {
		// Generating an x, y coord between 0 and 500
		int x = rand() % 200 + 200;
		int y = rand() % 200 + 200;

		// Adding coords x, y to life map
		this->addCell(x, y);
	}
}

// ACCESSORS //
	// Returning copy of map storing cell data
std::map<int, bool> LifeContainer::copyMap() {
	return cells;
}

void LifeContainer::printMap() {
	for (std::map<int, bool>::iterator it = cells.begin(); it != cells.end(); ++it) {
		auto x = convertCoords(it->first).first;
		auto y = convertCoords(it->first).second;
		std::cout << x << " " << y << std::endl;
	}
	std::cout << "===" << std::endl;
}

// METHODS //
	// Evaluating N, E, S, W neighbors of the current cell and based on the rules,
	// to determine if the cell will live or die next step.
void LifeContainer::evaluateNeighbors() {

	// Looping through all the cells in cells map
	for (std::map<int, bool>::iterator it = cells.begin(); it != cells.end(); ++it) {

		int x = convertCoords(it->first).first;
		int y = convertCoords(it->first).second;

		int neighborCounter = 0;

		// Checking if cell at neighbor index is contained within the cells map.
		// If it is, increment neighbor counter.
		// If it is NOT, add or update the pending cell map

		// N: x, +y
		if (cells.find(convertCoords(x, y + 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x, y + 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x, y + 1);
			}
		}
		// NE: +x, +y
		if (cells.find(convertCoords(x + 1, y + 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x + 1, y + 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x + 1, y + 1);
			}
		}
		// E: +x, y
		if (cells.find(convertCoords(x + 1, y)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x + 1, y));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x + 1, y);
			}
		}
		// SE: +x, -y
		if (cells.find(convertCoords(x + 1, y - 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x + 1, y - 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x + 1, y - 1);
			}
		}
		// S: x, -y
		if (cells.find(convertCoords(x, y - 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x, y - 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x, y - 1);
			}
		}
		// SW: -x, -y
		if (cells.find(convertCoords(x - 1, y - 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x - 1, y - 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x - 1, y - 1);
			}
		}
		// W: -x, y
		if (cells.find(convertCoords(x - 1, y)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x - 1, y));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x - 1, y);
			}
		}
		// NW: -x, +y
		if (cells.find(convertCoords(x - 1, y + 1)) != cells.end()) {
			++neighborCounter;
		}
		else {
			// if pending cell is found at neighbor space, and is already in pendingCell map, increment neighbor count
			std::map<int, int>::iterator it = pendingAlive.find(convertCoords(x - 1, y + 1));
			if (it != pendingAlive.end()) {
				it->second += 1;
			}
			// Else, it's not in the pending alive cells map. Therefore, add it.
			else {
				addPendingAliveCell(x - 1, y + 1);
			}
		}

		// 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
		if (neighborCounter <= 1) {
			// Setting life tracker to false, will be killed on next step.
			cells.find(convertCoords(x, y))->second = false;
		}
		// 2) Any live cell with two or three live neighbours lives on to the next generation.
		//        - No action needed, move on.

		// 3) Any live cell with more than three live neighbours dies, as if by overpopulation.
		if (neighborCounter >= 4) {
			// Setting life tracker to false, will be killed on next step.
			cells.find(convertCoords(x, y))->second = false;
		}

		/*
			If I use another map, same way I'm doing it now. Lets call it the pendingAliveMap.
			But rahter than a boolean for the next state I use an integer counter that starts at 0
			and moves upward.
			Every time ANOTHER CELL LOOKS AT IT, I increase the counter by 1. If the resulting number
			is exactly 3, then the cell becomes alive next step and is added to the cells map.
			BRILLIANT!
		*/
	}
}

// Next Step will kill off any cells marked for death, and add any dead cells with exactly three neighbors
void LifeContainer::nextStep() {

	// Looping through all the cells in the cell map. Removing any marked for death.
	std::map<int, bool>::iterator it = cells.begin();
	while (it != cells.end()) {
		// If boolean is false, that means the cell is marked for dead and will now be removed.
		if (it->second == false) {
			it = this->cells.erase(it);
		}
		// Else, keeping alive. moving iterator forward one to account for the one deleted.
		else {
			++it;
		}
	}

	// Per rule 4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction,
	// I will now loop through all the pending alive cells and check if their neighbor count is equal to 3 exactly.
	// If so, they will be added to the cells map as alive cells.
	for (std::map<int, int>::iterator it = pendingAlive.begin(); it != pendingAlive.end(); ++it) {
		if (it->second == 3) {
			// Bringing dead cell back to life
			int x = convertCoords(it->first).first;
			int y = convertCoords(it->first).second;

			std::cout << "Adding: " << x << " " << y << std::endl;

			addCell(x, y);
		}
	}

	// Last thing to do is remove all the pending alive cells from the pending alive map.
	clearPendingAlive();
}

// Converting 2D coords to 1D coord. Returning int
int LifeContainer::convertCoords(int x, int y) {
	return x * w + y;
}

// Converting 1D coord to 2D coords. Returning x, y pair
std::pair<int, int> LifeContainer::convertCoords(int singleCoord) {
	int x = singleCoord / w;
	int y = singleCoord % h;

	return std::pair<int, int>(x, y);
}