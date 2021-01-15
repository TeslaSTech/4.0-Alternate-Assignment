#pragma once

#include <iomanip>
#include <string>
#include <vector>

class MovieFood {

	

public: 
	// Constructor
	MovieFood();
	// Variables and functions
	static void chooseItems();
	static void paymentAndPreparation(std::vector<int> items, double total);
	static int ItemMenu(std::vector<int> items);
	static std::vector<double> ListItemsAndOutputTotal(std::vector<int> items);
	static int numberOfOrders;
private:
	static std::vector<double> prices;
};