#include "Bank.h"

class CustomException: public exception {
public:
	string msg;
	CustomException(string input):msg(input){}

	const char * what () const throw () {
		return msg.c_str();
	}
};

Bank::Bank ()
{
    Account account;
    ifstream infile;
    infile.open ("Bank.data");
    if (!infile)
    {
        //cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert (pair < long, Account > (account.getAccNo (), account));
    }
    Account::setLastAccountNumber (account.getAccNo ());
    infile.close ();
}

Bank::~Bank()
{
	// Open new empty Bank.data file
	ofstream outfile;
	outfile.open ("Bank.data", ios::trunc);
	map<long, Account>::iterator itr;

	// Insert all existing accounts into output file
    for (itr = accounts.begin (); itr != accounts.end (); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}

Account Bank::OpenAccount(string fname, string lname, float balance)
{
    // Open empty Bank.data file
    ofstream outfile;
    outfile.open ("Bank.data", ios::trunc);
    map<long, Account>::iterator itr;

    // Create new bank account
    Account newAccount(fname,lname,balance);
    long newAccountNo = newAccount.getAccNo();
    accounts.insert(pair<long, Account>(newAccountNo, newAccount));

    // Iterate accounts map and write all map data into file
    for (itr = accounts.begin (); itr != accounts.end (); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return newAccount;
}

Account Bank::BalanceEnquiry(long accountNumber)
{
	if(accounts.find(accountNumber) != accounts.end())
	{
		return accounts[accountNumber];
	}
}

Account Bank::Deposit(long accountNumber, float amount)
{
	if(accounts.find(accountNumber) != accounts.end())
	{
		accounts[accountNumber].Deposit(amount);
		return accounts[accountNumber];
	}
}

Account Bank::Withdraw(long accountNumber, float amount)
{
	try
	{
		if(accounts.find(accountNumber) != accounts.end())
		{
			if(accounts[accountNumber].getBalance() >= amount)
			{
				accounts[accountNumber].Withdraw(amount);
			}
			else
				throw CustomException("Insufficient amount! Withdrawl failed.");
		
			cout << "Line after throw" << endl;
			return accounts[accountNumber];
		}
		else
		{
			cout << "Account not found! Withdrawl abort." << endl;
		}
	}
	catch(CustomException &e)
	{
		cout << "Exception: " << e.what() << endl;
		return accounts[accountNumber];
	}
}

void Bank::CloseAccount(long accountNumber)
{
	if(accounts.find(accountNumber) != accounts.end())
	{
		accounts.erase(accountNumber);
	}	
}

void Bank::ShowAllAccounts()
{
    map<long, Account>::iterator it;

    cout << left << setw(10) << "Account#"; 
    cout << right << setw(12) << "First Name"; 
    cout << right << setw(12) << "Last Name";
    cout << right << setw(12) << "Balance";
    cout << "\n";

    for(map<long, Account>::iterator it = accounts.begin(); it != accounts.end(); it++)
    {
        cout << left << setw(10) << it->second.getAccNo(); 
        cout << right << setw(12) << it->second.getFirstName(); 
        cout << right << setw(12) << it->second.getLastName();
        cout << right << fixed << setprecision(2) << setw(12) << it->second.getBalance();
        cout << "\n";
    }
}
