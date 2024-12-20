#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "header_PRODUIT.h"

int main() {
    // Add a credit card for the client


    add_credit_card("AM123", "mohamed");

    // Open credit card file
    FILE *CDM = fopen("CREDIT_CARD.dat", "rb");
    if (CDM == NULL) {
        printf("Error: CREDIT_CARD.dat does not exist!\n");
        return 1; // Return a non-zero value for error
    }

    // -----------------------------------------------// Display credit card details

    display_credit_cards(CDM, "mohamed","AM123");

    // -----------------------------------------------

    // Open PCM file
    FILE *PCM = fopen("produit.txt", "rt");
    if (PCM == NULL) {
        printf("Error: PCM.dat does not exist!\n");
        return 1;
    }
    // Open client choice file
    FILE *C = fopen("client_choice.txt", "rb");
    if (C == NULL) {
        printf("Error: client_choice.dat does not exist!\n");
        fclose(PCM); 
        return 1; 
    }

    // -----------------------------------------------

    Display_the_Supplier_Total_amount_sales_in_the_Day(PCM, C, "AM123", 1); // Ensure the correct CIN is passed
    // -----------------------------------------------
   fclose(C);
    
    C = fopen("client_choice.txt", "rt");
    if (C == NULL) {
        printf("Error: client_choice.dat does not exist!\n");
        fclose(PCM); 
        return 1; 
    }
    PCM = fopen("produit.txt", "rt");
    if (PCM == NULL) {
        printf("Error: PCM.dat does not exist!\n");
        return 1;
    }

    // -----------------------------------------------

    client_factor(PCM,CDM,C,"AM123");

    // -----------------------------------------------
    fclose(PCM); 
    fclose(C);
    c_getch();
    c_clrscr();

    // -----------------------------------------------

    feedback_and_rate_the_product("mohamed" , 1 );

     // -----------------------------------------------
    fclose(CDM);
    c_getch();
    return 0;
}
