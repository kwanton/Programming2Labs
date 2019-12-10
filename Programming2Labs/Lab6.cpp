//Blake Blakeslee MW
//Lab6
//Takes in a list of names and heights and sorts them accordingly

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

//cadet structure (needs to be global to be used in function)
struct cadet{
	char lastName[15];
	char firstName[15];
	double height;
};

int main()
{
	//vars
	ifstream inputFile;
	char fileName[20];
	bool incorrectFile;
	cadet cadetList[10];
	
	//get file name from user and open inputfile
	do {
		incorrectFile = true;
		cout << "Please input the file name + extension: ";
		cin >> fileName;
		inputFile.open(fileName);
		if (inputFile) {
			cout << "That file exists\n";
			incorrectFile = false;
		} else {
			cout << "Silly billy, that file doesn't exist\n";
		}
	} while (incorrectFile);
	
	//read file and write to cadet list. close file.
	for (int i = 0; i < 10; i++) {
		inputFile >> cadetList[i].lastName;
		inputFile >> cadetList[i].firstName;
		inputFile >> cadetList[i].height;
	}
	inputFile.close();
	
	//output unordered list
	cout << endl << "The unordered list:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << cadetList[i].lastName << ", " << cadetList[i].firstName << 
				" - " << cadetList[i].height << endl;
	}
	cout << endl;
	
	//sort list by height, then last name, then first name
	int loops = 1;
	bool trigger = true;
	while (trigger == true && loops <= 10) {
		int i = 0;
		trigger = false;
		//three nested bubble sorts
		while (i < 9) {
			if (cadetList[i].height > cadetList[i + 1].height) {
				cadet temp;
				temp = cadetList[i];
				cadetList[i] = cadetList[i + 1];
				cadetList[i + 1] = temp;
				trigger = true;
			} else if (cadetList[i].height == cadetList[i + 1].height) {
				if (strcmp(cadetList[i].lastName, cadetList[i + 1].lastName) 
					> 0) {
					cadet temp;
					temp = cadetList[i];
					cadetList[i] = cadetList[i + 1];
					cadetList[i + 1] = temp;
					trigger = true;
				} else if (strcmp(cadetList[i].lastName, 
							cadetList[i + 1].lastName) == 0) {
					if (strcmp(cadetList[i].firstName, 
						cadetList[i + 1].firstName) > 0) {
						cadet temp;
						temp = cadetList[i];
						cadetList[i] = cadetList[i + 1];
						cadetList[i + 1] = temp;
						trigger = true;
					}
				}
			}
			//increment
			i++;
		}
		//increment
		loops++;
	}
	
	//output ordered list
	cout << endl << "The ordered list:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << cadetList[i].lastName << ", " << cadetList[i].firstName << 
				" - " << cadetList[i].height << endl;
	}
	cout << endl;
	cout << endl;
	return 0;
}
