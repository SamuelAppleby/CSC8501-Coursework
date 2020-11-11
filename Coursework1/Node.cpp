/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This contains Node implementation, used to generate a maze and for pathfinding */
#include "Node.h"
/* Overload operators */
Node::Node(const Node& n) {
	value = n.value;
	row = n.row;
	element = n.element;
	neighbours = n.neighbours;
	parentRow = n.parentRow;
	parentElement = n.parentElement;
	g = n.g;
	f = n.f;
	h = n.h;
}

void Node::operator=(const Node& n) {
	value = n.value;
	row = n.row;
	element = n.element;
	neighbours = n.neighbours;
	parentRow = n.parentRow;
	parentElement = n.parentElement;
	g = n.g;
	f = n.f;
	h = n.h;
}

inline bool operator<(const Node& lhs, const Node& rhs) {
	return lhs.f < rhs.f;
}

bool operator==(const Node& lhs, const Node& rhs) {
	return lhs.row == rhs.row && lhs.element == rhs.element;
}
