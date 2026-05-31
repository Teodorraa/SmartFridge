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

    void deleteProduct(const char* name){
        for(size_t i=0; i<items.size(); i++) {
            if(strcmp(items[i]->getName(), name) == 0) {
                delete items[i];
                items.erase(items.begin() + i);
                cout << "Deleted product.\n";
                return;
            }
        }
        cout << "Product not found.\n";
    }

    void editProduct(const char* name){
        for(size_t i=0; i<items.size(); i++) {
            if(strcmp(items[i]->getName(), name) == 0) {
                char cat[50], exp[15];
                int qty;
                cout << "New category: "; cin >> cat;
                cout << "New quantity: "; cin >> qty;
                cout << "New expiration: "; cin >> exp;
                delete items[i];
                items[i] = new FoodProduct(name, cat, qty, exp);
                cout << "Product updated.\n";
                return;
            }
        }

        cout << "Product not found.\n";
    }

    void showAll() const {
        for(size_t i=0; i<items.size(); i++) items[i]->showInfo();
    }

    void searchByName(const char* name) const {

        for(size_t i=0; i<items.size(); i++)
            if(strcmp(items[i]->getName(), name) == 0) items[i]->showInfo();
    }

    void filterByCategory(const char* cat) const {
        for(size_t i=0; i<items.size(); i++)
            if(strcmp(items[i]->getCategory(), cat) == 0) items[i]->showInfo();
    }

    void checkExpiringSoon(const char* today) const{
      cout << "Products expiring soon:\n";
      for(size_t i=0; i<items.size(); i++)
      if(strcmp(items[i]->getExpiration(), today) <= 0) items[i]->showInfo();
    }

    void checkExpired(const char* today) const{
        cout << "Expired products:\n";
        for(size_t i=0; i<items.size(); i++)
        if(strcmp(items[i]->getExpiration(), today) < 0) items[i]->showInfo();
    
    }

    void sortByName() {
        for(size_t i=0; i<items.size(); i++) {
            for(size_t j=i+1; j<items.size(); j++) {
                if(strcmp(items[i]->getName(), items[j]->getName()) > 0) {
                    FoodProduct* temp = items[i];
                    items[i] = items[j];
                    items[j] = temp;
                }
            }
        }
        cout << "Products sorted by name.\n";
    }

    void lowStockAlert() const {
        cout << "Low stock products (<=2):\n";
        for(size_t i=0; i<items.size(); i++) {
            if(items[i]->getQuantity() <= 2)
                cout << items[i]->getName() << " - Quantity: " << items[i]->getQuantity() << endl;
        }
    }


    void saveToFile(const char* filename) const;

    void loadFromFile(const char* filename);

    FoodProduct** getItems();

    int getItemCount() const;
};

#endif