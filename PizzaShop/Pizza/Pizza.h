#pragma once
#include <string>
#include <stack>
#include "../Ingredient/Ingredient.h"

constexpr size_t PIZZA_INGREDIENT_LIMIT = 20;

class Pizza {
private:
	std::stack<std::pair<Ingredient*, short int>>* pizza;
public:
	std::string name{};

	Pizza() : pizza(new std::stack<std::pair<Ingredient*, short int>>()) {}

	~Pizza() {
		delete pizza;
	}

	void addIngredient(Ingredient* ingr, short int s /*1 to 3*/) {
		assert(pizza->size() < PIZZA_INGREDIENT_LIMIT && "Exceeded the ingredient limit for the pizza");
		assert(s >= 0 && s <= 3 && "Multiplier must be in the range of 0 to 3");
		pizza->push(std::make_pair(ingr, s));
	}

	std::stack<std::pair<Ingredient*, short int>>& getPizza() {
		return *(pizza);
	}

	std::stack<std::pair<Ingredient*, short int>> getPizzaCpy() {
		return *(pizza);
	}

	std::stack<std::pair<Ingredient*, short int>>* getPizzaPtr() {
		return pizza;
	}

	void modifyMultiplicator(Ingredient* ingr, short int s);
	Pizza* clone();
};

