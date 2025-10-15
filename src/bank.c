#include <stdio.h>
#include <string.h>
#include "types.h"
#include "logger.h"

#define MAX_ACCOUNTS 100

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

Account* find_account(int number) {
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_number == number) {
            return &accounts[i];
        }
    }
    return NULL;
}

Account* get_accounts() {
    return accounts;
}

int get_account_count() {
    return account_count;
}

void create_account(int account_number, const char* name, const char* pin) {
    if (find_account(account_number)) {
        printf("ERROR: Account already exists...\n");
        return;
    }

    Account a = {account_number, "", 0.0, ""};
    strncpy(a.name, name, MAX_NAME_LEN - 1);
    strncpy(a.pin, pin, 4);
    a.pin[4] = '\0';

    accounts[account_count++] = a;
    printf("Account %d created for %s\n", account_number, name);

    char log[100];
    sprintf(log, "Created account %d for %s", account_number, name);
    log_event(log);
}

void view_balance(int account_number) {
    Account* a = find_account(account_number);
    if (!a) {
        printf("ERROR: Account not found...\n");
        return;
    }
    printf("Account %d balance: %.2f$\n", account_number, a->balance);
}

void deposit(int account_number, double amount) {
    Account* a = find_account(account_number);
    if (!a) {
        printf("ERROR: Account not found...\n");
        return;
    }

    a->balance += amount;
    printf("Deposited %.2f$ into account %d\n", amount, account_number);
    printf("New balance: %.2f\n", a->balance);

    char log[100];
    sprintf(log, "Deposited %.2f$ to account %d", amount, account_number);
    log_event(log);
}

void withdraw(int account_number, double amount) {
    Account* a = find_account(account_number);
    if (!a) {
        printf("ERROR: Account not found...\n");
        return;
    }

    if (a->balance < amount) {
        printf("ERROR: Insufficient funds.\n");
        return;
    }

    a->balance -= amount;
    printf("Withdrew %.2f$ from account %d\n", amount, account_number);
    printf("New balance: %.2f\n", a->balance);

    char log[100];
    sprintf(log, "Withdrew %.2f$ from account %d", amount, account_number);
    log_event(log);
}

void transfer(int account_number1, int account_number2, double amount) {
    Account* a1 = find_account(account_number1);
    Account* a2 = find_account(account_number2);

    if (!a1 && !a2) {
        printf("ERROR: Neither account found...\n");
        return;
    }
    if (!a1) {
        printf("ERROR: Sender account not found...\n");
        return;
    }
    if (!a2) {
        printf("ERROR: Receiver account not found...\n");
        return;
    }
    if (a1->balance < amount) {
        printf("ERROR: Not enough funds for this transaction...\n");
        return;
    }

    a1->balance -= amount;
    a2->balance += amount;

    printf("Transferred %.2f$ from account %d to account %d\n", amount, account_number1, account_number2);
    printf("New balance of sender: %.2f\n", a1->balance);
    printf("New balance of receiver: %.2f\n", a2->balance);

    char log[150];
    sprintf(log, "Transferred %.2f$ from %d to %d", amount, account_number1, account_number2);
    log_event(log);
}
