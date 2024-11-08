#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
void Login(void);
void sign_in(void);
void leave(void);

void View_Product_List(void);
void Add_Purchases(void);
void View_Purchases(void);
void Remove_Purchases(void);



typedef struct {
    char last_name[50];
    char First_name[50];
    char CIN[20];
    char password[20];
    char confirm_password[20];
} Client;

typedef struct {
    int id_product;
    char category[50];
    char name[20];
    char description[100];
    float price;
    int quantity;

}product;


void leave(){

printf("Exiting the Aplication...\n\t**GOOD BYE**\t");

 exit(0);

}

int is_CIN_unique(const char *cin) {
    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) return 1;

    char file_cin[20];
    while (fscanf(fp, "%*s %*s %s %*s", file_cin) == 1) {
        if (strcmp(file_cin, cin) == 0) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void sign_in() {
    int i,j;
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        printf("The file does not exist or could not be opened!\n");
        return;
    }

    printf("Enter your LAST NAME: ");
    scanf("%s", client.last_name);
    printf("Enter your FIRST NAME: ");
    scanf("%s", client.First_name);

    do {
        printf("Enter your CIN: ");
        scanf("%s", client.CIN);
        if (!is_CIN_unique(client.CIN)) {

                printf("Error: CIN already exists. Please enter a unique CIN.\n");


        }
    } while (!is_CIN_unique(client.CIN));

    do {

    printf("Enter NEW PASSWORD: ");
    for (i = 0; i < 19; i++) {
        client.password[i] = getch();  // Read character without displaying it

        if (client.password[i] == '\r') {  // Stop if Enter is pressed
            break;
        }

        printf("*");
    }

    client.password[i] = '\0';


        printf("\nConfirm your PASSWORD: ");
           for (j = 0; j < 19; j++) {
        client.confirm_password[j] = getch();

        if (client.confirm_password[j] == '\r') {
            break;
        }

        printf("*");
    }

    client.confirm_password[j] = '\0';

        if (strcmp(client.password, client.confirm_password) != 0) {

                printf("\nError: Passwords do not match. Please try again.\n");

        }
    } while (strcmp(client.password, client.confirm_password) != 0);

    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);

                 printf("\nInformation added successfully!\n");



    fclose(fp);
}


void liste() {
    int c;
    do {

 ;
        printf("    \n ---------------------------");
        printf("     \n----- LIST OF OPTIONS -----");
          printf("      \n---------------------------");


          printf("         \n 1 - View Product List");
          printf("     \n2 - Add Purchases");
          printf("     \n   3 - View Purchases ");
          printf("      \n  4 - Remove Purchases");

          printf(" \n 5 - Leave Page");
          printf("  \n    ---------------------------");



        printf("\n------->> SELECT YOUR OPTION: ");scanf("%d", &c);


        switch (c) {
            case 1: {
                View_Product_List();

                break;

            }
            case 2: {
            Add_Purchases();
                break;
            }
            case 3: {
            View_Purchases();
           break;
            }
            case 4: {
                Remove_Purchases();
                break;
            }

            case 5: {
                leave();
                break;
            }
            default:

                printf("Incorrect choice! Your choice should be between [1 - 8]. Please retry.");

        }

    } while (c != 0); // Loop until the user decides to exit
}
void Login() {

    char passw[20];
    int found = 0;
    char CINN[20];
    int k;

    printf("Let's connect to your account:\n");
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = getch();

        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        printf("\nError: Could not open the file.\n");
        return;
    }

    Client client;
    while (fscanf(fp, "%*s %*s %s %s", client.CIN, client.password) == 2) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {

            printf("\nConnected successfully!\n");

            found = 1;
            system("cls");
            liste();

            break;
        }
    }

    if (!found) {

        printf("\nYou need to create an account first!\n");

    }

    fclose(fp);
}
void View_Product_List() {
    product p;

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
        printf("The file does not exist or could not be opened!\n");
        return;
    }

    printf("\n====== THE PRODUCTS LIST ======\n\n");
    printf("%-20s %-20s %-15s %-15s %-10s %-10s\n", "ID_PRODUCT", "CATEGORY", "NAME", "DESCRIPTION", "PRICE", "QUANTITY");
    printf("-----------------------------------------------------------------------------------------------------\n");

    while (fscanf(fk, "%d %19s %19s %19s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
        printf("%-20d %-20s %-15s %-15s %-10.2f %-10d\n", p.id_product, p.category, p.name, p.description, p.price, p.quantity);
    }

    fclose(fk);
    printf("\n\n\n\n\n");
}


