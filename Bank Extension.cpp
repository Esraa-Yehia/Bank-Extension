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

double ReadNum(string Message)   // ÏÇ reusability , åŞÑÃ ãä ÎáÇáåÇ Çá deposit & withdraw
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

short ReadMainMenuOption()  // íŞÑÃ ÇÎÊíÇÑ ÇáíæÒÑ ãä Çáãíä ãíäæ ÇÓßÑíä
{
		short Number = 0;
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Number;
		return Number;
}

short ReadTransactionMenuOption() //transaction Menue íŞÑÃ ÇÎÊíÇÑ ÇáíæÒÑ ãä Çá   
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Number;
	return Number;
}

void ShowHeaderScreen(string Message) //ÇáåíÏÑ ÈÊÇÚ Çí ÈÑæÓíÓ
{
	cout << "\n\n----------------------------------------------------\n";
	cout << "                  " << Message << "                      \n";
	cout << "\n----------------------------------------------------\n";

}

vector <string > SplitString(string S1, string Delim) //  Ïí ÈÊÇÎÏ ÇáÓØÑ ãä ÇáİÇíá æ ÈÊÍĞİ ÇáİæÇÕá æ ÊÍØ ÇáÈíÇäÇÊ İ İíßÊæÑ , ÇáİÊßæÑ Ïå İ ÈíäÇäÇÊ Úãíá æÇÍÏ 
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

sClient ConvertLineToRecord(string Line, string Seperator = "#//#") // ÏÇ ÈŞÇ ÈíÇÎÏ ÇááÇíä ÈíÚãáå İíßÊæÑ æãä ÇáİíßÊæÑ íãáí ÈíÇäÇÊ ÇÓÊÑÇßÔÑ áÚãíá æÇÍÏ
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

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") // áæ ÚÇæÒå ÊÖíİ ÇáÈíÇäÇÊ áİÇíá İ ÈÊÇÎÏ ÓÊÑÇßÔÑ æ ÈÊÍæáå á áÇíä 
{
	string Line = "";

	Line = Client.AccountNumber + Seperator;
	Line += Client.Pincode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.Phone + Seperator;
	Line += to_string(Client.AccountBalance);

	return Line;


}

vector <sClient> LoadDataFromFile(string FileName) // İíßÊæÑ ãä äæÚ ÇÓÊÑÇßÊ İíå ÇáÚãáÇÁ ßáåã
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
			Client = ConvertLineToRecord(Line);  // Ïí ÈíÑÌÚáí ÇÓÊÑÇßÔÑ ãáíÇä İ ÇÎÒäå İ İíßÊæÑ ÇáÚãáÇÁ
			vClients.push_back(Client);

		}

		MyFile.close();

	}

	return vClients;

}

void PrintClientRecord(sClient Client) // ÈØÈÚ ÈíÇäÇÊ Úãíá æÇÍÏ İ ÇááíÓÊ æÇäÇ ÈÓÊÏÚíåÇ áßá æÇÍÏ ÈŞÇ
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.Pincode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;


}

void PrintAllClientsData(vector <sClient>& vClients) // Client List
{
	// (ÇáÚäæÇä (ÈÏÇíÉ ÇááíÓÊ
	cout << "\n\t\t\t\t Client List (" << vClients.size() << ") Client(s).";
	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n\n";

	// ÊŞÓíã ÌÏæá ÇááíÓÊ

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n";


	// ÈíÇäÇÊ ÇáÚãáÇÁ ÈŞÇ

	for (sClient C : vClients)
	{
		PrintClientRecord(C);
		cout << endl;

	}


}

string ReadAccountNumber() // ÈÍŞ æÍŞíŞí ÈÌÏ reusability ÏÇ Çá 
{
	string AccountNumber;
	cout << "Please enter Account Number ?  ";
	cin >> AccountNumber;
	return AccountNumber;

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client) // ÇÔæİ ÑŞã ÇáÍÓÇÈ ãæÌæÏ ÚäÏäÇ æáÇ áÇ
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;  // áæ ãæÌæÏ ÈÇÎÏ ÈíÇäÇÊå
			return true;
		}

	}
	return false;

}

