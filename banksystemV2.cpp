#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int linecounter();

class BankAccount {
private:
    float amount;
public:
    float balance;
    float add(float currentBalance) {
        cout << "\nInsert deposit amount: ";
        cin >> amount;
        if (amount < 0) {
            cout << "Must deposit a positive value!\n";
            return currentBalance;
        }
        currentBalance += amount;
        cout << "Amount deposited: " << amount << ". Current balance: " << currentBalance << endl;
        return currentBalance;
    }
    float withdraw(float currentBalance) {
        cout << "\nInsert withdraw amount: ";
        cin >> amount;
        if (amount > currentBalance) {
            cout << "Insufficient funds!\n";
            return currentBalance;
        }
        if (amount < 0) {
            cout << "Cannot withdraw a negative amount!\n";
            return currentBalance;
        }
        currentBalance -= amount;
        cout << "Amount withdrawn: " << amount << ". Current balance: " << currentBalance << endl;
        return currentBalance;
    }
};

int main()
{
    BankAccount account;
    fstream file;
    int linecount = 0;
    int accountNumber;
    int option;

    cout << "Welcome to the bank!\n";
    cout << "Insert 0 to create new account\n";
    cout << "Insert 1 to login\n";
    cin >> option;
    if(option == 0)
    {
        file.open("database.csv", ios::app);
        string username;
        float userbalance;
        cout << "Insert owner name: ";
        cin >> username;
        cout << "Insert current balance: ";
        cin >> userbalance;
        file << username << ',' << userbalance << endl;
        cout << "Account sucessfully created with index " << linecounter() - 1 << endl;
        file.close();
        return 1;
    }
    else if(option == 1)
    {
    cout << "What account do you want to access?: ";
    cin >> accountNumber;
    }
    else
    {
        cout << "Invalid operation!\n";
        return 1;
    }
    file.open("database.csv", ios::in);
    if (!file)
    {
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
        return 1;
    }

    string line;
    vector<string> lines;

    while (getline(file, line))
    {
        lines.push_back(line);
        linecount++;
    }

    file.close();

    stringstream linestream(lines[accountNumber]);
    vector<string> tokens;
    string intermediate;
    while (getline(linestream, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 2) {
        cout << "Invalid data format in the file!" << endl;
        return 1;
    }

    account.balance = stof(tokens[1]);

    cout << "\n1 - Withdraw\n2 - Deposit\n3 - Balance\n4 - Exit\n\n";
    char operation;
    cin >> operation;

    switch (operation) {
    case '1':
        // Withdraw logic
        float withdrawAmount;
        cout << "Insert withdraw amount: ";
        cin >> withdrawAmount;
        if (withdrawAmount < 0) {
            cout << "Invalid withdraw amount!" << endl;
            return 1;
        }
        if (withdrawAmount > account.balance) {
            cout << "Insufficient funds!" << endl;
            return 1;
        }
        account.balance -= withdrawAmount;
        cout << "Your current balance is: " << account.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(account.balance);
        break;
    case '2':
        // Deposit logic
        float depositAmount;
        cout << "Insert deposit amount: ";
        cin >> depositAmount;
        if (depositAmount < 0) {
            cout << "Invalid deposit amount!" << endl;
            return 1;
        }
        account.balance += depositAmount;
        cout << "Your current balance is: " << account.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(account.balance);
        break;
    case '3':
        cout << "\nHello, " << tokens[0] << endl;
        cout << "Your current balance is: " << account.balance << endl;
        break;
    case '4':
        cout << "\nExiting!\n" << endl;
        return 0;
    default:
        cout << "\nInvalid operation!\n";
        return 1;
    }

    file.open("database.csv", ios::out | ios::trunc);
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    for (const auto &line : lines) {
        file << line << endl;
    }

    file.close();

    return 0;
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
    return linecount;
}