void Add_Purchases() {
    product l, p;
    Client client;
    char filename[100];

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
        printf("Error opening the product file!\n");
        return;
    }

    int found = 0;
    printf("\nEnter PRODUCT ID: ");
    while (scanf("%d", &l.id_product) != 1) {
        printf("Please enter a valid product ID (integer): ");
        while (getchar() != '\n');
    }

    // Search for product in the inventory
    while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
        if (p.id_product == l.id_product) {
            found = 1;
            break;
        }
    }

    fclose(fk);

    if (!found) {
        printf("Product ID %d not found in inventory!\n", l.id_product);
        return;
    }

    printf("\nEnter quantity (1 - %d): ", p.quantity);
    while (scanf("%d", &l.quantity) != 1 || l.quantity < 1 || l.quantity > p.quantity) {
        printf("Invalid quantity. Enter a value between 1 and %d: ", p.quantity);
        while (getchar() != '\n');
    }

    // Read the existing cart and check for the product
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Create if not exists
        if (ff == NULL) {
            printf("Error opening the cart file!\n");
            return;
        }
    }

    product cart[100];
    int cartSize = 0;
    int exists = 0;

    // Load existing cart items
    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                printf("Cannot add to cart. The total quantity (%d) exceeds stock available (%d).\n", totalQuantity, p.quantity);
                fclose(ff);
                return;
            }
            cart[cartSize].quantity = totalQuantity;  // Sum quantities if product already in cart
            exists = 1;
        }
        cartSize++;
    }

    // If product is new to the cart
    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    // Rewrite cart with updated quantities
    freopen(filename, "w", ff);
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }

    printf("Product successfully added to cart.\n");

    fclose(ff);
}
void View_Purchases() {
    Client client;
    char filename[100];
    float total_price = 0.0;

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        printf("You have no purchases in your cart or the cart file doesn't exist.\n");
        return;
    }

    printf("\n===== YOUR PURCHASES =====\n");
    printf("%-20s %-15s %-15s %-10s %-10s %-10s\n", "Product ID", "Name", "Category", "Price", "Quantity", "Total Price");
    printf("---------------------------------------------------------------------------------------------------------\n");

    int found = 0;
    int id_product, quantity;
    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {

        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
            printf("Error opening the product list file!\n");
            fclose(ff);
            return;
        }

        product p;
        while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
            if (p.id_product == id_product) {
                float item_total_price = p.price * quantity;
                printf("%-20d %-15s %-15s %-10.2f %-10d %-10.2f\n", p.id_product, p.name, p.category, p.price, quantity, item_total_price);
                total_price += item_total_price;
                found = 1;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
        printf("Your cart is empty.\n");
    } else {

        printf("\n------------------------------------------------------------\n");
        printf("%-20s %-15s %-15s %-10s %-10s %-10.2f\n", "Total", "", "", "", "", total_price);
    }

    fclose(ff);
}


void Remove_Purchases() {
    Client client;
    char filename[100];
    int id_product, quantity, found = 0;

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n'); // Clear input buffer

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN); // Construct filename based on CIN

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        printf("Your cart is empty or the cart file doesn't exist.\n");
        return;
    }

    // Create a temporary file to store the updated cart
    FILE *tempFile = fopen("temp_cart.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(ff);
        return;
    }

    product p;
    int id_product_in_cart, quantity_in_cart;

    // Display the current items in the cart
    printf("\n===== YOUR CURRENT PURCHASES =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "Product ID", "Name", "Price", "Quantity");
    printf("--------------------------------------------\n");

    // Read the items from the cart and print them
    while (fscanf(ff, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
            printf("Error opening product list file!\n");
            fclose(ff);
            fclose(tempFile);
            return;
        }

        while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
            if (p.id_product == id_product_in_cart) {
                printf("%-20d %-15s %-10.2f %-10d\n", p.id_product, p.name, p.price, quantity_in_cart);
                found = 1;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
        printf("No products found in your cart.\n");
        fclose(ff);
        fclose(tempFile);
        return;
    }

    // Ask the user for the product ID and quantity to remove
    printf("\nEnter the Product ID to REMOVE: ");
    scanf("%d", &id_product);

    printf("Enter the quantity to REMOVE: ");
    scanf("%d", &quantity);

    // Rewind the cart file and copy all items to the temporary file except the one to be removed
    rewind(ff);

    while (fscanf(ff, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        // If the current product is the one to be removed
        if (id_product_in_cart == id_product) {
            // If the quantity to be removed is less than the cart quantity, update the remaining quantity
            if (quantity_in_cart > quantity) {
                fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart - quantity);
                printf("Removed %d items from cart. %d items remain.\n", quantity, quantity_in_cart - quantity);
            } else {
                printf("Removed all %d items from cart.\n", quantity_in_cart);
            }
        } else {
            // Otherwise, copy the item to the temporary file
            fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
        }
    }

    // Close the original and temporary files
    fclose(ff);
    fclose(tempFile);

    // Replace the original cart file with the updated cart
    remove(filename); // Delete the original cart file
    rename("temp_cart.txt", filename); // Rename the temporary file to the original cart filename

    printf("\nCart updated successfully.\n");
}




#endif // FONCTION_H_INCLUDED
