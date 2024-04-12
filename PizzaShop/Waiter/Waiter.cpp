#include "Waiter.h"

size_t Waiter::handleUserChoice(DB* db) {
	displayOptions(db);

	size_t choice;
	std::cout << "Enter your choice: ";
	std::cin >> choice;

	if (choice == 0) {
		std::cout << "Custom pizza selected." << endl;
		overrideCustomPizza(db); // Override custom pizza object in DB
		return 0;
	}
	else if (choice >= 1 && choice <= db->pizzas.size()) {
		return choice;
	}
	else {
		std::cout << "Invalid choice." << endl;
		return SIZE_MAX; // Invalid choice, return SIZE_MAX
	}
}

void Waiter::displayOptions(DB* db) {
	std::cout << "Choose a pizza:" << std::endl;
	std::cout << "0. Custom Pizza" << std::endl;
	for (size_t i = 0; i < db->pizzas.size(); ++i) {
		if (db->pizzas[i] == nullptr) continue;
		std::cout << i << ". " << db->pizzas[i]->name << std::endl;
	}
}

void Waiter::customizePizza(Pizza* pizza) {
	bool modifyIngredients = true;
	while (modifyIngredients) {
		
		displayPizzaDetails(pizza);

		std::cout << "Do you want to modify ingredients? (yes/no): ";
		string choice;
		std::cin >> choice;

		if (choice == "yes") {
			// Modify ingredients
			modifyIngredients = modifyPizzaIngredients(pizza);
		}
		else {
			modifyIngredients = false;
		}
	}
}

void Waiter::displayPizzaDetails(Pizza* pizza) {
	float totalCost = 0.0f;

	std::cout << "Pizza Details:" << endl;
	std::cout << "Ingredients:" << endl;
	std::stack<std::pair<Ingredient*, short int>> tempStack{ pizza->getPizzaCpy() };
	while (!tempStack.empty()) {
		std::pair<Ingredient*, short int> ingredientPair = tempStack.top();
		Ingredient* ingredient = ingredientPair.first;
		short int index = ingredientPair.second;
		std::cout << "- " << ingredient->name << ": " <<
			ingredient->basePrice * ingredient->multipliers[index] << " (Portion: " << (
				(index == 0) ? "no" :
				(index == 1) ? "small" :
				(index == 2) ? "normal" :
				(index == 3) ? "large" :
				"NULL") << ')'
			<< endl;
		totalCost += ingredient->basePrice * ingredient->multipliers[index];
		tempStack.pop();
	}
	std::cout << "Total Price: " << totalCost << endl;
}

bool Waiter::modifyPizzaIngredients(Pizza* pizza) {

	std::cout << "Ingredients:" << endl;
	Ingredient** ingrs = new Ingredient * [pizza->getPizzaPtr()->size()];
	std::stack<std::pair<Ingredient*, short int>> tempStack{ pizza->getPizzaCpy() };
	size_t i = 0;
	while (!tempStack.empty()) {
		std::pair<Ingredient*, short int> ingredientPair = tempStack.top();
		Ingredient* ingredient = ingredientPair.first;
		ingrs[i] = ingredient;
		short int index = ingredientPair.second;
		std::cout << i + 1 << ". " << ingredient->name << ": " <<
			ingredient->basePrice * ingredient->multipliers[index] << " (Portion: " << (
				(index == 0) ? "no" :
				(index == 1) ? "small" :
				(index == 2) ? "normal" :
				(index == 3) ? "large" :
				"NULL") << ')' << std::endl;
		tempStack.pop();
		++i;
	}

	std::cout << "Which ingredient do you want to modify? (Enter ingredient number or 0 to exit): ";
	int ingredientIndex;
	std::cin >> ingredientIndex;

	// Validate ingredient index
	if (ingredientIndex < 0 || ingredientIndex > static_cast<int>(pizza->getPizzaPtr()->size())) {
		std::cout << "Invalid ingredient index." << std::endl;
		delete[] ingrs;
		return true;
	}
	else if (ingredientIndex == 0) {
		delete[] ingrs;
		return false; 
	}

	std::cout << "Enter new portion for the ingredient (0 for none, 1 for small, 2 for normal, 3 for large): ";
	short int newPortion;
	std::cin >> newPortion;

	if (newPortion < 0 || newPortion > 3) {
		std::cout << "Invalid portion." << std::endl;
		delete[] ingrs;
		return true;
	}

	// Modify ingredient portion
	pizza->modifyMultiplicator(ingrs[ingredientIndex], newPortion);
	std::cout << "Ingredient portion modified successfully." << endl;
	delete[] ingrs;
	return true;
}

void Waiter::overrideCustomPizza(DB* db)
{
	std::cout << "Creating custom pizza..." << endl;

	listIngredientsWithPrices(db);

	Pizza* customPizza = new Pizza();
	customPizza->name = "Custom Pizza";
	char addMore;
	do {
		size_t ingredientIndex;
		short int portion;
		std::cout << "Enter the index of the ingredient you want to add: ";
		std::cin >> ingredientIndex;
		std::cout << "Enter portion size for this ingredient (0 for none, 1 for small, 2 for normal, 3 for large): ";
		std::cin >> portion;

		if (ingredientIndex < db->ingredients.size() && portion >= 0 && portion <= 3) {
			customPizza->addIngredient(db->ingredients[ingredientIndex], portion);
		}
		else {
			std::cout << "Invalid input. Please try again." << endl;
		}

		std::cout << "Do you want to add more ingredients? (y/n): ";
		std::cin >> addMore;
	} while (addMore == 'y' || addMore == 'Y');

	std::cout << "Your custom pizza: " << endl;
	displayPizzaDetails(customPizza);
	char confirm;
	std::cout << "Confirm order? (y/n): ";
	std::cin >> confirm;

	if (confirm == 'y' || confirm == 'Y') {
		// Override custom pizza object in DB
		delete db->pizzas[0];
		db->pizzas[0] = customPizza;
		std::cout << "Custom pizza order confirmed." << endl;
	}
	else {
		delete customPizza;
		std::cout << "Custom pizza order discarded." << endl;
	}
}

void Waiter::listIngredientsWithPrices(DB* db)
{
	cout << "Available Ingredients:" << endl;
	for (size_t i = 0; i < db->ingredients.size(); ++i) {
		cout << i << ". " << db->ingredients[i]->name << " - Base Price: $" << db->ingredients[i]->basePrice << " per portion" << endl;
	}
}
