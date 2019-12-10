//Blake Blakeslee MW
//Lab1
//Read from an input file of stock info and runs a basic cash register for the user

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	//setup
	cout << setprecision(2) << fixed << showpoint;
	ifstream inputFile;
	ofstream outputFile;
	
	//variables
	int stockInput;
	bool foundItem;
	int i;
	int stockNumber;
	char description[12];
	double itemPrice;
	double subtotal;
	double total;
	
	//create an output file
	outputFile.open("Sales.txt");
	
	//ask for inputs until '0' is input
	do {
		foundItem = false;
		inputFile.open("Stock.txt");
		i = 0;
		cout << "Please input a stock number. '0' will total the transaction: ";
		cin >> stockInput;
		//searches input file for stock number
		while (stockInput != 0 && i < 9 && foundItem == false) {
			inputFile >> stockNumber;
			inputFile >> description;
			inputFile >> itemPrice;
			//if stock number is found, add item to both sales.txt and ending receit
			if (stockInput == stockNumber) {
				foundItem = true;
				cout << stockNumber << setw(12) << description << setw(13) <<
				itemPrice << endl;
				subtotal += itemPrice;
				outputFile << stockNumber << setw(12) << description <<
				setw(13) << itemPrice << endl;
			}
			i += 1;
		}
		//if item was not found
		if (!foundItem && stockInput != 0) {
			cout << "I didn't find the item you were looking for. Please try" <<
			" again.\n";
		}
		
		inputFile.close();
	} while (stockInput != 0);
	
	//output subtotal and total after 8% tax
	cout << "Subtotal: $" << subtotal << endl;
	total = subtotal * 1.08;
	cout << "Total: $" << total << endl;
	
	//create an amount owed
	double amountOwed = total;
	double amountGiven;
	
	//while the user owes more then 0 dollars
	while (amountOwed > 0) {
		cout << "How much cash is being tendered? ";
		cin >> amountGiven;
		if (amountGiven <= 0) {
			cout << "That's an incorrect value. Please try again.\n";
		} else {
			//subtract amount given and then check if user owes more
			amountOwed -= amountGiven;
			
			if (amountOwed > 0) {
				cout << "remaining Total: $" << amountOwed << endl;
			} else {
				cout << "Transaction complete!\n";
			}
		}
	}
	
	//output receit info to sales.txt
	outputFile << "Subtotal: $" << subtotal << endl;
	outputFile << "Total: $" << total << endl;
	outputFile << "Change: $" << abs(amountOwed) << endl;
	
	//output receit information
	cout << "Subtotal: $" << subtotal << endl;
	cout << "Total: $" << total << endl;
	if (amountOwed < 0) {
		cout << "Change: $" << abs(amountOwed) << endl;
	}
	
	//close sales.txt
	outputFile.close();
	cout << endl;
	return 0;
}
