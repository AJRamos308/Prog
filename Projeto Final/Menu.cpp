#include "Menu.h"

Menu::Menu()
{

}

void Menu::setClientsFileName(string File)
{
	ClientsFile = File;
	ExtractClients(File);
}

void Menu::setProductsFileName(string File)
{
	ProductsFile = File;
	ExtractProducts(File);
}

void Menu::setTransFileName(string File)
{
	TransactionsFile = File;
	ExtractTransactions(File);
}

//Clients

void Menu::ExtractClients(string ClientsFile)
{
	f.open(ClientsFile);
	if (getline(f, line))
		line.erase();
	while (getline(f, line)) {
		int id = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string name = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string date = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		double valuespent = stof(line.substr(0, line.length()));
		clientsV.push_back(Clients(id, name, date, valuespent));
	}
	f.close();
}

void Menu::WriteClients(string ClientsFile) // Writes on file finnished clients vector
{
	ofstream f;
	unsigned int i;
	f.open(ClientsFile);
	f << clientsV.size() << endl;
	for (i = 0; i < clientsV.size(); i++)
	{
		f << clientsV.at(i).getClientID() << " ; " << clientsV.at(i).getClientName() << " ; " << setprecision(2) << fixed << clientsV.at(i).getClientDate() << " ; " << clientsV.at(i).getClientValueSpent() << endl;
	}
	f.close();
	return;
}

void Menu::AddClients(unsigned int &nclients)
{
	Utilities u;
	while (nclients > 0)
	{
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                          Add Clients                          |\n";
		cout << setw(0) << "================================================================\n\n";
		cin.clear();
		cin.ignore(1000, '\n');
		for (unsigned int i = 0; i < nclients; i++) // Adds multiple clients
		{
			unsigned int ID = 0;
			/*bool exists = false;
			while (true)
			{
				cout << "Please insert client's ID: ";
				cin >> ID;
				while (cin.fail())
				{
					cin.clear();
					u.setcolor(12);
					cerr << "\a> Not a valid ID!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert ID: ";
					cin >> ID;
				}
				for (unsigned int h = 0; h < clientsV.size(); h++)
				{
					if (ID == clientsV.at(h).getClientID())
						exists = true;
				}
				if (exists)
				{
					u.setcolor(12);
					cerr << "\a> ID already exists! Please insert another ID!\n";
					u.setcolor(15);
				}
				else
					break;
			}*/
			unsigned int max = 0;
			for (unsigned int h = 0; h < clientsV.size(); h++)
			{
				if (clientsV.at(h).getClientID() > max)
					max = clientsV.at(h).getClientID();
			}
			ID = max + 1;
			string name;
			cout << "Please insert client number " << i + 1 << " Name: ";
			getline(cin, name);
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				u.setcolor(12);
				cerr << "\a> Not a valid name!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert Name: ";
				getline(cin, name);
			}
			time_t tt = time(0);   // get time now
			struct tm * now = localtime(&tt);
			ostringstream oss;
			string date;
			if ((now->tm_mon + 1) > 9) // Adds a zero before the month if month < 9
			{
				oss << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
			}
			else
			{
				oss << now->tm_mday << "/0" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
			};
			date = oss.str();
			clientsV.push_back(Clients(ID, FormatName(name), date, 0)); // Pushes back information to Client vector
			nclients--;
		}
	}
	u.setcolor(14);
	cout << "\n\nOperation Complete\nGoing back to Manage Clients"; Sleep(400); cout << "."; Sleep(400); cout << "."; Sleep(400); cout << "."; Sleep(400); // Displays a nice "thinking" animation (can be removed if it slows the programm too much)
	u.setcolor(15);
	return;
}

string Menu::FormatName(string name)
{
	string FixedName = name;

	//altera primeiro tudo para minusculas
	for (unsigned int i = 1; i < FixedName.length(); i++)
	{
		FixedName.at(i) = tolower(FixedName.at(i));
	}

	//altera a primeira letra da string para maiusculas
	if (!isupper(FixedName.at(0)))
	{
		FixedName.at(0) = toupper(FixedName.at(0));
	}

	//altera a letra depois de um espaço para maiusculas
	for (unsigned int i = 1; i < FixedName.length(); i++)
	{
		if (FixedName.at(i - 1) == ' ' && !isupper(FixedName.at(i)))
		{
			FixedName.at(i) = toupper(FixedName.at(i));
		}
	}

	return FixedName ;
}

void Menu::RemoveClients(unsigned int &nclients)
{
	Utilities u;

	while (nclients > 0)
	{
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                        Remove Clients                        |\n";
		cout << setw(0) << "================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "First Name"; u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << " Last Name\n\n";
		cout << "\tHow do you want to search for the client?: ";
		unsigned int sa;
		cin >> sa;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\t\a> No such option in menu!\n";
			u.setcolor(15);
			cout << "\t\nPlease reinsert your option: ";
			cin >> sa;
		}
		switch (sa)
		{

		case 1: // Remove a Client based on ID
		{
			system("cls");
			cout << setw(0) << "================================================================\n";
			cout << setw(0) << "|                        Remove Clients                        |\n";
			cout << setw(0) << "================================================================\n\n";
			unsigned int ID;
			cout << "\tPlease insert client's ID: ";
			cin >> ID;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\t\a> Not a valid ID!\n";
				u.setcolor(15);
				cout << "\t\nPlease reinsert ID: ";
				cin >> ID;
			}
			bool duplicateID = false;
			for (unsigned int u = 0; u < clientsV.size(); u++)
			{
				if (clientsV.at(u).getClientID() == ID)
				{
					duplicateID = true; // Found ID equal to the given one
					clientsV.erase(clientsV.begin() + u);
				}
			}
			if (!duplicateID) // Error if no ID is equal to the given one
			{
				u.setcolor(12);
				cerr << "\a> ID '" << ID << "' not in use!\n";
				u.setcolor(15);
				Sleep(1000);
				RemoveClients(nclients);
			}
		};
		break;

		case 2: // Asks for First name then displays clients with that name with associated IDs to choose from
		{
			{
				cin.ignore();
				cin.clear();
				system("cls");
				cout << setw(0) << "================================================================\n";
				cout << setw(0) << "|                        Remove Clients                        |\n";
				cout << setw(0) << "================================================================\n\n";
				string name, tempname, tempname1;
				vector <string> temp;
				cout << "\tPlease insert client's First Name: ";
				getline(cin, name);
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					u.setcolor(12);
					cerr << "\t\a> Not a valid name!\n";
					u.setcolor(15);
					cout << "\t\nPlease reinsert Name: ";
					getline(cin, name);
				}
				cout << setw(5) << "\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
				bool duplicateID = false;
				for (unsigned int k = 0; k < clientsV.size(); k++)
				{
					SplitName(clientsV.at(k).getClientName(), temp); // Splits name in First name and Last name
					tempname = temp[0];
					tempname1 = temp[1];
					if (name == tempname) // Found a name equal to the one given
					{
						duplicateID = true;
						cout << setw(5) << clientsV.at(k).getClientID();
						cout << setw(27) << clientsV.at(k).getClientName();
						cout << setw(15) << clientsV.at(k).getClientDate();
						cout << setw(10) << setprecision(2) << fixed << clientsV.at(k).getClientValueSpent() << endl;
					}
				};
				if (duplicateID == false) // Has not found a name equal to the one given
				{
					u.setcolor(12);
					cerr << "\a> " << name << " not found!\n";
					u.setcolor(15);
					Sleep(1000);
					RemoveClients(nclients);
				}
				unsigned int ID;
				cout << "\t\nPlease insert client's ID: ";
				cin >> ID;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\t\a> Not a valid ID!\n";
					u.setcolor(15);
					cout << "\t\nPlease reinsert ID: ";
					cin >> ID;
				}
				bool foundID = false;
				for (unsigned u = 0; u < clientsV.size(); u++)
				{
					if (ID == clientsV.at(u).getClientID())
					{
						foundID = true;
						clientsV.erase(clientsV.begin() + u); // Remove Client with given ID
					};
				};
				if (foundID == false)
				{
					u.setcolor(12);
					cerr << "\t\a> Client ID " << ID << " not found!\n";
					u.setcolor(15);
					Sleep(1000);
					RemoveClients(nclients);
				}
			};
		};
		break;

		case 3: // Asks for Last name then displays clients with that name with associated IDs to choose from
		{
			{
				cin.ignore();
				cin.clear();
				system("cls");
				cout << setw(0) << "================================================================\n";
				cout << setw(0) << "|                        Remove Clients                        |\n";
				cout << setw(0) << "================================================================\n\n";
				string name, tempname, tempname1;
				vector <string> temp;
				cout << "\tPlease insert client's Last Name: ";
				getline(cin, name);
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					u.setcolor(12);
					cerr << "\t\a> Not a valid name!\n";
					u.setcolor(15);
					cout << "\t\nPlease reinsert Name: ";
					getline(cin, name);
				}
				cout << setw(5) << "\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
				bool duplicateID = false;
				for (unsigned int k = 0; k < clientsV.size(); k++)
				{
					SplitName(clientsV.at(k).getClientName(), temp); // Splits name in First name and Last name
					tempname = temp[0];
					tempname1 = temp[1];
					if (name == tempname1)// Found a Last name equal to the one given
					{
						duplicateID = true;
						cout << setw(5) << clientsV.at(k).getClientID();
						cout << setw(27) << clientsV.at(k).getClientName();
						cout << setw(15) << clientsV.at(k).getClientDate();
						cout << setw(10) << setprecision(2) << fixed << clientsV.at(k).getClientValueSpent() << endl;
					}
				};
				if (duplicateID == false) // Has not found a name equal to the one given
				{
					u.setcolor(12);
					cerr << "\t\a> " << name << " not found!\n";
					u.setcolor(15);
					Sleep(1000);
					RemoveClients(nclients);
				}
				unsigned int ID;
				cout << "\t\nPlease insert client's ID: ";
				cin >> ID;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\t\a> Not a valid ID!\n";
					u.setcolor(15);
					cout << "\t\nPlease reinsert ID: ";
					cin >> ID;
				}
				bool foundID = false;
				for (unsigned u = 0; u < clientsV.size(); u++)
				{
					if (ID == clientsV.at(u).getClientID())
					{
						foundID = true;
						clientsV.erase(clientsV.begin() + u); // Remove Client with given ID
					};
				};
				if (foundID == false)
				{
					u.setcolor(12);
					cerr << "\t\a> Client ID " << ID << " not found!\n";
					u.setcolor(15);
					Sleep(1000);
					RemoveClients(nclients);
				}
			};
		};
		break;
		}
		nclients--;
	}
	u.setcolor(14);
	cout << "\n\nOperation Complete\nGoing back to Manage Clients"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500);
	u.setcolor(15);
	return;
}

