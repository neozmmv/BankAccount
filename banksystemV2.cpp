#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <windows.h>

using namespace std;

int linecounter();
int menu();
int menuoption;
class BankAccount{
private:
    float amount;
public:
    float balance;
    float add(float currentBalance) 
    {
        cout << "\nInsert deposit amount: ";
        cin >> amount;
        if (amount < 0)
        {
            cout << "Must deposit a positive value!\n";
            return currentBalance;
        }
        currentBalance += amount;
        cout << "Amount deposited: " << amount << ". Current balance: " << currentBalance << endl;
        system("pause");
        return currentBalance;
    }
    float withdraw(float currentBalance)
    {
        cout << "\nInsert withdraw amount: ";
        cin >> amount;
        if (amount > currentBalance)
        {
            cout << "Insufficient funds!\n";
            system("pause");
            return currentBalance;
        }
        if (amount < 0)
        {
            cout << "Cannot withdraw a negative amount!\n";
            system("pause");
            return currentBalance;
        }
        currentBalance -= amount;
        cout << "Amount withdrawn: " << amount << ". Current balance: " << currentBalance << endl;
        system("pause");
        return currentBalance;
    }
};

int main()
{
    menu();
}

int linecounter()
{
    fstream file;
    int linecount = 0;
    string templinecounter;
    file.open("database.csv", ios::in);
    while(getline(file, templinecounter))
    {
        linecount++;
    }
    file.close();
    return linecount;
}

int menu()
{
    BankAccount account;
    fstream file;
    int linecount = 0;
    int accountNumber;
    int option;
    cout << "************************\n";
    cout << "* Welcome to the Bank! *\n";
    cout << "************************\n\n";

    cout << "1 - Create new account\n";
    cout << "2 - Login\n";
    cout << "3 - Exit\n\n";
    cin >> option;
    if(option == 1)
    {
        system("cls");
        file.open("database.csv", ios::app);
        string username;
        float userbalance;
        cout << "\nInsert owner name: ";
        cin >> username;
        cout << "Insert current balance: ";
        cin >> userbalance;
        file << username << ',' << userbalance << endl;
        cout << "Account sucessfully created with index " << linecounter() - 1 << endl;
        cout << "\n1 - Menu\n2 - Exit\n\n";
        cin >> menuoption;
        if(menuoption == 1)
        {
            system("cls");
            menu();
        }
        else if(menuoption == 2)
        {
            file.close();
            system("pause");
            return 1;
        }
    }
    else if(option == 2)
    {
        system("cls");
        cout << "\nWhat account do you want to access?: ";
        cin >> accountNumber;
    }
    else if(option == 3)
    {
        system("cls");
        cout << "\nExiting!\n";
        Sleep(2000);
        return 1;
    }
    else
    {
        cout << "Invalid operation!\n";
        Sleep(2000);
        return 1;
    }
    file.open("database.csv", ios::in);
    if (!file)
    {
        system("cls");
        string name;
        float balance;
        cout << "Error opening file!" << endl;
        file.open("database.csv", ios::out);
        cout << "Insert owner's name: ";
        cin >> name;
        cout << "Insert current balance: ";
        cin >> balance;
        file << name << ',' << balance << endl;
        file.close();
        system("pause");
        return 1;
    }

    string line;
    vector<string> lines;

    while (getline(file, line))
    {
        lines.push_back(line);
        linecount++;
    }

    if(accountNumber > linecount)
    {
        system("cls");
        cout << "Invalid account!\n";
        cout << "Highest account index is: " << linecounter() -1 << endl;
        system("pause");
        return 1;
    }

    file.close();

    stringstream linestream(lines[accountNumber]);
    vector<string> tokens;
    string intermediate;
    while (getline(linestream, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 2)
    {
        cout << "Invalid data format in the file!" << endl;
        return 1;
    }

    account.balance = stof(tokens[1]);

    cout << "\n1 - Withdraw\n2 - Deposit\n3 - Balance\n4 - Exit\n\n";
    char operation;
    cin >> operation;

    switch (operation)
    {
    case '1':
        // Withdraw logic
        system("cls");
        float withdrawAmount;
        cout << "Insert withdraw amount: ";
        cin >> withdrawAmount;
        if (withdrawAmount < 0)
        {
            cout << "Invalid withdraw amount!" << endl;
            system("pause");
            return 1;
        }
        if (withdrawAmount > account.balance)
        {
            cout << "Insufficient funds!" << endl;
            system("pause");
            return 1;
        }
        account.balance -= withdrawAmount;
        cout << "Your current balance is: " << account.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(account.balance);
        cout << "\n1 - Menu" << endl;
        cout << "2 - Exit" << endl;
        cin >> menuoption;
        if(menuoption == 1)
        {
            system("cls");
            menu();
        }
        else if(menuoption == 2);
        {
            system("pause");
        }
        break;
    case '2':
        // Deposit logic
        system("cls");
        float depositAmount;
        cout << "Insert deposit amount: ";
        cin >> depositAmount;
        if (depositAmount < 0)
        {
            cout << "Invalid deposit amount!" << endl;
            system("pause");
            return 1;
        }
        account.balance += depositAmount;
        cout << "Your current balance is: " << account.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(account.balance);
        cout << "\n1 - Menu" << endl;
        cout << "2 - Exit" << endl;
        cin >> menuoption;
        if(menuoption == 1)
        {
            system("cls");
            menu();
        }
        else if(menuoption == 2)
        {
            system("pause");
        }
        break;
    case '3':
        system("cls");
        cout << "\nHello, " << tokens[0] << endl;
        cout << "Your current balance is: " << account.balance << endl;
        cout << "\n1 - Menu" << endl;
        cout << "2 - Exit" << endl;
        cin >> menuoption;
        if(menuoption == 1)
        {
            system("cls");
            menu();
        }
        else if(menuoption == 2)
        {
            system("pause");
        }
        break;
    case '4':
        system("cls");
        cout << "\nExiting!\n" << endl;
        return 0;
    default:
        cout << "\nInvalid operation!\n";
        system("pause");
        return 1;
    }

    file.open("database.csv", ios::out);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        system("pause");
        return 1;
    }

    for (const auto &line : lines)
    {
        file << line << endl;
    }

    file.close();
    return 0;
}
