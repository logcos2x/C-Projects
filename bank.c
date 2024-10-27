#include <stdio.h>
#include <string.h>

typedef struct bank{
    char name[35];
    int acc_no;
    float balance;
}bk;
void cr_acc()
{
    bk user;
    FILE *ptr=fopen("details.txt","a");
    if(ptr==NULL){
        printf("\nServer Error 404 :(");
    }
    char c;
    do{
        c=getchar();
    }while(c!='\n' && c!=EOF);
    printf("\nCreating an account...\n");
    printf("\nEnter your name: ");
    fgets(user.name, sizeof(user.name),stdin);
    user.name[strcspn(user.name, "\n")]='\0';
    printf("Enter your account  number: ");
    scanf("%d", &user.acc_no);
    user.balance=0;
    fwrite(&user,sizeof(user),1, ptr);
    fclose(ptr);
    printf("\nAccount Created Successfully!\n");
}
void dep_m()
{
    printf("\nEnter the amount to deposit: ");
}
void withdraw_m()
{
    printf("\nEnter the amount to withdraw: ");
}
void check_b()
{
     bk read;
     int comp;
    FILE *ptr=fopen("details.txt","a");
    if(ptr==NULL){
        printf("\nServer Error 404 :(");
    }
    printf("\nChecking Balance...\n");
    printf("\nEnter account number: ");
    scanf("%d", &comp);
    while(fread(&read, sizeof(read), 1, ptr))
    {
        if(read.acc_no==comp){
        printf("\nYour Account Balance is %.2f\n", read.balance);
        fclose(ptr);
        return;
        }
    }
        fclose(ptr);
        printf("\nAccount number %d was not found :(\n",comp);
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
            printf("\nThank you for visitng\n");
            return 0;
            break;
        default:
            printf("\nInvalid Choice. Please Try Again\n");
            break;
        }
    }
    return 0;
}