/*	Conway's Game of Life Rules:
		1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
		2) Any live cell with two or three live neighbours lives on to the next generation.
		3) Any live cell with more than three live neighbours dies, as if by overpopulation.
		4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime>

// holding width and height of screen for calculations
static const int h = 500;
static const int w = 500;

// Frames Per Second
static int FPS = 60;

// Class holding and modifying all the cells currently in the game
class LifeContainer {
	// Holding contests of the each cell in the game
	std::map<int, bool> cells;
	
public:
	// Will generate a random set of cells placed around the grid
	LifeContainer() {
		// Seeding rand
		srand(time( nullptr ));

		randomize();
	}
	~LifeContainer() { cells.clear(); }

// MODIFIERS //
	// Adding cell at position x, y
	void addCell(int x, int y) {
		int heldCoords = convertCoords(x, y);
		cells.insert(std::pair<int, bool>(heldCoords, true));
	}

	// Removing cell at position x, y
	void removeCell(int x, int y) {
		int heldCoords = convertCoords(x, y);
		cells.erase(heldCoords);
	}
	
	// Removing cell at single coord position
	void removeCell(int singleCoord) {
		cells.erase(singleCoord);
	}

	// clearing contents of cells map
	void clear() {
		cells.clear();
	}

	// clears contents of cells map and randomize
	void randomize() {

		// Clearing cells map
		cells.clear();

		// Placing random cells in the grid
		for (int i = 0; i < 1000; ++i) {
			// Generating an x, y coord between 0 and 500
			int x = rand() % 500;
			int y = rand() % 500;

			// Adding coords x, y to life map
			this->addCell(x, y);
		}
	}

// ACCESSORS //
	// Returning copy of map storing cell data
	std::map<int, bool> copyMap() {
		return cells;
	}

	// Given x, y coords, check neighbor will look at all four neighbors N, E, S, W, of the 
	// current cell and return the number of neighbors it has
	int checkNeighbors(int singleCoord) {
		int x = this->convertCoords(singleCoord).first;
		int y = this->convertCoords(singleCoord).second;

		// Checking for N neighbor in 

		/*
			If I use another map, same way I'm doing it now. Lets call it the pendingAliveMap.
			But rahter than a boolean for the next state I use an integer counter that starts at 0
			and moves upward.
			Every time ANOTHER CELL LOOKS AT IT, I increase the counter by 1. If the resulting number
			is exactly 3, then the cell becomes alive next step and is added to the cells map.
			BRILLIANT!
		*/
	}

// METHODS //
	// Converting 2D coords to 1D coord. Returning int
	int convertCoords(int x, int y) {
		return x * w + y;
	}

	// Converting 1D coord to 2D coords. Returning x, y pair
	std::pair<int, int> convertCoords(int singleCoord) {
		int x = singleCoord / w;
		int y = singleCoord % h;

		return std::pair<int, int>(x, y);
	}
};

// lc containing all the cells for the program
static LifeContainer lc;

// REMEMBER: Static variables are initialized only once, and they hold their values even though function calls

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: /*DO SOMETHING*/; break;
	case GLUT_KEY_RIGHT: /*DO SOMETHING*/; break;
	case GLUT_KEY_UP:
		if (FPS < 180) {
			FPS += 10;
		}
		break;
	case GLUT_KEY_DOWN:
		if (FPS > 10) {
			FPS -= 10;
		}
		break;
	default: return;
	}
	glutPostRedisplay();
}

// Handles the timer by incrementing the angle of rotation and requesting the
// window to display again, provided the program is in the spinning state.
// Since the timer function is only called once, it sets the same function to
// be called again.
void timer(int v) {

	glutPostRedisplay();

	glutTimerFunc(1000 / FPS, timer, v);
}

// Displays the arm in its current position and orientation.  The whole
// function is bracketed by glPushMatrix and glPopMatrix calls because every
// time we call it we are in an "environment" in which a gluLookAt is in
// effect.  (Note that in particular, replacing glPushMatrix with
// glLoadIdentity makes you lose the camera setting from gluLookAt).
void display() {
	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	glBegin(GL_POINTS);
	
	// Creating copy of map storing life cell values
	std::map<int, bool> heldMap = lc.copyMap();

	// Iterating through the map to get the points
	for (std::map<int, bool>::iterator it = heldMap.begin(); it != heldMap.end(); ++it) {
		
		// Taking the converted x, y from the life container map
		double coordX = lc.convertCoords(it->first).first;
		double coordY = lc.convertCoords(it->first).second;

		// Holding variables for converted screen coords
		double screenCoordX = 0;
		double screenCoordY = 0;

		// I am checking to see what quadrant the points are in by checking if x, y are bigger or
		// smaller than the half way points of the width and height of the screen.
		// I then linearly interpolate between screen space and world space to get the approproate
		// values for x, y between (-1,1).
		// QI
		if (coordX > (w / 2) && coordY > (h / 2)) {
			screenCoordX = (coordX - 250) / (w / 2);
			screenCoordY = (coordY - 250) / (h / 2);
		}
		// QII
		else if (coordX < (w / 2) && coordY > (h / 2)) {
			screenCoordX = (250 - coordX) / (w / 2) * -1;
			screenCoordY = (coordY - 250) / (h / 2);
		}
		// QIII
		else if (coordX < (w / 2) && coordY < (h / 2)) {
			screenCoordX = (250 - coordX) / (w / 2) * -1;
			screenCoordY = (250 - coordY) / (h / 2) * -1;
		}
		// QIV
		else if (coordX > (w / 2) && coordY < (h / 2)) {
			screenCoordX = (coordX - 250) / (w / 2);
			screenCoordY = (250 - coordY) / (h / 2) * -1;
		}

		//input coord points
		glVertex3f(screenCoordX, screenCoordY, 0);

		//std::cout << "Adding: " << screenCoordX << " " << screenCoordY << std::endl;
	}

	glEnd();

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(300, 80);
	glutInitWindowSize(w, h);
	glutCreateWindow("Conway's Game of Life");
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
}