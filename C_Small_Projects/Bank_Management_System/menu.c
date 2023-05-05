#include "menu.h"
#include <stdio.h>
#include "bank_display.h"
#include <stdlib.h>
#include <time.h>

typedef struct cst
{
    char name[50];
    char surname[50];
    float balance;
}customer;

void inputHandler(int input);
void AddNewCustomer(void);
void Save_Customer(customer *mycustomer);
void ListCustomers();
void ChangeCustomerInfo();
enum choice
{
    List = 0x01,
    Add = 0x02,
    Change = 0x03,
    Quit = 0x04,
};
enum choice input = 0;
void ShowMenu()
{
    Draw_Free_Frame();
    
    //hidecursor();
    gotoxy(10,4); 
    printf("1 - List all Customers!\n");
    gotoxy(10,5);
    printf("2 - Add new Customer!\n");
    gotoxy(10,6);
    printf("3 - Change Customer Data\n");
    gotoxy(10,7);
    printf("4 - Quit\n");
    

    gotoxy(10, 11);
    printf("Your choice :");
    scanf("%d", &input);
    inputHandler(input);

}
void inputHandler(int input)
{
    switch(input)
    {
        case List:
            ListCustomers();
            break;
        case Add:
            AddNewCustomer();
            break;
        case Change:
            ChangeCustomerInfo();
            break;
        case Quit :
            gotoxy(80,20);
            printf("Good Bye!");
            break;
        default: 
        {   
            gotoxy(80,20);
            printf("Invalid Input. Press a Key to continue!");
            fflush(stdin);
            getchar();
            
            system("CLS");
            ShowMenu();
        }   

        
    }
}
void ChangeCustomerInfo()
{
    int id, count = 1;
    int current_x = cursor_position.x;
    gotoxy(current_x, cursor_position.y + 1);
    printf("Enter Costumer number you want to edit info : ");
    scanf("%d", &id);
    customer myCustomers;
    FILE *myRecords = fopen("database.dat", "r+");
    while((fread(&myCustomers, sizeof(myCustomers), 1,myRecords)) != NULL)
    {
        if(id == count)
        {
            gotoxy(current_x, cursor_position.y + 1);
            printf("Customer #%d %s %s %f", count, myCustomers.name, myCustomers.name, myCustomers.balance);
            gotoxy(current_x, cursor_position.y + 1);
            printf("Edit Name : ");
            scanf("%s", &myCustomers.name);
            gotoxy(current_x, cursor_position.y + 1);
            printf("Edit Surname :");
            scanf("%s", &myCustomers.surname);
            gotoxy(current_x, cursor_position.y + 1);
            printf("Edit Balance : ");
            scanf("%f", &myCustomers.balance);
            gotoxy(current_x, cursor_position.y + 1); 
            fseek(myRecords, 2,SEEK_SET );
            fwrite(&myCustomers, sizeof(customer), 1, myRecords);
            break;
        }
        count++;
    }
    fclose(myRecords);
    gotoxy(80,20);
    printf("Customer info edited!");
    sleep(5);
    system("CLS");
    ShowMenu();
}
void ListCustomers()
{
    int x = 80, y = 5;
    int count = 1;
    gotoxy(x,y);
    FILE *myRecords = fopen("database.dat", "r");
    customer myCustomers;
    while((fread(&myCustomers, sizeof(myCustomers), 1,myRecords)) != NULL)
    {
        printf("#%d Customer name : %s %s Balance -> %f", count, myCustomers.name,myCustomers.surname, myCustomers.balance);
        count++;
        y++;
        gotoxy(x,y);
    }
    sleep(10);
    system("CLS");
    fclose(myRecords);
    ShowMenu();

}
void AddNewCustomer()
{
    system("CLS");
    Draw_Free_Frame();
    gotoxy(10,4);
    customer *mycustomer = malloc(sizeof(customer));
    printf("Name : ");
    scanf("%s", &mycustomer->name);
    gotoxy(10,5);
    printf("Surname :");
    scanf("%s",&mycustomer->surname);    
    gotoxy(10,6);
    printf("Balance ($):");
    scanf("%f", &mycustomer->balance);

    gotoxy(80,20);
    printf("Customer %s %s registered to the system", mycustomer->name, mycustomer->surname, mycustomer->balance);
    Save_Customer(mycustomer);
    sleep(5);
    system("CLS");
    ShowMenu();
}
void Save_Customer(customer *mycustomer)
{
    FILE *myRecords = fopen("database.dat", "a");
    fwrite(mycustomer, sizeof(customer), 1, myRecords);
    fclose(myRecords);
}