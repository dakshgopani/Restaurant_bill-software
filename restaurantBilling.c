// HEADERS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
// structures

struct items
{
    char item[100];
    float price;
    int qty;
};

struct orders
{
    char customer[100];
    char date[100];
    int numOFitems;
    struct items itm[100];
};

// functions to generate bills

void generateBillHeader(char name[100], char date[100])
{
    printf("\n\n");
    printf("\t            SAI PALACE RESTAURANT ");
    printf("\n\t          -------------------------------");
    printf("\nDate : %s", date);
    printf("\nInvoice in Name of : %s ", name);
    printf("\n");
    printf("-------------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t");
    printf("Total\t");
    printf("\n-------------------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[100], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.1 * netTotal, grandTotal = netTotal + 2 * cgst; // netTotal + cgst + sgst
    printf("-------------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total \t\t\t%.2f", netTotal);
    printf("\nCGST @10%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @10%s\t\t\t%.2f", "%", cgst);
    printf("\n-------------------------------------------------");
    printf("\nGrand Total \t\t\t%.2f", grandTotal);
    printf("\n-------------------------------------------------\n");
}
int main()
{
    int input;
    int n;
    float total;
    struct orders order;
    struct orders ord;
    char saveBill = 'y', continueB = 'y';
    char name[50];
    FILE *fp;
    // dashboard
    while (continueB == 'y')
    {
        system("cls");
        float total = 0;
        int billFound = 0;
        printf("\t===============SAI PALACE RESTAURANT===============\n");
        printf("\nPlease select any one of the options from above\t");
        printf("\n1.Generate Your Bill");
        printf("\n2.Show all your Previous Bills and transactions");
        printf("\n3.Search any of your bills");
        printf("\n4.Exit");

        printf("\n\nYour Choice : \t");
        scanf("%d", &input);
        fgetc(stdin);
        switch (input)
        {
        case 1:
            system("cls");
            printf("\nEnter Your Name : \t");
            fgets(ord.customer, 100, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0; // to remove \n
            strcpy(ord.date, __DATE__);
            printf("\nPlease enter the number of items : \t");
            scanf("%d", &n);
            ord.numOFitems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d : \t  ", i + 1);
                fgets(ord.itm[i].item, 100, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("Please enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("Please enter the price of %s (1 unit) : \t", ord.itm[i].item);
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOFitems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);
            printf("\n Do you want to save your bill [y/n] : \t");
            scanf("%s", &saveBill);
            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.pdf", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                {
                    printf("\nSuccessfully saved");
                }
                else
                {
                    printf("\nError Saving");
                }
                fclose(fp);
            }
            else
            {
                printf("\nBill Not Saved ! Thank You for Paying the Bill");
            }
            break;

        case 2:
            system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n  *****Your Previous Bills*****\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOFitems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the name of the customer : \t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("cls");
            fp = fopen("RestaurantBill.pdf", "r");
            printf("\n\t *****Bill of %s*****\n", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOFitems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    billFound = 1;
                }
            }
            if (!billFound)
            {
                printf("Sorry the bill for %s does not exist", name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Thank You for visiting ! Come soon");
            exit(0);
            break;

        default:
            printf("Enter Valid input");
        }
        printf("\nDo you want to perform another operation? [y/n] : \t");
        scanf("%s", &continueB);
    }
    printf("\n\t\t Thank You for visiting ! Come soon"); 
    printf("\n\n");
    return 0;
}
