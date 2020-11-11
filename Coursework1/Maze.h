/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This header defines a Maze */
#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;
class Maze {
private:
	int width;
	int height;
	int exitSize;
	Node** nodes;
	vector<Node> exits;
	bool found;
public:
	Maze() {
		width = 0;
		height = 0;
		exitSize = 0;
		nodes = new Node * [height];
		for (int i = 0; i < height; ++i)
			nodes[i] = new Node[width];
		found = false;
	}
	Maze(int width, int height, int exits) {
		this->width = width;
		this->height = height;
		exitSize = exits;
		nodes = new Node * [height];
		for (int i = 0; i < height; ++i)
			nodes[i] = new Node[width];
		found = false;
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
	bool isValid(Node n) const;
	bool isDestination(Node n, Node dest) const;
	stack<Node> makePath(Node start, Node dest);
	stack<Node> aStar(Node start, Node dest);
	void printMap() const;
	void writeFile(string name) const;
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
};

