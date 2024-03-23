#include "../domain/models.h"
#include <stdbool.h>

#ifndef LAB2_4_REPOS_H
#define LAB2_4_REPOS_H

typedef struct {
    Product** products;
    int numberOfProducts;
}ProductsRepo;

ProductsRepo* createRepo();

void destroyRepo(ProductsRepo* repoToDestroy);

bool addProductRepo(ProductsRepo* repo, Product* newProduct);

bool updateProductRepo(ProductsRepo* repo, int productToUpdateId, int newQuantity, float newPrice);

bool deleteProductRepo(ProductsRepo* repo, int productToDeleteId);

#endif //LAB2_4_REPOS_H
