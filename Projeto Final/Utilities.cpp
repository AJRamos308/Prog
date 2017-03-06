#include "Utilities.h"

Utilities::Utilities()
{
}

void Utilities::setcolor(unsigned int color) // Allows the use of colors in console
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}
