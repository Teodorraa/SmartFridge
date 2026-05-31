#include <iostream>
#include "fridge.h"
#include "food_product.h"
#include "recipes.h"
#include "utils.h"  

using namespace std;

int dateToInt(const char* date) {
    int day, month, year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    return year*10000 + month*100 + day;
}

int main() {
    Fridge fridge;
    int choice;

    const char* saladIngredients[] = {"Lettuce", "Tomato", "Cucumber"};
    const char* sandwichIngredients[] = {"Bread", "Cheese", "Tomato"};
    Recipe r1("Salad", saladIngredients, 3);
    Recipe r2("Sandwich", sandwichIngredients, 3);
    Recipe* recipes[] = {&r1, &r2};
    int recipeCount = 2;

    do {
        cout << "\n--- Smart Fridge ---\n";
        cout << "1.Add 2.Delete 3.Edit 4.Show 5.Search 6.Filter 7.Sort 8.Low stock 9.Save 10.Load 11.Show recipes 12.Check expiration 0.Exit\nChoice: ";
        cin >> choice;

        char name[50], category[50], exp[15];
        int qty;

        switch(choice) {
            case 1:
                cout << "Name: "; cin >> name;
                cout << "Category: "; cin >> category;
                cout << "Quantity: "; cin >> qty;
                cout << "Expiration (DD.MM.YYYY): "; cin >> exp;
                fridge.addProduct(new FoodProduct(name, category, qty, exp));
                break;
            case 2:
                cout << "Name to delete: "; cin >> name;
                fridge.deleteProduct(name);
                break;
            case 3:
                cout << "Name to edit: "; cin >> name;
                fridge.editProduct(name);
                break;
            case 4:
                fridge.showAll();
                break;
            case 5:
                cout << "Name to search: "; cin >> name;
                fridge.searchByName(name);
                break;
            case 6:
                cout << "Category to filter: "; cin >> category;
                fridge.filterByCategory(category);
                break;
            case 7:
                fridge.sortByName();
                break;
            case 8:
                fridge.lowStockAlert();
                break;
            case 9:
                fridge.saveToFile("data.txt");
                break;
            case 10:
                fridge.loadFromFile("data.txt");
                break;
            case 11:
                cout << "Available recipes:\n";
                for(int i=0; i<recipeCount; i++) {
                    if(recipes[i]->canMake(fridge.getItems()))
                        recipes[i]->showRecipe();
                }
                break;
            case 12: {
                char today[15];
                cout << "Enter today's date (DD.MM.YYYY): ";
                cin >> today;
                cout << "\nProducts expiring soon:\n";
                fridge.checkExpiringSoon(today);
                cout << "\nProducts already expired:\n";
                fridge.checkExpired(today);
                break;
            }
        }
    } while(choice != 0);

    return 0;
}