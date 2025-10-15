#include <stdio.h>
#include <string.h>
#include "types.h"

void create_account(int account_number, const char* name, const char* pin);
void deposit(int account_number, double amount);
void withdraw(int account_number, double amount);
void transfer(int account_number1, int account_number2, double amount);
void view_balance(int account_number);
void load_accounts();
void save_accounts();

int main() {
    load_accounts();
    char command[100];
    printf("C Mini Banking System\n");

    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }

        if (strncmp(command, "create", 6) == 0) {
            int account_number;
            char name[MAX_NAME_LEN];
            char pin[5];
            if (sscanf(command, "create %d %s %s", &account_number, name, pin) == 3) {
                create_account(account_number, name, pin);
            }
            else {
                printf("Usage: create [account_number] [name] [pin]\n");
            }
        }
        else if (strncmp(command, "deposit", 7) == 0) {
            int account_number;
            double amount;
            if (sscanf(command, "deposit %d %lf", &account_number, &amount) == 2) {
                deposit(account_number, amount);
            }
            else {
                printf("Usage: deposit [account_number] [amount]\n");
            }
        }
        else if (strncmp(command, "withdraw", 8) == 0) {
            int account_number;
            double amount;
            if (sscanf(command, "withdraw %d %lf", &account_number, &amount) == 2) {
                withdraw(account_number, amount);
            }
            else {
                printf("Usage: withdraw [account_number] [amount]\n");
            }
        }
        else if (strncmp(command, "transfer", 8) == 0) {
            int account_number1, account_number2;
            double amount;
            if (sscanf(command, "transfer %d %d %lf", &account_number1, &account_number2, &amount) == 3) {
                transfer(account_number1, account_number2, amount);
            }
            else {
                printf("Usage: transfer [from_account] [to_account] [amount]\n");
            }
        }
        else if (strncmp(command, "view", 4) == 0) {
            int account_number;
            if (sscanf(command, "view %d", &account_number) == 1) {
                view_balance(account_number);
            }
            else {
                printf("Usage: view [account_number]\n");
            }
        }
        else if (strncmp(command, "help", 4) == 0 || strncmp(command, "commands", 8) == 0) {
            printf("Commands:\n"
                   "  view [account_number]          - View account balance\n"
                   "  create [number] [name] [pin]   - Create account\n"
                   "  deposit [number] [amount]      - Deposit funds\n"
                   "  withdraw [number] [amount]     - Withdraw funds\n"
                   "  transfer [from] [to] [amount]  - Transfer funds\n"
                   "  exit                           - Exit program\n");
        }
        else if (strncmp(command, "exit", 4) == 0) {
            break;
        }
        else {
            printf("ERROR: Unknown command. Type 'help' for assistance.\n");
        }
    }

    save_accounts();
    printf("All accounts saved. Exiting...\n");
    return 0;
}
