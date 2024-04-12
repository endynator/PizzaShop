#pragma once
#include "../Ingredient/IngredientBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/error/en.h"

using namespace rapidjson;
using namespace std;

class DB
{
private:
	IngredientBuilder ingredientBuilder;
	bool isIngrImported = false;
public:
	vector<Pizza*> pizzas = { nullptr }; 
	// Initialise 1st object as our "custom" option
	
	vector<Ingredient*> ingredients;

	DB() {}

	void importIngredients(const string& filename);

	void importPizzas(const string& filename);
private:
	char* allocateBuffer();
	void readJSON(FILE* file, char* readBuffer, const string& filename);

	void parseIngredientsJSON(char* readBuffer, const string& filename);
	void parsePizzasJSON(char* readBuffer, const string& filename);
};

