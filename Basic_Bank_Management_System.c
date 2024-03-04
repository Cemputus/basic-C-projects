#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

// Structure to represent a bank account
struct BankAccount {
    char accountHolder[100];
    int accountNumber;
    float balance;
};

// Function to create a new bank account
void createAccount(struct BankAccount accounts[], int *numAccounts) {
    if (*numAccounts < MAX_ACCOUNTS) {
        printf("Enter account holder's name: ");
        scanf("%s", accounts[*numAccounts].accountHolder);

        accounts[*numAccounts].accountNumber = *numAccounts + 1;  // Assign a unique account number
        accounts[*numAccounts].balance = 0.0;  // Initial balance is set to zero

        (*numAccounts)++;
        printf("Account created successfully!\n");
    } else {
        printf("Cannot create more accounts. Limit reached.\n");
    }
}

// Function to display account details
void displayAccountDetails(struct BankAccount accounts[], int numAccounts) {
    printf("\nBank Account Details:\n");
    printf("Account Number\tAccount Holder\tBalance\n");
    for (int i = 0; i < numAccounts; i++) {
        printf("%d\t\t%s\t\t%.2f\n", accounts[i].accountNumber, accounts[i].accountHolder, accounts[i].balance);
    }
    printf("\n");
}

// Function to check account balance
void checkBalance(struct BankAccount accounts[], int numAccounts, int accountNumber) {
    int found = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            found = 1;
            printf("Account Holder: %s\n", accounts[i].accountHolder);
            printf("Account Balance: %.2f\n", accounts[i].balance);
            break;
        }
    }
    if (!found) {
        printf("Account with number %d not found.\n", accountNumber);
    }
}

// Function to make a deposit
void makeDeposit(struct BankAccount accounts[], int numAccounts, int accountNumber, float amount) {
    int found = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            found = 1;
            accounts[i].balance += amount;
            printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
            break;
        }
    }
    if (!found) {
        printf("Account with number %d not found.\n", accountNumber);
    }
}

// Function to make a withdrawal
void makeWithdrawal(struct BankAccount accounts[], int numAccounts, int accountNumber, float amount) {
    int found = 0;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            found = 1;
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
            } else {
                printf("Insufficient funds for withdrawal.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Account with number %d not found.\n", accountNumber);
    }
}

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int numAccounts = 0;
    int choice;

    do {
        printf("\nBank Management System\n");
        printf("1. Create a new account\n");
        printf("2. Display account details\n");
        printf("3. Check account balance\n");
        printf("4. Make a deposit\n");
        printf("5. Make a withdrawal\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accounts, &numAccounts);
                break;
            case 2:
                displayAccountDetails(accounts, numAccounts);
                break;
            case 3:
                int checkAccNumber;
                printf("Enter account number to check balance: ");
                scanf("%d", &checkAccNumber);
                checkBalance(accounts, numAccounts, checkAccNumber);
                break;
            case 4:
                int depositAccNumber;
                float depositAmount;
                printf("Enter account number for deposit: ");
                scanf("%d", &depositAccNumber);
                printf("Enter deposit amount: ");
                scanf("%f", &depositAmount);
                makeDeposit(accounts, numAccounts, depositAccNumber, depositAmount);
                break;
            case 5:
                int withdrawAccNumber;
                float withdrawAmount;
                printf("Enter account number for withdrawal: ");
                scanf("%d", &withdrawAccNumber);
                printf("Enter withdrawal amount: ");
                scanf("%f", &withdrawAmount);
                makeWithdrawal(accounts, numAccounts, withdrawAccNumber, withdrawAmount);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
