#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "Date.h"

using namespace std;

Date::Date()
{

}

bool Date::Valid(int day, int month, int year)
{
	time_t tt = time(0);   // get time now
	struct tm * now = localtime(&tt);
	if ((year <= (now->tm_year + 1900)) & (1900 < year))
	{
		if (year == (now->tm_year + 1900))
		{
			if (month > now->tm_mon + 1)
				return false;
			if (month == now->tm_mon + 1)
				if (day > now->tm_mday)
					return false;
		}
		if ((0 < month) & (month < 13))
		{
			if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
			{
				if ((0 < day) & (day < 32))
				{
					return true;
				}
				else
					return false;
			}
			if (month == 2)
			{
				if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				{
					if ((0 < day) & (day < 30))
						return true;
					else
						return false;
				}
				else if ((0 < day) & (day < 29))
				{
					return true;
				}
				else
					return false;
			}
			else
			{
				if ((0 < day) & (day < 31))
				{
					return true;
				}
				else
					return false;
			}

		}
		else
			return false;
	}
	else
		return false;
}