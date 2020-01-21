#include <iostream>
#include "Header.h"

#define PRINT_ADD

int add(int x, int y)
{
#ifdef PRINT_ADD
#define PRINT_SUB
	std::cout << "defining sub" << std::endl;
	std::cout << "PRINTING JOE: " << x + y << std::endl;
#endif

#ifdef PRINT_SUB
	std::cout << "PRINTING BOB: " << x - y << std::endl;
#endif

	return x + y;
}