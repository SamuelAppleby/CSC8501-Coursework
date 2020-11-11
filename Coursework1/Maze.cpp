/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This contains Maze implmentation,
 AStar adapted from: https://github.coventry.ac.uk/jansonsa/D1/blob/master/pokemonGUI/pokemonGUI/Cordinate.h
 Maze generation adapted from: https://www.cefns.nau.edu/~pek7/CS200/Project%209.pdf */
#include "Maze.h"
void Maze::createMap() {
	/* Default all to 'X' */
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Node node;
			node.setValue('X');
			node.setRow(i);
			node.setElement(j);
			nodes[i][j] = node;
		}
	}
	generateMaze();
}

void Maze::createMapFromFile(string fileName) {
	ifstream myfile(fileName);
	string line;
	int currentRow = 0;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			int currentElement = 0;
			for (char& c : line) {
				Node node;
				node.setValue(c);
				node.setRow(currentRow);
				node.setElement(currentElement);
				nodes[currentRow][currentElement] = node;
				nodes[currentRow][currentElement] = node;
				currentElement++;
			}
			currentRow++;
		}
		myfile.close();
	}
	setNeighbours();
}

void Maze::setNeighbours() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			vector<Node*> neighbours;
			if (i != 0)
				neighbours.push_back(&nodes[i - 1][j]);
			if (i != height - 1)
				neighbours.push_back(&nodes[i + 1][j]);
			if (j != 0)
				neighbours.push_back(&nodes[i][j - 1]);
			if (j != width - 1)
				neighbours.push_back(&nodes[i][j + 1]);
			nodes[i][j].setNeighbours(neighbours);
			if (nodes[i][j].getValue() == 'E' || nodes[i][j].getValue() == 'P')
				exits.push_back(nodes[i][j]);		// Maintain exit list
		}
	}
}

bool Maze::isInBounds(int row, int element) const {
	if (row < 0 || row >= height || element < 0 || element >= width)
		return false;
	return true;
}

void Maze::generateMaze() {
	generatePaths(1, 1);		// Start generating from top left of maze
	/* Set middle area after generation */
	for (int i = (height / 2) - 1; i <= (height / 2) + 1; ++i) {
		for (int j = (width / 2) - 1; j <= (width / 2) + 1; ++j) {
			if (i == height / 2 && j == width / 2)
				nodes[i][j].setValue('S');
			else
				nodes[i][j].setValue(' ');
		}
	}
	/* Set random exits along edge of maze, cannot be corners */
	for (int i = 0; i < exitSize; ++i) {
		int row, element;
		do {
			row = rand() % height + 0;
			element = rand() % width + 0;
			if (row < element) {		// On top or bottom row
				row = rand() > RAND_MAX / 2 ? (height - 1) : 0;
				element = rand() % (width - 2) + 1;
			}
			else {		// On maze sides
				element = rand() > RAND_MAX / 2 ? (width - 1) : 0;
				row = rand() % (height - 2) + 1;
			}
		} while (nodes[row][element].getValue() == 'E');
		nodes[row][element].setValue('E');
	}
	setNeighbours();
	/* Ensure each exit has open space infront of it */
	for (auto& start : exits) {
		int count = 0;
		for (auto& neighbour : start.getNeighbours()) {
			count++;
			if (neighbour->getValue() == ' ')
				break;
			if (count = start.getNeighbours().size()) {
				if (start.getRow() == 0)
					nodes[start.getRow() + 1][start.getElement()].setValue(' ');
				if (start.getRow() == height - 1)
					nodes[start.getRow() - 1][start.getElement()].setValue(' ');
				if (start.getElement() == 0)
					nodes[start.getRow()][start.getElement() + 1].setValue(' ');
				if (start.getElement() == width - 1)
					nodes[start.getRow()][start.getElement() - 1].setValue(' ');
			}
		}
	}
}

void Maze::generatePaths(int row, int element) {
	nodes[row][element].setValue(' ');
	int directions[4]{ 0, 1, 2, 3 };
	/* Randomly assign each direction */
	for (int i = 0; i < 4; ++i) {
		int ranDir = rand() & 3;
		int temp = directions[ranDir];
		directions[ranDir] = directions[i];
		directions[i] = temp;
	}
	for (int i = 0; i < 4; ++i) {
		int dx = 0, dy = 0;
		switch (directions[i]) {
		case 0: dy = -1; break;
		case 1: dx = 1; break;
		case 2: dy = 1; break;
		case 3: dx = -1; break;
		}
		/* Tunnel in another direction */
		int newRow = row + (dy << 1);
		int newElement = element + (dx << 1);
		if (!(newRow < 0 || newRow >= height || newElement < 0 || newElement >= width)) {
			if (nodes[newRow][newElement].getValue() == 'X') {
				nodes[newRow - dy][newElement - dx].setValue(' ');
				generatePaths(newRow, newElement);
			}
		}
	}
}

