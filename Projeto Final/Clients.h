#pragma once
#include <iostream>
#include <string>

#pragma warning(disable : 4996) // Stops warning for using windows current time

using namespace std;

class Clients
{
private:
	unsigned int id;
	string name;
	string date;
	double valuespent;
public:
	Clients();
	Clients(unsigned int id, string name, string date, double valuespent);
	//Access every client information.
	unsigned int getClientID();
	string getClientName();
	string getClientDate();
	double getClientValueSpent();
	//Modify every client information.
	void setClientID(unsigned int content);
	void setClientName(string content);
	void setClientDate(string content);
	void setClientValueSpent(double content);
	~Clients();
};
