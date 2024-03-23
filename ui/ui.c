#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../domain/validators.h"
#include "../controllers/controllers.h"
#include "../utils/utils.h"
#include "../repos/repos.h"

void app() {
    printf("This is a electronics store shop.\n");

    bool running = true;
    ProductsRepo* productsRepo= createRepo();
    // needed for fgets to pause the execution of the program
    char dummyInput[100];
    while (running) {
        printf(
            "Choose one of the following commands:\n"
           "  1. Add new product.\n"
           "  2. Update product.\n"
           "  3. Delete product.\n"
           "  4. Display available products.\n"
           "  5. Display products filtered by a certain criteria.\n"
           "  6. Exit the application.\n"
           );
        char* option = getInput();
        if (validateOption(option)) {
            switch (atoi(option)) {
                // add new product feature
                case 1:
                    // get type
                    printf("Input the type of the product, the product can be a Laptop, a Computer or a Fridge.\n");
                    char* type = getInput();

                    // get id for new product
                    int id = getIdForNewProduct(productsRepo);

                    // get manufacturer
                    printf("Input the manufacturer of the product.\n");
                    char* manufacturer = getInput();

                    // get model
                    printf("Input the model of the product.\n");
                    char* model = getInput();

                    // get price
                    printf("Input the price of the product.\n");
                    char* price = getInput();

                    // get quantity
                    printf("Input the quantity of the product.\n");
                    char* quantity = getInput();

                    // check if the input data is valid
                    if (
                            validateType(type) &&
                            validateManufacturer(manufacturer) &&
                            validateModel(model) &&
                            validatePrice(price) &&
                            validateQuantity(quantity)
                            ) {
                        // add the product if the data is valid
                        bool result = addProductController(productsRepo, id, type, manufacturer, model, price, quantity);
                        if (result) {
                            printf("The product was added successfully.\n");
                        } else {
                            printf("The product was not added.\n");
                        }

                    } else {
                        printf("The input data is invalid.\n");
                    }
                    free(type);
                    free(manufacturer);
                    free(model);
                    free(price);
                    free(quantity);
                    break;
                // update product
                case 2:
                    // check if there are any products to update
                    if (productsRepo->numberOfProducts == 0) {
                        printf("There are no products to update.\n");
                    } else {
                        // display products and get the id
                        printf("Input the id of the product that will be updated.\n");
                        displayProducts(productsRepo);
                        char* idChar = getInput();

                        // get the new price
                        printf("Input the updated price of the chosen product.\n");
                        char* newPrice = getInput();

                        // get the new quantity
                        printf("Input the updated quantity of the chosen product\n");
                        char* newQuantity = getInput();

                        // check if the input is valid and if it is attempt the update
                        if (validatePrice(newPrice) && validateQuantity(newQuantity)) {
                            bool result = updateProductController(
                                    productsRepo,
                                    atoi(idChar),
                                    atoi(newQuantity),
                                    atof(newPrice)
                                    );
                            if (!result) {
                                printf("The update was unsuccessful\n");
                            } else {
                                printf("The update was successful\n");
                            }
                        }
                        free(idChar);
                        free(newPrice);
                        free(newQuantity);
                    }
                    break;
                // delete product
                case 3:
                    // check if there are any products to display
                    if (productsRepo->numberOfProducts == 0) {
                        printf("There are no products to delete.\n");
                    } else {
                        // display the products and obtain the id of the product that will be deleted
                        printf("Input the id of the product that will be deleted.\n");
                        displayProducts(productsRepo);
                        char* idChar = getInput();

                        // attempt to delete the product with the input id
                        if (validateId(idChar)) {
                            bool result = deleteProductController(productsRepo, atoi(idChar));
                            if (result) {
                                printf("The selected product was deleted successfully.\n");
                            } else {
                                printf("The deletion was unsuccessful.\n");
                            }
                        } else {
                            printf("The input id was invalid.\n");
                        }
                        free(idChar);
                    }
                    break;
                case 4:
                    // get the ordering of the list
                    printf("Input the ordering of the available products: ascending / descending\n");
                    char* ordering = getInput();

                    // check if the input is valid
                    if (strcmp(ordering, "ascending") == 0 || strcmp(ordering, "descending") == 0) {
                        ProductsRepo* result;
                        if(strcmp(ordering, "ascending") == 0) {
                             result = getAvailableProducts(productsRepo,
                                                                 compareProductsInAscendantOrder);
                        } else {
                            result = getAvailableProducts(productsRepo,
                                                                        compareProductsInDescendantOrder);
                        }
                        // display a table if there are any products available, otherwise show a message
                        if (result->numberOfProducts > 0) {
                            displayProducts(result);
                        } else {
                            printf("There are no products available.\n");
                        }
                        if (result->numberOfProducts != 0) {
                            free(result->products);
                        }
                        free(result);
                    } else {
                        printf("The input ordering is invalid.\n");
                    }
                    free(ordering);
                    break;
                case 5:
                    // get the criteria
                    printf("Input the criteria by which the products will be filtered: manufacturer / price / quantity\n");
                    char* criteria = getInput();

                    // check if the input is valid
                    if (
                            strcmp(criteria, "manufacturer") == 0 ||
                            strcmp(criteria, "price") == 0 ||
                            strcmp(criteria, "quantity") == 0
                            ) {
                        // get the value by which the products should be filtered
                        char* valueToFilterBy;
                        ProductsRepo* result;
                        if (strcmp(criteria, "manufacturer") == 0) {
                            printf("Input the manufacturer of the product.\n");
                            valueToFilterBy = getInput();

                            // check if the manufacturer is valid
                            if (validateManufacturer(valueToFilterBy)) {
                                // get the number of filtered products and the result
                                result = getProductsFiltered(productsRepo, compareManufacturers, valueToFilterBy);
                            } else {
                                printf("The input manufacturer is invalid.\n");
                            }
                        } else if (strcmp(criteria, "price") == 0) {
                            printf("Input the price of the product.\n");
                            valueToFilterBy = getInput();

                            // check if the price is valid
                            if (validatePrice(valueToFilterBy)) {
                                // get the number of filtered products and the result
                                result = getProductsFiltered(productsRepo, comparePrice, valueToFilterBy);
                            } else {
                                printf("The input price is invalid.\n");
                            }
                        } else if (strcmp(criteria, "quantity") == 0) {
                            printf("Input the quantity of the product.\n");
                            valueToFilterBy = getInput();

                            // check if the quantity is valid
                            if (validateQuantity(valueToFilterBy)) {
                                // get the number of filtered products and the result
                                result = getProductsFiltered(productsRepo, compareQuantity, valueToFilterBy);
                            } else {
                                printf("The input quantity is invalid.\n");
                            }
                        }
                        free(valueToFilterBy);
                        // display a message if there are no products after the filtering and display the remaining ones otherwise
                        if (result->numberOfProducts == 0) {
                            printf("There are no products after the filtering.\n");
                        } else {
                            displayProducts(result);
                        }
                        if (result->numberOfProducts != 0) {
                            free(result->products);
                        }
                        free(result);
                    } else {
                        printf("The input criteria is invalid.\n");
                    }
                    free(criteria);
                    break;
                case 6:
                    running = false;
                    printf("Thank you for using this application.\n");
                    break;
            }
            printf("Press ENTER to continue.\n");
            fgets(dummyInput, 100, stdin);

        }
        free(option);
    }
    destroyRepo(productsRepo);
}

