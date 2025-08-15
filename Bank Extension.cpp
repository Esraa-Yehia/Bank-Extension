#include <iostream>
#include <string>
#include <cctype>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;
const string FileName = "Clients.txt.";

// Functin Declaration 
void ShowMainMenu();
void ShowTransactionMenu();


enum enMainMenuOptions
{
	ShowClientLists = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Transaction = 6,
	Exit = 7
};

enum enTransactionMenuOptions
{
	Deposit = 1,
	Withdraw = 2,
	TotalBalance = 3,
	MainMenueScreen = 4

};

double ReadNum(string Message)   // �� reusability , ���� �� ������ �� deposit & withdraw
{
	int Num;

	cout << "\n" << Message ;
	cin >> Num;

	return Num;


}  

struct sClient
{
	string AccountNumber;
	string Pincode;
	string Name;
	string Phone;
	double AccountBalance = 0.0;
	bool MarkForDelete = false;


};

short ReadMainMenuOption()  // ���� ������ ������ �� ����� ���� ������
{
		short Number = 0;
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Number;
		return Number;
}

short ReadTransactionMenuOption() //transaction Menue ���� ������ ������ �� ��   
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Number;
	return Number;
}

void ShowHeaderScreen(string Message) //������ ���� �� ������
{
	cout << "\n\n----------------------------------------------------\n";
	cout << "                  " << Message << "                      \n";
	cout << "\n----------------------------------------------------\n";

}

vector <string > SplitString(string S1, string Delim) //  �� ����� ����� �� ������ � ����� ������� � ��� �������� � ������ , ������� �� � ������� ���� ���� 
{
	vector <string> vData;
	int Pos = 0;
	string sWord = "";

	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos);
		if (sWord != "")
		{
			vData.push_back(sWord);
		}

		S1.erase(0, Pos + Delim.length());

	}

	if (S1 != "")
	{
		vData.push_back(S1);
	}


	return vData;


}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#") // �� ��� ����� ������ ������ ������ ��� �������� ���� ������ �������� ����� ����
{
	sClient Client;
	vector <string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.Pincode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);


	return Client;


}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") // �� ����� ���� �������� ����� � ����� ������� � ������ � ���� 
{
	string Line = "";

	Line = Client.AccountNumber + Seperator;
	Line += Client.Pincode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.Phone + Seperator;
	Line += to_string(Client.AccountBalance);

	return Line;


}

vector <sClient> LoadDataFromFile(string FileName) // ������ �� ��� ������� ��� ������� ����
{
	vector <sClient> vClients;

	fstream MyFile;

	MyFile.open(FileName, ios::in); //Read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);  // �� ������� �������� ����� � ����� � ������ �������
			vClients.push_back(Client);

		}

		MyFile.close();

	}

	return vClients;

}

void PrintClientRecord(sClient Client) // ���� ������ ���� ���� � ������ ���� �������� ��� ���� ���
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.Pincode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;


}

void PrintAllClientsData(vector <sClient>& vClients) // Client List
{
	// (������� (����� ������
	cout << "\n\t\t\t\t Client List (" << vClients.size() << ") Client(s).";
	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n\n";

	// ����� ���� ������

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n";


	// ������ ������� ���

	for (sClient C : vClients)
	{
		PrintClientRecord(C);
		cout << endl;

	}


}

string ReadAccountNumber() // ��� ������ ��� reusability �� �� 
{
	string AccountNumber;
	cout << "Please enter Account Number ?  ";
	cin >> AccountNumber;
	return AccountNumber;

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client) // ���� ��� ������ ����� ����� ��� ��
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;  // �� ����� ���� �������
			return true;
		}

	}
	return false;

}

sClient NewClientData(string AccountNumber) // ���� ������ ������ ������
{
	sClient	NewClient;

	NewClient.AccountNumber = AccountNumber; // ��� ������ �� ����� , ���� ������ ������ ��

	cout << "\nEnter Pin Code ? ";
	getline(cin >> ws, NewClient.Pincode);

	cout << "\nEnter Name ? ";
	getline(cin, NewClient.Name);

	cout << "\nEnter Phone ? ";
	getline(cin, NewClient.Phone);

	cout << "\nEnter Account Balance ? ";
	cin >> NewClient.AccountBalance;



	return NewClient;

}

void SaveClientsToFile(string FileName, vector <sClient>& vClients) // ���� �������� ���� ������ � ������ , ���� ���� ����
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			//  ����� � ���� � �� ���� ��� ���� � ��� ������Make for delete ��  by default ������ �� ������� ���� , �� ������� ���� ���� � ������   
			//���� � � ����� � ������ Make for delete ���� ���� � ��� ��� ���� ����� 

			if (C.MarkForDelete == false)
			{
				MyFile << ConvertRecordToLine(C) << endl;
			}

		}

		MyFile.close();

	}


}

