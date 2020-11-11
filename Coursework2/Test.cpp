/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This file allows the user to generate and test Mazes */
#include <iostream>
#include "Maze.h"
#include "Player.h"
#include <time.h>
#include <limits>
#include <string>
#include <unordered_map> 
using namespace std;
int width;
int height;
int players;
bool analyse;
int fullyPassed;
int partiallyPassed;
int notPassed;
char answer;
void setUp();
void createOrLoad();
void viewMap(Maze* maze);
void initialiseGame(Maze* maze);
void userInput();
int main() {
	srand(time(NULL));
	setUp();
	return 0;
}

void setUp() {
	width = 0, height = 0, players = 0, fullyPassed = 0, partiallyPassed = 0, notPassed = 0;
	createOrLoad();
	cout << "Would you like to play again (Y/N)?: ";
	userInput();
	if (answer == 'y')
		setUp();
}

void createOrLoad() {
	cout << "Welcome to the Maze Game!" << endl << "Would you like to: " << endl << "1) Create a new map" << endl
		<< "2) Load a new map/Load previously saved map" << endl << "3) Maze Analysis" << endl << "Answer: ";
	cin >> answer;
	answer = tolower(answer);
	while (cin.fail() || answer != '1' && answer != '2' && answer != '3') {
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
		cout << "Enter height (minimum is 5 and must be odd): ";
		cin >> height;
		while (height < 5 || height % 2 == 0 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter height (minimum is 5 and must be odd): ";
			cin >> height;
		}
		cout << "How many players are there (minimum is 1)? : ";
		cin >> players;
		while (players < 1 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter number of players (minimum is 1): ";
			cin >> players;
		}
		Maze* maze = new Maze(width, height, players);
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
		initialiseGame(maze);
		delete maze;
	}
	else if (answer == '2') {
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
					players++;
			height++;
		}
		Maze* maze = new Maze(width, height, players);
		maze->createMapFromFile(fileName);
		viewMap(maze);
		myfile.close();
		initialiseGame(maze);
		delete maze;
	}
	else if (answer == '3') {
		analyse = true;
		cout << "-- Maze Analysis --" << endl << "Enter upper limit for maze width (min is 5, max is 101, must be odd): ";
		cin >> width;
		while (width < 5 || width % 2 == 0 || width > 101 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter width (min is 5, max is 101, must be odd): ";
			cin >> width;
		}
		cout << "Enter upper limit for maze height (min is 5, max is 101, must be odd): ";
		cin >> height;
		while (height < 5 || height % 2 == 0 || height > 101 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter height (min is 5, max is 50, must be odd): ";
			cin >> height;
		}
		cout << "Enter upper limit for players (min 1, max 5)? : ";
		cin >> players;
		while (players < 1 || players > 5 || cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Bad value, enter number of players (min 1, max 5): ";
			cin >> players;
		}
		int maxWidth = width;
		int maxHeight = height;
		int maxPlayers = players;
		int totalTests = 0;
		/* Generate 100 random mazes for all maze size and player number combinations */
		for (int i = maxWidth; i >= 5; i -= 2) {
			height = maxHeight;
			for (int j = maxHeight; j >= 5; j -= 2) {
				players = maxPlayers;
				for (int k = maxPlayers; k >= 1; k--) {
					cout << "---- Testing ----" << endl << "Players: " << players << ", Width: " << width << ", Height: " << height << endl;
					for (int l = 1; l <= 100; ++l) {
						Maze* maze = new Maze(width, height, players);
						maze->createMap();
						initialiseGame(maze);
						delete maze;
						totalTests++;
						cout << "Test: " << l << " complete" << endl;
					}
					players--;
				}
				height -= 2;
			}
			width -= 2;
		}
		cout << "---- Testing Complete ----" << endl << "Total tests: " << totalTests << endl << "Tests fully passed: " <<
			fullyPassed << endl << "Tests partially passed: " << partiallyPassed << endl << "Tests not passed: " << notPassed << endl;
	}
}

void viewMap(Maze* maze) {
	cout << "Map Loaded, would you like to print it (Y/N)?: ";
	userInput();
	if (answer == 'y')
		maze->printMap();
}

void initialiseGame(Maze* maze) {
	bool save = false, automatic = false;
	if (!analyse) {
		cout << "Play Game (Y/N)?: ";
		userInput();
		if (answer == 'y') {
			cout << "Would you like to save player progression to a file (Y/N)?: ";
			userInput();
			if (answer == 'y')
				save = true;
			cout << "Assigning Players... " << endl;
			maze->placePlayers(players);
			maze->printMap();
			cout << "Would you like to:" << endl << "1) View each turn individually" << endl 
				<< "2) Skip until the end (you will only see results)?" << endl << "Answer: ";
			cin >> answer;
			answer = tolower(answer);
			while (cin.fail() || answer != '1' && answer != '2') {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Incorrect input, choose from options above: ";
				cin >> answer;
				answer = tolower(answer);
			}
			if (answer == '2')
				automatic = true;
		}
		else
			return;
	}
	else {
		automatic = true;
		maze->placePlayers(players);
	}
	Node dest = maze->getNodes()[height / 2][width / 2];
	vector<stack<Node>> routes;
	unordered_map<Player*, stack<Node>> allRoutes;
	for (auto& start : maze->getExits()) {
		stack<Node> path = maze->aStar(start, dest);
		if (path.size() != 0) {
			while (path.top().getValue() != ' ')
				path.pop();		// Start path from empty node
			routes.push_back(path);
		}
		else
			routes.push_back(path);		// Empty path put onto stack
	}
	for (int i = 0; i < maze->getPlayerList().size(); i++)
		allRoutes.insert(pair<Player*, stack<Node>>(maze->getPlayerList().at(i), routes.at(i)));
	int result = maze->playGame(allRoutes, save, automatic, analyse);
	switch (result) {
	case 0: fullyPassed++;  break;
	case 1:  partiallyPassed++; break;
	case 2: notPassed++; break;
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
