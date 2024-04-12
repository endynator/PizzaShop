#pragma once
#include "../Pizza/Pizza.h"

class IngredientBuilder {
private:
	Ingredient* ingredient = nullptr;
public:
	Ingredient* build(const std::string& name, float basePrice, std::array<float, 4> multipliers) {
		ingredient = new Ingredient{};
		ingredient->name = name;
		ingredient->setBasePrice(basePrice);
		ingredient->configMultipliers(multipliers);
		return ingredient;
	}
};

