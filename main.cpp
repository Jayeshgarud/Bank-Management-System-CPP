#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>

using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    float balance;
};

// Generate Account Number
int generateAccountNumber()
{
    Account a;
    int lastAccNo = 0;

    ifstream file("accounts.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        lastAccNo = a.accountNumber;
    }

    file.close();

    return lastAccNo + 1;
}

// Create Account
void createAccount()
{
    Account a;

    a.accountNumber = generateAccountNumber();

    cout << "\nGenerated Account Number: ";
    cout << setfill('0') << setw(3)
         << a.accountNumber << endl;

    cout << setfill(' ');

    cout << "Enter Account Holder Name: ";
    cin >> a.name;

    cout << "Enter Initial Balance: ";
    cin >> a.balance;

    ofstream file("accounts.txt", ios::app);

    file << a.accountNumber << " "
         << a.name << " "
         << a.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display Accounts
void displayAccounts()
{
    Account a;

    ifstream file("accounts.txt");

    cout << "\n--------------------------------------------------\n";
    cout << left
         << setw(15) << "Account No"
         << setw(20) << "Name"
         << setw(10) << "Balance" << endl;
    cout << "--------------------------------------------------\n";

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        cout << setw(15) << a.accountNumber
             << setw(20) << a.name
             << setw(10) << a.balance
             << endl;
    }

    file.close();
}

// Search Account
void searchAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    Account a;

    ifstream file("accounts.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        if (a.accountNumber == accNo)
        {
            cout << "\nAccount Found\n";
            cout << "Account Number : " << a.accountNumber << endl;
            cout << "Name           : " << a.name << endl;
            cout << "Balance        : " << a.balance << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit Money
void depositMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    Account a;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        if (a.accountNumber == accNo)
        {
            a.balance += amount;
            found = true;
        }

        temp << a.accountNumber << " "
             << a.name << " "
             << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "\nAmount Deposited Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

// Withdraw Money
void withdrawMoney()
{
    int accNo;
    float amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    Account a;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        if (a.accountNumber == accNo)
        {
            found = true;

            if (amount <= a.balance)
            {
                a.balance -= amount;
                cout << "\nWithdrawal Successful!\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }
        }

        temp << a.accountNumber << " "
             << a.name << " "
             << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Check Balance
void checkBalance()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    Account a;

    ifstream file("accounts.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        if (a.accountNumber == accNo)
        {
            cout << "\nCurrent Balance = " << a.balance << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Delete Account
void deleteAccount()
{
    int accNo;
    bool found = false;

    cout << "\nEnter Account Number to Delete: ";
    cin >> accNo;

    Account a;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> a.accountNumber >> a.name >> a.balance)
    {
        if (a.accountNumber == accNo)
        {
            found = true;
            continue;
        }

        temp << a.accountNumber << " "
             << a.name << " "
             << a.balance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "\nAccount Deleted Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "       BANK MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Search Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            depositMoney();
            break;

        case 3:
            withdrawMoney();
            break;

        case 4:
            checkBalance();
            break;

        case 5:
            displayAccounts();
            break;

        case 6:
            searchAccount();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}