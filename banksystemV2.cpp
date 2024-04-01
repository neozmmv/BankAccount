#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

int main() {
    BankAccount conta1;
    fstream file;
    file.open("database.csv", ios::in);
    int linecount = 0;
    int accountNumber;
    cout << "What account do you want to access?: ";
    cin >> accountNumber;

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
    while (getline(linestream, intermediate, ',')) {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 2) {
        cout << "Invalid data format in the file!" << endl;
        return 1;
    }

    conta1.balance = stof(tokens[1]);

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
        if (withdrawAmount > conta1.balance) {
            cout << "Insufficient funds!" << endl;
            return 1;
        }
        conta1.balance -= withdrawAmount;
        cout << "Your current balance is: " << conta1.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(conta1.balance);
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
        conta1.balance += depositAmount;
        cout << "Your current balance is: " << conta1.balance << endl;
        lines[accountNumber] = tokens[0] + "," + to_string(conta1.balance);
        break;
    case '3':
        cout << "\nHello, " << tokens[0] << endl;
        cout << "Your current balance is: " << conta1.balance << endl;
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
