#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_TRIES 3
#define MAX_TRANSACTIONS 10

// Structure for storing transaction history
typedef struct {
    char transactionDetails[100];
} Transaction;

// Structure for representing a user's account
typedef struct {
    int pin;
    float balance;
    char name[30];
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;  // Keeps track of the number of transactions
} Account;

// Function prototypes
void checkBalance(Account* account);
void deposit(Account* account);
void withdraw(Account* account);
void atmMenu(Account* account);
void printTransactionHistory(Account* account);
int authenticate(Account accounts[], int accountCount);
void logTransaction(Account* account, const char* transactionDetails);

// Main function
int main() {
    Account accounts[MAX_USERS] = {
        {1234, 1000.0, "Alice", {}, 0},
        {2345, 2000.0, "Bob", {}, 0},
        {3456, 3000.0, "Charlie", {}, 0},
        {4567, 4000.0, "David", {}, 0},
        {5678, 5000.0, "Eve", {}, 0}
    };

    int currentUser = authenticate(accounts, MAX_USERS);
    
    if (currentUser == -1) {
        printf("Authentication failed. Exiting...\n");
        return 0;
    }

    atmMenu(&accounts[currentUser]);
    return 0;
}

// Function to authenticate the user
int authenticate(Account accounts[], int accountCount) {
    int enteredPin;
    int tries = 0;
    printf("Enter your PIN: ");
    while (tries < MAX_TRIES) {
        scanf("%d", &enteredPin);
        
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].pin == enteredPin) {
                printf("Authentication successful! Welcome %s.\n", accounts[i].name);
                return i; // Return the index of the authenticated user
            }
        }
        
        tries++;
        if (tries < MAX_TRIES) {
            printf("Incorrect PIN. Try again: ");
        } else {
            printf("Incorrect PIN. You have been locked out.\n");
        }
    }
    
    return -1; // Authentication failed
}

// Function to display the balance
void checkBalance(Account* account) {
    printf("Your current balance is: $%.2f\n", account->balance);
}

// Function to deposit money into the account
void deposit(Account* account) {
    float depositAmount;
    printf("Enter the amount to deposit: $");
    scanf("%f", &depositAmount);
    
    if (depositAmount > 0) {
        account->balance += depositAmount;
        logTransaction(account, "Deposited money");
        printf("Successfully deposited $%.2f. New balance: $%.2f\n", depositAmount, account->balance);
    } else {
        printf("Invalid deposit amount.\n");
    }
}

// Function to withdraw money from the account
void withdraw(Account* account) {
    float withdrawAmount;
    printf("Enter the amount to withdraw: $");
    scanf("%f", &withdrawAmount);
    
    if (withdrawAmount > 0 && withdrawAmount <= account->balance) {
        account->balance -= withdrawAmount;
        logTransaction(account, "Withdrew money");
        printf("Successfully withdrew $%.2f. New balance: $%.2f\n", withdrawAmount, account->balance);
    } else if (withdrawAmount > account->balance) {
        printf("Insufficient funds. Your balance is $%.2f.\n", account->balance);
    } else {
        printf("Invalid withdrawal amount.\n");
    }
}

// Function to log transactions in the user's transaction history
void logTransaction(Account* account, const char* transactionDetails) {
    if (account->transactionCount < MAX_TRANSACTIONS) {
        strcpy(account->transactions[account->transactionCount].transactionDetails, transactionDetails);
        account->transactionCount++;
    } else {
        printf("Transaction history is full.\n");
    }
}

// Function to print the ATM menu and perform operations
void atmMenu(Account* account) {
    int choice;
    
    while (1) {
        printf("\nATM Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. View Transaction History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                checkBalance(account);
                break;
            case 2:
                deposit(account);
                break;
            case 3:
                withdraw(account);
                break;
            case 4:
                printTransactionHistory(account);
                break;
            case 5:
                printf("Thank you for using the ATM. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to print the transaction history
void printTransactionHistory(Account* account) {
    if (account->transactionCount == 0) {
        printf("No transactions found.\n");
    } else {
        printf("\nTransaction History:\n");
        for (int i = 0; i < account->transactionCount; i++) {
            printf("%d. %s\n", i + 1, account->transactions[i].transactionDetails);
        }
    }
}