void Menu::ModifyClients(unsigned int &nclients)
{
	Utilities u;

	while (nclients > 0)
	{
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                        Modify Clients                        |\n";
		cout << setw(0) << "================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "First Name"; u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << " Last Name\n\n";
		cout << "\tHow do you want to serch for the client?: ";
		unsigned sa;
		cin >> sa;
		cout << endl;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			cout << "\nPlease reinsert your option: ";
			cin >> sa;
		}
		switch (sa)
		{

		case 1:
		{
			system("cls");
			cout << setw(0) << "================================================================\n";
			cout << setw(0) << "|                        Modify Clients                        |\n";
			cout << setw(0) << "================================================================\n\n";
			unsigned int ID;
			cout << "\tPlease insert client's ID: ";
			cin >> ID;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> Not a valid ID!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert ID: ";
				cin >> ID;
			}
			bool duplicateID = false;
			for (unsigned int l = 0; l < clientsV.size(); l++)
			{
				if (clientsV.at(l).getClientID() == ID)
				{
					duplicateID = true;
					u.setcolor(3); cout << "\n\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\n\t2. "; u.setcolor(15); cout << "Name"; u.setcolor(3); cout << "\n\t3. "; u.setcolor(15); cout << "Value Spent" << endl;
					cout << "\tWhich values do you want to modify for the client? ";
					int choice;
					cin >> choice;
					while (cin.fail())
					{
						if (cin.eof())
						{
							cin.clear();
							return;
						}
						cin.clear();
						cin.ignore(1000, '\n');
						u.setcolor(12);
						cerr << "\a> No such option in menu!\n";
						u.setcolor(15);
						cout << "\nPlease reinsert your option: ";
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
					{
						cout << "\n\tNew ID: ";
						unsigned int NEWID;
						cin.clear();
						cin >> NEWID;
						while (cin.fail())
						{
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid ID!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert ID: ";
							cin >> NEWID;
						}
						bool Duplicate = false;
						while (true)
						{
							Duplicate = false;
							for (unsigned int g = 0; g < clientsV.size(); g++)
							{
								if (NEWID == clientsV.at(g).getClientID())
								{
									Duplicate = true;
									if (NEWID == ID)
									{
										Duplicate = false;
										break;
									}
								}
							}
							if (Duplicate == true)
							{
								u.setcolor(12);
								cerr << "\a\t> ID '" << NEWID << "' already in use!\n";
								u.setcolor(15);
								cout << "\n\tNew ID: ";
								cin.clear();
								cin >> NEWID;
								while (cin.fail())
								{
									if (cin.eof())
									{
										cin.clear();
										return;
									}
									cin.clear();
									cin.ignore(1000, '\n');
									u.setcolor(12);
									cerr << "\a> Not a valid ID!\n";
									u.setcolor(15);
									cout << "\nPlease reinsert ID: ";
									cin >> NEWID;
								}
							}
							if (Duplicate == false)
								break;
						}
						clientsV.at(l).setClientID(NEWID);
						for (unsigned int e = 0; e < transactionsV.size(); e++)
						{
							if (ID == transactionsV.at(e).GetId())
							{
								transactionsV.at(e).setTransID(NEWID);
							}
						}
					}
					break;

					case 2:
					{
						cout << "\n\tNew Name: ";
						string NEWName;
						getline(cin, NEWName);
						while (cin.fail())
						{
							cin.clear();
							u.setcolor(12);
							cerr << "\a> Not a valid name!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Name: ";
							getline(cin, NEWName);
							cin.ignore();
						}
						clientsV.at(l).setClientName(NEWName);
					}
					break;

					case 3:
					{
						cout << "\n\tNew Value Spent: ";
						double NEWValue;
						cin >> NEWValue;
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid Value!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Value Spent: ";
							cin >> NEWValue;
						}
						clientsV.at(l).setClientValueSpent(NEWValue);
					}
					break;

					default:
						ModifyClients(nclients);
						break;
					}
				}
			}
			if (!duplicateID)
			{
				u.setcolor(12);
				cerr << "\a> ID '" << ID << "' not in use!\n";
				u.setcolor(15);
				Sleep(1000);
				ModifyClients(nclients);
			}
		};
		break;

		case 2:
		{
			cin.ignore();
			cin.clear();
			system("cls");
			cout << setw(0) << "================================================================\n";
			cout << setw(0) << "|                        Modify Clients                        |\n";
			cout << setw(0) << "================================================================\n\n";
			string name, tempname, tempname1;
			vector <string> temp;
			cout << "\tPlease insert client's First Name: ";
			cin.clear();
			getline(cin, name);
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				u.setcolor(12);
				cerr << "\a> Not a valid name!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert Name: ";
				getline(cin, name);
			}
			cout << setw(5) << "\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
			bool duplicateID = false;
			for (unsigned int k = 0; k < clientsV.size(); k++)
			{
				SplitName(clientsV.at(k).getClientName(), temp);
				tempname = temp[0]; // Takes names out of vector to a variable
				tempname1 = temp[1];
				if (name == tempname)
				{
					duplicateID = true; // If found a name displays it
					cout << setw(5) << clientsV.at(k).getClientID();
					cout << setw(27) << clientsV.at(k).getClientName();
					cout << setw(15) << clientsV.at(k).getClientDate();
					cout << setw(10) << setprecision(2) << fixed << clientsV.at(k).getClientValueSpent() << endl;
				}
			};
			if (duplicateID == false) // If no name was found Error
			{
				u.setcolor(12);
				cerr << "\a> " << name << " not found!\n";
				u.setcolor(15);
				Sleep(1000);
				ModifyClients(nclients);
			}
			unsigned int ID;
			cout << "\t\nPlease insert client's ID: ";
			cin >> ID;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> No such option in menu!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert your option: ";
				cin >> ID;
			}
			bool foundID = false;
			for (unsigned l = 0; l < clientsV.size(); l++)
			{
				if (ID == clientsV.at(l).getClientID())
				{
					foundID = true;
					u.setcolor(3); cout << "\n\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\n\t2. "; u.setcolor(15); cout << "Name"; u.setcolor(3); cout << "\n\t3. "; u.setcolor(15); cout << "Value Spent" << endl;
					cout << "\tWhich values do you want to modify for the client? ";
					int choice;
					cin >> choice;
					while (cin.fail())
					{
						if (cin.eof())
						{
							cin.clear();
							return;
						}
						cin.clear();
						cin.ignore(1000, '\n');
						u.setcolor(12);
						cerr << "\a> No such option in menu!\n";
						u.setcolor(15);
						cout << "\nPlease reinsert your option: ";
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
					{
						cout << "\n\tNew ID: ";
						unsigned int NEWID;
						cin.clear();
						cin >> NEWID;
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid ID!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert ID: ";
							cin >> NEWID;
						}
						bool Duplicate = false; // Stops user from creating duplicate IDs
						while (true)
						{
							Duplicate = false;
							for (unsigned int g = 0; g < clientsV.size(); g++)
							{
								if (NEWID == clientsV.at(g).getClientID())
								{
									Duplicate = true;
									if (NEWID == ID)
									{
										Duplicate = false;
										break;
									}
								}
							}
							if (Duplicate == true)
							{
								u.setcolor(12);
								cerr << "\a\t> ID '" << NEWID << "' already in use!\n";
								u.setcolor(15);
								cout << "\n\tNew ID: ";
								cin.clear();
								cin >> NEWID;
								while (cin.fail())
								{
									if (cin.eof())
									{
										cin.clear();
										return;
									}
									cin.clear();
									cin.ignore(1000, '\n');
									u.setcolor(12);
									cerr << "\a> Not a valid ID!\n";
									u.setcolor(15);
									cout << "\nPlease reinsert ID: ";
									cin >> NEWID;
								}
							}
							if (Duplicate == false)
								break;
						}
						clientsV.at(l).setClientID(NEWID);
						for (unsigned int e = 0; e < transactionsV.size(); e++)
						{
							if (ID == transactionsV.at(l).GetId())
							{
								transactionsV.at(e).setTransID(NEWID);
							}
						}
					}
					break;

					case 2:
					{
						cout << "\n\tNew Name: ";
						string NEWName;
						getline(cin, NEWName);
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							u.setcolor(12);
							cerr << "\a> Not a valid name!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Name: ";
							getline(cin, NEWName);
							cin.ignore();
						}
						clientsV.at(l).setClientName(NEWName);
					}
					break;

					case 3:
					{
						cout << "\n\tNew Value Spent: ";
						double NEWValue;
						cin >> NEWValue;
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid Value!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Value Spent: ";
							cin >> NEWValue;
						}
						clientsV.at(l).setClientValueSpent(NEWValue);
					}
					break;

					default:
						ModifyClients(nclients);
						break;
					}
				};
			};
			if (foundID == false)
			{
				u.setcolor(12);
				cerr << "\a> Client ID " << ID << " not found!\n";
				u.setcolor(15);
				Sleep(1000);
				ModifyClients(nclients);
			}
		};
		break;

		case 3:
		{
			cin.ignore();
			cin.clear();
			system("cls");
			cout << setw(0) << "================================================================\n";
			cout << setw(0) << "|                        Modify Clients                        |\n";
			cout << setw(0) << "================================================================\n\n";
			string name, tempname, tempname1;
			vector <string> temp;
			cout << "\tPlease insert client's Last Name: ";
			cin.clear();
			getline(cin, name);
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				u.setcolor(12);
				cerr << "\a> Not a valid name!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert Name: ";
				getline(cin, name);
			}
			cout << setw(5) << "\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
			bool duplicateID = false;
			for (unsigned int k = 0; k < clientsV.size(); k++)
			{
				SplitName(clientsV.at(k).getClientName(), temp);
				tempname = temp[0]; // Takes names out of vector to a variable
				tempname1 = temp[1];
				if (name == tempname1)
				{
					duplicateID = true; // If found a name displays it
					cout << setw(5) << clientsV.at(k).getClientID();
					cout << setw(27) << clientsV.at(k).getClientName();
					cout << setw(15) << clientsV.at(k).getClientDate();
					cout << setw(10) << setprecision(2) << fixed << clientsV.at(k).getClientValueSpent() << endl;
				}
			};
			if (duplicateID == false) // If no name was found Error
			{
				u.setcolor(12);
				cerr << "\a> " << name << " not found!\n";
				u.setcolor(15);
				Sleep(1000);
				ModifyClients(nclients);
			}
			unsigned int ID;
			cout << "\t\nPlease insert client's ID: ";
			cin >> ID;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> No such option in menu!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert your option: ";
				cin >> ID;
			}
			bool foundID = false;
			for (unsigned l = 0; l < clientsV.size(); l++)
			{
				if (ID == clientsV.at(l).getClientID())
				{
					foundID = true;
					u.setcolor(3); cout << "\n\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\n\t2. "; u.setcolor(15); cout << "Name"; u.setcolor(3); cout << "\n\t3. "; u.setcolor(15); cout << "Value Spent" << endl;
					cout << "\tWhich values do you want to modify for the client? ";
					int choice;
					cin >> choice;
					while (cin.fail())
					{
						if (cin.eof())
						{
							cin.clear();
							return;
						}
						cin.clear();
						cin.ignore(1000, '\n');
						u.setcolor(12);
						cerr << "\a> No such option in menu!\n";
						u.setcolor(15);
						cout << "\nPlease reinsert your option: ";
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
					{
						cout << "\n\tNew ID: ";
						unsigned int NEWID;
						cin.clear();
						cin >> NEWID;
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid ID!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert ID: ";
							cin >> NEWID;
						}
						bool Duplicate = false; // Stops user from creating duplicate IDs
						while (true)
						{
							Duplicate = false;
							for (unsigned int g = 0; g < clientsV.size(); g++)
							{
								if (NEWID == clientsV.at(g).getClientID())
								{
									Duplicate = true;
									if (NEWID == ID)
									{
										Duplicate = false;
										break;
									}
								}
							}
							if (Duplicate == true)
							{
								u.setcolor(12);
								cerr << "\a\t> ID '" << NEWID << "' already in use!\n";
								u.setcolor(15);
								cout << "\n\tNew ID: ";
								cin.clear();
								cin >> NEWID;
								while (cin.fail())
								{
									if (cin.eof())
									{
										cin.clear();
										return;
									}
									cin.clear();
									cin.ignore(1000, '\n');
									u.setcolor(12);
									cerr << "\a> Not a valid ID!\n";
									u.setcolor(15);
									cout << "\nPlease reinsert ID: ";
									cin >> NEWID;
								}
							}
							if (Duplicate == false)
								break;
						}
						clientsV.at(l).setClientID(NEWID);
						for (unsigned int e = 0; e < transactionsV.size(); e++)
						{
							if (ID == transactionsV.at(e).GetId())
							{
								transactionsV.at(e).setTransID(NEWID);
							}
						}
					}
					break;

					case 2:
					{
						cout << "\n\tNew Name: ";
						string NEWName;
						getline(cin, NEWName);
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							u.setcolor(12);
							cerr << "\a> Not a valid name!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Name: ";
							getline(cin, NEWName);
							cin.ignore();
						}
						clientsV.at(l).setClientName(NEWName);
					}
					break;

					case 3:
					{
						cout << "\n\tNew Value Spent: ";
						double NEWValue;
						cin >> NEWValue;
						while (cin.fail())
						{
							if (cin.eof())
							{
								cin.clear();
								return;
							}
							cin.clear();
							cin.ignore(1000, '\n');
							u.setcolor(12);
							cerr << "\a> Not a valid Value!\n";
							u.setcolor(15);
							cout << "\nPlease reinsert Value Spent: ";
							cin >> NEWValue;
						}
						clientsV.at(l).setClientValueSpent(NEWValue);
					}
					break;

					default:
						ModifyClients(nclients);
						break;
					}
				};
			};
			if (foundID == false)
			{
				u.setcolor(12);
				cerr << "\a> Client ID " << ID << " not found!\n";
				u.setcolor(15);
				Sleep(1000);
				ModifyClients(nclients);
			}
		};
		break;
		default:
		{
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
			ModifyClients(nclients);
		}
		}
		nclients--;
	}
	u.setcolor(14);
	cout << "\n\nOperation Complete\nGoing back to Manage Clients"; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(500);
	u.setcolor(15);
	return;
}