sClient NewClientData(string AccountNumber) // ÈÇÎÏ ÈíÇäÇÊ ÇáÚãíá ÇáÌÏíÏ
{
	sClient	NewClient;

	NewClient.AccountNumber = AccountNumber; // ÑŞã ÇáÍÓÇÈ ãÔ ÈÛíÑå , ÈÛíÑ ÈíÇäÇÊ ÇáÚãíá ÈÓ

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

void SaveClientsToFile(string FileName, vector <sClient>& vClients) // ÈÍİÙ ÇáÊÛíÑÇÊ Çááí ÚãáÊåÇ İ ÇáİÇíá , ÖíİÊ Úãíá ÌÏíÏ
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			//  åÊßæä È İæáÓ æ áæ ÚÏáÊ Úáí Úãíá İ äİÓ ÇáßáÇãMake for delete Çá  by default ÇáÎØæå Ïí ÚÕİæÑíä ÈÍÌÑ , áæ ÇáÇÖÇİå Úãíá ÌÏíÏ İ ÇæÑíÏí   
			//ÈÊÑæ İ ã åíÊÍØ İ ÇáİÇíá Make for delete ÊÇäí ÍÇÌå İ ÌÒÁ ãÓÍ Úãíá åÊßæä 

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
	// Çá format 

	ShowHeaderScreen("Add New Client");
	cout << "Adding New Client : \n\n";


	// ÇÎÏ ÇáÇßæäÊ äãÈÑ ÚáÔÇä ÇÊÔíß Úáíå

	sClient Client;
	string AccountNumber = ReadAccountNumber();

	// ÇÊÔíß ÈŞÇ 
	// áæ ãæÌæÏ íÏÎá ÑŞã ÊÇäí , áæ ã ãæÌæÏ ÇÎÏ ãäå ÈÇŞí ÇáÈíÇäÇÊ

	while (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with [" << AccountNumber << "] already exists , Enter another Account Number ? ";
		cin >> AccountNumber;
	}

	Client = NewClientData(AccountNumber);
	vClients.push_back(Client);    // ÇÖíİ ÇáÚãíá ÇáÌÏíÏ ááİíßÊæÑ 

	SaveClientsToFile(FileName, vClients); // ÇÍİÙ ÇáÊÛííÑÇÊ Ïí ÈŞÇ 

	char Answer;
	cout << "\nDo you want to add another client? (Y/N): ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		AddNewClientScreen(vClients); // áæ ÚÇæÒ íÖíİ Úãíá ÊÇäí
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

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) // ÈÊÇÚÊå È ÊÑæMake for delete ÇáÚãíá Çááí ÚÇæÒå ÇãÓÍå ÇÎáí Çá 
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
	string AccountNumber = ReadAccountNumber(); // åÇÎÏ ÇáÇßæäÊ äãÈÑ

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client); // ÇØÈÚ ÈíÇäÇÊ ÇáÚãíá Ïå ŞÈá ãÇ ÇãÓÍå

		cout << "\n\nAre you sure you want to delete this client ? y/n ?  "; // ÇáÊÇßíÏ Úáí ÎØæÉ ÇáãÓÍ
		cin >> Answer;


		if (Answer == 'Y' || Answer == 'y')   // áæ ãÊÃßÏ Çäå åíÓãÍ
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients); // ÈÊÇÚÊå È ÊÑæMake for delete ÇÎáí Çá 
			SaveClientsToFile(FileName, vClients);                       // ÇãÓÍå ãä ÇáİÇíá
			vClients = LoadDataFromFile(FileName);                       // ÇÚÏá Úáí ÇáİíßÊæÑ , ÇãÓÍå ãäå ÈÑÏæ
			cout << "\n\nClient Deleted Successfully.\n";


		}


	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n"; // áæ ÇáÇßæäÊ äãÈÑ ã ãæÌæÏ
	}

}

