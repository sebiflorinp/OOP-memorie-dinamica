#include "tests.h"
#include "repoTests.h"
#include "validatorsTest.h"
#include "controllerTests.h"
#include "utilsTests.h"

void runAllTests() {
    // repo tests
    testAddProductRepo();
    testUpdateProductRepo();
    testDeleteProductRepo();

    // validators tests
    testValidateId();
    testValidateManufacturer();
    testValidateModel();
    testValidateOption();
    testValidatePrice();
    testValidateQuantity();
    testValidateType();

    // controller tests
    testAddProductController();
    testUpdateProductController();
    testDeleteProductController();
    testGetAvailableProducts();
    testGetProductsFiltered();

    // utils tests
    testGetIdForNewProduct();
    testCompareProductsInAscendantOrder();
    testCompareProductsInDescendantOrder();
    testCompareManufacturers();
    testComparePrice();
    testCompareQuantity();
}