void Menu::ListClients()
{
	Utilities u;
	int a = -1;
	while (a != 4)
	{
		system("cls");
		cin.clear();
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                          Client List                         |\n";
		cout << setw(0) << "================================================================\n\n";
		cout << setw(5) << "ID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		for (unsigned int i = 0; i < clientsV.size(); i++) // Shows list of clients
		{
			cout << setw(5) << clientsV.at(i).getClientID();
			cout << setw(27) << clientsV.at(i).getClientName();
			cout << setw(15) << clientsV.at(i).getClientDate();
			cout << setw(10) << setprecision(2) << fixed << clientsV.at(i).getClientValueSpent() << endl;
		}
		cout << setw(0) << "\n================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Search for a Client"; u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "Ordered Client List\n";
		u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << "Bottom 10"; u.setcolor(3); cout << "\t\t4. "; u.setcolor(15); cout << "Exit to Menu" << endl;
		cout << setw(0) << "\n================================================================\n" << endl;
		cout << "Insert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		switch (a)
		{

		case 1:
			SearchClients();
		break;
		case 2:
			ListClientsOrd();
			break;
		case 3:
			Bottom10();
			break;
		case 4:
			return;
			break;
		}
	}
	return;
}

void Menu::SearchClients()
{
	Utilities u;
	system("cls");
	cout << setw(0) << "================================================================\n";
	cout << setw(0) << "|                        Search Client                         |\n";
	cout << setw(0) << "================================================================\n\n";
	u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "ID"; u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "First Name"; u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << " Last Name\n\n";
	cout << "\tHow do you want to search for the client?: ";
	unsigned sa;
	cin >> sa;
	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(12);
		cerr << "\a> No such option in menu!\n";
		u.setcolor(15);
		cout << "\nPlease reinsert your option: ";
		cin >> sa;
	}
	switch (sa)
	{

	case 1:
	{
		unsigned int ID;
		cout << "\nPlease insert client's ID: ";
		cin >> ID;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> That is not an ID!\n";
			u.setcolor(15);
			cout << "\nPlease reinsert client's ID: ";
			cin >> ID;
		}
		cout << setw(5) << "\n\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		bool nonexistent = false;
		for (unsigned i = 0; i < clientsV.size(); i++)
		{
			if (ID == clientsV.at(i).getClientID())
			{
				nonexistent = true;
				cout << setw(5) << clientsV.at(i).getClientID();
				cout << setw(27) << clientsV.at(i).getClientName();
				cout << setw(15) << clientsV.at(i).getClientDate();
				cout << setw(10) << setprecision(2) << fixed << clientsV.at(i).getClientValueSpent() << endl;

			};
		};
		if (nonexistent == false)
		{
			u.setcolor(12);
			cerr << "\a> ID not found!\n";
			u.setcolor(15);
		}
		cout << "\nPress any key to go back to Client List... ";
		_getch();
	};
	break;

	case 2:
	{
		string name, tempname, tempname1;
		vector <string> temp;
		cin.ignore();
		cin.clear();
		cout << "\n\tPlease insert client's First Name: ";
		getline(cin, name);
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			u.setcolor(12);
			cerr << "\a> Not a valid name!\n";
			u.setcolor(15);
			cout << "\nPlease reinsert Name: ";
			getline(cin, name);
			cin.ignore();
		}
		string namef = FormatName(name);
		cout << setw(5) << "\n\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		bool nonexistent = false;
		for (unsigned i = 0; i < clientsV.size(); i++)
		{
			SplitName(clientsV.at(i).getClientName(), temp);
			tempname = temp[0];
			tempname1 = temp[1];
			if (namef == tempname)
			{
				nonexistent = true;
				cout << setw(5) << clientsV.at(i).getClientID();
				cout << setw(27) << clientsV.at(i).getClientName();
				cout << setw(15) << clientsV.at(i).getClientDate();
				cout << setw(10) << setprecision(2) << fixed << clientsV.at(i).getClientValueSpent() << endl;
			};
		};
		if (nonexistent == false)
		{
			u.setcolor(12);
			cerr << "\a> " << namef << " not found!\n";
			u.setcolor(15);
		}
		cout << "\nPress any key to go back to Client List... ";
		_getch();
	};
	break;

	case 3:
	{
		string name, tempname, tempname1;
		vector <string> temp;
		cin.ignore();
		cin.clear();
		cout << "\n\tPlease insert client's Last Name: ";
		getline(cin, name);
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			u.setcolor(12);
			cerr << "\a> Not a valid name!\n";
			u.setcolor(15);
			cout << "\nPlease reinsert Name: ";
			getline(cin, name);
			cin.ignore();
		}
		string namef = FormatName(name);
		cout << setw(5) << "\n\nID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		bool nonexistent = false;
		for (unsigned i = 0; i < clientsV.size(); i++)
		{
			SplitName(clientsV.at(i).getClientName(), temp);
			tempname = temp[0];
			tempname1 = temp[1];
			if (namef == tempname1)
			{
				nonexistent = true;
				cout << setw(5) << clientsV.at(i).getClientID();
				cout << setw(27) << clientsV.at(i).getClientName();
				cout << setw(15) << clientsV.at(i).getClientDate();
				cout << setw(10) << setprecision(2) << fixed << clientsV.at(i).getClientValueSpent() << endl;
			};
		};
		if (nonexistent == false)
		{
			u.setcolor(12);
			cerr << "\a> " << namef << " not found!\n";
			u.setcolor(15);
		}
		cout << "\nPress any key to go back to Client List... ";
		_getch();
	};
	break;
	};
	return;
}

