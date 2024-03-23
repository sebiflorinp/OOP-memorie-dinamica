#include "repoTests.h"
#include "assert.h"
#include "../domain/models.h"
#include "../repos/repos.h"

void testAddProductRepo() {
    // Arrange
    ProductsRepo* repo = createRepo();
    Product* newProduct = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    Product* newProduct1 = createProduct(2, "Computer", "AAAA", "Aaaa", 12, 12);

    //Act
    bool actual1 = addProductRepo(repo, newProduct);
    bool actual2 = addProductRepo(repo, newProduct);
    bool actual3 = addProductRepo(repo, newProduct1);

    // Assert
    assert(repo->products[0]->id == 1);
    assert(actual1 == true);
    assert(actual2 == false);
    assert(actual3 == true);

    // Cleanup
    destroyRepo(repo);
}

void testUpdateProductRepo() {
    // Arrange
    ProductsRepo* repo = createRepo();
    Product* newProduct = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    addProductRepo(repo, newProduct);

    // Arrange
    bool actual1 = updateProductRepo(repo, 1, 30, 30);
    bool actual2 = updateProductRepo(repo, 2, 30,30);

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);

    // Cleanup
    destroyRepo(repo);
}

void testDeleteProductRepo() {
    // Arrange
    ProductsRepo* repo = createRepo();
    Product* product1 = createProduct(1, "Computer", "AAAA", "Aaaa", 12, 12);
    addProductRepo(repo, product1);
    Product* product2 = createProduct(2, "Computer", "AAAA", "Aaa", 12, 12);
    addProductRepo(repo, product2);

    // Act
    bool actual1 = deleteProductRepo(repo, 1);
    bool actual2 = deleteProductRepo(repo, 1);

    // Assert
    assert(actual1 == true);
    assert(actual2 == false);
    assert(repo->products[0]->id == 2);
    assert(repo->numberOfProducts == 1);

    // Cleanup
    destroyRepo(repo);
}