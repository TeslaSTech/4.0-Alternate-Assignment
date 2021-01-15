#include "Functions.h"
#include <iostream>

int MovieFood::numberOfOrders = 999;
std::vector<double> MovieFood::prices{ 5.00, 2.25, 7.00, 6.75, 4.50 };

MovieFood::MovieFood() {

}

void MovieFood::chooseItems() {

	// S E T U P //
	std::vector<int> items(5, 0);
	std::vector<double> totals;
	double total = 0;
	bool exit = false;
	int numberChosen = 0;
	int index;
	char continuing = ' ';
	std::string userName;
	bool nameEnt = false;

	// E X E C U T I O N // 
	while (MovieFood::numberOfOrders <= 1000) {
		while (!exit) {
			if (!nameEnt) {
				total = 0;
				totals.assign(5, 0);
				items.assign(5, 0);
				printf("Hello there! You are customer %i for the day. What's your full name? \t", MovieFood::numberOfOrders);
				std::cin.clear();
				std::cin.ignore();
				std::getline(std::cin, userName);
				nameEnt = true;
			}
			printf("\n");
			index = MovieFood::ItemMenu(items); // Find the chosen item from the menu
			if (index == -1) {
				exit = true;
				break;
			}
			printf("Enter how many of this item you would like:\t");
			std::cin >> numberChosen;
			items[index] += numberChosen; // Log it into the vector
			totals = MovieFood::ListItemsAndOutputTotal(items);
			for (int i = 0; i < totals.size(); i++) {
				total += totals[i];
			}
			printf("Would you like to add more items? (y/n)\t");
			std::cin >> continuing;
			continuing = toupper(continuing);
			switch (continuing) {
			case 'Y':
				break;
			case 'N':
				printf("\n\n");
				MovieFood::paymentAndPreparation(items, total);
				exit = true;
				break;
			default:
				printf("Invalid entry, assuming that you would like to continue.\n");
				break;
			}
		}
		MovieFood::numberOfOrders++; // log that another customer has been served
		exit = false;
		nameEnt = false;
	}

	printf("Shutting down to rebuild resources...\n\n");

	// And we're all done here!

}

void MovieFood::paymentAndPreparation(std::vector<int> items, double total) {
	
	// S E T U P //
	int numberOfOrderedItems = 0;
	int numberToGo;
	std::vector<bool> hasItemBeenOrdered(items.size(), false);
	std::vector<bool> isItemPlural(items.size(), false);
	std::vector<std::string> singularItemNames{ "beverage", "candy", "hot dog", "popcorn", "pizza" };
	std::vector<std::string> pluralItemNames{ "beverages", "candies", "hot dogs", "popcorn", "pizza" };

	// E X E C U T I O N //
	for (int i = 0; i < hasItemBeenOrdered.size(); i++) {
		if (items[i] > 0) {
			hasItemBeenOrdered[i] = true;
			numberOfOrderedItems++;
			if (items[i] > 1)
				isItemPlural[i] = true;
		}
	}

	numberToGo = numberOfOrderedItems;

	printf("Please deposit $%.2f while I prepare your ", total);
	for (int i = 0; i < hasItemBeenOrdered.size(); i++) {
		if (hasItemBeenOrdered[i] && numberToGo > 1 && numberOfOrderedItems > 1) {
			if (isItemPlural[i]) {
				printf("%s, ", pluralItemNames[i].c_str());
			}
			else {
				printf("%s, ", singularItemNames[i].c_str());
			}
			numberToGo--;
		}
		else if (hasItemBeenOrdered[i] && numberToGo == 1 && numberOfOrderedItems > 1) {
			if (isItemPlural[i]) {
				printf("and %s. \n", pluralItemNames[i].c_str());
			}
			else {
				printf("and %s. \n", singularItemNames[i].c_str());
			}
			numberToGo--;
		}
		else if (hasItemBeenOrdered[i] && numberToGo == 1 && numberOfOrderedItems == 1) {
			if (isItemPlural[i]) {
				printf("%s. \n", pluralItemNames[i].c_str());
			}
			else {
				printf("%s. \n", singularItemNames[i].c_str());
			}
			numberToGo--;
		}
		if (numberToGo == 0)
			break;
	}

	printf("\n\n");
}

int MovieFood::ItemMenu(std::vector<int> items) {
	
	// S E T U P //
	char answerChoice = ' ';
	int index = 0;
	bool validAnswer = false;
	std::string adminpassword;

	// E X E C U T I O N //
	while (!validAnswer) {
		printf("a. (B)everage\t$5.00\nb. (C)andy\t$2.25\nc. (H)ot Dog\t$7.00\nd. (P)opcorn\t$6.75\ne. P(i)zza\t$4.50\nPlease enter the letter in parentheses for the item you would like:\t");
		std::cin >> answerChoice;
		answerChoice = toupper(answerChoice);
		switch (answerChoice) {
		case 'B':
			index = 0;
			validAnswer = true;
			break;
		case 'C':
			index = 1;
			validAnswer = true;
			break;
		case 'H':
			index = 2;
			validAnswer = true;
			break;
		case 'P':
			index = 3;
			validAnswer = true;
			break;
		case 'I':
			index = 4;
			validAnswer = true;
			break;
		case 'Q':
			printf("Enter admin password:\t");
			std::cin >> adminpassword;
			if (adminpassword == "ShutMeDown!") {
				printf("Shutting down...\n");
				exit(0);
			} else
				break;
		default:
			char choice;
			printf("That is not a proper menu choice. I'll assume that you are not hungry. \nWould you like to try again, or would you like to let the next patron order? (y/n)\t");
			std::cin >> choice;
			choice = toupper(choice);
			switch (choice) {
			case 'Y':
				break;
			case 'N':
				printf("Okay. Thank you! \n");
				return -1;
			default:
				printf("Assuming you'd like to let the next patron order.\n");
				return -1;
			}
		}
	}
	return index; // Return the answer choice (letter converted into the correct std::vector<int> index)
}

std::vector<double> MovieFood::ListItemsAndOutputTotal(std::vector<int> items) {
	// Time to print the chart of items ordered so far!

			/*
			* Item			Quantity   Total
			* -------------------------------
			* Beverage		X          $XX.XX
			* Candy			X          $XX.XX
			* Hot Dog		X          $XX.XX
			* Popcorn		X          $XX.XX
			* Pizza			X          $XX.XX
			* -------------------------------
			* Total:                   $X.XX
			*/
	
	// S E T U P //
	std::vector<double> totals(5, 0);
	double total = 0;

	// P R E - E X E C U T I O N //
	for (int i = 0; i < MovieFood::prices.size(); i++) {
		totals[i] = items[i] * MovieFood::prices[i]; // Calculating totals so far
	}
	for (int i = 0; i < totals.size(); i++) {
		total += totals[i];
	}

	// E X E C U T I O N //
	printf("Here is your list of ordered items: \n\n");
	printf("\
%-20s %-20s %-20s\n\
%-20s %-20i $%-.2f\n\
%-20s %-20i $%-.2f\n\
%-20s %-20i $%-.2f\n\
%-20s %-20i $%-.2f\n\
%-20s %-20i $%-.2f\n\
%-35s       $%-.2f\n\n",
"Item", "Quantity", "Total",
"Beverage", items[0], totals[0],
"Candy", items[1], totals[1],
"Hot Dog", items[2], totals[2],
"Popcorn", items[3], totals[3],
"Pizza", items[4], totals[4],
"Total", total);

	// one last thing to do... //
	return totals;
	// And that's a wrap! // 
}