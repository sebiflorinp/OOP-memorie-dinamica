#include <stdbool.h>
#include "../domain/models.h"
#include "../repos/repos.h"

#ifndef LAB2_4_CONTROLLERS_H
#define LAB2_4_CONTROLLERS_H

bool addProductController(ProductsRepo* repo, int id, char* type, char* manufacturer, char* model,
               char* price, char* quantity);

bool updateProductController(ProductsRepo* repo, int productToUpdateId, int newQuantity, float newPrice);

bool deleteProductController(ProductsRepo* repo, int productToDeleteId);

ProductsRepo* getAvailableProducts(ProductsRepo* repo, bool (*compareProducts)(Product*, Product*));

ProductsRepo* getProductsFiltered(ProductsRepo* repo, bool (*checkProductProperty)(Product*, char*), char* valueToCompareWith);

#endif //LAB2_4_CONTROLLERS_H

