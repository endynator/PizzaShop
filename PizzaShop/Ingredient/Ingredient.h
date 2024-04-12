#pragma once
#include <map>
#include <cassert>
#include <array>

/*enum s {
	No,
	Few,
	Normal,
	Extra
};*/

class Ingredient {
public:
	float basePrice = 0.0;
	std::array<float, 4> multipliers = {
		0.0f,
		0.4f,
		1.0f,
		1.5f
	};
public:
	std::string name;
	Ingredient() {}

	void setBasePrice(float baseP) {
		assert(basePrice == 0.0); // In case we were to try overwriting basePrice again
		basePrice = baseP;
	}
	// Leave first value 0.0f (optional)
	virtual void configMultipliers(std::array<float, 4> multipliers_) {
		multipliers = multipliers_;
	}
	virtual float price(int i /* from 0 to 3 */) {
		assert(i < 3 || i > 0);
		return basePrice * multipliers[i];
	}
};