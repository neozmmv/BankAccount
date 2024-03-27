#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount
{
    private:
    float amount;
    public:
    float balance, deposit_amount, withdraw_amount;
    float add()
    {
        cout << "\nInsert deposit amount: ";
        cin >> amount;
        deposit_amount = balance + amount;
        cout << "Amount deposited: " << amount << ". Current balance: " << deposit_amount << endl;
        return deposit_amount;
    }
    float withdraw()
    {
        cout << "\nInsert withdraw amount: ";
        cin >> amount;
        withdraw_amount = balance - amount;
        cout << "Amount withdrawn: " << amount << ". Current balance: " << withdraw_amount << endl;
        return withdraw_amount;
    }
};

int main()
{
    BankAccount conta1;
    fstream file;
    file.open("conta1.txt", ios::in);

    if(!file)
    {
        file.open("conta1.txt", ios::out);
        float newBalance;
        cout << "It seems like you don't have an account!" << endl;
        cout << "Insert your current balance: ";
        cin >> newBalance;
        cout << "Account successfully created!" << endl;
        file << newBalance << endl;
        file.close();
        return 3;
    }
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            conta1.balance = stof(line);
            cout << "Current balance: " << line << endl;
        }
    }
    file.close();

    cout << "\n1 - Withdraw\n2 - Deposit\n3 - Balance\n4 - Exit\n\n";
    char operation;
    cin >> operation;

    switch (operation)
    {
    case '1':
        file.open("conta1.txt", ios:: out);
        if(file.is_open())
        {
            file << conta1.withdraw() << endl;
        }
        file.close();
        break;
    case '2':
        file.open("conta1.txt", ios::out);
        if(file.is_open())
        {
            file << conta1.add() << endl;
        }
        file.close();
        break;
    case '3':
        cout << "Current balance is: " << conta1.balance << endl;
        break;
        return 1;
    case '4':
        cout << "\nExiting!\n" << endl;
        break;
        return 1;
    default:
        cout << "\nInvalid operation!\n";
        break;
        return 2;
    }
}
