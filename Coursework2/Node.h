/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This header defines a Node, used to generate a maze and for pathfinding */
#pragma once
#include <vector>
using namespace std;
class Node {
private:
	char value;
	int row;
	int element;
	vector<Node*> neighbours;
	int parentRow;
	int parentElement;
	int g;
	int f;
	int h;
public:
	Node() {
		value = 'X';
		row = 0;
		element = 0;
		parentRow = -1;
		parentElement = -1;
		g = INT_MAX;
		f = INT_MAX;
		h = INT_MAX;
	}
	Node(char value) {
		this->value = value;
		row = 0;
		element = 0;
		parentRow = -1;
		parentElement = -1;
		g = INT_MAX;
		f = INT_MAX;
		h = INT_MAX;
	}
	Node(const Node& p2);
	void operator=(const Node& D);
	friend inline bool operator<(const Node& lhs, const Node& rhs);
	friend bool operator==(const Node& lhs, const Node& rhs);
	char getValue() const {
		return value;
	}
	int getRow() const {
		return row;
	}
	int getElement() const {
		return element;
	}
	vector<Node*> getNeighbours() const {
		return neighbours;
	}
	int getParentRow() const {
		return parentRow;
	}
	int getParentElement() const {
		return parentElement;
	}
	int getF() const {
		return f;
	}
	int getG() const {
		return g;
	}
	int getH() const {
		return h;
	}
	void setValue(char value) {
		this->value = value;
	}
	void setRow(int row) {
		this->row = row;
	}
	void setElement(int element) {
		this->element = element;
	}
	void setNeighbours(vector<Node*> neighbours) {
		this->neighbours = neighbours;
	}
	void setParentRow(int parentRow) {
		this->parentRow = parentRow;
	}
	void setParentElement(int parentElement) {
		this->parentElement = parentElement;
	}
	void setF(int f) {
		this->f = f;
	}
	void setG(int g) {
		this->g = g;
	}
	void setH(int h) {
		this->h = h;
	}
};
