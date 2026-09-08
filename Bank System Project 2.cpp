#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

const string FileName = "Clients.text";

enum enMainOperation { Show = 1, Add, Delete, Update, Find, Transactions, Exit };

enum enTransactionOption {Deposit = 1, Withdraw, TotalBalances, MainMenue};

struct stClient
{
	string AccountNum;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDeleted = false;
};

void ShowMainScreen();

enMainOperation UserChoice()
{
	short ch = 0;
	do
	{
		cout << "Choose What do you want to do? [1 to 7]: ";
		cin >> ch;
	} while (ch < 1 || ch > 7);

	return enMainOperation(ch);
}

void GoBackToMainMenue()
{
	cout << "\nPress any Key to go back to Main Menue....";
	system("pause>0");
	ShowMainScreen();
}

bool IsFound(vector <stClient> vClients, string AccountNum, stClient& client)
{
	for (stClient& c : vClients)
	{
		if (AccountNum == c.AccountNum)
		{
			client = c;
			return true;
		}
	}
	return false;
}

//# Show CLients
vector <string> Split(string line, string seperator)
{
	vector <string> vWords;
	short pos = 0;
	string word;
	while ((pos = line.find(seperator)) != std::string::npos)
	{
		word = line.substr(0, pos);
		if (word != "")
			vWords.push_back(word);

		line.erase(0, pos + seperator.length());
	}
	if (line != "")
		vWords.push_back(line);

	return vWords;
}

stClient ConvertLineToRecord(string line, string seperator)
{
	stClient client;
	vector <string> vWords = Split(line, seperator);

	client.AccountNum = vWords[0];
	client.PinCode = vWords[1];
	client.Name = vWords[2];
	client.Phone = vWords[3];
	client.AccountBalance = stod(vWords[4]);

	return client;
}

vector <stClient> ReadClientsFromFile()
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string line;
		while (getline(MyFile, line))
			vClients.push_back(ConvertLineToRecord(line, "#//#"));

		MyFile.close();
	}

	return vClients;
}

void ShowClients()
{
	vector <stClient> vClients = ReadClientsFromFile();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)";
	cout << "\n_____________________________________________________________________________________\n";
	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(30) << "Client Name";
	cout << "| " << left << setw(10) << "Phone";
	cout << "| " << left << setw(10) << "Balance";
	cout << "\n_____________________________________________________________________________________\n";

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available in the sysytem!\n";

	else
	{
		for (stClient& c : vClients)
		{
			cout << "| " << left << setw(16) << c.AccountNum
				<< "| " << left << setw(10) << c.PinCode
				<< "| " << left << setw(30) << c.Name
				<< "| " << left << setw(10) << c.Phone
				<< "| " << left << setw(10) << c.AccountBalance << endl;
		}
		cout << "_____________________________________________________________________________________\n";
	}
}


//# Add Client
bool ClientExitByAccountNum(string AccountNum, string FilName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string line;
		stClient client;
		while (getline(MyFile, line))
		{
			client = ConvertLineToRecord(line, "#//#");
			if (AccountNum == client.AccountNum)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(client);
		}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient()
{
	stClient client;
	cout << "Enter Account Number: ";
	getline(cin >> ws, client.AccountNum);

	while (ClientExitByAccountNum(client.AccountNum, FileName))
	{
		cout << "\nClient with [" << client.AccountNum << "] already exits, Enter another AccountNum: ";
		getline(cin >> ws, client.AccountNum);
	}

	cout << "Enter PinCode: ";
	getline(cin >> ws, client.PinCode);

	cout << "Enter Name: ";
	getline(cin, client.Name);

	cout << "Enter Phone: ";
	getline(cin, client.Phone);

	cout << "Enter AccountBalance: ";
	cin >> client.AccountBalance;

	return client;
}

string ConvertRecordToLine(stClient info, string seperator)
{
	string line = "";

	line += info.AccountNum + seperator;
	line += info.PinCode + seperator;
	line += info.Name + seperator;
	line += info.Phone + seperator;
	line += to_string(info.AccountBalance);

	return line;
}

void AddLineToFile(string line, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << line << endl;
		MyFile.close();
	}

}

void AddNewClient()
{
	stClient client = ReadNewClient();
	AddLineToFile(ConvertRecordToLine(client, "#//#"), FileName);
}

void AddClients()
{
	char addMore;
	do
	{
		cout << "Adding New Clients:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients(Y/N): \n";

		cin >> addMore;
	} while (tolower(addMore) == 'y');
}

void ShowAddNewClientsScreen()
{
	cout << "--------------------------------------------\n";
	cout << "\t\tAdd New Client Screen\n";
	cout << "---------------------------------------------\n";

	AddClients();
}

