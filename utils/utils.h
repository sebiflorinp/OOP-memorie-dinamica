#include "../domain/models.h"
#include "../repos/repos.h"

#ifndef LAB2_4_UTILS_H
#define LAB2_4_UTILS_H

int getIdForNewProduct(ProductsRepo* repo);

bool compareProductsInAscendantOrder(Product* product1, Product* product2);

bool compareProductsInDescendantOrder(Product* product1, Product* product2);

bool compareManufacturers(Product* product, char* manufacturer);

bool comparePrice(Product* product, char* price);

bool compareQuantity(Product* product, char* quantity);

#endif //LAB2_4_UTILS_H
