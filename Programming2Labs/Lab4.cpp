//Blake Blakeslee MW
//Lab4
//Pig truffle game

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

//Prototypes
void printBoard(int [][10], bool);
bool checkForStuck(int, int, int[][10]);
string locateTruffle(int, int, int, int);
void calculateDirection(int, int*, int*);

int main()
{
	//Map: 1 = current location, 2 = visited location, 3 = truffle Location
	//[x][y]
	int map[10][10];
	
	//fixes a bug with comparing null values
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = 0;
		}
	}
	
	int locationX;
	int locationY;
	int directionNum;
	int directionX;
	int directionY;
	int truffleX;
	int truffleY;
	
	//system time and seed rand function
	unsigned seed = time(0);
	srand(seed);
	
	
	//Rules
	cout << "Whuh oh, looks like the litte piggy here is a lost and hungry " <<
			"in the woods.\nLooks like it's up to you to help him out.\n";
	cout << "His sense of smell is great, but his sense of direction is not.\n"<<
			"Won't you help him find where he needs to go?\n";
	cout << "The pig knows where the truffle is, but you have to guide him.\n"<<
			"Use the numberpad to input your directions for the piggy.\n";
	cout << "You can move in all eight directions.\n";
	
	//Get starting location
	do {
		cout << "\nThe game takes place on a 10x10 grid.\n";
		cout << "Please input the starting 'x' location: ";
		cin >> locationX;
		//input validation
		if (locationX < 1 || locationX > 10) {
			cout << "That input appears to be outside the range. Try again.\n";
		}
	} while (locationX < 1 || locationX > 10);
	do {
		cout << "\nPlease input the starting 'y' location: ";
		cin >> locationY;
		//input validation
		if (locationY < 1 || locationY > 10) {
			cout << "That input appears to be outside the range. Try again.\n";
		}
	} while (locationY < 1 || locationY > 10);
	
	map[locationX-1][locationY-1] = 1;
	
	//Generate truffle location - "(rand() % (1 - 10 + 1)) + 1" for RNG
	do {
		truffleX = (rand() % (1 - 10 + 1)) + 1;
	} while (truffleX == locationX);
	do {
		truffleY = (rand() % (1 - 10 + 1)) + 1;
	} while (truffleY == locationY);
	map[truffleX - 1][truffleY - 1] = 3;
	
	//rules
	cout << "\nAlright! Let's begin!\n";
	cout << "The 'P' represents the piggy and 'X's on the board are " <<
			"places you been.\nYou cannot return to places you've been or " <<
			"the simply minded pig will get lost.";
	
	//pre-setup variables
	bool gameOver = false;
	bool win = false;
	bool softLock = false;
	
	//Open the game!
	for (int i = 0; i < 10; i++) {
		cout << endl;
		//call print board function
		printBoard(map, false);
		
		//call function that determines truffle location
		cout << "The truffle is located roughly to the " << 
				locateTruffle(locationX,locationY, truffleX, truffleY) << 
				endl;
		
		//direction help
		cout << "8 = N\n6 = E\n2 = S\n4 = W\n7 = NW" << 
				"\n9 = NE\n3 = SE\n1 = SW\n";
		cout << "Please input a direction: ";
		cin >> directionNum;
		if (directionNum > 0 && directionNum < 10 && directionNum != 5) {
			calculateDirection(directionNum, &directionX, &directionY);
			
			//check for edge of map
			if (locationX + directionX > 0 && locationX + directionX <= 10){
				if (locationY + directionY > 0 && 
					locationY + directionY <= 10){
					if (map[locationX + directionX-1][locationY + directionY-1]
						== 2) {
							cout << "The pig got lost in circles. " <<
									"-Turn Wasted-\n";
					} else
					if (map[locationX + directionX-1][locationY + directionY-1]
						== 3) {
							//found truffle. winner.
							cout << "You found the truffle!\n";
							gameOver = true;
							win = true;
					} else {
						map[locationX-1][locationY-1] = 2;
						locationX += directionX;
						locationY += directionY;
						map[locationX-1][locationY-1] = 1;
					}
				} else {
					//tries to leave map
					cout << "The pig tried leaving the grove, but fell " <<
						"into a river. -Turn Wasted-\n";
				}
			} else {
				//tries to leave map... again.
				cout << "The pig tried leaving the grove, but fell into " <<
						"a river. -Turn Wasted-\n";
			}
		} else if (directionNum == 5) {
			//easter egg if you press '5' (5 would be stand still on a numpad)
			cout << "You told the pig to stand in place and do nothing.\n";
			cout << "He was happy to comply. -Turn Wasted-\n";
		} else {
			//user input not understood
			cout << "The pig didn't understand you and ate a rock. ";
			cout << "-Turn Wasted-\n";
		}
		
		//prevents softlock
		if (checkForStuck(locationX, locationY, map)){
			gameOver = true;
			softLock =true;
		}
		
		//slap in a sentinal
		if (gameOver) {
			i = 10000;
		}
	}
	
	//output text depending on how the game ended.
	if (win) {
		cout << "Victory is yours and the pig will not become dinner... today.";
		cout << "\nYou win!";
	} else if (softLock){
		cout << "Incredible! You soft locked the game, and got somewhere\n";
		cout << "that you can't move from! This is truly the greatest of\n";
		cout << "failures.\n";
		cout << "You lose.";
	} else {
		cout << "Somehow, your incompetence left the pig to suffer a slow\n"
				"demise to the effects of starvation. \nYou lose.";
	}
	
	//output the map with the location of the truffle
	cout << endl;
	printBoard(map,true);
	
	cout << endl;
	return 0;
}

