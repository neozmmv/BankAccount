#include <iostream>
using namespace std;

class BankAccount
{
    private:
    float amount;
    public:
    float balance;
    void withdraw()
    {
        cout << "Quanto quer sacar: ";
        cin >> amount;
        if(amount > balance)
        {
            cout << "Dinheiro insuficiente!";
            return;
        }
        cout << "Quantia sacada: " << amount << ". Dinheiro restante: " << balance - amount << endl << endl;
    }
    void deposit()
    {
        cout << "Quanto quer depositar: ";
        cin >> amount;
        cout << "Quantia depositada: " << amount << ". Saldo na conta: " << balance + amount << endl << endl;
    }
    void mostrarSaldo()
    {
        cout << "Saldo na conta: " << balance << endl;
    }
    void quit()
    {
        cout << "Saindo!\n";
        return;
    }
};

int main()
{
    BankAccount conta1;
    conta1.balance = 1000;
    char option;
    cout << "Saldo em conta: " << conta1.balance << endl << endl;
    cout << "1 - Sacar\n2 - Depositar\n3 - Saldo\n4 - Sair\n" << endl;
    cin >> option;
    switch(option)
    {
    case '1':
        conta1.withdraw();
        break;
    case '2':
        conta1.deposit();
        break;
    case '3':
        conta1.mostrarSaldo();
        break;
    case '4':
        conta1.quit();
        break;
    default:
        cout << "Opcao invalida" << endl;
        break;
    }
}