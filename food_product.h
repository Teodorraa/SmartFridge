#ifndef FOODPRODUCT_H
#define FOODPRODUCT_H

#include "product.h"

class FoodProduct : public Product {
private:
    int quantity;
    char* expirationDate;

public:
    FoodProduct(): Product() {
        quantity = 0;
        expirationDate = nullptr;
    }

    FoodProduct(const char* n, const char* c, int q, const char* exp)
        : Product(n,c), quantity(q) {
            if(exp) {
            expirationDate = new char[strlen(exp)+1];
            strcpy(expirationDate, exp);
        } else expirationDate = nullptr;
        }

    FoodProduct(const FoodProduct& other)
        : Product(other), quantity(other.quantity) {
            if(other.expirationDate) {
            expirationDate = new char[strlen(other.expirationDate)+1];
            strcpy(expirationDate, other.expirationDate);
        } else expirationDate = nullptr;
}
    
    FoodProduct& operator=(const FoodProduct& other) {
         if(this == &other) return *this; // self-assignment check

        delete[] name;
        delete[] category;

        if(other.getName()) {
        name = new char[strlen(other.getName())+1];
        strcpy(name, other.getName());
        } else name = nullptr;

        if(other.getCategory()) {
        category = new char[strlen(other.getCategory())+1];
        strcpy(category, other.getCategory());
        } else category = nullptr;

        quantity = other.quantity;
        delete[] expirationDate;

        if(other.expirationDate) {
        expirationDate = new char[strlen(other.expirationDate)+1];
        strcpy(expirationDate, other.expirationDate);
        } else expirationDate = nullptr;

        return *this;
}

    ~FoodProduct() {
        delete[] expirationDate;
    }

    void showInfo() const {
        cout << *this
             << ", Quantity: " << quantity
             << ", Expiration Date: " << expirationDate
             << endl;
    }

    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
    const char* getExpiration() const { return expirationDate; }
    
    bool isExpired(const char* today) const {
        return expirationDate && today && strcmp(expirationDate,today)<=0;
}

    friend ostream& operator<<(ostream& out, const FoodProduct& f) {
        out << f.getName() << " (" << f.getCategory() << ")";

        return out;
    };
};
#endif