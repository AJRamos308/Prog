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
#include "Clients.h"
#include "Transactions.h"
#include "Products.h"
#include "Utilities.h"
#include "Menu.h"


using namespace std;

Menu* Menu::singleton_instance = 0;

bool Valid(string File)
{
	fstream f;
	f.open(File);
	if (f.is_open()) { //Tests whether the file was found.
		f.close();
		return true;
	}
	return false;
}

string AskClients()
{
	string File;
	Utilities u;
	File = "";
	cout << "Clients file name:           "; 
	cin >> File;
	if (File.find(".")>9000)
		File.append(".txt");
	while (cin.fail() || Valid(File) == false)
	{
		if (cin.eof())
		{
			cin.clear();
			main();
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
		u.setcolor(12);
		cerr << "\a> Error! " << File << " could not be found!\n\n"; //Displays error if txt was not found.
		u.setcolor(15);
		Sleep(1500);
		main();
	}
	return File;
}

string AskProducts()
{
	string File;
	Utilities u;
	File = "";
	cout << "Products file name:          ";
	cin >> File;
	if (File.find(".")>9000)
		File.append(".txt");
	while (cin.fail() || Valid(File) == false)
	{
		if (cin.eof())
		{
			cin.clear();
			main();
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
		u.setcolor(12);
		cerr << "\a> Error! " << File << " could not be found!\n\n"; //Displays error if txt was not found.
		u.setcolor(15);
		Sleep(1500);
		main();
	}
	return File; 
}

string AskTransactions()
{
	string File;
	Utilities u;
	File = "";
	cout << "Transactions file name:      ";
	cin >> File;
	if (File.find(".")>9000)
		File.append(".txt");
	while (cin.fail() || Valid(File) == false)
	{
		if (cin.eof())
		{
			cin.clear();
			main();
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;
		u.setcolor(12);
		cerr << "\a> Error! " << File << " could not be found!\n\n"; //Displays error if txt was not found.
		u.setcolor(15);
		Sleep(1500);
		main();
	}
	
	return File;
}

void main()
{
	Utilities u;
	Menu M;
	system("cls"); // clear window
	u.setcolor(15);
	system("cls"); // clear window
	u.setcolor(15);
	cout << "================================================================\n";
	cout << "|                     VENDE++ Super Market                     |\n";
	cout << "| "; u.setcolor(10); cout << "        __     __             _                             ";u.setcolor(15); cout << " |" << endl;
	cout << "| "; u.setcolor(10); cout << "        \\ \\   / /__ _ __   __| | ___     _       _  " << char(184) << "     ";u.setcolor(15); cout << "   |" << endl;
	cout << "| "; u.setcolor(10); cout << "         \\ \\ / / _ \\ '_ \\ / _` |/ _ \\  _| |_   _| |_    ";u.setcolor(15); cout << "     |" << endl;
	cout << "| ";u.setcolor(10); cout << "          \\ V /  __/ | | | (_| |  __/ |_   _| |_   _|      ";u.setcolor(15); cout << "  |" << endl;
	cout << "| ";u.setcolor(10); cout << "           \\_/ \\___|_| |_|\\__,_|\\___|   |_|     |_|      ";u.setcolor(15); cout << "    |" << endl;
	cout << "|                                                              |" << endl;
	cout << "|                      Management Sofware                      |\n";
	cout << "================================================================\n\n";
	cout << "NOTE: At any time you can use the command CTRL+Z to go back to\nthe previous menu!\n\n";
	cout << "Please insert filenames \n(if extension '.txt' not necessary to include)\n\n";
	string c, p, t;
	c = AskClients();
	p = AskProducts();
	t = AskTransactions();
	Menu::instance()->setClientsFileName(c);
	Menu::instance()->setProductsFileName(p);
	Menu::instance()->setTransFileName(t);
	Menu::instance()->Options();
	
	return;
}