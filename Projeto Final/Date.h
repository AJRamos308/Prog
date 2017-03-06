#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <ctype.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <array>
#include "WINDOWS.H"
#pragma warning(disable : 4996) // Stops warning for using windows current time
using namespace std;

class Date
{
public:
	Date();
	bool Valid(int day, int month, int year);

private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
};