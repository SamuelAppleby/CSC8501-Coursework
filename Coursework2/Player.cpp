/*          Created By Samuel Buzz Appleby
 *               08/11/2020
 *                170348069                   */
 /* This contains Player implementation */
#include "Player.h"
Player::Player() {
	row = 0;
	element = 0;
	name = "";
	finished = false;
	score = 0;
}

Player::Player(int row, int element) {
	this->row = row;
	this->element = element;
	name = "";
	finished = false;
	score = 0;
}