void Menu::ManageClients()
{
	Utilities u;
	int a = -1;
	while (a != 4)
	{
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                        Manage Clients                        |\n";
		cout << setw(0) << "================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Add Client"; u.setcolor(3); cout << "\t\t3. "; u.setcolor(15); cout << "Modify Clients" << endl;
		u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "Remove Clients"; u.setcolor(3); cout << "\t4. "; u.setcolor(15); cout << "Exit to Menu" << endl;
		cout << setw(0) << "\n================================================================\n";
		cout << "\nInsert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		switch (a)
		{
		case 1:
		{
			cout << endl << "How many valid clients do you want to add?: ";
			unsigned int howclients;
			cin >> howclients;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> Not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert how many clients you want to add: ";
				cin >> howclients;
			}
			AddClients(howclients);
		}
		break;

		case 2:
		{
			cout << endl << "How many clients do you want to remove?: ";
			unsigned int howclients;
			cin >> howclients;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> Not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert how many clients you want to remove: ";
				cin >> howclients;
			}
			RemoveClients(howclients);

		}
		break;

		case 3:
		{
			cout << endl << "How many clients do you want to modify?: ";
			unsigned int howclients;
			cin >> howclients;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> Not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert how many clients you want to modify: ";
				cin >> howclients;
			}
			ModifyClients(howclients);
		}
		break;

		case 4:
			return;
			break;
		}
	}
	return;
}

//Products

void Menu::ExtractProducts(string ProductsFile)
{
	f.open(ProductsFile);
	if (getline(f, line))
		line.erase();
	while (getline(f, line)) {
		string prod = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		double price = stof(line.substr(0, line.length()));
		productsV.push_back(Products(prod, price));
	}
	f.close();
}

void Menu::WriteProducts(string ProductsFile) // Writes on file finnished products vector
{
	ofstream f;
	unsigned int i;
	f.open(ProductsFile);
	f << productsV.size() << endl;
	for (i = 0; i < productsV.size(); i++)
	{
		f << productsV.at(i).getProductName() << " ; " << productsV.at(i).getProductPrice() << endl;
	}
	f.close();
	return;
}

void Menu::ListProducts()
{
	Utilities u;
	int a = -1;
	while (a != 2)
	{
		Utilities u;
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                         Product List                         |\n";
		cout << setw(0) << "================================================================\n\n";
		cout << "\tRef.\t\t\tName\t\tPrice\n";
		for (unsigned int i = 0; i < productsV.size(); i++)
		{
			ostringstream ref;
			ref << "[" << i + 1 << "] ";
			u.setcolor(11);
			cout << setw(13) << ref.str();
			u.setcolor(15); 
			cout << setw(23) << productsV.at(i).getProductName();
			cout << setw(17) <<setprecision(2) << fixed << productsV.at(i).getProductPrice() << endl;
			ref.str("");
			ref.clear();
		}
		cout << setw(0) << "\n================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Add Product"; u.setcolor(3); cout << "\t\t2. "; u.setcolor(15); cout << "Exit to Menu" << endl;
		cout << setw(0) << "\n================================================================\n";
		int a;
		cout << "\nInsert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
			ListProducts();
		}
		switch (a)
		{
		case 1:
			AddProducts();
			break;
		case 2:
			return;
			break;
		default:
		{
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		}
	}
	return;
}

void Menu::Bottom10()
{
	int a=-1;
	while (a != 1)
	{
		Utilities u;
		vector <Clients> bottomV = clientsV;

		sort(bottomV.begin(), bottomV.end(), [](Clients &a, Clients &b) {return a.getClientValueSpent() < b.getClientValueSpent(); });
		system("cls");
		cin.clear();
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                           Bottom 10                          |\n";
		cout << setw(0) << "================================================================\n\n";
		cout << setw(5) << "ID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		for (unsigned int i = 0; i < 10; i++) // Shows list of clients
		{
			cout << setw(5) << bottomV.at(i).getClientID();
			cout << setw(27) << bottomV.at(i).getClientName();
			cout << setw(15) << bottomV.at(i).getClientDate();
			cout << setw(10) << setprecision(2) << fixed << bottomV.at(i).getClientValueSpent() << endl;
		}
		if (bottomV.size() < 10)
		{
			u.setcolor(12);
			cout << "\a\nWarning: Less than 10 created clients!";
			u.setcolor(15);
		}
		cout << setw(0) << "\n\n================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Exit to Client List" << endl;
		cout << setw(0) << "\n================================================================\n" << endl;
		cout << "Insert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			cout << "Please reinsert your option: ";
			cin >> a;
		}
		switch (a)
		{
		case 1:
			return;
			break;
		default:
		{
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		}
	}
	return;
}	

void Menu::ListClientsOrd()
{
	int a = -1;
	while (a != 1)
	{
		Utilities u;
		vector <Clients> clientsOrdV = clientsV;

		sort(clientsOrdV.begin(), clientsOrdV.end(), [](Clients &a, Clients &b) {return a.getClientName() < b.getClientName(); });
		system("cls");
		cin.clear();
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                      Ordered Client List                     |\n";
		cout << setw(0) << "================================================================\n\n";
		cout << setw(5) << "ID" << setw(27) << "Client Name" << setw(12) << "Date" << setw(19) << "Money Spent\n\n";
		for (unsigned int i = 0; i < clientsOrdV.size(); i++) // Shows list of clients
		{
			cout << setw(5) << clientsOrdV.at(i).getClientID();
			cout << setw(27) << clientsOrdV.at(i).getClientName();
			cout << setw(15) << clientsOrdV.at(i).getClientDate();
			cout << setw(10) << setprecision(2) << fixed << clientsOrdV.at(i).getClientValueSpent() << endl;
		}
		cout << setw(0) << "\n\n================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Exit to Client List" << endl;
		cout << setw(0) << "\n================================================================\n" << endl;
		int a;
		cout << "Insert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
			return;
		}
		switch (a)
		{
		case 1:
			return;
			break;
		default:
		{
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		}
	}
	return;
}

