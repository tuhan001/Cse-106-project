// Restaurant Management System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};
struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

// For ADMIN
void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add New Items\n");
    printf("\t\t\t\t\t\t\t3. Delete Items\n");
    printf("\t\t\t\t\t\t\t4. Display Order\n");
    printf("\t\t\t\t\t\t\t5. Back to Main Menu\n\n");
    printf("\t\t\t\t\t\t\t Enter Your Choice----->");
}

// FOR CUSTOMER
void custromermenu()
{
    printf("\t\t\t\t\t\t\t1. Place Your Order\n");
    printf("\t\t\t\t\t\t\t2. View Your Ordered Items\n");
    printf("\t\t\t\t\t\t\t3. Delete Items\n");
    printf("\t\t\t\t\t\t\t4. Display Bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t ENTER YOUR CHOICE----->");
}

struct node *createadmin(struct node *head, int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;
    if (temp == NULL)
        heada = taila = newnode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }
    return heada;
}

struct node *createcustomer(struct node *head, int data, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }
    if (flag == 1)
    {
        newnode->data = data;
        newnode->price = quantity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;
        if (temp == NULL)
            headc = tailc = newnode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present int Menu!\n");
    }
    return headc;
}

// Display

void displaylist(struct node *head)
{
    struct node *temp1 = head;
    if (temp1 != NULL)
    {
        printf("\n\t\t\t\t\t\tList Is EMPTY!!\n\n");
    }
    else
    {
        printf("\n");
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                printf("\t\t\t\t\t\t\t\t%0.2f\n", temp1->data, temp1->foodname, temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t\t\t%0.2f\n", temp1->data, temp1->foodname, temp1->quantity, temp1->price);
            }
            temp1 = temp1->next;
        }
        printf("\n");
    }
}

struct node *totalsales(int data, int quantity)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    int flag = 0;
    struct node *temp1 = headc;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity * (temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }
    return head_s;
}

// CALCULATETOT SALES

