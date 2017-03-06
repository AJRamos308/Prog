#include "Clients.h"

Clients::Clients()
{

}

Clients::Clients(unsigned int id, string name, string date, double valuespent)
{
	this->id = id;
	this->name = name;
	this->date = date;
	this->valuespent = valuespent;
}
//Access every client information.
unsigned int Clients::getClientID()
{
	return id;
}
string Clients::getClientName()
{
	return name;
}
string Clients::getClientDate()
{
	return date;
}
double Clients::getClientValueSpent()
{
	return valuespent;
}
//Modify every client information.
void Clients::setClientID(unsigned int content)
{
	id = content;
}
void Clients::setClientName(string content)
{
	name = content;
}
void Clients::setClientDate(string content)
{
	date = content;
}
void Clients::setClientValueSpent(double content)
{
	valuespent = content;
}

Clients::~Clients()
{
}
