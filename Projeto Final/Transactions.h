#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Transactions
{
private:
	unsigned int id;
	string date;
	vector <string> products;
public:
	Transactions(const unsigned int id, const string date, const vector <string> products);

	unsigned int GetId();
	string GetDate();
	vector <string> GetProducts();

	//Access every transaction information
	

	//Modify every transaction information
	void setTransID(unsigned int content)
	{
		id = content;
	}
	void setTransDate(string content)
	{
		date = content;
	}
	~Transactions();
};

