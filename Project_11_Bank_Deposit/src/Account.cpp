#include "Account.h"

long Account::NextAccountNumber = 0;

Account::Account(string fname, string lname, float balance)
{
    this->firstName = fname;
    this->lastName = lname;
    this->balance = balance;
    accountNumber = ++NextAccountNumber;
}

void Account::Deposit(float amount)
{
	this->balance += amount;
}

void Account::Withdraw(float amount)
{
	this->balance -= amount;
}

void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}

ofstream & operator << (ofstream & ofs, Account & acc)
{
    ofs << acc.accountNumber << " ";
    ofs << acc.firstName << " ";
    ofs << acc.lastName << " ";
    ofs << acc.balance << "\n";
    return ofs;
}

ifstream & operator >> (ifstream & ifs, Account & acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}

ostream & operator << (ostream & os, Account & acc)
{
    os << "First Name:" << acc.getFirstName () << endl;
    os << "Last Name:" << acc.getLastName () << endl;
    os << "Account Number:" << acc.getAccNo () << endl;
    os << "Balance:" << acc.getBalance () << endl;
    return os;
}
