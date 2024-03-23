#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "repos.h"

/*
 * Instantiates a repository and returns a pointer to it.
 * Preconditions: -
 * Post-conditions: a pointer to an instance of ProductsRepo
 */
ProductsRepo* createRepo() {
    // create the repo
    ProductsRepo* productsRepo = malloc(sizeof(ProductsRepo));

    // initialize the numberOfProducts
    productsRepo->numberOfProducts = 0;
    return productsRepo;
}

/*
 * Deallocates the memory that is used by a given instance of the ProductsRepo class.
 * Preconditions: repoToDestroy: a pointer to a ProductsRepo struct
 * Post-conditions: -
 */
void destroyRepo(ProductsRepo* repoToDestroy) {
    // destroy the products in the repo
    for (int i = 0; i < repoToDestroy->numberOfProducts; i++) {
        destroyProduct(repoToDestroy->products[i]);
    }

    // destroy the pointer to the repo
    if (repoToDestroy->numberOfProducts != 0) {
        free(repoToDestroy->products);
    }
    free(repoToDestroy);
}

/*
 * Attempts to add the received product in the repo
 * Preconditions: repo: a pointer to an instance of the ProductsRepo
 *                newProducts: a pointer to an instance of the Product struct
 * Post-conditions: a bool
 */
bool addProductRepo(ProductsRepo* repo, Product* newProduct) {
    // check if there is already a product with the id of the received one
        for (int i = 0; i < repo->numberOfProducts; i++) {
        if (repo->products[i]->id == newProduct->id) {
            return false;
        }
    }

    // allocate space for the new product

    // check if there is already a product with the same type, name, producer and model
    for (int i = 0; i < repo->numberOfProducts; i++) {
        if (
                strcmp(repo->products[i]->model, newProduct->model) == 0 &&
                strcmp(repo->products[i]->manufacturer, newProduct->manufacturer) == 0 &&
                repo->products[i]->price == newProduct->price &&
                strcmp(repo->products[i]->type, newProduct->type) == 0
                ) {
            repo->products[i]->quantity += newProduct->quantity;
            destroyProduct(newProduct);
            return true;
        }
    }

    if (repo->numberOfProducts == 0) {
        repo->products = malloc(sizeof(Product*));
    } else {
        Product** reallocatedProducts = realloc(repo->products, sizeof(Product*) * (repo->numberOfProducts + 1));
        repo->products = reallocatedProducts;
    }

    // add the new product and increase the number of products
    repo->products[repo->numberOfProducts++] = newProduct;
    return true;
}

/*
 * Attempts to update the product with the received id.
 * Preconditions: repo: a pointer to an instance of the ProductsRepo struct
 *                productToUpdateId: a positive integer
 *                newQuantity: a positive integer
 *                newPrice: a positive float
 * Post-conditions: a boolean
 */
bool updateProductRepo(ProductsRepo* repo, int productToUpdateId, int newQuantity, float newPrice) {
    // check if there is a product with the id of productToUpdateId
    int position = -1;
    for (int i = 0; i < repo->numberOfProducts; i++) {
        if (repo->products[i]->id == productToUpdateId) {
            position = i;
        }
    }

    // if the product is found, update it
    if (position != -1) {
        repo->products[position]->quantity = newQuantity;
        repo->products[position]->price = newPrice;
        return true;
    }

    // return false a product with the id of productToUpdateId does not exist
    return false;
}

/*
 * Attempts to delete the product with the received id.
 * Preconditions: repo: a pointer to an instance of the ProductsRepo class.
 *                productToDeleteId: a positive integer
 * Post-conditions: a bool
 */
bool deleteProductRepo(ProductsRepo* repo, int productToDeleteId) {
    // check if there is a product with the id of productToDeleteId
    bool exists = false;
    int position = -1;
    for (int i = 0; i < repo->numberOfProducts; i++) {
        if (repo->products[i]->id == productToDeleteId) {
            exists = true;
            position = i;
        }
    }

    // return false if the product does not exist
    if (!exists) {
        return false;
    }

    // destroy the product that is deleted
    destroyProduct(repo->products[position]);
    for (int i = position; i < repo->numberOfProducts - 1; i++) {
        repo->products[i] = repo->products[i + 1];
    }

    // reallocate the memory of products
    //repo->products = realloc(repo->products, repo->numberOfProducts - 1);
    repo->numberOfProducts--;

    return true;
}