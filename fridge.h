#ifndef FRIDGE_H
#define FRIDGE_H

#include "food_product.h"
#include <fstream>
#include <vector>

using namespace std;

class Fridge {
private:
    vector<FoodProduct*> items;

public:
    Fridge(){}

    ~Fridge(){
    for(size_t i=0; i<items.size(); i++) delete items[i];
        items.clear();
}

    void addProduct(FoodProduct* f) { items.push_back(f); }

    void deleteProduct(const char* name);

    void editProduct(const char* name);

    void showAll() const;

    void searchByName(const char* name) const;

    void filterByCategory(const char* cat) const;

    void checkExpiringSoon(const char* today) const;

    void checkExpired(const char* today) const;

    void saveToFile(const char* filename) const;

    void loadFromFile(const char* filename);

    FoodProduct** getItems();

    int getItemCount() const;
};

#endif