#include "Transactions.h"

Transactions::Transactions(const unsigned int id, const string date, const vector <string> products)
{
	this->id = id;
	this->date = date;
	this->products = products;
}

unsigned int Transactions::GetId()
{
	return id;
}

string Transactions::GetDate()
{
	return date;
}

vector <string> Transactions::GetProducts()
{
	return products;
}

Transactions::~Transactions()
{
}
