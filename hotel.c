#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//structure for the hotel food management
struct node
{
    char dish_name[200];
    int price;
    struct node *prev;
    struct node *next;
} * header;
//structure for the customer food management
struct order
{
    char dish_name[200];
    int price, qty;
    struct order *prev1;
    struct order *next1;
} * header1;

//function to generate the bill and display it on the screen
void generate_bill(struct order *header1)
{
    struct order *temp = header1;
    int j, i = 1, Total = 0;
    if (temp == NULL)
    {
        printf("\nNo food is ordered :(\n");
    }
    else
    {
        printf("--------------------------------------------\n");
        printf("-------------------BILL---------------------\n");
        printf("sl no\tDish Name\tQuantity\tPrice\n");
        while (temp != NULL)
        {
            printf("%d\t", i);
            //printf("%s", ptr1->dish_name);
            //printf("%d\n", ptr1->price);
            for (j = 0; temp->dish_name[j] != '\n'; j++)
            {
                printf("%c", temp->dish_name[j]);
            }
            printf("\t");
            printf("\t%d", temp->qty);
            printf("\t%d\n", temp->price);
            Total = Total + temp->price;
            temp = temp->next1;
            i++;
        }
        printf("--------------------------------------------\n");
        printf("                           TOTAL : %d/-\n", Total);
        printf("--------------------------------------------\n");
    }
}
//sample function to display the dishes ordered
void display_order(struct order *header1)
{
    int j, i = 1;
    struct order *ptr1 = header1;
    if (ptr1 == NULL)
    {
        printf("\nOops , no dishes are ordered yet!1\n");
    }
    else
    {
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
        printf("Sl.No.\tDish Name\tPrice\n");
        while (ptr1 != NULL)
        {
            printf("%d\t", i);
            //printf("%s", ptr1->dish_name);
            //printf("%d\n", ptr1->price);
            for (j = 0; ptr1->dish_name[j] != '\n'; j++)
            {
                printf("%c", ptr1->dish_name[j]);
            }
            printf("\t");
            printf("\t%d\n", ptr1->price);
            ptr1 = ptr1->next1;
            i++;
        }
        printf("-----------------------------------\n");
        printf("-----------------------------------\n");
    }
}

//function to display the menu
void display_menu(struct node *header)
{
    //function for viewing the added dishes
    struct node *ptr = header;
    if (ptr == NULL)
    {
        printf("\nSorry the dishes are not ready now!\n");
    }
    else
    {
        int j, i = 1;
        printf("\n-----------------------------------\n");
        printf("--------------MENU-----------------\n");
        printf("Sl.No.\tDish Name\tPrice\n");
        while (ptr != NULL)
        {

            printf("%d\t", i);
            //printf("%s", ptr1->dish_name);
            //printf("%d\n", ptr1->price);
            for (j = 0; ptr->dish_name[j] != '\n'; j++)
            {
                printf("%c", ptr->dish_name[j]);
            }
            printf("\t");
            printf("\t%d\n", ptr->price);
            ptr = ptr->next;
            i++;
        }
        printf("-----------------------------------\n");
        printf("-----------------------------------\n\n");
    }
}

/////////////////////////////////////////////ADMIN FUNCTIONS START//////////////////////////////////////////////////
struct node *add_new(struct node *header)
{
    //function for adding new dishes
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;
    struct node *ptr = header;
    printf("\nEnter the name of the dish: ");
    fgetc(stdin);
    fgets(newnode->dish_name, 200, stdin);
    printf("Enter the unit price of the dish: ");
    scanf("%d", &newnode->price);
    fgetc(stdin);
    if (ptr == NULL)
    {
        newnode->prev = NULL;
        header = newnode;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        newnode->prev = ptr;
        ptr->next = newnode;
    }
    return header;
}

//function to delete the dishes
struct node *delete_dish(struct node *header)
{
    struct node *ptr = header;
    int k, i = 1;
    if (ptr == NULL)
    {
        printf("\nThere are no available dishes in the list to delete!\n");
    }
    else
    {
        display_menu(header);
        printf("Enter the Dish index to delete: ");
        scanf("%d", &k);
        while (ptr != NULL)
        {
            if (i == k)
            {
                break;
            }
            i = i + 1;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            printf("\nEntered index out of bound!\n");
        }
        else
        {
            if (ptr->next == NULL)
            {
                if (ptr->prev == NULL)
                {
                    header = ptr->next;
                    //free(ptr);
                }
                else
                {
                    ptr->prev->next = NULL;
                    //free(ptr);
                }
                //display
            }
            else if (ptr == header)
            {
                ptr->next->prev = NULL;
                header = ptr->next;
                //free(ptr);
            }
            else
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                //free(ptr);
            }
            printf("\n           *.Menu Updated.*           \n");
            display_menu(header);
        }
    }
    return header;
}

