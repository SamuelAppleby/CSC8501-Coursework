/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This header defines a Maze */
#pragma once
#include "Node.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>
using namespace std;
class Maze {
private:
	int width;
	int height;
	int players;
	Node** nodes;
	vector<Node> exits;
	vector<Player*> playerList;
public:
	Maze() {
		width = 0;
		height = 0;
		players = 0;
		nodes = new Node * [height];
		for (int i = 0; i < height; ++i)
			nodes[i] = new Node[width];
	}
	Maze(int width, int height, int players) {
		this->width = width;
		this->height = height;
		this->players = players;
		nodes = new Node * [height];
		for (int i = 0; i < height; ++i)
			nodes[i] = new Node[width];
	}
	~Maze() {
		for (int i = 0; i < height; ++i) {
			delete[] nodes[i];
		}
		delete[] nodes;
	}
	void createMap();
	void createMapFromFile(string fileName);
	void setNeighbours();
	void generateMaze();
	bool isInBounds(int row, int element) const;
	void generatePaths(int row, int element);
	void placePlayers(int players);
	bool isValid(Node n) const;
	bool isDestination(Node n, Node dest) const;
	stack<Node> makePath(Node start, Node dest);
	stack<Node> aStar(Node start, Node dest);
	void printMap() const;
	void writeFile(string name) const;
	int playGame(unordered_map<Player*, stack<Node>>, bool save, bool automatic, bool analyse);
	bool gameFinished() const;
	void displayResults();
	int getHeight() const {
		return height;
	}
	int getWidth() const {
		return width;
	}
	Node** getNodes() const {
		return nodes;
	}
	vector<Node> getExits() const {
		return exits;
	}
	vector<Player*> getPlayerList() const {
		return playerList;
	}
};

