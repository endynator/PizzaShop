#include "Pizza.h"
#include <iostream>
#include "PizzaCalculator.h"

using namespace std;

Pizza* Pizza::clone() {
	Pizza* clonedPizza = new Pizza;
	clonedPizza->name = this->name;
	clonedPizza->pizza = pizza;
	return clonedPizza;
}

void Pizza::modifyMultiplicator(Ingredient* ingr, short int s)
{
	assert(s >= 0 && s <= 3 && "Multiplier must be in the range of 0 to 3");
	std::stack<std::pair<Ingredient*, short int>>* tempStack = new std::stack<std::pair<Ingredient*, short int>>();
	bool found = false;

	// Copy elements from original stack to temporary stack, modifying the multiplier of the target ingredient
	while (!pizza->empty()) {
		if (pizza->top().first == ingr && !found) {
			// Modify the multiplier of the ingredient
			tempStack->emplace(ingr, s);
			found = true;
		}
		else {
			tempStack->push(pizza->top());
		}
		pizza->pop();
	}

	// Reasign data
	delete pizza;
	pizza = tempStack;
}