struct node *Modify(struct node *header)
{
    struct node *ptr = header;
    int k, i = 1, nprice;
    if (ptr == NULL)
    {
        printf("\nSorry the dishes are not ready now!\n");
    }
    else
    {
        display_menu(header);
        printf("\nEnter Dish Index whose Price has to be Altered: ");
        scanf("%d", &k);
        while (ptr != NULL)
        {
            if (i == k)
                break;
            i = i + 1;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            printf("\nThe entered dish index is not accessible!\n");
        }
        else
        {
            printf("Enter New Price for the Dish: ");
            scanf("%d", &nprice);
            ptr->price = nprice;
            printf("Dish Price Changed!\n");
        }
    }
    return header;
}
/////////////////////////////////////////////ADMIN FUNCTIONS END///////////////////////////////////////////////////

////////////////////////////////////////CUSTOMER FUNCTION STARTS///////////////////////////////////////////////////
struct order *searchNode(struct node *header, struct order *header1, int num)
{
    int i = 1, flag = 0, Qty;
    struct node *ptr = header;
    struct order *ptr1 = header1;
    struct order *new1 = (struct order *)malloc(sizeof(struct order));
    new1->next1 = NULL;
    while (ptr != NULL)
    {
        if (i == num)
        {
            printf("Enter the quantity(in no.s) of dish %d : ", num);
            scanf("%d", &Qty);
            strcpy(new1->dish_name, ptr->dish_name);
            new1->price = (ptr->price) * Qty;
            new1->qty = Qty;
            flag = 1;
            break;
        }
        ptr = ptr->next;
        i++;
    }
    if (flag == 1)
    {
        if (ptr1 == NULL)
        {
            header1 = new1;
        }
        else
        {
            while (ptr1->next1 != NULL)
            {
                ptr1 = ptr1->next1;
            }
            new1->prev1 = ptr1;
            ptr1->next1 = new1;
        }
        printf("Order placed successfully\n");
    }
    else
    {
        printf("\nDish with the entered index number is not present!\n");
    }
    return header1;
}
struct order *placeOrder(struct node *header, struct order *header1)
{

    int i = 1, index;
    struct node *ptr = header;
    if (ptr == NULL)
    {
        printf("\nDishes are not yet ready to be ordered!!\n");
        //return 0;
    }
    else
    {
        //display_menu(header);
        printf("\nPlace the order   \n(1)'0' to view menu\n(2)Specify the dish index and quantity to place order\n(3)'-1' to finish ordering\n");
        while (1)
        {
            printf("\nEnter the dish index : ");
            scanf("%d", &index);
            if (index == 0)
                display_menu(header);
            else if (index == -1)
            {
                if (i == 1)
                {
                    printf("\nNothing selected!");
                    break;
                }
                else
                {
                    printf("Order placed successfully..\n");
                    break;
                }
            }
            else
            {
                //printf("Enter the quantity of the selected dish:");
                //scanf("%d", &qty);
                header1 = searchNode(header, header1, index);
                i++;
            }
        }
        display_order(header1);
    }
    return header1;
}

/////////////////////////////CUSTOMER FUNCTION END//////////////////////////////////////////

//--------------function detailing about the admin section...............
struct node *admin(struct node *header)
{
    int option, flag = 0;
    while (flag == 0)
    {
        printf("\nChoose an option:\n1.Display menu\n2.Add new item\n3.Delete dish\n4.Modify price of dish\n5.logout\nOption: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            header = add_new(header);
            break;
        case 3:
            header = delete_dish(header);
            break;
        case 4:
            header = Modify(header);
            break;
        case 5:
            flag = 1;
            break;
        default:
            printf("\nInvalid choice!\n");
            break;
        }
    }
    return header;
}

//................................function detailing about the customer section.........................
struct order *customer(struct node *header, struct order *header1)
{
    int option, flag = 0;
    while (flag == 0)
    {
        printf("\nChoose an option:\n1.Display menu\n2.Place order.\n3.Generate bill\n4.Logout\nOption: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            header1 = placeOrder(header, header1);
            break;
        case 3:
            generate_bill(header1);
            break;
        case 4:
            flag = 1;
            break;
        default:
            printf("invalid choice!\n");
            break;
        }
    }
    return header1;
}

//function to check the login credentials of the admin
int is_admin()
{
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter the password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//function to check the login credential of the customer
int is_customer()
{
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter the password: ");
    scanf("%s", password);
    if (strcmp(username, "cust") == 0 && strcmp(password, "cust") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//main function
int main()
{
    int option, flag = 0;
    //struct node* header=NULL;
    while (flag == 0)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~HOTEL MANAGEMENT SYSTEM~~~~~~~~~");
        printf("\n1 for admin.\n2 for customer.\n3 exit\n");
        printf("Choose your option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nAdmin\n");
            if (is_admin())
            {
                printf("\nSuccesfully logged in as admin!\n");
                header = admin(header);
            }
            else
            {
                printf("\nInvalid username/password for admin!\n");
            }
            //dsiplay menu
            //add new dish
            //delete dish
            //modify the price of the dish
            break;
        case 2:
            printf("\nUser\n");
            if (is_customer())
            {
                printf("\nSuccesfully logged as customer!\n");
                header1 = customer(header, header1);
            }
            else
            {
                printf("\nInvalid username/password for customer!\n");
            }
            //view menu
            //place order
            //generate bill for order
            break;
        case 3:
            flag = 1;
            break;
        default:
            printf("\nUnknown option.\n");
            break;
        }
    }
}
