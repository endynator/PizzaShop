#pragma once
#include "Pizza.h"
#include "../DB/DB.h"

class PizzaFactory
{
private:
	DB* const db = nullptr;
public:
	PizzaFactory(DB* db_) :
		db{ db_ }
	{}

	Pizza* createPizza(size_t id) {
		if (id >= db->pizzas.size()) {
			return nullptr;
		}
		return db->pizzas[id]->clone();
	}
};

