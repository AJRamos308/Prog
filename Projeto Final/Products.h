#pragma once
#include <iostream>
#include <string>

using namespace std;

class Products
{
private:
	string prod;
	double price;
public:
	Products(const string prod, const double price);
	string getProductName();
	double getProductPrice();
	~Products();
};

