#include "DB.h"

constexpr size_t bufferSize = 65536;

void DB::importIngredients(const string& filename) {
    FILE* file;
    if (fopen_s(&file, filename.c_str(), "rb") != 0) {
        cerr << "Error: Unable to open file " << filename << " for reading." << endl;
        exit(1);
    }

    char* readBuffer = allocateBuffer();
    readJSON(file, readBuffer, filename);
    parseIngredientsJSON(readBuffer, filename);
    isIngrImported = true;
    delete[] readBuffer;
}

void DB::importPizzas(const string& filename) {
    assert(isIngrImported && "Use of importPizzas() before importIngredients()");
    FILE* file;
    if (fopen_s(&file, filename.c_str(), "rb") != 0) {
        cerr << "Error: Unable to open file " << filename << " for reading." << endl;
        exit(1);
    }

    char* readBuffer = allocateBuffer();
    readJSON(file, readBuffer, filename);
    parsePizzasJSON(readBuffer, filename);
    delete[] readBuffer;
}

char* DB::allocateBuffer() {
    return new char[bufferSize];
}

void DB::readJSON(FILE* file, char* readBuffer, const string& filename) {
    FileReadStream is(file, readBuffer, bufferSize);
    Document doc;
    doc.ParseStream(is);
    fclose(file);

    if (doc.HasParseError()) {
        cerr << "Error: Parse error in " << filename << " at position " << doc.GetErrorOffset() << ": " << GetParseError_En(doc.GetParseError()) << endl;
        exit(1);
    }
}

void DB::parseIngredientsJSON(char* readBuffer, const string& filename) {
    Document doc;
    doc.Parse(readBuffer);

    const Value& ingredients = doc["ingredients"];
    for (SizeType i = 0; i < ingredients.Size(); i++) {
        const Value& ingredient = ingredients[i];
        string name = ingredient["name"].GetString();
        float basePrice = ingredient["basePrice"].GetFloat();
        array<float, 4> multipliers{};
        const Value& multipliersArr = ingredient["multipliers"];
        for (SizeType j = 0; j < multipliersArr.Size(); j++) {
            multipliers[j] = multipliersArr[j].GetFloat();
        }
        Ingredient* ing = ingredientBuilder.build(name, basePrice, multipliers);
        this->ingredients.push_back(ing);
    }
}

void DB::parsePizzasJSON(char* readBuffer, const string& filename) {
    Document doc;
    doc.Parse(readBuffer);

    const Value& pizzas = doc["pizzas"];
    for (SizeType i = 0; i < pizzas.Size(); i++) {
        const Value& pizzaObj = pizzas[i];
        string pizzaName = pizzaObj["name"].GetString();
        Pizza* pizza = new Pizza{};
        pizza->name = pizzaName;
        const Value& ingredientsArray = pizzaObj["ingredients"];
        for (SizeType j = 0; j < ingredientsArray.Size(); j++) {
            string ingredientName = ingredientsArray[j].GetString();
            Ingredient* ingredient = nullptr;
            for (auto ing : this->ingredients) {
                if (ing->name == ingredientName) {
                    ingredient = ing;
                    break;
                }
            }
            pizza->addIngredient(ingredient, 2);
        }
        this->pizzas.push_back(pizza);
    }
}