void Menu::AddProducts()
{
	Utilities u;
	system("cls");
	cout << setw(0) << "================================================================\n";
	cout << setw(0) << "|                         Product List                         |\n";
	cout << setw(0) << "================================================================\n\n";
	cout << "\tHow many products do you want to add? ";
	int unsigned howmany;
	cin >> howmany;
	while (cin.fail())
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		u.setcolor(12);
		cerr << "\n\t\a> Not a valid number!\n";
		u.setcolor(15);
		cout << "\n\tPlease reinsert how many products do you want to add: ";
		cin >> howmany;
	}
	for (unsigned int i = 0; i < howmany; i++)
	{
		cout << "\n\tWhat is the name of the product you want to add?\n\t>";
		string name;
		cin.clear();
		cin.ignore();
		getline(cin,name);
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a\t> Not a valid name!\n";
			u.setcolor(15);
			cout << "\n\tPlease reinsert product name: ";
			getline(cin, name);
		}
		cout << "\n\tWhat is " << name << "'s price?\n\t>";
		double price;
		cin >> price;
		while (cin.fail())
		{
			if (cin.eof())	
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a\t> Not a valid price!\n";
			u.setcolor(15);
			cout << "\n\tPlease reinsert product's price: ";
			cin >> price;
		}
		productsV.push_back(Products(FormatName(name), price));
	}
	u.setcolor(14);
	cout << "\n\nOperation Complete\nGoing back to Product List"; Sleep(400); cout << "."; Sleep(400); cout << "."; Sleep(400); cout << "."; Sleep(400); // Displays a nice "thinking" animation (can be removed if it slows the programm too much)
	u.setcolor(15);
	return;
}

//Transactions

void Menu::ExtractTransactions(string TransactionsFile)
{
	vector<string> temptransactionsV;
	f.open(TransactionsFile);
	if (getline(f, line))
		line.erase();

	while (getline(f, line)) {
		unsigned int id = stoi(line.substr(0, line.find(" ; ")));
		line.erase(0, line.find(" ; ") + 3);
		string date = line.substr(0, line.find(" ; "));
		line.erase(0, line.find(" ; ") + 3);
		string products = line.substr(0, line.length());
		while (true)
		{
			if (products.find(", ") == -1) 
			{
				temptransactionsV.push_back(products);
				break;
			}
			temptransactionsV.push_back(products.substr(0, products.find(", ")));
			products.erase(0, products.find(", ") + 2);
		}
		transactionsV.push_back(Transactions(id,date, temptransactionsV));
		temptransactionsV.clear();
	}
	f.close();
}

void Menu::WriteTransactions(string TransactionsFile) // Writes on file finnished transactions vector
{
	ofstream f;
	unsigned int i;
	f.open(TransactionsFile);
	f << transactionsV.size() << endl;
	for (i = 0; i < transactionsV.size(); i++)
	{
		f << transactionsV.at(i).GetId() << " ; " << transactionsV.at(i).GetDate() << " ; ";
		//Analisa o vetor dos produtos para cada linha da transação.
		for (unsigned int index2 = 0; index2 != transactionsV[i].GetProducts().size(); index2++) 
		{
			f << transactionsV[i].GetProducts()[index2];

			//Verifica se chegou ao fim do vetor dos produtos.
			if (index2 != transactionsV[i].GetProducts().size() - 1)
			{
				f << ", ";
			}
			else
				f << endl;
		}
	}
	f.close();
	return;
}

void Menu::ListTransactions()
{
	Utilities u;
	int list = -1;
	while (list != 5)
	{
		Date D;
		system("cls");
		cout << setw(0) << "=======================================================================================================================\n";
		cout << setw(0) << "|                                                   Transations List                                                  |\n";
		cout << setw(0) << "=======================================================================================================================\n\n"; 
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Client's ID"; u.setcolor(3); cout << "\t\t2. "; u.setcolor(15); cout << "Day's";  u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << "Between Two Dates";  u.setcolor(3); cout << "\t4. "; u.setcolor(15); cout << "All Transactions"; u.setcolor(3); cout << "\t5. "; u.setcolor(15); cout << "Exit to Menu\n";
		cout << setw(0) << "\n=======================================================================================================================\n";
		cout << setw(10) << "\nWhich transactions do you want to see?: ";
		cin >> list;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
		}
		switch (list)
		{

		case 1:
		{
			system("cls");
			cout << setw(0) << "=======================================================================================================================\n";
			cout << setw(0) << "|                                                   Transations List                                                  |\n";
			cout << setw(0) << "=======================================================================================================================\n\n";
			cout << "Which client do you want to look for?: ";
			int ID;
			cin >> ID;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> Not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert ID: ";
				cin >> ID;
			}
			cout << endl << setw(5) << "ID" << setw(12) << "Date" << setw(14) << "Products\n\n";
			bool IDinVec = false;
			for (unsigned int i = 0; i < transactionsV.size(); i++)
			{
				if (ID == transactionsV.at(i).GetId()) // Looks for ID's purchase
				{
					IDinVec = true;
					cout << right << setw(5) << transactionsV.at(i).GetId();
					cout << right << setw(12) << transactionsV.at(i).GetDate() << "     ";
					for (unsigned int j = 0; j < transactionsV.at(i).GetProducts().size(); j++)
					{
						cout << transactionsV.at(i).GetProducts().at(j);
						if (j != transactionsV[i].GetProducts().size() - 1)
						{
							cout << ", ";
						}
						else
							cout << endl;
					};
				};
			};
			if (IDinVec == false) // NOT found error
			{
				u.setcolor(12);
				cerr << "\a> There are no transactions for that client!\n";
				u.setcolor(15);
			}
		};
		break;

		case 2:
		{
			system("cls");
			cout << setw(0) << "=======================================================================================================================\n";
			cout << setw(0) << "|                                                   Transations List                                                  |\n";
			cout << setw(0) << "=======================================================================================================================\n\n";
			cout << "Which day's transactions do you want to see?\n";
			string date;
			int day, month, year;
			cout << "Day: ";
			cin >> day;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert day: ";
				cin >> day;
			}
			cout << "Month: ";
			cin >> month;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert month: ";
				cin >> month;
			}
			cout << "Year: ";
			cin >> year;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert year: ";
				cin >> year;
			}
			while (!D.Valid(day, month, year))
			{
				u.setcolor(12);
				cerr << "\a> That date is unvalid!\n";
				u.setcolor(15);
				cout << "Please reinsert a date: \n";
				cout << "Day: ";
				cin >> day;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert day: ";
					cin >> day;
				}
				cout << "Month: ";
				cin >> month;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert month: ";
					cin >> month;
				}
				cout << "Year: ";
				cin >> year;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert year: ";
					cin >> year;
				}
			}
			ostringstream oss;
			if (month < 9)
			{
				if (day < 9)
					oss << "0" << day << "/0" << month << "/" << year;
				else
					oss << day << "/0" << month << "/" << year;
			}
			else
			{
				if (day < 9)
					oss << "0" << day << "/" << month << "/" << year;
				else
					oss << day << "/" << month << "/" << year;
			}
			system("cls");
			cout << setw(0) << "=======================================================================================================================\n";
			cout << setw(0) << "|                                                   Transations List                                                  |\n";
			cout << setw(0) << "=======================================================================================================================\n\n";
			cout << "Transactions from " << oss.str() << " :\n\n";
			cout << setw(5) << "ID" << setw(12) << "Date" << setw(14) << "Products\n\n";
			date = oss.str();
			bool DateinVec = false;
			for (unsigned int i = 0; i < transactionsV.size(); i++)
			{
				if (date == transactionsV.at(i).GetDate())
				{
					DateinVec = true;
					cout << right << setw(5) << transactionsV.at(i).GetId();
					cout << right << setw(12) << transactionsV.at(i).GetDate() << "     ";
					for (unsigned int j = 0; j < transactionsV.at(i).GetProducts().size(); j++)
					{
						cout << transactionsV.at(i).GetProducts().at(j);
						if (j != transactionsV[i].GetProducts().size() - 1)
						{
							cout << ", ";
						}
						else
							cout << endl;
					};
				};
			};
			if (DateinVec == false)
			{
				u.setcolor(12);
				cerr << "\a> There are no transactions in that date!\n";
				u.setcolor(15);
			}
		};
		break;

		case 3:
		{
			system("cls");
			cout << setw(0) << "=======================================================================================================================\n";
			cout << setw(0) << "|                                                   Transations List                                                  |\n";
			cout << setw(0) << "=======================================================================================================================\n\n";
			cout << "Between which days do you want to see transactions from?\n";
			int day, month, year, date1, date2;
			cout << "From:\nDay: ";
			cin >> day;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert day: ";
				cin >> day;
			}
			cout << "Month: ";
			cin >> month;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert month: ";
				cin >> month;
			}
			cout << "Year: ";
			cin >> year;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert year: ";
				cin >> year;
			}
			while (!D.Valid(day, month, year))
			{
				u.setcolor(12);
				cerr << "\a> That date is unvalid!\n";
				u.setcolor(15);
				cout << "Please reinsert a date: \n";
				cout << "Day: ";
				cin >> day;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert day: ";
					cin >> day;
				}
				cout << "Month: ";
				cin >> month;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert month: ";
					cin >> month;
				}
				cout << "Year: ";
				cin >> year;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert year: ";
					cin >> year;
				}
			}
			ostringstream d1, dat1;
			if (month > 9)
				d1 << day << "/" << month << "/" << year;
			else
				d1 << day << "/0" << month << "/" << year;

			if (month > 9)
				dat1 << year << month << day;
			else
				dat1 << year << 0 << month << day;

			cout << "To:\nDay: ";
			cin >> day;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert day: ";
				cin >> day;
			}
			cout << "Month: ";
			cin >> month;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert month: ";
				cin >> month;
			}
			cout << "Year: ";
			cin >> year;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> That is not a valid number!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert year: ";
				cin >> year;
			}
			while (!D.Valid(day, month, year))
			{
				u.setcolor(12);
				cerr << "\a> That date is unvalid!\n";
				u.setcolor(15);
				cout << "Please reinsert a date: \n";
				cout << "Day: ";
				cin >> day;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert day: ";
					cin >> day;
				}
				cout << "Month: ";
				cin >> month;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert month: ";
					cin >> month;
				}
				cout << "Year: ";
				cin >> year;
				while (cin.fail())
				{
					if (cin.eof())
					{
						cin.clear();
						return;
					}
					cin.clear();
					cin.ignore(1000, '\n');
					u.setcolor(12);
					cerr << "\a> That is not a valid number!\n";
					u.setcolor(15);
					cout << "\nPlease reinsert year: ";
					cin >> year;
				}
			}
			ostringstream d2, dat2;
			if (month > 9)
				d2 << day << "/" << month << "/" << year;
			else
				d2 << day << "/0" << month << "/" << year;

			if (month > 9)
				dat2 << year << month << day;
			else
				dat2 << year << 0 << month << day;

			istringstream iss1(dat1.str());
			iss1 >> date1;
			istringstream iss2(dat2.str());
			iss2 >> date2;
			system("cls");
			cout << setw(0) << "=======================================================================================================================\n";
			cout << setw(0) << "|                                                   Transations List                                                  |\n";
			cout << setw(0) << "=======================================================================================================================\n\n";
			cout << "Transactions from " << d1.str() << " to " << d2.str() << " :\n\n";
			cout << setw(5) << "ID" << setw(12) << "Date" << setw(14) << "Products\n\n";
			bool DateinVec = false;
			string DateDigits, CompleteDate;
			int DateInteger;
			for (unsigned int i = 0; i < transactionsV.size(); i++)
			{
				CompleteDate = transactionsV.at(i).GetDate(); // Complete Date
				DateDigits = CompleteDate.substr(CompleteDate.find_last_of("/") + 1, CompleteDate.size() - CompleteDate.find_last_of("/") - 1);  //"Push" year
				DateDigits.append(CompleteDate.substr(CompleteDate.find_first_of("/") + 1, CompleteDate.find_last_of("/") - CompleteDate.find_first_of("/") - 1));  //"Push" month
				DateDigits.append(CompleteDate.substr(0, DateDigits.find_first_of("/"))); //"Push" day : Format ---> yearmonthday
				DateInteger = stoi(DateDigits, nullptr, 10); //Convert to integer

				if ((DateInteger >= date1) && (DateInteger <= date2))
				{
					DateinVec = true;
					cout << right << setw(5) << transactionsV.at(i).GetId();
					cout << right << setw(12) << transactionsV.at(i).GetDate() << "     ";
					for (unsigned int j = 0; j < transactionsV.at(i).GetProducts().size(); j++)
					{
						cout << transactionsV.at(i).GetProducts().at(j);
						if (j != transactionsV[i].GetProducts().size() - 1)
						{
							cout << ", ";
						}
						else
							cout << endl;
					};
				}
			}
			if (DateinVec == false)
			{
				u.setcolor(12);
				cerr << "\a> There are no transactions between the specified dates!\n";
				u.setcolor(15);
			}
		};
		break;

		case 4:
		{
			cout << endl << setw(5) << "ID" << setw(12) << "Date" << setw(14) << "Products\n\n";
			for (unsigned int i = 0; i < transactionsV.size(); i++)
			{
				cout << right << setw(5) << transactionsV.at(i).GetId();
				cout << right << setw(12) << transactionsV.at(i).GetDate() << "     ";
				for (unsigned int j = 0; j < transactionsV.at(i).GetProducts().size(); j++)
				{
					cout << transactionsV.at(i).GetProducts().at(j);
					if (j != transactionsV[i].GetProducts().size() - 1)
					{
						cout << ", ";
					}
					else
						cout << endl;
				};
			};
		}
		break;
		case 5:
			return;
			break;

		default:
		{
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		};
		cout << right << setw(0) << "\n=======================================================================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Exit to Menu\n";
		cout << setw(0) << "\n=======================================================================================================================" << endl;
		int a=-1;
		cout << endl << "Insert your option: ";
		while (a != 1)
		{
			cin >> a;
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\n\a> No such option in menu!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert your option: ";
				cin >> a;
			}
			switch (a)
			{
			case 1:
				return;
				break;
			default:
			{
				u.setcolor(12);
				cerr << "\a> No such option in menu!\n";
				u.setcolor(15);
				cout << "\nPlease reinsert your option: ";
			}
			}
		}
	}
	return;
}

