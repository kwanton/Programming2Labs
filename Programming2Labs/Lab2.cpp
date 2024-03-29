//Blake Blakeslee MW
//Lab2
//Calculates volume of three different snowmen and their three snowballs.

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

//Prototypes
void displayInstructions(string);
void computeVolumes(double, double, double);
void displayResults();

//Program wide variables
double const PI = 3.14159;
int snowmanCount;
double radii1;
double radii2;
double radii3;
double daddyVol;
double mommyVol;
double babyVol;
double familyVol;

int main()
{
	//do three times for each snowman in snowman family. Pass snowman name into function
	for (snowmanCount = 0; snowmanCount < 3; snowmanCount++){
		if (snowmanCount == 0) {
			displayInstructions("daddy");
		} else if (snowmanCount == 1) {
			displayInstructions("mommy");
		} else {
			displayInstructions("baby");
		}
	}
	
	
	displayResults();
	
	cout << endl;
	return 0;
}

//Asks the user for the radii of three different snowman. The snowman being calulcated for is passed into function
void displayInstructions(string whichSnowman) {
	cout << "Please give the first radius for " << whichSnowman
	<< " snowman: ";
	cin >> radii1;
	cout << "Please give the second radius for " << whichSnowman
	<< " snowman: ";
	cin >> radii2;
	cout << "Please give the third radius for " << whichSnowman
	<< " snowman: ";
	cin >> radii3;
	
	computeVolumes(radii1, radii2, radii3);
}

//takes in three radii and calculates the volume the the snowmen.
void computeVolumes(double num1, double num2, double num3) {
	if (snowmanCount == 0) {
		daddyVol = ((4./3.)*PI*pow(num1, 3)) + ((4./3.)*PI*pow(num2, 3)) 
		+ ((4./3.)*PI*pow(num3, 3));
	} else if (snowmanCount == 1) {
		mommyVol = (4./3.)*PI*pow(num1, 3) + (4./3.)*PI*pow(num2, 3) 
		+ (4./3.)*PI*pow(radii3, 3);
	} else {
		babyVol = (4./3.)*PI*pow(num1, 3) + (4./3.)*PI*pow(num2, 3) 
		+ (4./3.)*PI*pow(num3, 3);
	}
}

//Outputs all results for user to read
void displayResults() {
	familyVol = daddyVol + mommyVol + babyVol;
	cout << "Daddy snowman's total volume is " << daddyVol << ".\n";
	cout << "Mommy snowman's total volume is " << mommyVol << ".\n";
	cout << "Baby snowman's total volume is " << babyVol << ".\n";
	cout << "The family's total volume is " << familyVol << ".\n";
}
