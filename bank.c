#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct bank
{
    char name[35];
    int acc_no;
    float balance;
} bk;
int ifc()
{
    int code = 0, ran;
    srand(time(0) + rand());
    for (int i = 0; i < 11; i++)
    {
        ran = rand() % 10;
        code = code * 10 + ran;
    }
    return code;
}
void cr_acc()
{
    bk user, read;
    FILE *ptr = fopen("details.txt", "a+");
    if (ptr == NULL)
    {
        printf("\nServer Error 404 :(\n");
        return;
    }

    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("\nCreating an account...\n");
    printf("\nEnter your name: ");
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';

    int unique = 0;
    while (!unique)
    {
        user.acc_no = fabs(ifc());
        unique = 1;

        rewind(ptr);
        while (fread(&read, sizeof(read), 1, ptr))
        {
            if (user.acc_no == read.acc_no)
            {
                unique = 0;
                break;
            }
        }
    }

    printf("Your generated account number: %d\n", user.acc_no);
    user.balance = 0;
    fwrite(&user, sizeof(user), 1, ptr);
    fclose(ptr);
    printf("\nAccount Created Successfully!\n");
}
void dep_m()
{
    bk read;
    int acc_no;
    float amt;
    FILE *ptr = fopen("details.txt", "r+b");
    if (ptr == NULL)
    {
        printf("\nServer Error 404 :(\n");
        return;
    }
    printf("\nEnter the account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter the amount to deposit: ");
    scanf("%f", &amt);
    if (amt <= 0)
    {
        printf("\nInvalid amount\n");
        fclose(ptr);
        return;
    }
    while (fread(&read, sizeof(read), 1, ptr))
    {
        if (read.acc_no == acc_no)
        {
            read.balance = read.balance + amt;
            fseek(ptr, -sizeof(read), SEEK_CUR);
            fwrite(&read, sizeof(read), 1, ptr);
            fclose(ptr);
            printf("\n%.2f deposited successfully\nUpdated balance: %.2f\n", amt, read.balance);
            return;
        }
    }
    fclose(ptr);
    printf("\nAmount could not be deposited as account number %d was not found :(\n", acc_no);
}
void withdraw_m()
{
    bk read;
    int acc_no;
    float amt;
    FILE *ptr = fopen("details.txt", "r+b");
    if (ptr == NULL)
    {
        printf("\nServer Error 404 :(\n");
        return;
    }
    printf("\nEnter the account number: ");
    scanf("%d", &acc_no);
    printf("\nEnter the amount to withdraw: ");
    scanf("%f", &amt);
    while (fread(&read, sizeof(read), 1, ptr))
    {
    if(read.balance>=amt){
        if (read.acc_no == acc_no)
        {
            read.balance = read.balance - amt;
            fseek(ptr, -sizeof(read), SEEK_CUR);
            fwrite(&read, sizeof(read), 1, ptr);
            fclose(ptr);
            printf("\n%.2f was withdrawn successfully\nRemaining balance: %.2f\n", amt, read.balance);
            return;
        }
    }
    else{
        printf("\nInsufficient balance!\n");
        fclose(ptr);
        return;
    }
    }
    fclose(ptr);
    printf("\nAmount could not be withdrawn as account number %d was not found :(\n", acc_no);
}
void check_b()
{
    bk read;
    int comp;
    FILE *ptr = fopen("details.txt", "r");
    if (ptr == NULL)
    {
        printf("\nServer Error 404 :(\n");
        return;
    }
    printf("\nChecking Balance...\n");
    printf("\nEnter account number: ");
    scanf("%d", &comp);
    while (fread(&read, sizeof(read), 1, ptr))
    {
        if (read.acc_no == comp)
        {
            printf("\nYour Account Balance is %.2f\n", read.balance);
            fclose(ptr);
            return;
        }
    }
    fclose(ptr);
    printf("\nAccount number %.d was not found :(\n", comp);
}
int main()
{
    int ch;
    while (1)
    {
        printf("\n**Welcome to Bank Management System**\n\t1. Create Account\n\t2. Deposit Money\n\t3. Withdraw Money\n\t4. Check Balance\n\t5. Exit\nEnter Your Choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            cr_acc();
            break;
        case 2:
            dep_m();
            break;
        case 3:
            withdraw_m();
            break;
        case 4:
            check_b();
            break;
        case 5:
            printf("\nThank you for visitng us. Have a good day!\n");
            return 0;
            break;
        default:
            printf("\nInvalid Choice. Please Try Again\n");
            break;
        }
    }
    return 0;
}