//# Delete Client
string ReadAccountNum()
{
	string n;
	cout << "\nEnter Account Number: ";
	cin >> n;

	return n;
}

void Print(stClient Client)
{
	cout << "\n\nThe Following are the client details:\n";
	cout << "----------------------------------------\n";
	cout << "Account Num    : " << Client.AccountNum;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n---------------------------------------\n";
}

void AddLineToFile(vector <stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClient& c : vClients)
		{
			if (!c.MarkForDeleted)
				MyFile << ConvertRecordToLine(c, "#//#") << endl;
		}
		MyFile.close();
	}

}

bool MarkClientForDelete(string AccountNum, vector <stClient>& vClients)
{
	for (stClient& c : vClients)
	{
		if (c.AccountNum == AccountNum)
		{
			c.MarkForDeleted = true;
			return true;
		}
	}
	return false;
}

void DeleteClient()
{
	vector <stClient> vClients = ReadClientsFromFile();
	cout << "--------------------------------------------\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "---------------------------------------------\n";

	string AccountNum = ReadAccountNum();
	stClient client;

	if (!IsFound(vClients, AccountNum, client))
		cout << "Client with Account Number (" << AccountNum << ") is Not Found!\n";
	else
	{
		Print(client);
		char ch;
		cout << "\n\nAre you sure you want to delete this client(Y/N): ";
		cin >> ch;

		if (tolower(ch) == 'y')
		{
			MarkClientForDelete(AccountNum, vClients);
			AddLineToFile(vClients);
			cout << "\nClient Deleted Successfuly.\n";
		}
	}
}


////# Update Client
stClient ChangeClient(string AccountNum)
{
	stClient client;
	client.AccountNum = AccountNum;

	cout << "Enter PinCode: ";
	getline(cin >> ws, client.PinCode);

	cout << "Enter Name: ";
	getline(cin, client.Name);

	cout << "Enter Phone: ";
	getline(cin, client.Phone);

	cout << "Enter AccountBalance: ";
	cin >> client.AccountBalance;

	return client;
}

void UpdateClientByAccountNum(string AccountNum, vector <stClient>& vClients)
{
	stClient client;

	if (!IsFound(vClients, AccountNum, client))
		cout << "Client with Account Number (" << AccountNum << ") is Not Found!\n";
	else
	{
		Print(client);
		char ch;
		cout << "\n\nAre you sure you want to update this client(Y/N): ";
		cin >> ch;

		if (tolower(ch) == 'y')
		{
			for (stClient& c : vClients)
			{
				if (c.AccountNum == AccountNum)
				{
					c = ChangeClient(AccountNum);
					break;
				}

			}
			AddLineToFile(vClients);
			cout << "\n\nClient updated Successfully.\n";
		}
	}
}

void UpdateClient()
{
	cout << "--------------------------------------------\n";
	cout << "\t\tUpdate Client Info Screen\n";
	cout << "---------------------------------------------\n";

	vector <stClient> vClients = ReadClientsFromFile();
	string AccountNum = ReadAccountNum();
	//stClient client;

	UpdateClientByAccountNum(AccountNum, vClients);
}

////# Find Client
void FindClient()
{
	vector <stClient> vClients = ReadClientsFromFile();
	cout << "--------------------------------------------\n";
	cout << "\t\tFind Client Screen\n";
	cout << "---------------------------------------------\n";

	string AccountNum = ReadAccountNum();
	stClient client;

	if (!IsFound(vClients, AccountNum, client))
		cout << "Client with Account Number [" << AccountNum << "] is Not Found!\n";
	else
		Print(client);
}

////# Exit
void ExitProgram()
{
	cout << "--------------------------------------------\n";
	cout << "\t\tProgram Ends :-)\n";
	cout << "---------------------------------------------\n";
	system("Pause>0");
}


////## Transactions
void ShowTransactionsScreen();

//***Deposit
void ChangeBalance(vector <stClient>& vClients, string AccountNum, double Amount)
{
	char ch;
	cout << "\nAre you sure you want to perform this transaction(Y/N): ";
	cin >> ch;

	if (tolower(ch) == 'y')
	{
		for (stClient& c : vClients)
		{
			if (c.AccountNum == AccountNum)
			{
				c.AccountBalance += Amount;
				AddLineToFile(vClients);
				cout << "\nDone Successfully, New Balance = " << c.AccountBalance << "\n";
				break;
			}
		}
	}
}

void deposit(vector <stClient>& vClients)
{
	stClient client;
	string AccountNum = ReadAccountNum();
	while (!IsFound(vClients, AccountNum, client))
	{
		cout << "\nClient with [" << AccountNum << "] deos Not exit.\n";
		AccountNum = ReadAccountNum();
	}
	Print(client);

	double DepositAmount = 0;
	cout << "\nPlease enter deposit amount: ";
	cin >> DepositAmount;

	ChangeBalance(vClients, AccountNum, DepositAmount);

}