void calculatetotsales()
{
    struct node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

struct node *delete(int data, struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\n\t\t\t\t\t\t\tLIST IS EMPTY\n");
    }
    else
    {
        struct node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next ;
             (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}
// DELETE

int deletecustomer()
{
    printf("\n\t\t\t\t\t\tENTER SERIAL NO. OF THE FOOD ITEM WHICE IS TO BE DELETED: ");
    int num;
    scanf("%d", &num);

    struct node *temp = headc;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            headc = delete (num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// DISPLAY BILL

void displaybill()
{
    displaylist(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp != NULL)
    {
        total_price += temp->price;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTOTAL PRICE: %0.02f\n", total_price);
}

struct node *deletelist(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

// ADMIN

void admin()
{
    printf("\n\t\t\t\t\t\t  ------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t\t\t  ------------------------------------\n");

    while (1)
    {
        adminmenu();
        int opt;
        scanf("%d", &opt);
        if (opt == 5)
            break;
        switch (opt)
        {
        case 1:
            displaylist(head_s);
            break;
        case 2:

            printf("\n\t\t\t\t\tENTRE NO. OF THE FOOD ITEM: ");
            int num, flag = 0;
            char name[50];
            float price;
            scanf("%d", &num);

            struct node *temp = heada;
            while (temp != NULL)
            {
                if (temp->data == num)
                {
                    printf("\n\t\t\t\t\t\t\tFOOD ITEM WITH GIVEN SERIAL NUMBER ALREADY EXISTS!!\n\n");
                    flag = 1;
                    break;
                } temp = temp->next;
            }

        if (flag == 1)
            break;

            printf("\t\t\t\t\t\t\t\tENTER FOOD ITEM NAME: ");
            printf("%s", name);
            printf("\t\t\t\t\t\t\tENTER PRICE: ");
            scanf("%f", &price);
            heada = createadmin(heada, num, name, price);
            printf("\n\t\t\t\t\t\t\tNEW FOOD ITEM ADD TO THE LIST!!\n\n");
            break;
        case 3:
            if(deleteadmin())
            {
                printf("\n\t\t\t\t\t\t### UPADATE LIST OF FOOD ITEMS MENU ###");
                displaylist(heada);
            }
            else
                printf("\n\t\t\t\t\t\t\tFOOD ITEM WITH GIVEN SERIAL NUMBER DOESN'T EXIST!\n\n");

            break;

        case 4:
            printf("\n\t\t\t\t\t\t## ORDER MENU##\n");
            displaylist(heada);
            break;

        default:
            printf("\n\t\t\t\t\t\tWRONG (*_*) INPUT !! PLEASE CHOOSE VALID QPTION\n");
            break;

        }
    }
}

// CUSTOMER

void customer()
{
    int flag = 0, j = 1;
    char ch;
    printf("\n\t\t\t\t\t -------------------------------\n");
    printf("\t\t\t\t\t\t     CUSTOMER SECTION\n");
    printf("\t\t\t\t\t\t -------------------------------\n");
    while (1)
    {
        custromermenu();
        int opt;
        scanf("%d", &opt);

        if (opt == 5)
            break;
        switch (opt)
        {
        case 1:
            displaylist(heada);
            printf("\n\t\t\t\t\t\t\tENTRE NUMBER CORRESPONDING TO THE ITEM YOU WANT TO ORDER: ");
            int n;
            scanf("%d", &n);
            printf("\t\t\t\t\t\tENTER QUANTITY: ");
            int quantity;
            scanf("%d", &quantity);
            headc = createcustomer(headc, n, quantity);
        break ;
            case 2:
            printf("\n\t\t\t\t\t\t ### LIST OF ORDERDD ITEMS ###\n");
            displaylist(headc);
            break;
        case 3:
            if (deletecustomer())
            {
                printf("\n\t\t\t\t\t\t\t### UPDATED LIST OF ORDERD ITEMS ###\n");
                displaylist(headc);
            }
            else
                 printf("\n\t\t\t\t\t\t\tFOOD ITEM WITH GIVEN SERIAL NUMBER DOESN'T EXIST!!\n");
                 break;
            case 4:
            calculatetotsales();
            printf("\n\t\t\t\t\t\t\t### FINAL BILL ###\n");
            displaybill();
            headc= deletelist(headc);
            printf("\n\t\t\t\t\t\t\tPRESS ANY TO TERURN TO MAIN MENU:\n\t\t\t\t\t");

            fflush(stdin);
            ch=fgetc(stdin);
            flag=1;
            break;
            default:
            printf("\n\t\t\t\t\tWRONG INTPUT !! PLAEASE CHOOSE VALID OPTION\n");
            break;
        }
        if (flag == 1)
            break;
    }
}

// mainmenu
void mainmenu()
{
    printf("\n******************************************\n");
    printf("          WELCOME TO FOOD VILLEGE           \n");
    printf("********************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION---> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--->\n");
    printf("\t\t\t\t\t\t\t3. EXIT---> \n\n");
    printf("\t\t\t\t\t\t\tENTER YOUR CHOICE ---->");
}

// main
int main()
{
    heada = createadmin(heada, 1, "Hot and Sour Soup", 100);
    heada = createadmin(heada, 2, "Fried Rice", 250);
    heada = createadmin(heada, 3, "Chicken Ramen", 300);
    heada = createadmin(heada, 4, "Beaf Ramen", 350);
    heada = createadmin(heada, 5, "Drinks", 70);

    while (1)
    {
        mainmenu();
        int choice;
        scanf("%d", &choice);
        if (choice == 3)
        {
            printf("\n\n\t\t\t\t\t\t*************Thank You!!*******\n");
            break;
        }
        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            break;

        default:
            printf("\n\t\t\t\t\t\tWRONG INPUT !! PLEASE CHOOSE VALID OPTION\n");
            break;
        }
    }
}
