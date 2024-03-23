#include "../domain/models.h"
#include "../repos/repos.h"

#ifndef LAB2_4_UI_H
#define LAB2_4_UI_H

void app();

void displayProducts(ProductsRepo* repo);

void removeTrailingNewLine(char* string);

char* getInput();

#endif //LAB2_4_UI_H