void UpdateClientDataScreen(vector<sClient>& vClients)  // ÇÚÏá Úáí ÈíÇäÇÊ Úãíá ãæÌæÏ ÈÇáİÚá
{
	ShowHeaderScreen("Update Client Info Screen");

	char Answer = 'n';
	sClient Client;
	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) // ÇÊÔíß áæ ãæÌæÏ ãä ÎáÇá ÇáÇßæäÊ äãÈÑ
	{
		PrintClientCard(Client);      // ÇØÈÚ ÈíÇäÇÊå

		cout << "\n\nAre you sure you want to update client ? y/n ? ";  // ÇáÊÇßíÏ Úáí ÇáÊÚÏíá
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')  // áæ ãÊÇßÏ Çäå åíÚÏá 
		{
			for (sClient& C : vClients) // ÇäÇ ÚÏáÊ åäÇ Úáí ÇáİíßÊæÑ áÇä ÚÇãáå ÈÇí Ñíİ
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = NewClientData(AccountNumber); // ÇÎÏ ÇáÈíÇäÇÊ ÇáÌÏíÏå æ ÚÏáÊåÇ
					break;
				}

			}

			SaveClientsToFile(FileName, vClients); // ÇÚÏá ÇáİÇíá 


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
	string AccountNumber = ReadAccountNumber(); // ÇÎÏ ÇáÇßæäÊ äãÈÑ

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))  // ÇÊÔíß 
	{
		PrintClientCard(Client);      // ÇØÈÚå áæ ãæÌæÏ 

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n"; // áæ ãÔ ãæÌæÏ 
	}


}


bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this Transaction ?  Y/N? "; // ÃßÏ ÇáÇæá Úáí Úãáíå (ÇáÇíÏÇÚ/ ÇáÓÍÈ) ŞÈá ãÇ ÇÚãáåÇ
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		for (sClient& C : vClients)       // ÈÇí Ñíİ ÚáÔÇä ÇÚÏá Úáí ÇáÇÕá ã äÓÎå ãäå 
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;                 //  ÇÒæÏ/ÇŞáá) Şíãå ÇáÈÇáäÓ áÕÇÍÈ ÇáÇßæäÊ äãÈÑ Ïå) , ÇÔÇÑå ÇáÇãæäÊ åÊİÑŞ åäÇ áæ ÓÍÈ åÈÚÊåÇ ÈÇáÓÇáÈ
				SaveClientsToFile(FileName, vClients);      // ÇÍİÙ ÇáÊÛííÑÇÊ Úáí ÇáİÇíá
				cout << "\n\nDone Successfully.\nNew Balance is : " << C.AccountBalance << endl;  // ÇØÈÚ ÇáÈÇáäÓ ÈÚÏ ÇáÊÚÏíá ÈŞÇ
				return true;
			}
		}

		return false;
	}
}

void DepositScreen(vector <sClient> &vClients)
{
	// ÈÊÇÚ ÈÏÇíÉ ÇáÔÇÔå format Çá
	ShowHeaderScreen("Deposit Screen");  


	// ÇáİÇÑÇíÈáÒ Çááí åÍÊÇÌåã
	sClient Client;
	double Amount = 0;
	string AccountNumber = ReadAccountNumber();


	//deposit ÇÊÔíß ÇáÇæá ÇáÇßæäÊ äãÈÑ ÚäÏí æáÇ áÇ ŞÈá ãÇ ÇÚãá Úãáíå 

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) // åİÖá ÇŞÑÇ áÍÏ ãÇ íÏÎá ÇßæäÊ äãÈÑ ÚäÏí 
	{
		cout << "Client with [" << AccountNumber << "] Does Not Exist! , Enter another Account Number :  ";
		cin >> AccountNumber;

	}

	// íÈŞí ÇáÇßæäÊ ÚäÏí while scope  ÈÏá ÎÑÌ ãä 
	// ÇØÈÚ ÈŞÇ ÏÇÊÇ ÇáßáÇíäÊ ÕÇÍÈ ÇáÇßæäÊ äãÈÑ Ïå æ ÇÎÏ ŞíãÉ ÇáÇíÏÇÚ

	PrintClientCard(Client);
	Amount = ReadNum("Please enter deposit number ? ");


	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients); // ÊäİíĞ ÚãáíÉ ÇáÇíÏÇÚ

	

}



