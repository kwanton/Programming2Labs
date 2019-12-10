//Blake Blakeslee MW
//Lab5
//Recreation of lab 1 using array of structures.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	//Set decimal precision to 2 and define input and output files
	cout << setprecision(2) << fixed << showpoint;
	ifstream inputFile;
	ofstream outputFile;
	
	//item list structure	
	struct itemList {
		int stockNumber;
		string  description;
		double price;
	};
	
	//variables
	int stockInput;
	bool foundItem;
	int i;
	double subtotal;
	double total;
	double tax;
	
	itemList items[9];
	
	//read input file and assign array 
	inputFile.open("Stock.txt");
	for (int i = 0; i < 9; i++) {
		inputFile >> items[i].stockNumber;
		inputFile >> items[i].description;
		inputFile >> items[i].price;
	}
	
	inputFile.close();
	
	//bubble sort for funsies
	int loops = 1;
	bool Switch = true;
	while (Switch == true && loops < 9) {
		int i = 0;
		itemList temp;
		Switch = false;
		while (i < 9-1) {
			if (items[i].stockNumber > items[i+1].stockNumber) {
				temp = items[i];
				items[i] = items[i+1];
				items[i+1] = temp;
				Switch = true;
			}
			i++;
		}
		loops++;
	}
	
	//print the list
	for (int i = 0; i < 9; i++) {
		cout << items[i].stockNumber << setw(13);
		cout << items[i].description << setw(13);
		cout << items[i].price << endl;
	}
	cout << endl;
	
	//Create and overwrite new output file
	outputFile.open("Sales.txt");
	do {
		//ask for stock input number
		foundItem = false;
		i = 0;
		cout << "Please input a stock number. '0' will total the transaction: ";
		cin >> stockInput;
		//searches input file for stock number
		while (stockInput != 0 && i < 9 && foundItem == false) {
			//If stock number exists
			if (stockInput == items[i].stockNumber) {
				foundItem = true;
				cout << items[i].stockNumber << setw(12) << 
				items[i].description << setw(13) << items[i].price << endl;
				//ask for item quantity
				int quantity;
				cout << "How many of this item do they want? ";
				cin >> quantity;
				//Repeat step for each in quantity
				for (int j = 0; j < quantity; j++) {
					subtotal += items[i].price;
					outputFile << items[i].stockNumber << setw(12) << 
					items[i].description << setw(13) << items[i].price <<
					setprecision(2) << fixed << showpoint << endl;
				}
			}
			//increment i
			i += 1;
		}
		//item not found and user wasn't escaping
		if (!foundItem && stockInput != 0) {
			cout << "I didn't find the item you were looking for. Please try" <<
			" again.\n";
		}
		inputFile.close();
		//when sentinal is input, escape from loop
	} while (stockInput != 0);
	
	//output subtotal and total after 8% tax
	cout << "Subtotal: $" << subtotal << endl;
	tax = subtotal * 0.08;
	cout << "Tax: $" << tax << endl;
	total = subtotal + tax;
	cout << "Total: $" << total << endl;
	double amountOwed = total;
	double amountGiven;
	
	//do while the user still owes money
	while (amountOwed > 0) {
		cout << "How much cash is being tendered? ";
		cin >> amountGiven;
		if (amountGiven <= 0) {
			cout << "That's an incorrect value. Please try again.\n";
		} else {
			amountOwed -= amountGiven;
			if (amountOwed > 0) {
				cout << "remaining Total: $" << amountOwed << endl;
			} else {
				cout << "Transaction complete!\n";
			}
		}
	}
	
	//save tender information to output file with decimal precision of 2
	outputFile << "Subtotal: $" << subtotal << setprecision(2) << fixed << 
	showpoint << endl;
	outputFile << "Tax: $" << tax << setprecision(2) << fixed << 
	showpoint << endl;
	outputFile << "Total: $" << total << setprecision(2) << fixed << 
	showpoint << endl;
	outputFile << "Change: $" << abs(amountOwed) << setprecision(2) << fixed << 
	showpoint << endl;
	
	//output tender information
	cout << "Subtotal: $" << subtotal << endl;
	cout << "Tax: $" << tax << endl;
	cout << "Total: $" << total << endl;
	//only output change if there is change
	if (amountOwed < 0) {
		cout << "Change: $" << abs(amountOwed) << endl;
	}
	
	outputFile.close();
	cout << endl;
	return 0;
}
