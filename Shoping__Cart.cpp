#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct item {
    int id;
    char description[100];
    float price;
    int quantity;
    struct item *next;
} item;

int count = 1; //global variable

item *createitem(char *description, float price, int quantity) {   //to create 1st item
    item *newitem = (item *)malloc(sizeof(item));
    newitem->id = count++;
    strcpy(newitem->description, description);
    newitem->price = price;
    newitem->quantity = quantity;
    newitem->next = NULL;
    return newitem;
}

void additem(item **cart, char *description, float price, int quantity) {  //add item
    item *newitem = createitem(description, price, quantity);
    newitem->next = *cart;
    *cart = newitem;
    printf("Item added to cart successfully!\n");
}

void displayCart(item *cart) {  //display item
    if (cart == NULL) {
        printf("Your cart is empty.\n");
        return;
    }
    else
        printf("Your Shopping Cart:\n");
    printf("ID\tDescription\tPrice\tQuantity\n");
    while (cart != NULL) {
        printf("%d\t%s\t\t%.2f\t%d\n", cart->id, cart->description, cart->price, cart->quantity);
        cart = cart->next;
    }
}

void deleteitem(item **cart, int id) {  //delete item
    item *current = *cart;
    item *prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item not found in cart.\n");
        return;
    }

    if (prev == NULL) {
        *cart = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Item deleted from cart successfully!\n");
}


void searchitem(item *cart, int id) {  //to search item
    while (cart != NULL) {
        if (cart->id == id) {
            printf("Item found in cart:\n");
            printf("ID\tDescription\tPrice\tQuantity\n");
            printf("%d\t%s\t\t%.2f\t%d\n", cart->id, cart->description, cart->price, cart->quantity);
            return;
        }
        cart = cart->next;
    }
    printf("Item not found in cart.\n");
}

void updateitem(item *cart, int id, int newQuantity) {  //to update item
    while (cart != NULL) {
        if (cart->id == id) {
            cart->quantity = newQuantity;
            printf("Item quantity updated.\n");
            return;
        }
        cart = cart->next;
    }
    printf("Item not found in cart.");
}

void prepareCart(item *cart) {  //prepared cart with items
    printf("Your cart is prepared successfully.\n");
}

void generateBill(item *cart) {  //generate bill
    float total = 0;
    printf("Final Bill:\n");
    printf("ID\tDescription\tPrice\tQuantity\tTotal\n");
    while (cart != NULL) {
        float itemTotal = cart->price * cart->quantity;
        printf("%d\t%s\t\t%.2f\t%d\t%.2f\n", cart->id, cart->description, cart->price, cart->quantity, itemTotal);
        total += itemTotal;
        cart = cart->next;
    }
    printf("Total Amount: %.2f\n", total);
}

int main() {           //main function
    item *shoppingCart = NULL;
    int choice;
    char description[100];
    float price;
    int quantity;
    int itemId;
    int newQuantity;

    do {
        printf("\nShopping Cart Menu:\n");   //menu
        printf("1. Add Item\n");
        printf("2. Delete Item\n");
        printf("3. Search Item\n");
        printf("4. Update Item Quantity\n");
        printf("5. Display Cart\n");
        printf("6. Prepare Cart\n");
        printf("7. Generate Bill\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {                       //All choices
            case 1:
                printf("Enter item description: ");
                scanf("%s", description);
                printf("Enter item price: ");
                scanf("%f", &price);
                printf("Enter item quantity: ");
                scanf("%d", &quantity);
                additem(&shoppingCart, description, price, quantity);
                break;

            case 2:
                printf("Enter ID of item to delete: ");
                scanf("%d", &itemId);
                deleteitem(&shoppingCart, itemId);
                break;

            case 3:
                printf("Enter ID of item to search: ");
                scanf("%d", &itemId);
                searchitem(shoppingCart, itemId);
                break;

            case 4:
                printf("Enter ID of item to update: ");
                scanf("%d", &itemId);
                printf("Enter new quantity: ");
                scanf("%d", &newQuantity);
                updateitem(shoppingCart, itemId, newQuantity);
                break;

            case 5:
                displayCart(shoppingCart);
                break;

            case 6:
                prepareCart(shoppingCart);
                break;

            case 7:
                generateBill(shoppingCart);
                break;
            case 8:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}

