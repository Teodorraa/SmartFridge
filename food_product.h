#ifndef FOODPRODUCT_H
#define FOODPRODUCT_H

#include "product.h"

class FoodProduct : public Product {
private:
    int quantity;
    char* expirationDate;

public:
    FoodProduct(): Product() {}

    FoodProduct(const char* n, const char* c, int q, const char* exp)
        : Product(n,c), quantity(q) {}

    FoodProduct(const FoodProduct& other)
        : Product(other), quantity(other.quantity) {}
    
    FoodProduct& operator=(const FoodProduct& other) {}

    ~FoodProduct() {}

    void showInfo() const {}

    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
    const char* getExpiration() const { return expirationDate; }
    
    bool isExpired(const char* today) const {}

    friend ostream& operator<<(ostream& out, const FoodProduct& f) {};
};
#endif