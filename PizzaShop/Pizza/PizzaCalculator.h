#pragma once
#include "Pizza.h"

class PizzaCalculator
{
private:
	std::stack<std::pair<Ingredient*, short int>>* pizza;
public:
	PizzaCalculator(Pizza* pizza_) :
		// We create a copy of original stack so as not to override original one
		pizza{ new std::stack<std::pair<Ingredient*, short int>>{ pizza_->getPizza() } }
	{}
	float Calculate() {
		float totPrice{};
		do {
			totPrice += pizza->top().first->price(pizza->top().second);
			pizza->pop();
		} while (!pizza->empty());
		return totPrice;
	}
};

