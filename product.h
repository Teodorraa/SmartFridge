#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <cstring>

using namespace std;

class Product {
protected:
    char* name;
    char* category;

public:
    Product() {
        name = nullptr;
        category = nullptr;
    }

    Product(const char* n, const char* c) {
        if(n) {
            name = new char[strlen(n)+1];
            strcpy(name,n);
        } else name = nullptr;

        if(c) {
            category = new char[strlen(c)+1];
            strcpy(category,c);
        } else category = nullptr;
}
};
#endif