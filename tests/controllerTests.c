#include <assert.h>
#include <stdlib.h>
#include "controllerTests.h"
#include "../controllers/controllers.h"
#include "../utils/utils.h"

void testAddProductController() {
    // Arrange
    ProductsRepo* repo = createRepo();

    //Act
    bool actual1 = addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12",
                                        "12");
    bool actual2 = addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12",
                                        "12");

    // Assert
    assert(actual1 == true);
    assert(repo->products[0]->id == 1);
    assert(actual2 == false);

    // Cleanup
    destroyRepo(repo);
}

void testUpdateProductController() {
    // Arrange
    ProductsRepo* repo = createRepo();
    addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12","12");

    // Act
    bool actual1 = updateProductController(repo, 1, 2, 2.3f);
    bool actual2 = updateProductController(repo, 2, 2, 2.3f);

    // Assert
    assert(actual1 == true);
    assert(repo->products[0]->quantity == 2);
    assert(actual2 == false);

    // Cleanup
    destroyRepo(repo);

}

void testDeleteProductController() {
    // Arrange
    ProductsRepo* repo = createRepo();
    addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12","12");
    addProductController(repo, 2, "Computer", "AAAA", "Aaa", "12","12");

    // Act
    bool actual1 = deleteProductController(repo, 1);
    bool actual2 = deleteProductController(repo, 3);

    // Assert
    assert(actual1 == true);
    assert(repo->products[0]->id == 2);
    assert(repo->numberOfProducts == 1);
    assert(actual2 == false);

    // Cleanup
    destroyRepo(repo);
}

void testGetAvailableProducts() {
    // Arrange
    ProductsRepo* repo = createRepo();
    addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12","12");
    addProductController(repo, 2, "Computer", "AAAA", "Aaaa", "11","12");
    addProductController(repo, 3, "Computer", "AAAA", "Aaaa", "13","0");

    // Act
    ProductsRepo* actual1 = getAvailableProducts(repo, compareProductsInAscendantOrder);

    // Assert
    assert(actual1->products[0]->id == 2);
    assert(actual1->products[1]->id == 1);

    // Cleanup
    destroyRepo(repo);
    free(actual1->products);
    free(actual1);
}

void testGetProductsFiltered() {
    // Arrange
    ProductsRepo* repo = createRepo();
    addProductController(repo, 1, "Computer", "AAAA", "Aaaa", "12","12");
    addProductController(repo, 2, "Computer", "AAAA", "aa", "11","12");
    addProductController(repo, 3, "Computer", "AAAA", "Aaa", "12","0");

    // Act
    ProductsRepo* actual1 = getProductsFiltered(repo, comparePrice, "12");

    // Assert
    assert(actual1->products[0]->id == 1);
    assert(actual1->products[1]->id == 3);

    // Cleanup
    destroyRepo(repo);
    free(actual1->products);
    free(actual1);
}
