#include <vector>
#include <algorithm> 
#include <cmath>
#include <cassert>
#include "DB/DB.h"
#include "Pizza/PizzaFactory.h"
#include "Pizza/Pizza.h"
#include "Waiter/Waiter.h"

static void display(DB* db) {
	for (Ingredient* ingr : db->ingredients) {
		bool is = false;
		cout << "{\n";
		cout << '\t' << ingr->name << endl;
		cout << '\t' << ingr->basePrice << endl;
		cout << '\t' << "multipliers: [ ";
		for (auto& m : ingr->multipliers) {
			if (is) cout << ", ";
			cout << m;
			is = true;
		}
		cout << " ]\n";
		cout << "}\n";
	}
}

int main() {
	DB db;
	db.importIngredients("DB/ingredients.json");
	db.importPizzas("DB/pizzas.json");

	// Create a Waiter object
	Waiter waiter(&db);

	// Handle user choice
	size_t indx = waiter.handleUserChoice(&db);


	PizzaFactory pFac{ &db };

	Pizza* pizza = pFac.createPizza(indx);

	waiter.customizePizza(pizza);

	waiter.displayPizzaDetails(pizza);

	return 0;
}