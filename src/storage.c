#include <stdio.h>
#include "types.h"

extern Account accounts[];
extern int account_count;

void save_accounts() {
    FILE* f = fopen("data/accounts.dat", "wb");
    if (!f) return;

    fwrite(&account_count, sizeof(int), 1, f);
    fwrite(accounts, sizeof(Account), account_count, f);
    fclose(f);
}

void load_accounts() {
    FILE* f = fopen("data/accounts.dat", "rb");
    if (!f) return;

    fread(&account_count, sizeof(int), 1, f);
    fread(accounts, sizeof(Account), account_count, f);
    fclose(f);
}
