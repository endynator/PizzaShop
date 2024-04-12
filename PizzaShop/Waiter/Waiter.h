#pragma once
#include <iostream>
#include <string>
#include "../DB/DB.h"
#include "../Pizza/PizzaFactory.h"
#include "../Pizza/PizzaCalculator.h"

class Waiter {
public:
	void displayOptions(DB* db);

	void customizePizza(Pizza* pizza);

	size_t handleUserChoice(DB* db);

	void displayPizzaDetails(Pizza* pizza);

	Waiter(DB* db) : pizzaFactory(db) {}

private:
	PizzaFactory pizzaFactory;

	bool modifyPizzaIngredients(Pizza* pizza);

	void overrideCustomPizza(DB* db);

	void listIngredientsWithPrices(DB* db);
};