void AddNewClientScreen(vector <sClient>& vClients)
{
	// �� format 

	ShowHeaderScreen("Add New Client");
	cout << "Adding New Client : \n\n";


	// ��� ������� ���� ����� ����� ����

	sClient Client;
	string AccountNumber = ReadAccountNumber();

	// ����� ��� 
	// �� ����� ���� ��� ���� , �� � ����� ��� ��� ���� ��������

	while (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with [" << AccountNumber << "] already exists , Enter another Account Number ? ";
		cin >> AccountNumber;
	}

	Client = NewClientData(AccountNumber);
	vClients.push_back(Client);    // ���� ������ ������ �������� 

	SaveClientsToFile(FileName, vClients); // ���� ��������� �� ��� 

	char Answer;
	cout << "\nDo you want to add another client? (Y/N): ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		AddNewClientScreen(vClients); // �� ���� ���� ���� ����
	}


}

void PrintClientCard(sClient Client)
{
	cout << "\n\nThe following are the client detials: \n";
	cout << "---------------------------------------\n";

	cout << "Account Number : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.Pincode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n---------------------------------------\n";

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) // ������ � ���Make for delete ������ ���� ����� ����� ���� �� 
{

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;

		}

	}
	return false;

}

void DeleteClientScreen(vector<sClient>& vClients)
{
	ShowHeaderScreen("Delete Client Screen");
	char Answer = 'n';
	sClient Client;
	string AccountNumber = ReadAccountNumber(); // ���� ������� ����

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client); // ���� ������ ������ �� ��� �� �����

		cout << "\n\nAre you sure you want to delete this client ? y/n ?  "; // ������� ��� ���� �����
		cin >> Answer;


		if (Answer == 'Y' || Answer == 'y')   // �� ����� ��� �����
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients); // ������ � ���Make for delete ���� �� 
			SaveClientsToFile(FileName, vClients);                       // ����� �� ������
			vClients = LoadDataFromFile(FileName);                       // ���� ��� �������� , ����� ��� ����
			cout << "\n\nClient Deleted Successfully.\n";


		}


	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n"; // �� ������� ���� � �����
	}

}

void UpdateClientDataScreen(vector<sClient>& vClients)  // ���� ��� ������ ���� ����� ������
{
	ShowHeaderScreen("Update Client Info Screen");

	char Answer = 'n';
	sClient Client;
	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) // ����� �� ����� �� ���� ������� ����
	{
		PrintClientCard(Client);      // ���� �������

		cout << "\n\nAre you sure you want to update client ? y/n ? ";  // ������� ��� �������
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')  // �� ����� ��� ����� 
		{
			for (sClient& C : vClients) // ��� ���� ��� ��� �������� ��� ����� ��� ���
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = NewClientData(AccountNumber); // ��� �������� ������� � ������
					break;
				}

			}

			SaveClientsToFile(FileName, vClients); // ���� ������ 


			cout << "\n\nClient Updated Successfully\n";
		}


	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	}

}

void FindClientScreen(vector<sClient>& vClients)
{
	ShowHeaderScreen("Find Client Screen");

	sClient Client;
	string AccountNumber = ReadAccountNumber(); // ��� ������� ����

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))  // ����� 
	{
		PrintClientCard(Client);      // ����� �� ����� 

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n"; // �� �� ����� 
	}


}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this Transaction ?  Y/N? "; // ��� ����� ��� ����� (�������/ �����) ��� �� ������
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		for (sClient& C : vClients)       // ��� ��� ����� ���� ��� ����� � ���� ��� 
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;                 //  ����/����) ���� ������� ����� ������� ���� ��) , ����� ������� ����� ��� �� ��� ������ �������
				SaveClientsToFile(FileName, vClients);      // ���� ��������� ��� ������
				cout << "\n\nDone Successfully.\nNew Balance is : " << C.AccountBalance << endl;  // ���� ������� ��� ������� ���
				return true;
			}
		}

		return false;
	}
}

void DepositScreen(vector <sClient> &vClients)
{
	// ���� ����� ������ format ��
	ShowHeaderScreen("Deposit Screen");  


	// ���������� ���� �������
	sClient Client;
	double Amount = 0;
	string AccountNumber = ReadAccountNumber();


	//deposit ����� ����� ������� ���� ���� ��� �� ��� �� ���� ����� 

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) // ���� ���� ��� �� ���� ����� ���� ���� 
	{
		cout << "Client with [" << AccountNumber << "] Does Not Exist! , Enter another Account Number :  ";
		cin >> AccountNumber;

	}

	// ���� ������� ���� while scope  ��� ��� �� 
	// ���� ��� ���� �������� ���� ������� ���� �� � ��� ���� �������

	PrintClientCard(Client);
	Amount = ReadNum("Please enter deposit number ? ");


	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients); // ����� ����� �������

	

}



double ReadWithdraw(string AccountNumber, sClient& Client) // ������ ����� ����� ���� ����� ����
{
	int Withdraw = ReadNum("Please enter withdraw amount ? ");

	while (Withdraw >= Client.AccountBalance)     // ����� ����� ���� ���� ��� �� ������ 
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << "\n";
		cout << "Please enter another withdraw amount ? ";
		cin >> Withdraw;


	}

	return Withdraw;

}

