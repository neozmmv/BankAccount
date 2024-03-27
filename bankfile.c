#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *balance_source = fopen("balance.txt", "r");
    float newBalance;
    if(balance_source == NULL)
    {
        balance_source = fopen("balance.txt", "w");
        printf("Account balance: ");
        scanf("%f", &newBalance);
        fprintf(balance_source, "%.2f", newBalance);
        return 1;
    }
    char *text = malloc(50);
    int operator;
    float withdraw, deposit;
    fscanf(balance_source, "%s", text);
    float balance = atof(text);
    printf("Balance: %.2f\n", balance);
    fclose(balance_source);

    printf("\n1 - Withdraw\n2 - Deposit\n3 - Balance\n4 - Exit\n\n");
    scanf("%i", &operator);
    
    if(operator == 1)
    {
        balance_source = fopen("balance.txt", "r+");
        printf("\nWithdraw: ");
        scanf("%f", &withdraw);
        fprintf(balance_source, "%.2f", balance - withdraw);
        fclose(balance_source);
        printf("Amount withdrawn: %.2f. New Balance: %.2f\n\n", withdraw, balance - withdraw);
    }
    else if(operator == 2)
    {
        balance_source = fopen("balance.txt", "r+");
        printf("\nDeposit: ");
        scanf("%f", &deposit);
        fprintf(balance_source, "%.2f", balance + deposit);
        fclose(balance_source);
        printf("Amount deposited: %.2f. New Balance: %.2f\n\n", deposit, balance + deposit);
    }
    else if(operator == 3)
    {
        printf("\nBalance: %.2f\n", balance);
    }
    else if(operator == 4)
    {
        printf("\nExiting!\n");
        return 1;
    }
    else
    {
        printf("\nInvalid operation!\n");
        return 1;
    }
    free(text);
}
