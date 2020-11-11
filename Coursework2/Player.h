/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This header defines a Player, who pathfinds the maze */
#pragma once
#include <string>
using namespace std;
class Player {
private:
	int row;
	int element;
	string name;
	bool finished;
	int score;
public:
	Player();
	Player(int row, int element);
	int getRow() const {
		return row;
	}
	int getElement() const {
		return element;
	}
	string getName() const {
		return name;
	}
	bool getFinished() const {
		return finished;
	}
	int getScore() const {
		return score;
	}
	void setRow(int row) {
		this->row = row;
	}
	void setElement(int element) {
		this->element = element;
	}
	void setName(string name) {
		this->name = name;
	}
	void setFinished(bool finished) {
		this->finished = finished;
	}
	void setScore(int score) {
		this->score = score;
	}
	void incrScore() {
		score++;
	}
};

