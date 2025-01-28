/* CSCI 200: Assignment 4 : A4 - Wild Left Center Right Simulation
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

#include "CircularLinkedList.hpp"
#include "Node.hpp"
#include "Player.hpp"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;

void rollDie(CircularLinkedList<Player>& playersLeft, int& centerCount, int& moveCount);

int main() {
	int players = 0;
	int centerCount = 0;
	int moveCount = 1;
	int diceRolls = 0;
	unsigned int turnNumber = 0;
	srand(time(0));

	cout << "How many players: ";
	cin >> players;

	CircularLinkedList<Player> playersLeft = CircularLinkedList<Player>();

	for (int i = 0; i < players; i++) {
		playersLeft.insert(i, Player(i+1));
	}
	Node<Player>* currPlayer = playersLeft.getCurrNode();
	int positionToDelete = -1;

	while (playersLeft.size() >= 2) {
		diceRolls = currPlayer->value.getChips();
		if (diceRolls > 3) {
			diceRolls = 3;
		}
		cout << "Player #" << currPlayer->value.getName() << " has " << currPlayer->value.getChips() << " chips left" << endl;
		cout << "     ";
		cout << "Rolling " << diceRolls << " dice" << endl;
		for (int i = 0; i < diceRolls; i++) {
			rollDie(playersLeft, centerCount, moveCount);
		}
		if (currPlayer->value.getChips() == 0) {
			positionToDelete = playersLeft.find(currPlayer->value);
			playersLeft.move();
			moveCount--;
			playersLeft.remove(positionToDelete);
			positionToDelete = -1;
		}
		for (int i = 0; i < moveCount; i++) {
			playersLeft.move();
		}
		moveCount = 1;
		currPlayer = playersLeft.getCurrNode();
		turnNumber++;
	}

	cout << "Player #" << currPlayer->value.getName() << " wins with " << currPlayer->value.getChips() << " chips left after " << turnNumber << " turns" << endl;

	playersLeft.~CircularLinkedList();
	delete currPlayer;
	return 0;
}


void rollDie(CircularLinkedList<Player>& playersLeft, int& centerCount, int& moveCount) {
	int result = rand() % 8;
	Node<Player>* currPlayer = playersLeft.getCurrNode();
	cout << "     ";
	if (result == 0 || result == 1 || result == 2) {
		cout << "Rolled a " << result << " - keep!" << endl;
	}else if (result == 3) {
		cout << "Rolled a 3 - give right - ";
		currPlayer->value.giveChip(currPlayer->pNext->value);
		cout << "Player #" << currPlayer->value.getName() << " has " << currPlayer->value.getChips() << " chips - ";
		cout << "Player #" << currPlayer->pNext->value.getName() << " has " << currPlayer->pNext->value.getChips() << endl;
	}else if (result == 4) {
		cout << "Rolled a 4 - give left - ";
		currPlayer->value.giveChip(currPlayer->pPrev->value);
		cout << "Player #" << currPlayer->value.getName() << " has " << currPlayer->value.getChips() << " chips - ";
		cout << "Player #" << currPlayer->pPrev->value.getName() << " has " << currPlayer->pPrev->value.getChips() << endl;
	}else if (result == 5) {
		cout << "Rolled a 5 - give center - ";
		currPlayer->value.giveCenter(centerCount);
		cout << "Center has " << centerCount << " chips - ";
		cout << "Player #" << currPlayer->value.getName() << " has " << currPlayer->value.getChips() << endl;
	}else if (result == 6) {
		cout << "Rolled a 6 - reverse!" << endl;
		playersLeft.reverseDirection();
	}else if (result == 7) {
		moveCount++;
		cout << "Rolled a 7 - skip! skipping " << moveCount-1 << " players" << endl;
	}
	delete currPlayer;
}