void Menu::MakePurchase()
{
	unsigned int ID;
	Utilities u;
		system("cls");
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                         Make Purchase                        |\n";
		cout << setw(0) << "================================================================\n\n";
		bool existence = false;
		while (true)
		{
			cout << "Which Client made the purchase(ID)?: ";
			cin >> ID; // Asks for Client ID
			while (cin.fail())
			{
				if (cin.eof())
				{
					cin.clear();
					return;
				}
				cin.clear();
				cin.ignore(1000, '\n');
				u.setcolor(12);
				cerr << "\a> No such option in menu!\n";
				u.setcolor(15);
				cout << "Which Client made the purchase(ID)?: ";
				cin >> ID;
			}
			for (unsigned int i = 0; i < clientsV.size(); i++)
			{
				if (ID == clientsV.at(i).getClientID()) // Checks if given ID exists
				{
					existence = true;
				}
			}
			if (existence != true) // Error if it doesn't and restarts MakePurchase
			{
				u.setcolor(12);
				cerr << "\a> Client ID does not exist! \n";
				u.setcolor(15);
			}
			else break;
		}
		time_t tt = time(0);   // get time now
		struct tm * now = localtime(&tt);
		ostringstream oss;
		if ((now->tm_mon + 1) > 9) // Adds a zero before the month if month < 9
		{
			oss << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
		}
		else
		{
			oss << now->tm_mday << "/0" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
		};
		cout << setw(0) << "\n================================================================\n\n";
		cout << "\tRef.\t\t\tName\t\tPrice\n";
		for (unsigned int i = 0; i < productsV.size(); i++)
		{
			ostringstream ref;
			ref << "[" << i + 1 << "] ";
			u.setcolor(11);
			cout << setw(13) << ref.str();
			u.setcolor(15);
			cout << setw(23) << productsV.at(i).getProductName();
			cout << setw(17) << setprecision(2) << fixed << productsV.at(i).getProductPrice() << endl;
			ref.str("");
			ref.clear();
		}
		cout << setw(0) << "\n================================================================\n\n";
		cout << "Write product references for which products the client wants to buy?\nWhen there is no more products to add write '0'\n"; // Asks for product references
		string reference; // It's a string because we want to avoid errors when reference given is a letter since giving letters to an Int returns 0
		vector <string> list;
		double Subtotal = 0;
		while (true)
		{
			cin >> reference;
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			unsigned int converted = atoi(reference.c_str()); // Converts to Integer
			if (reference == "0") // Terminates if '0' is given
				break;
			else if (converted == 0) // A letter when converted to int returns 0
			{
				u.setcolor(12);
				cerr << "\a> References are numbers! Not letters! \n";
				u.setcolor(15);
			}
			else
			{
				if (converted <= productsV.size()) // Checks if product exists
				{
					list.push_back(productsV.at(converted - 1).getProductName());
					cout << "Product added! "; // Adds the product
					clientsV.at(ID - 1).setClientValueSpent(productsV.at(converted - 1).getProductPrice() + clientsV.at(ID - 1).getClientValueSpent());
					Subtotal += productsV.at(converted - 1).getProductPrice();
					u.setcolor(14);
					cout << "Subtotal : " << Subtotal << " EUR" << endl;
					u.setcolor(15);
				}
				else
				{
					u.setcolor(12);
					cerr << "\a> Reference does not exist!\n"; // Error
					u.setcolor(15);
				}
			}
		}
		if (!list.empty()) // Only adds to transactions vector if any reference was given
		{
			u.setcolor(14);
			cout << "Total : " << Subtotal << " EUR" << endl;
			u.setcolor(15);
			string date = oss.str();
			transactionsV.push_back(Transactions(ID, date, list)); // Sends purchase to transactions vector
		}
		cout << right << setw(0) << "\n================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Make Purchase"; u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "Exit to Menu" << endl;
		cout << setw(0) << "\n================================================================" << endl;
		int a;
		cout << endl << "Insert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				return;
			} 
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			cout << "\nPlease reinsert your option: ";
			cin >> a;
		}
		switch (a)
		{
		case 1:
			MakePurchase();
			break;
		case 2:
			return;
			break;
		};
	return;
}

