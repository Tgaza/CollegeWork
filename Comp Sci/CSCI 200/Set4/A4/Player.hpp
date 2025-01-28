/* CSCI 200: Assignment 4 : A4 - Wild Left Center Right Simulation
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

using namespace std;

 
#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
public:
	Player();
	Player(int name);
	bool operator!=(const Player& OTHER) const;
	int getName() const;
	int getChips() const;
	void giveChip(Player& targetPlayer);
	void giveCenter(int& centerCount);
	void takeChip();
private:
	int name;
	int chips;
};


#endif // !LINKED_LIST_H


//Method definitions
Player::Player() {
	this->name = 0;
	this->chips = 3;
}

Player::Player(int name) {
	this->name = name;
	this->chips = 3;
}

bool Player::operator!=(const Player& OTHER) const {
	return name != OTHER.getName();
}

int Player::getName() const {
	return name;
}

int Player::getChips() const {
	return chips;
}

void Player::giveChip(Player& targetPlayer) {
	chips--;
	targetPlayer.takeChip();
}

void Player::giveCenter(int& centerCount) {
	chips--;
	centerCount++;
}

void Player::takeChip() {
	chips++;
}
