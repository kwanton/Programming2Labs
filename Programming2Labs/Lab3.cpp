//Blake Blakeslee MW
//Lab3
//Uses Object Orientated programming to write out a date in different ways

#include <iostream>
#include <string>
using namespace std;

//Date Class
class Date {
	public:
		//constructor that sets month, day, and year variables
		Date (int x, int y, int z) {
			month = x;
			day = y;
			year = z;
		}
		//function that outputs the dates in three different methods
		void outputDates() {
			cout << monthNames[month-1] << " " << day << ", " << year << endl;
			cout << month << "/" << day << "/" << year << endl;
			cout << day << " " << monthNames[month-1]<< " " << year << endl;
		}
	private:
		//list of month names. Used to prevent countless if statements
		string monthNames[12] = {"January","Feburary","March","April","May",
								"June","July","August","September","October",
								"November","December"};
		int month, day, year;
};

int main()
{
	//variable setup
	int monthIn, dayIn, yearIn;
	bool canContinue = true;
	//Array that contains the info for how many days exist in each month
	int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	//ask user for current month and check if month exists
	do {
		cout << "Please give me the current month: ";
		cin >> monthIn;
		if (monthIn <=0 || monthIn > 12) {
			canContinue = false;
			cout << "this month is incorrect. Please try again.\n";
		} else {
			canContinue = true;
		}
	} while (!canContinue);
	
	//ask user for current day and check if day exists
	do {
		cout << "Please give me the current day in the month: ";
		cin >> dayIn;
		if (dayIn <=0 || dayIn > daysInMonth[monthIn-1]) {
			canContinue = false;
			cout << "this day is incorrect. Please try again.\n";
		} else {
			canContinue = true;
		}
	} while (!canContinue);
	
	//ask user for year and if year exists
	do {
		cout << "Please give me the current year: ";
		cin >> yearIn;
		if (yearIn <= 0) {
			canContinue = false;
			cout << "this year is incorrect. Please try again.\n";
		} else {
			canContinue = true;
		}
	} while (!canContinue);
	
	//create new date object
	Date dateObj(monthIn, dayIn, yearIn);
	//output dates from date class
	dateObj.outputDates();

	cout << endl;
	return 0;
}
