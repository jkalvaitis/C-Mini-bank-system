#ifndef TYPES_H
#define TYPES_H

#define MAX_NAME_LEN 50

typedef struct {
    int account_number;
    char name[MAX_NAME_LEN];
    double balance;
    char pin[5];
} Account;

typedef struct {
    int from_account;
    int to_account;
    double amount;
    char type[20];
    char timestamp[25];
} Transaction;

#endif