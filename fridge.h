#ifndef FRIDGE_H
#define FRIDGE_H

#include "food_product.h"
#include <fstream>
#include <vector>
#include "utils.h"

using namespace std;

int dateToInt(const char* date);

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
        if(items.empty()) {
            cout << "No products in fridge." << endl;
            return;
        }
        for(size_t i=0; i<items.size(); i++) items[i]->showInfo();
    }

    void searchByName(const char* name) const {
        bool found = false;
        for(size_t i=0; i<items.size(); i++) {
            if(strcmp(items[i]->getName(), name) == 0) {
                items[i]->showInfo();
                found = true;
            }
        }
        if(!found) cout << "No product found with that name." << endl;
    }

    void filterByCategory(const char* cat) const {
        bool found = false;
        for(size_t i=0; i<items.size(); i++) {
            if(strcmp(items[i]->getCategory(), cat) == 0) {
                items[i]->showInfo();
                found = true;
            }
        }
        if(!found) cout << "No products found in that category." << endl;
    }

    void checkExpiringSoon(const char* today) const {
        int todayInt = dateToInt(today);
        bool found = false;
        for(size_t i=0; i<items.size(); i++) {
            if(dateToInt(items[i]->getExpiration()) > todayInt) {
                items[i]->showInfo();
                found = true;
            }
        }
        if(!found) cout << "No products expiring soon." << endl;
    }

    void checkExpired(const char* today) const {
        int todayInt = dateToInt(today);
        bool found = false;
        for(size_t i=0; i<items.size(); i++) {
            if(dateToInt(items[i]->getExpiration()) < todayInt) {
                items[i]->showInfo();
                found = true;
            }
        }
        if(!found) cout << "No expired products." << endl;
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
        bool found = false;
        for(size_t i=0; i<items.size(); i++) {
            if(items[i]->getQuantity() <= 2) {
                cout << items[i]->getName() << " - Quantity: " << items[i]->getQuantity() << endl;
                found = true;
            }
        }
        if(!found) cout << "No low stock products." << endl;
    }


    void saveToFile(const char* filename) const{
        ofstream file(filename);
        for(size_t i=0; i<items.size(); i++)
            file << items[i]->getName() << " "
                 << items[i]->getCategory() << " "
                 << items[i]->getQuantity() << " "
                 << items[i]->getExpiration() << endl;
        cout << "Saved to file.\n";
    }

    void loadFromFile(const char* filename){
        ifstream file(filename);
        if(!file) {
            cout << "Could not open file '" << filename << "'." << endl;
            return;
        }
        for(size_t i=0; i<items.size(); i++) delete items[i];
        items.clear();

        char n[50], c[50], exp[15];
        int qty;
        while(file >> n >> c >> qty >> exp)
            items.push_back(new FoodProduct(n, c, qty, exp));
        cout << "Loaded from file.\n";
    }

    vector<FoodProduct*>& getItems() { return items; }

    size_t itemCount() const { return items.size(); }
};

#endif