double ReadWithdraw(string AccountNumber, sClient& Client) // İÇäßÔä áæÍÏå ÚáÔÇä åÚãá ÇÊÔíß Úáíå
{
	int Withdraw = ReadNum("Please enter withdraw amount ? ");

	while (Withdraw >= Client.AccountBalance)     // ãŞÏÇÑ ÇáÓÍÈ áÇÒã íßæä ÇŞá ãä ÇáãÈáÛ 
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << "\n";
		cout << "Please enter another withdraw amount ? ";
		cin >> Withdraw;


	}

	return Withdraw;

}

void WithdrawScreen(vector <sClient> &vClients)
{
	// ÈÊÇÚ ÈÏÇíÉ ÇáÔÇÔå format Çá
	ShowHeaderScreen("Withdraw Screen");


	// ÇáİÇÑÇíÈáÒ Çááí åÍÊÇÌåã
	sClient Client;
	double Amount = 0;
	string AccountNumber = ReadAccountNumber();



	// withdraw ÇÊÔíß ÇáÇæá ÇáÇßæäÊ äãÈÑ ÚäÏí æáÇ áÇ ŞÈá ãÇ ÇÚãá Úãáíå 

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "Client with [" << AccountNumber << "] Does Not Exist! , Enter another Account Number :  ";
		cin >> AccountNumber;

	}

	// íÈŞí ÇáÇßæäÊ ÚäÏí while scope  ÈÏá ÎÑÌ ãä 
	// ÇØÈÚ ÈŞÇ ÏÇÊÇ ÇáßáÇíäÊ ÕÇÍÈ ÇáÇßæäÊ äãÈÑ Ïå ŞÈá Çí ÊÚÏíá æ ÇÎÏ Şíãå ÇáÓÍÈ æ ÇÊÔíß ÚáíåÇ
	
	PrintClientCard(Client);
	Amount = ReadWithdraw(AccountNumber, Client);

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients); // äİÓ áæÌíß ÇáÇíÏÇÚ áßä ÈÚßÓ ÇáÇÔÇÑå
	

}



void PrintClientRecordBalanceLine(sClient& Client) // ØÈÇÚÉ ÈíÇäÇÊ ÇáÚãáÇÁ İ ÇáÈÇáäÓ áíÓÊ
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintTotalBalance(vector <sClient> vClients)
{
	// (ÇáÚäæÇä (ÈÏÇíÉ ÇááíÓÊ
	cout << "\n\t\t\t\t Balances List (" << vClients.size() << ") Client(s).";
	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n\n";

	// ÊŞÓíã ÌÏæá ÇááíÓÊ

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n\n--------------------------------------------------------------------------------";
	cout << "--------------------------\n";


	int TotalBalance = 0;

	for (sClient& C : vClients)
	{
		PrintClientRecordBalanceLine(C);   //( ØÈÚ ÈíÇäÇÊ ßá Úãíá ( ÇáÇßæäÊ äãÈÑ / ÇáÇÓã / ÇáÑÕíÏ 
		TotalBalance += C.AccountBalance;   // ÇÍÓÈ ÇáÊæÊÇá ÈÇáäÓ áßá ÇáÚãáÇÁ

	}

	cout << "\t\t\t\t\t" << "TotalBalance = " << TotalBalance;  // ÇØÈÚå 



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
	PerformMainMenuOption(enMainMenuOptions(ReadMainMenuOption())); // ÇÎÏ ÑŞã ÇáÚãáíå æ ÇäİĞåÇ

	

}




int main()
{

	ShowMainMenu();


}