void ShowDepositScreen()
{
	vector <stClient> vClients = ReadClientsFromFile();
	cout << "--------------------------------------------\n";
	cout << "\t\tDeposit Screen\n";
	cout << "---------------------------------------------\n";

	deposit(vClients);
}


//**Withdraw
void withDraw(vector <stClient>& vClients)
{
	stClient client;
	string AccountNum = ReadAccountNum();
	while (!IsFound(vClients, AccountNum, client))
	{
		cout << "\nClient with [" << AccountNum << "] deos Not exit.\n";
		AccountNum = ReadAccountNum();
	}
	Print(client);

	double WithDrawAmount = 0;
	cout << "\nPlease enter withdraw amount: ";
	cin >> WithDrawAmount;

	while (WithDrawAmount > client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << client.AccountBalance;
		cout << "\nPlease enter another amount: ";
		cin >> WithDrawAmount;
	}

	ChangeBalance(vClients, AccountNum, -WithDrawAmount);
}

void ShowWithDrawScreen()
{
	vector <stClient> vClients = ReadClientsFromFile();
	cout << "--------------------------------------------\n";
	cout << "\t\tWithdraw Screen\n";
	cout << "---------------------------------------------\n";

	withDraw(vClients);
}

//**Total Balances
void ShowTotalBalances()
{
	vector <stClient> vClients = ReadClientsFromFile();

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)";
	cout << "\n_____________________________________________________________________________________\n";
	cout << "| " << left << setw(16) << "Account Number";
	cout << "| " << left << setw(30) << "Client Name";
	cout << "| " << left << setw(10) << "Balance";
	cout << "\n_____________________________________________________________________________________\n";

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available in the sysytem!\n";

	else
	{
		double Total = 0;
		for (stClient& c : vClients)
		{
			cout<< "| " << left << setw(16) << c.AccountNum
				<< "| " << left << setw(30) << c.Name
				<< "| " << left << setw(10) << c.AccountBalance << endl;

				Total += c.AccountBalance;
		}
		cout << "_____________________________________________________________________________________\n";

		cout << "\n\t\t\t\tTotal Balaces = " << Total << "\n";
	}
}


void GoBackToTransactionsMenue()
{
	cout << "\nPress any Key to go back to Transactions Menue....";
	system("pause>0");
	ShowTransactionsScreen();
}

enTransactionOption choice()
{
	short ch = 0;
	do
	{
		cout << "Choose What do you want to do? [1 to 4]: ";
		cin >> ch;
	} while (ch < 1 || ch > 4);

	return enTransactionOption(ch);
}

void PerformTransactionOperation(enTransactionOption ch)
{
	system("cls");
	switch (ch)
	{
	case enTransactionOption::Deposit:
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionOption::Withdraw:
		ShowWithDrawScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionOption::TotalBalances:
		ShowTotalBalances();
		GoBackToTransactionsMenue();
		break;

	case enTransactionOption::MainMenue:
		ShowMainScreen();
	}
}

void ShowTransactionsScreen()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\t  Transactions Menue Screen\n";
	cout << "=================================================\n";
	cout << " [1] Deposit.\n";
	cout << " [2] Withdraw.\n";
	cout << " [3] Total Balances.\n";
	cout << " [4] Main Menue.\n";
	cout << "=================================================\n";
	PerformTransactionOperation(choice());
}
//#####################################\\


void PerformMainMenueOption(enMainOperation choice)
{
	system("cls");
	switch (choice)
	{
	case enMainOperation::Show:
		ShowClients();
		GoBackToMainMenue();
		break;

	case enMainOperation::Add:
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainOperation::Delete:
		DeleteClient();
		GoBackToMainMenue();
		break;

	case enMainOperation::Update:
		UpdateClient();
		GoBackToMainMenue();
		break;

	case enMainOperation::Find:
		FindClient();
		GoBackToMainMenue();
		break;

	case enMainOperation::Transactions:
		ShowTransactionsScreen();
		break;

	case enMainOperation::Exit:
		ExitProgram();
	}
}

void ShowMainScreen()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\t  Main Menue Screen\n";
	cout << "=================================================\n";
	cout << " [1] Show Client List.\n";
	cout << " [2] Add New Client.\n";
	cout << " [3] Delete Client.\n";
	cout << " [4] Update Client Info.\n";
	cout << " [5] Find Client.\n";
	cout << " [6] Transactions.\n";
	cout << " [7] Exit.\n";
	cout << "=================================================\n";

	PerformMainMenueOption(UserChoice());
}

int main()
{
	ShowMainScreen();
}