//easily callable function for printing the current board
void printBoard(int map[][10],bool showTruffle) {
	cout << "---------------\n\n";
	
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (map[x][y] == 1) {
				cout << "P";
			} else if (map[x][y] == 2) {
				cout << "X";
			} else if (map[x][y] == 3 && showTruffle) {
				cout << "T";
			} else {
				cout << ".";
			}
		}
		cout << endl;
	}
}

//checks if the player is in a location they cant move from
bool checkForStuck(int locationX, int locationY, int map[][10]) {
	int stuckNum = 9;
	bool helpImStuck = false;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (locationX-1+i < 0 || locationX-1+i > 9 ||
				locationY-1+j < 0 || locationY-1+j > 9 ||
				map[locationX-1+i][locationY-1+j] == 2 ||
				map[locationX-1+i][locationY-1+j] == 1) {
				stuckNum -= 1;
			}
		}
	}
	if (stuckNum <= 0){
		helpImStuck = true;
	}
	return helpImStuck;
}

//string function that returns the direction the truffle is in
string locateTruffle(int locationX, int locationY, int truffleX,
					int truffleY) {
	string compass;
	if (locationY > truffleY) {
		compass += "North";
	} else if (locationY < truffleY) {
		compass += "South";
	}
	if (locationX > truffleX) {
		compass += "West";
	} else if (locationX < truffleX) {
		compass += "East";
	}
	return compass;
}

//takes in the numpad input from user and converts to an x and y direction for use
void calculateDirection(int directionNum, int *directionX, int *directionY){
	if (directionNum >= 7 && directionNum <= 9){
				*directionY = -1;
				if (directionNum == 7){
					*directionX = -1;
				} else if (directionNum == 9){
					*directionX = 1;
				} else {
					*directionX = 0;
				}
			} else if (directionNum >= 1 && directionNum <= 3) {
				*directionY = 1;
				if (directionNum == 1) {
					*directionX = -1;
				} else if (directionNum == 3) {
					*directionX = 1;
				} else {
					*directionX = 0;
				}
			} else {
				*directionY = 0;
			}
			if (directionNum == 4){
				*directionX = -1;
			} else if (directionNum == 6) {
				*directionX = 1;
			}
}
