/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This file allows the user to generate and test Mazes */
#include <iostream>
#include "Maze.h"
#include <time.h>
#include <limits>
#include <string>
using namespace std;
int width;
int height;
int exits;
char answer;
void setUp();
void createOrLoad();
void viewMap(Maze* maze);
void shortestPath(Maze* maze);
void userInput();
int main() {
	srand(time(NULL));
	setUp();
	return 0;
}

void setUp() {
	width = 0, height = 0, exits = 0;
	createOrLoad();
	cout << "Would you like to play again (Y/N)?: ";
	userInput();
	if (answer == 'y')
		setUp();
}

void createOrLoad() {
	cout << "Welcome to the Maze Game!" << endl << "Would you like to: " << endl <<
		"1) Create a new map" << endl << "2) Load a new map" << endl << "Answer: ";
	cin >> answer;
	answer = tolower(answer);
	while (cin.fail() || answer != '1' && answer != '2') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Incorrect input, choose from options above: ";
		cin >> answer;
		answer = tolower(answer);
	}
	if (answer == '1') {
		cout << "-- WELCOME TO MAZE CREATION --" << endl
			<< "Enter width (minimum is 5 and must be odd): ";
		cin >> width;
		while (width < 5 || width % 2 == 0 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter width (minimum is 5 and must be odd): ";
			cin >> width;
		}
		cout << "Enter height (Minimum is 5 and must be odd): ";
		cin >> height;
		while (height < 5 || height % 2 == 0 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter height (minimum is 5 and must be odd): ";
			cin >> height;
		}
		cout << "How many exits (minimum is 1)? : ";
		cin >> exits;
		while (exits < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter number of exits (minimum is 1): ";
			cin >> exits;
		}
		Maze* maze = new Maze(width, height, exits);
		maze->createMap();
		viewMap(maze);
		cout << "Would you like to save this map (Y/N): ";
		userInput();
		if (answer == 'y') {
			string name;
			cout << "What would you like to call it?: ";
			cin.ignore();
			getline(cin, name);
			maze->writeFile(name);
		}
		shortestPath(maze);
		delete maze;
	}
	if (answer == '2') {
		string fileName;
		ifstream myfile;
		cin.ignore();
		while (!myfile.is_open()) {
			cout << "File name (file type unrequired): ";
			getline(cin, fileName);
			fileName.insert(0, "Maps/");
			fileName.append(".txt");
			myfile.open(fileName);
			if (!myfile.is_open())
				cout << "ERROR FINDING FILE" << endl;
		}
		string line;
		while (getline(myfile, line)) {
			if (height == 0)
				width = line.length();
			for (char& c : line)
				if (c == 'E')
					exits++;
			height++;
		}
		Maze* maze = new Maze(width, height, exits);
		maze->createMapFromFile(fileName);
		viewMap(maze);
		myfile.close();
		shortestPath(maze);
		delete maze;
	}
}

void viewMap(Maze* maze) {
	cout << "Map Loaded, would you like to print it (Y/N)?: ";
	userInput();
	if (answer == 'y')
		maze->printMap();
}

void shortestPath(Maze* maze) {
	cout << "Calculate Shortest Path (Y/N)? : ";
	userInput();
	if (answer == 'y') {
		Node dest = maze->getNodes()[height / 2][width / 2];
		for (auto& start : maze->getExits())
			stack<Node> path = maze->aStar(start, dest);
		maze->printMap();
	}
}

/* For yes or no questions only */
void userInput() {
	cin >> answer;
	answer = tolower(answer);
	while (cin.fail() || answer != 'y' && answer != 'n') {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Incorrect input, choose from options above: ";
		cin >> answer;
		answer = tolower(answer);
	}
}