void displayProducts(ProductsRepo* repo) {
    printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    printf("|  %-6s  |  %-10s  |  %-20s  |  %-20s  |  %-11s  |  %-11s  |\n", "Id", "Type", "Manufacturer", "Model", "Price", "Quantity");
    printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    for (int i = 0; i < repo->numberOfProducts; i++) {
        printf(
                "|  %-6d  |  %-10s  |  %-20s  |  %-20s  |  %-11f  |  %-11d  |\n",
                repo->products[i]->id,
                repo->products[i]->type,
                repo->products[i]->manufacturer,
                repo->products[i]->model,
                repo->products[i]->price,
                repo->products[i]->quantity
                );
        printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");
    }
    if (repo->numberOfProducts == 0) {
        printf("|  %-6s  |  %-10s  |  %-20s  |  %-20s  |  %-11s  |  %-11s  |\n", " ", " ", " ", " ", " ", " ");
        printf("+----------+--------------+------------------------+------------------------+---------------+---------------+\n");

    }
}

/*
 * A function that removes the trailing new line from fgets.
 * Preconditions: string: a pointer to a char array
 * Post-conditions: -
 */
void removeTrailingNewLine(char* string) {
    if (strlen(string) > 0) {
        string[strlen(string) - 1] = '\0';
    }
}

char* getInput() {
    // get the input from the user
    char* input = malloc(sizeof(char) * 20);
    fgets(input, 20, stdin);
    removeTrailingNewLine(input);

    // return a pointer to the input
    return input;
}
