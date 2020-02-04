// This program is from the OpenGL Programming Guide.  It shows a robot arm
// that you can rotate by pressing the arrow keys.

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

// Class holding and modifying all the cells currently in the game
class LifeContainer {
	// Holding contests of the each cell in the game
	std::map<int, bool> cells;
	
public:
	// Will generate a random set of cells placed around the grid
	LifeContainer() {

		// Seeding rand
		srand(time( nullptr ));

		// Placing 500 random cells in the grid
		for (int i = 0; i < w; ++i) {
			// Generating an x, y coord between 0 and 500
			int x = rand() % 500;
			int y = rand() % 500;

			// Adding coords x, y to life map
			this->addCell(x, y);
		}
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

// ACCESSORS //
	std::map<int, bool> copyMap() {
		return cells;
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
	case GLUT_KEY_UP: /*DO SOMETHING*/; break;
	case GLUT_KEY_DOWN: /*DO SOMETHING*/; break;
	default: return;
	}
	glutPostRedisplay();
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

		std::cout << "Adding: " << screenCoordX << " " << screenCoordY << std::endl;

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
	glutMainLoop();
}