#include <stdlib.h>
#include <string.h>
#include "controllers.h"
#include "../domain/validators.h"
#include "../repos/repos.h"

/*
 * Attempts to add a new product in the list of products
 * Preconditions: products: a pointer to an instance of the ProductsRepo class
 *                id: a positive integer
 *                type: a pointer to a char
 *                manufacturer: a pointer to a char
 *                model: a pointer to a char
 *                price: a pointer to a char
 *                quantity: a pointer to a char
 * Post-conditions: a boolean
 */
bool addProductController(ProductsRepo* repo, int id, char* type, char* manufacturer, char* model,
                          char* price, char* quantity) {
    // create the new product
    Product* newProduct = createProduct(id, type, manufacturer, model, atof(price), atoi(quantity));

    // add the new product
    bool result = addProductRepo(repo, newProduct);

    // if the result is false free the memory allocated to the new product
    if (!result) {
        destroyProduct(newProduct);
    }
    return result;
}

/*
 * Attempts to update the product with the received id
 * Preconditions: repo: a pointer to an instance of the ProductsRepo class
 *                productToUpdateId: a positive integer
 *                newQuantity: a positive integer
 *                newPrice: a positive float
 * Post-conditions: a boolean
 */
bool updateProductController(ProductsRepo* repo, int productToUpdateId, int newQuantity, float newPrice) {
    // attempt to update the product
    bool result = updateProductRepo(repo, productToUpdateId, newQuantity, newPrice);
    return result;
}

/*
 * Attempts to delete the product with the received id
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                productToDeleteId: a positive integer
 * Post-conditions: a boolean
 */
bool deleteProductController(ProductsRepo* repo, int productToDeleteId) {
    // attempt to delete the product
    bool result = deleteProductRepo(repo, productToDeleteId);
    return result;
}

/*
 * Returns the available products sorted depending on the function received as a parameter
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                compareProducts: a function that returns a bool and takes two instances of the Product struct as parameters
 * Post-conditions: a pointer to an instance of the ProductsRepo struct
 */
ProductsRepo* getAvailableProducts(ProductsRepo* repo, bool (*compareProducts)(Product*, Product*)) {
    // allocate memory for the result and initialize the number of products
    ProductsRepo* result = createRepo();

    // go through all products and only copy those that are still available
    for (int i = 0; i < repo->numberOfProducts; i++) {
        if (repo->products[i]->quantity > 0) {
            addProductRepo(result, repo->products[i]);
        }
    }
        // sort depending on the comparison function
        for (int i = 0; i < result->numberOfProducts - 1; i++) {
            for (int j = i + 1; j < result->numberOfProducts; j++) {
                if (!compareProducts(result->products[i], result->products[j])) {
                    Product* aux = result->products[i];
                    result->products[i] = result->products[j];
                    result->products[j] = aux;
                }
            }
        }

    return result;
}

/*
 * Returns the products that meet a certain property depending on the value and function received as parameters
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                checkProductProperty: a function that returns a bool and takes as arguments a pointer to a Product and a pointer to a char
 *                valueToCompareWith: a pointer to a char
 * Post-conditions: a pointer to an instance of the ProductsRepo
 */
ProductsRepo* getProductsFiltered(ProductsRepo* repo, bool (*checkProductProperty)(Product*, char*), char* valueToCompareWith) {
    // allocate memory to the result repo
    ProductsRepo* result = createRepo();

    // filter by different criteria
    for (int i = 0; i < repo->numberOfProducts; i++) {
        if (checkProductProperty(repo->products[i], valueToCompareWith)) {
            addProductRepo(result, repo->products[i]);
        }
    }

    return result;
}
