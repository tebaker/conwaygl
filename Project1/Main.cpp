// Describing the progect is a smart first step.
// Letting yourself know what it is you will accomplish by the end of the project.

/* An idea: model a system using machine learning and an OpenGL graphical output */
// OR
/* Creating some very simple user GUI for visually outputting tree diagrams and other 
   things that cracking the coding interview will want you to see.
   Big O, Tree stuff, linked lists and other storage, search and sort algorithms. */


#include <iostream>
#include "Header.h"

// Anywhere MY_NAME is present, "Talon" will be put in it's place.
#define MY_NAME "Talon" // Book states generally not a good practice. There are other ways to get the same result

void doPrint()
{
	std::cout << "In doPrint()";
}


int main()
{
	// Copy initalization of value 5 into variable width.
	// This takes two steps: define the variable, assign the variable.
	int width = 5;

	// Direct initalization. For simple data types like integers, copy and direct initalization are essentially the same. However, direct initalization will directly assign the value 10 into height rahter than creating 10 and then assigning it to height.
	int height(10);

	// Direct brace initalization. Used when you have an object with a list of data. directly assigning 25 to depth.
	int depth{ 25 }; // Direct brace initalization is perfered

	int x{}; // Initalizes the value to 0

	std::cout << "value x: " << x << std::endl;

	doPrint();

	std::cout << std::endl;

	std::cout << "result of addition: " << add(3, 4) << std::endl;

	std::cout << "Outputting results of MY_NAME: " << MY_NAME << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
	std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
	std::cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes\n";
	std::cout << "char16_t:\t" << sizeof(char16_t) << " bytes\n"; // C++11 only
	std::cout << "char32_t:\t" << sizeof(char32_t) << " bytes\n"; // C++11 only
	std::cout << "short:\t\t" << sizeof(short) << " bytes\n";
	std::cout << "int:\t\t" << sizeof(int) << " bytes\n";
	std::cout << "long:\t\t" << sizeof(long) << " bytes\n";
	std::cout << "long long:\t" << sizeof(long long) << " bytes\n"; // C++11 only
	std::cout << "float:\t\t" << sizeof(float) << " bytes\n";
	std::cout << "double:\t\t" << sizeof(double) << " bytes\n";
	std::cout << "long double:\t" << sizeof(long double) << " bytes\n";













	// Holding for user input
	std::cout << "Press any key to continue..." << std::endl;
	// Reset any error flags
	std::cin.clear();
	// Ignores any characters in the input buffer until we find an enter character
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// Get one more character from the user
	std::cin.get();

	return 0;
}