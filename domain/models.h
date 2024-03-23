#ifndef LAB2_4_MODELS_H
#define LAB2_4_MODELS_H

typedef struct {
    int id;
    char *type;
    char *manufacturer;
    char *model;
    float price;
    int quantity;
}Product;

Product* createProduct(int id, char* type, char* manufacturer, char* model, float price, int quantity);

void destroyProduct(Product* productToDestroy);

#endif //LAB2_4_MODELS_H
