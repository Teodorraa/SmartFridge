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

    Product& operator=(const Product& other) {
        if(this == &other) return *this;
        delete[] name;
        delete[] category;
        if(other.name) {
            name = new char[strlen(other.name)+1];
            strcpy(name, other.name);
        } else name = nullptr;

        if(other.category) {
            category = new char[strlen(other.category)+1];
            strcpy(category, other.category);
        } else category = nullptr;
        return *this;
    }

    virtual ~Product() {
        delete[] name;
        delete[] category;
   }

    virtual void showInfo() const = 0;
    const char* getName() const { return name; }
    const char* getCategory() const { return category; }

    friend ostream& operator<<(ostream& out, const Product& p) {
       out << "Name: " << p.name
            << ", Category: " << p.category;
        return out;
    }
};
#endif