bool Maze::isValid(Node n) const {
	if (n.getValue() == 'X' || n.getValue() != 'E' && (n.getElement() == 0 || n.getElement() == width - 1 || n.getRow() == 0 || n.getRow() == height - 1))
		return false;
	return true;
}

bool Maze::isDestination(Node n, Node dest) const {
	if (n.getRow() == dest.getRow() && n.getElement() == dest.getElement())
		return true;
	return false;
}

/* Called if successful path is found */
stack<Node> Maze::makePath(Node start, Node dest) {
	cout << "Shortest Path Found" << endl;
	stack<Node> path;
	int row = dest.getRow(), element = dest.getElement();
	while (!(isDestination(nodes[row][element], nodes[nodes[row][element].getParentRow()][nodes[row][element].getParentElement()]))
		&& nodes[row][element].getRow() != -1 && nodes[row][element].getElement() != -1) {
		if (nodes[row][element].getValue() != 'E' && nodes[row][element].getValue() != 'S')
			nodes[row][element].setValue('o');
		path.push(nodes[row][element]);
		int parentRow = nodes[row][element].getParentRow(), parentY = nodes[row][element].getParentElement();
		row = parentRow;
		element = parentY;
	}
	path.push(nodes[row][element]);		// Start node is last node pushed
	return path;
}

stack<Node> Maze::aStar(Node start, Node dest) {
	stack<Node> error;
	if (!isValid(dest)) {
		cout << "Destination is an obstacle" << endl;
		return error;
	}
	if (isDestination(start, dest)) {
		cout << "You are the destination" << endl;
		return error;
	}
	bool** closedList = new bool* [height];
	for (int i = 0; i < height; ++i)
		closedList[i] = new bool[width];
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			nodes[i][j].setRow(i);
			nodes[i][j].setElement(j);
			nodes[i][j].setF(INT_MAX);
			nodes[i][j].setG(INT_MAX);
			nodes[i][j].setH(INT_MAX);
			nodes[i][j].setParentRow(-1);
			nodes[i][j].setParentElement(-1);
			closedList[i][j] = false;
		}
	}
	int row = start.getRow(), element = start.getElement();
	nodes[row][element].setF(0);
	nodes[row][element].setG(0);
	nodes[row][element].setH(0);
	nodes[row][element].setParentRow(row);
	nodes[row][element].setParentElement(element);
	vector<Node> openList;
	openList.emplace_back(nodes[row][element]);
	while (!openList.empty()) {
		Node node;
		do {
			int temp = INT_MAX;
			for (auto& n : openList) {
				if (n.getF() < temp) {
					temp = n.getF();
					node = n;
				}
			}
			openList.erase(remove(openList.begin(), openList.end(), node), openList.end());
		} while (!isValid(node));
		row = node.getRow();
		element = node.getElement();
		closedList[row][element] = true;
		for (const auto& n : nodes[row][element].getNeighbours()) {
			int gNew, hNew, fNew;
			if (isValid(*n)) {
				if (isDestination(*n, dest)) {
					nodes[n->getRow()][n->getElement()].setParentRow(row);
					nodes[n->getRow()][n->getElement()].setParentElement(element);
					return makePath(start, dest);
				}
				else if (!closedList[n->getRow()][n->getElement()]) {
					gNew = node.getG() + 1;
					hNew = abs(node.getRow() - dest.getRow()) + abs(node.getElement() - dest.getElement());		// Manhattan distance
					fNew = gNew + hNew;
					if (nodes[n->getRow()][n->getElement()].getF() == INT_MAX || nodes[n->getRow()][n->getElement()].getF() > fNew) {
						nodes[n->getRow()][n->getElement()].setF(fNew);
						nodes[n->getRow()][n->getElement()].setG(gNew);
						nodes[n->getRow()][n->getElement()].setH(hNew);
						nodes[n->getRow()][n->getElement()].setParentRow(row);
						nodes[n->getRow()][n->getElement()].setParentElement(element);
						openList.emplace_back(nodes[n->getRow()][n->getElement()]);
					}
				}
			}
		}
	}
	cout << "Cannot Reach Destination" << endl;		// Open list empty, impossible destination
	return error;
}

void Maze::printMap() const {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			cout << nodes[i][j].getValue();
		}
		cout << endl;
	}
}

void Maze::writeFile(string name) const {
	ofstream myfile;
	name.insert(0, "Maps/");
	name.append(".txt");
	myfile.open(name);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			myfile << nodes[i][j].getValue();
		}
		myfile << "\n";
	}
	myfile.close();
}
