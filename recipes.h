#ifndef RECIPE_H
#define RECIPE_H

#include "food_product.h"
#include <vector>

using namespace std;

class Recipe {
private:
    char* name;               
    char* ingredients[10];    
    int ingredientCount;     

public:
   
    Recipe(const char* n, const char* ingr[], int count) {
        name = new char[strlen(n)+1]; strcpy(name,n);
        ingredientCount = count;
        for(int i=0;i<count;i++){
            ingredients[i] = new char[strlen(ingr[i])+1];
            strcpy(ingredients[i],ingr[i]);
        }
    }

    ~Recipe() {
        delete[] name;
        for(int i=0;i<ingredientCount;i++) delete[] ingredients[i];
    }

    bool canMake(const vector<FoodProduct*>& items) const {
        for(int i=0;i<ingredientCount;i++){
            bool found=false;
            for(size_t j=0;j<items.size();j++){
                if(strcmp(items[j]->getName(),ingredients[i])==0 && items[j]->getQuantity()>0){
                    found=true; break;
                }
            }
            if(!found) return false; 
        }
        return true;
    }

    void showRecipe() const {
        cout << name << " (needs: ";
        for(int i=0;i<ingredientCount;i++){
            cout << ingredients[i];
            if(i<ingredientCount-1) cout << ", ";
        }
        cout << ")\n";
    }
};

#endif