//Publicidade

// estrutura para o vetor de produtos recomendados
struct ProdutosRecomendados
{
	string produto;
	int total;
};

// algoritmo que obtem o valor maximo de um vetor de inteiros
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
	if (first == last) return last;
	ForwardIterator largest = first;

	while (++first != last)
		if (*largest < *first)    // or: if (comp(*largest,*first)) for version (2)
			largest = first;
	return largest;
}


bool Menu::transExisteID(int id)
{
	for (unsigned int i = 0; i < transactionsV.size(); i++)
	{
		if (transactionsV.at(i).GetId() == id)
			return true;
	}
	return false;
}

// publicidade para um cliente alvo
int Menu::IndividualAdvertising()
{
	Utilities u;
	int id;

	cout << endl << "Please insert client ID: ";  cin >> id;

	if (transExisteID(id)) //verifica se o cliente realizou transacoes
	{
		vector<unsigned int> all_clients;    //vetor com os id clientes existentes e os que ja foram apagados mas possuem transacooes

		for (unsigned int i = 0; i < transactionsV.size(); i++) //percorre o vetor de transacoes
		{
			if (find(all_clients.begin(), all_clients.end(), transactionsV[i].GetId()) == all_clients.end()) //verifica se o id da transaçao na posiçao i ja existe no vetor all_clients
			{
				all_clients.push_back(transactionsV[i].GetId()); //adiciona se nao existir
			}
		}

		for (unsigned int  i = 0; i < all_clients.size(); i++)
		{
			Client_IdIx.insert(make_pair(all_clients.at(i), i)); //preenche o map de clientes com os clientes existentes no vetor all_clients e a sua posiçao
		}

		for (unsigned int  i = 0; i < productsV.size(); i++)
		{
			Prod_Ix.insert(make_pair(productsV.at(i).getProductName(), i)); //preenche o map de produtos com os produtos existentes no vetor e a sua posiçao
		}


		//criacao da matriz
		vector<vector<bool>> matrix_target(all_clients.size(), vector<bool>(productsV.size(), false)); //inicia a matriz a false

		for (unsigned int  i = 0; i < transactionsV.size(); i++) //percorre o vetor produtos
		{
			for (unsigned int  a = 0; a < transactionsV.at(i).GetProducts().size(); a++) //percorre o vetor de produtos em cada transacao
			{
				matrix_target[Client_IdIx[transactionsV[i].GetId()]][Prod_Ix[transactionsV[i].GetProducts().at(a)]] = true; // identifi  o cliente de cada transacao e na linha desse cliente na matriz coloque a true os produtos registados nessa transação
			}
		}

		// Parte para usar o id do cliente a recomendar

		if (find(all_clients.begin(), all_clients.end(), id) != all_clients.end()) //percorre o vetor all clients enquanto nao chega ao fim
		{
			vector<bool> client_recommend; //vetor igual à linha da matriz do cliente alvo
			vector<string> products_recommend; //vetor de potenciais produtos para recomendar

			for (unsigned int  i = 0; i < matrix_target.size(); i++)
			{
				if (i == Client_IdIx[id])
				{
					client_recommend = matrix_target[i];
				}
			}

			for (unsigned int  i = 0; i < matrix_target.size(); i++) //percorre todos os clientes da matriz
			{
				for (unsigned int  a = 0; a < matrix_target[i].size(); a++) //percorre cada produto de cada cliente
				{

					if (matrix_target[i][a] != client_recommend[a]) //se o bool do produto do cliente que esta a ser analizado for diferente do bool do mesmo produto do cliente alvo
					{
						int c = 0; //contador de produtos adicionados em cada cliente ao vetor de potenciais produtos a recomendar

						if (matrix_target[i][a] == true) // se o cliente que esta a ser analizado comprou o produto
						{
							products_recommend.push_back(productsV.at(a).getProductName()); //adiciona o produto à lista de potencias produtos
							c++; //adiciona ao contador
						}

						if (matrix_target[i][a] == false) //se o cliente alvo comprou o produto e o cliente que esta a ser analizado nao comprou
						{
							products_recommend.erase(products_recommend.end() - c, products_recommend.end()); //apaga os produtos adicinados ao vetor potencias produtos a reocmendar deste cliente
						}
					}
				}
			}

			// cria um vetor de produtos recomendados com a estrutura (nome do produto, numero de vezes que aparece)
			vector<ProdutosRecomendados> VPR;

			for (unsigned int  i = 0; i < products_recommend.size(); i++)
			{
				int t = 0; //numero de vezes que cada produto repete
				for (unsigned int  j = 0; j < products_recommend.size(); j++)
				{
					if (products_recommend.at(i) == products_recommend.at(j))
						t++;
				}
				ProdutosRecomendados novoelem; //criacao novo elemento
				novoelem.produto = products_recommend.at(i);
				novoelem.total = t;
				VPR.push_back(novoelem);
			}

			// elimina os produtos repetidos, de maneira a ficar apenas uma vez cada produto
			if (VPR.size() > 1)
			{
				for (unsigned int  i = 0; i < VPR.size(); i++)
				{
					for (unsigned int  j = 1; j < VPR.size(); j++)
					{
						if (VPR.at(i).produto == VPR.at(j).produto)
							VPR.erase(VPR.begin() + j);
					}
				}
				if (VPR.size() > 1)
				{
					// cria um vetor com todos os totais dos produtos, de maneira a calcular o total maximo, ou seja, o produto mais frequente
					vector<int> Totais;
					vector<int>::iterator result;
					int totalMaximo;
					for (unsigned int  i = 0; i < VPR.size(); i++)
					{
						Totais.push_back(VPR.at(i).total);
					}
					result = std::max_element(Totais.begin(), Totais.end()); // retorna a posicao do maior elemento (comecando em 1)
					totalMaximo = Totais.at(std::distance(Totais.begin(), result) + 1);

					//display dos produtos recomendados, os mais frequentes
					u.setcolor(14); cout << "\n> ";  u.setcolor(15); cout << "Recomended product(s):\n";
					for (unsigned int  i = 0; i < VPR.size(); i++)
					{
						if (totalMaximo == VPR.at(i).total)
						{
							u.setcolor(11); cout << "   - ";  u.setcolor(15); cout << VPR.at(i).produto << endl;
						}
					}
				}
				else
				{
					u.setcolor(14); cout << "\n> ";  u.setcolor(15); cout << "Recomended product(s):\n";
					for (unsigned int  i = 0; i < VPR.size(); i++)
					{
						u.setcolor(11); cout << "   - ";  u.setcolor(15); cout << VPR.at(i).produto << endl;
					}
				}
			}
			else
			{
				u.setcolor(14); cout << "\n> ";  u.setcolor(15); cout << "Recomended product(s):\n";
				for (unsigned int  i = 0; i < VPR.size(); i++)
				{
					u.setcolor(11); cout << "   - ";  u.setcolor(15); cout << VPR.at(i).produto << endl;
				}
			}
		}
		u.setcolor(4); cout << "\nPress any key to go back..."; u.setcolor(15); getchar();

		
	}
	else
	{
		u.setcolor(4); cout << "\nThis Client hasn't made any purchase.\n";
		u.setcolor(4); cout << "\nPress any key to go back..."; u.setcolor(15); getchar();
	}

	getchar();
	return 0;
}

