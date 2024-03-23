#include <string.h>
#include "models.h"
#include <stdlib.h>

/*
 * Creates a new product
 * Preconditions: id: a positive integer
 *                type: a pointer to a char
 *                manufacturer: a pointer to a char
 *                model: a pointer to a char
 *                price: a positive float
 *                quantity: a positive integer
 * Post-conditions: a pointer to a new instance of the Product struct
 */
Product* createProduct(int id, char* type, char* manufacturer, char *model, float price, int quantity) {
    // allocate the necessary space for a new product
    Product* newProduct = malloc(sizeof(Product));
    newProduct->type = malloc(sizeof(char) * (strlen(type) + 1));
    newProduct->manufacturer = malloc(sizeof(char) * (strlen(manufacturer) + 1));
    newProduct->model = malloc(sizeof(char) * (strlen(model) + 1));

    // assign the values
    newProduct->id = id;
    strcpy(newProduct->type, type);
    strcpy(newProduct->manufacturer, manufacturer);
    strcpy(newProduct->model, model);
    newProduct->price = price;
    newProduct->quantity = quantity;

    // return the pointer to the newProduct
    return newProduct;
}

/*
 * Deallocates all the memory used by the received Product.
 * Preconditions: productToDestroy: a pointer to an instance of the Product class
 * Post-conditions: -
 */
void destroyProduct(Product* productToDestroy) {
    // deallocate the space used by the char fields
    free(productToDestroy->type);
    free(productToDestroy->manufacturer);
    free(productToDestroy->model);

    // deallocate the pointer to the product
    free(productToDestroy);
}
