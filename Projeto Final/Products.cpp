#include "Products.h"

Products::Products(const string prod, const double price)
{
	this->prod = prod;
	this->price = price;
}

//Access every product information
string Products::getProductName()
{
	return prod;
}

double Products::getProductPrice()
{
	return price;
}

Products::~Products()
{
}