void WithdrawScreen(vector <sClient> &vClients)
{
	// ���� ����� ������ format ��
	ShowHeaderScreen("Withdraw Screen");


	// ���������� ���� �������
	sClient Client;
	double Amount = 0;
	string AccountNumber = ReadAccountNumber();



	// withdraw ����� ����� ������� ���� ���� ��� �� ��� �� ���� ����� 

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with [" << AccountNumber << "] Does Not Exist! , Enter another Account Number :  ";
		cin >> AccountNumber;

	}

	// ���� ������� ���� while scope  ��� ��� �� 
	// ���� ��� ���� �������� ���� ������� ���� �� ��� �� ����� � ��� ���� ����� � ����� �����
	
	PrintClientCard(Client);
	Amount = ReadWithdraw(AccountNumber, Client);

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // ��� ����� ������� ��� ���� �������
	

}



void PrintClientRecordBalanceLine(sClient& Client) // ����� ������ ������� � ������� ����
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintTotalBalance(vector <sClient> vClients)
{
	// (������� (����� ������
	cout << "\n\t\t\t\t Balances List (" << vClients.size() << ") Client(s).";
	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n\n";

	// ����� ���� ������

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n";


	int TotalBalance = 0;

	for (sClient& C : vClients)
	{
		PrintClientRecordBalanceLine(C);   //( ��� ������ �� ���� ( ������� ���� / ����� / ������ 
		TotalBalance += C.AccountBalance;   // ���� ������� ����� ��� �������

	}

	cout << "\t\t\t\t\t" << "TotalBalance = " << TotalBalance;  // ����� 



}



void ShowEndScreen()
{
	system("cls");
	ShowHeaderScreen("Program Ends :-)");

}


void GoBackToMainMenuScreen()
{
	cout << "\n\n\nPress any key to go back to Main Menu... ";
	system("pause>0");
	ShowMainMenu();
}

void GoBackToTransactionMenuScreen()
{
	cout << "\n\n\nPress any key to go back to Transaction Menu... ";
	system("pause>0");
	ShowTransactionMenu();
}


void PerformMainMenuOption(enMainMenuOptions MainMenueOptions)
{
	vector <sClient> vClients = LoadDataFromFile(FileName);

	switch (MainMenueOptions)
	{
	case(enMainMenuOptions::ShowClientLists):
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenuScreen();
		break;

	case(enMainMenuOptions::AddNewClient):
		system("cls");
		AddNewClientScreen(vClients);
		GoBackToMainMenuScreen();
		break;

	case(enMainMenuOptions::DeleteClient):
		system("cls");
		DeleteClientScreen(vClients);
		GoBackToMainMenuScreen();
		break;

	case(enMainMenuOptions::UpdateClientInfo):
		system("cls");
		UpdateClientDataScreen(vClients);
		GoBackToMainMenuScreen();
		break;

	case(enMainMenuOptions::FindClient):
		system("cls");
		FindClientScreen(vClients);
		GoBackToMainMenuScreen();
		break;

	case(enMainMenuOptions::Transaction):
	{
		system("cls");
		ShowTransactionMenu();
		break;
	}
	case(enMainMenuOptions::Exit):
		ShowEndScreen();
		break;
	}


}

void PerformTransactionMenuOptions(enTransactionMenuOptions TransactionMenueOptions)
{
	vector <sClient> vClients = LoadDataFromFile(FileName);

	switch (TransactionMenueOptions)
	{
	case(enTransactionMenuOptions::Deposit):
	{
		system("cls");
		DepositScreen(vClients);
		GoBackToTransactionMenuScreen();

	}

	case(enTransactionMenuOptions::Withdraw):
	{
		system("cls");
		WithdrawScreen(vClients);
		GoBackToTransactionMenuScreen();

	}

	case(enTransactionMenuOptions::TotalBalance):
	{
		system("cls");
		PrintTotalBalance(vClients);
		GoBackToTransactionMenuScreen();

	}

	case(enTransactionMenuOptions::MainMenueScreen):
	{
		system("cls");
		ShowMainMenu();

	}


	}

}



void ShowTransactionMenu()
{
	system("cls");

	cout << "================================================\n";
	cout << "\tTransaction Menu Screen";
	cout << "\n================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "================================================\n";
	PerformTransactionMenuOptions(enTransactionMenuOptions(ReadTransactionMenuOption()));

}

void ShowMainMenu()
{
	system("cls");

	cout << "==============================================================\n";
	cout << "                   Main Menu Screen\n";
	cout << "==============================================================\n";
	cout << "                   [1] Show Client List.\n";
	cout << "                   [2] Add New Client.\n";
	cout << "                   [3] Delete Client.\n";
	cout << "                   [4] Update Client Info\n";
	cout << "                   [5] Find Client.\n";
	cout << "                   [6] Transaction.\n";
	cout << "                   [7] Exit.\n";
	cout << "===============================================================\n";
	PerformMainMenuOption(enMainMenuOptions(ReadMainMenuOption())); // ��� ��� ������� � ������

	

}




int main()
{

	ShowMainMenu();


}