void Menu::Bottom10Advertising()
{
	vector<Clients>bottom10 = clientsV;
	vector<int>bottom10_ids;
	vector<Transactions>bottom10_trans;
	vector<Clients>interessantes;
	vector<int> interessantes_ids;
	vector<Transactions>interessantes_trans;

	sort(bottom10.begin(), bottom10.end(), [](Clients &a, Clients &b) {return a.getClientValueSpent() < b.getClientValueSpent(); });

	//preenche o vetor de interessantes com os clientes que importam
	if (bottom10.size() > 10)
	{
		for (unsigned int i = 10; i < bottom10.size(); i++)
			interessantes.push_back(bottom10[i]);

		bottom10.erase(bottom10.begin() + 10, bottom10.end());
	}

	//preenche o bottom10_ids
	for (unsigned int i = 0; i < bottom10.size(); i++)
	{
		bottom10_ids.push_back(bottom10[i].getClientID());
	}

	//guarda apenas as transacoes dos bottom10
	for (unsigned int i = 0; i < transactionsV.size(); i++)
	{
		for (unsigned int j = 0; j < bottom10_ids.size(); j++)
		{
			if (transactionsV[i].GetId() == bottom10_ids[j])
				bottom10_trans.push_back(transactionsV[i]);
		}
	}

	//preenche o interessantes_ids
	for (unsigned int i = 0; i < interessantes.size(); i++)
	{
		interessantes_ids.push_back(interessantes[i].getClientID());
	}

	//guarda apenas as transacoes dos clientes interessantes
	for (unsigned int i = 0; i < transactionsV.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_ids.size(); j++)
		{
			if (transactionsV[i].GetId() == interessantes_ids[j])
				interessantes_trans.push_back(transactionsV[i]);
		}
	}

	//adiciona valores ao map clientIdx
	for (unsigned int i = 0; i < bottom10.size(); i++)
	{
		clientIdx[bottom10_ids.at(i)] = i;
	}

	//adiciona valores ao map produtoIdx
	for (unsigned int i = 0; i < productsV.size(); i++)
	{
		productIdx.insert(make_pair(productsV.at(i).getProductName(), i));
	}

	vector<vector<bool>>matriz_bottom10(bottom10.size(), vector<bool>(productsV.size(), false)); //Cria a matriz

																								// preenche a matriz de true nos produtos adquiridos por cada cliente
	for (unsigned int i = 0; i < bottom10_trans.size(); i++)
	{
		for (unsigned int j = 0; j < bottom10_trans[i].GetProducts().size(); j++)
		{
			matriz_bottom10[clientIdx[bottom10_trans[i].GetId()]][productIdx[bottom10_trans[i].GetProducts().at(j)]] = true;
		}
	}

	vector<bool>pro_comuns(productsV.size(), false); //posicao dos produtos comuns aos bottom10

													//coloca a true a posicao do vetor dos produtos comuns correspondente ao produto comum
	for (unsigned int i = 0; i < productsV.size(); i++)
	{
		for (unsigned int j = 0; j < bottom10.size(); j++)
		{
			if (matriz_bottom10[clientIdx[j]][i])
				pro_comuns[i] = true;
			else
			{
				pro_comuns[i] = false;
				break;
			}
		}
	}

	//Cria map igual a clientIdx
	map<int, int>cliente_interessanteIdx;

	for (unsigned int i = 0; i < interessantes.size(); i++)
	{
		cliente_interessanteIdx[interessantes_ids.at(i)] = i;
	}

	vector<vector<bool>>matriz_interessantes(interessantes.size(), vector<bool>(productsV.size(), false)); //Cria a matriz


	for (unsigned int i = 0; i < interessantes_trans.size(); i++) // preenche a matriz de true nos produtos adquiridos por cada cliente
	{
		for (unsigned int j = 0; j < interessantes_trans[i].GetProducts().size(); j++)
		{
			matriz_interessantes[cliente_interessanteIdx[interessantes_trans[i].GetId()]][productIdx[interessantes_trans[i].GetProducts().at(j)]] = true;
		}
	}

	vector<int>v;//vetor temporario que vai guardar os ids dos clientes interessantes "semelhantes"

	for (unsigned int i = 0; i < pro_comuns.size(); i++)
	{
		if (pro_comuns[i])
		{
			for (unsigned int j = 0; j < interessantes_ids.size(); j++)
			{
				if (matriz_interessantes[cliente_interessanteIdx[interessantes_ids[j]]][i])
					v.push_back(interessantes_ids[j]);
			}
		}
	}
	interessantes_ids = v;


	vector<vector<bool>>matriz_final;//Cria a matriz
	vector<Transactions>interessantes_final_trans;//vetor que contem transacoes dos clientes interessantes "semelhantes"

	matriz_final.push_back(pro_comuns);

	for (unsigned int i = 0; i < transactionsV.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_ids.size(); j++)
		{
			if (transactionsV[i].GetId() == interessantes_ids[j])
				interessantes_final_trans.push_back(transactionsV[i]);
		}
	}

	//preenche a matriz de true nos produtos adquiridos por cada cliente
	for (unsigned int i = 0; i < interessantes_final_trans.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_final_trans[i].GetProducts().size(); j++)
		{
			matriz_final[clientIdx[interessantes_final_trans[i].GetId()]][productIdx[interessantes_final_trans[i].GetProducts().at(j)]] = true;
		}
	}

	vector<int> coluna(productsV.size(), 0); //vetor para ver quantas trues ha numa coluna

	for (unsigned int i = 0; i < interessantes_ids.size(); i++)
	{
		for (unsigned int j = 0; j < productsV.size(); j++)
		{
			if (!pro_comuns[j] && matriz_final[i][j])
				coluna[j] = coluna[j] + 1;
		}
	}

	int a; //Produto mais comprado pelo cliente semelhante e nao comprado pelo cliente alvo
	int b; //Posicao no vetor dos produtos


	if (interessantes_ids.size() == 0) {
		cout << "There is no suggested product... " << endl;
		_getch();
	}
	else {
		for (unsigned int i = 0; i < coluna.size(); i++)
		{
			if ((i + 1) == coluna.size() && coluna[i] > coluna[i - 1]) {
				a = coluna[i];
				b = i;
			}
			else if ((i + 1) == coluna.size()) {
				break;
			}
			else if (coluna[i] > coluna[i + 1]) {
				a = coluna[i];
				b = i;
			}
		}
		cout << "The suggested product for the bottom 10 clients is: " << productsV[b].getProductName() << endl;
		_getch();
	}
}

//Extra

void Menu::SplitName(string full, vector <string> &temp)
{
	string delimiter = " ";
	temp.clear();
	string token = full.substr(0, full.find(delimiter));

	temp.push_back(token);
	full.erase(0, full.find(delimiter) + 1);
	token = full.substr(0, full.find(delimiter));
	temp.push_back(token);
	temp.push_back(full);

	return;
} // Splits Client name in First and Last name

void Menu::Options()
{
	Utilities u;
	int a=-1;
	while (a != 0)
	{
		system("cls"); // clear window
		cout << setw(0) << "================================================================\n";
		cout << setw(0) << "|                             Menu                             |\n";
		cout << setw(0) << "================================================================\n\n";
		u.setcolor(3); cout << "\t1. "; u.setcolor(15); cout << "Client List";  u.setcolor(3); cout << "\t\t5. "; u.setcolor(15); cout << "Available Products" << endl;
		u.setcolor(3); cout << "\t2. "; u.setcolor(15); cout << "Manage Clients";  u.setcolor(3); cout << "\t6. "; u.setcolor(15); cout << "Personalized Advertising" << endl;
		u.setcolor(3); cout << "\t3. "; u.setcolor(15); cout << "Make Purchase";  u.setcolor(3); cout << "\t7. "; u.setcolor(15); cout << "Bottom10 Advertising" << endl;
		u.setcolor(3); cout << "\t4. "; u.setcolor(15); cout << "Transactions";  u.setcolor(3); cout << "\t\t0. "; u.setcolor(15); cout << "Exit Software" << endl;
		cout << setw(0) << "\n================================================================\n";
		cout << "\nInsert your option: ";
		cin >> a;
		while (cin.fail())
		{
			if (cin.eof())
			{
				cin.clear();
				ExitProgram();
			}
			cin.clear();
			cin.ignore(1000, '\n');
			u.setcolor(12);
			cerr << "\a> No such option in menu!\n";
			u.setcolor(15);
			Sleep(1000);
		}
		switch (a)
		{
		case 1:
			ListClients();
			break;
		case 2:
			ManageClients();
			break;
		case 3:
			MakePurchase();
			break;
		case 4:
			ListTransactions();
			break;
		case 5:
			ListProducts();
			break;
		case 6:
			IndividualAdvertising();
		break;
		case 7:
			Bottom10Advertising();
		break;
		case 0:
		{
			ExitProgram();
		}
		break;
		}
	};
	return;
}

void Menu::ExitProgram()
{
	Utilities u;
	system("cls");
	WriteClients(ClientsFile);
	WriteProducts(ProductsFile);
	WriteTransactions(TransactionsFile);
	cout << "\a";
	cout << "================================================================\n";
	cout << "|                     VENDE++ Super Market                     |\n";
	cout << "| "; u.setcolor(10); cout << "        __     __             _                             "; u.setcolor(15); cout << " |" << endl;
	cout << "| "; u.setcolor(10); cout << "        \\ \\   / /__ _ __   __| | ___     _       _  " << char(184) << "     "; u.setcolor(15); cout << "   |" << endl;
	cout << "| "; u.setcolor(10); cout << "         \\ \\ / / _ \\ '_ \\ / _` |/ _ \\  _| |_   _| |_    "; u.setcolor(15); cout << "     |" << endl;
	cout << "| "; u.setcolor(10); cout << "          \\ V /  __/ | | | (_| |  __/ |_   _| |_   _|      "; u.setcolor(15); cout << "  |" << endl;
	cout << "| "; u.setcolor(10); cout << "           \\_/ \\___|_| |_|\\__,_|\\___|   |_|     |_|      "; u.setcolor(15); cout << "    |" << endl;
	cout << "|                                                              |" << endl;
	cout << "|                      Management Sofware                      |\n";
	cout << "|                   Developed by "; u.setcolor(14); cout << "Afonso Ramos"; u.setcolor(15); cout << "                  |\n";
	cout << "================================================================\n\n";
	cout << "\n             Thank you for using this software!";
	Sleep(2500);
	exit(0);
}
