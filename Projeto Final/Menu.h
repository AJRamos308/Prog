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
#include <algorithm>
#include <array>
#include <map>
#include <climits>
#include "WINDOWS.H"
#include "Clients.h"
#include "Products.h"
#include "Transactions.h"
#include "Utilities.h"
#include "Date.h"

using namespace std;

void main();

class Menu
{
private:
	static Menu* singleton_instance;
	string ClientsFile, ProductsFile, TransactionsFile, line;
	fstream f;
	vector<Clients> clientsV;
	vector<Products> productsV;
	vector<Transactions> transactionsV;
	map<int, int> Client_IdIx;
	map<string, int> Prod_Ix;
	map<int, int> clientIdx;
	map<string, int> productIdx;
	multimap<int, int> transactionIdx;
public:
	Menu();
	void setClientsFileName(string File);
	void setProductsFileName(string File);
	void setTransFileName(string File);
	////Leitura e Gravação de Ficheiros////
	//Clients
	void ExtractClients(string ClientsFile);
	void WriteClients(string ClientsFile);
	void AddClients(unsigned int & nclients);
	string FormatName(string name);
	void RemoveClients(unsigned int & nclients);
	void ModifyClients(unsigned int & nclients);
	void ListClients();
	void SearchClients();
	void ManageClients();
	//Products
	void ExtractProducts(string ProductsFile);
	void WriteProducts(string ProductsFile);
	void ListProducts();
	void Bottom10();
	void ListClientsOrd();
	void AddProducts();
	//Transactions
	void ExtractTransactions(string TransactionsFile);
	void WriteTransactions(string TransactionsFile);
	void ListTransactions();
	void MakePurchase();

	static Menu* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Menu;

		return singleton_instance;
	}	
	bool transExisteID(int id);
	int IndividualAdvertising();
	void Bottom10Advertising();
	void SplitName(string full, vector<string>& temp);
	void Options();
	void ExitProgram();

};

