/* 
 * Solution class stores the 3 cards that a player proposes as a potential solution to the game.
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package clueGame;

import java.util.ArrayList;

public class Solution {
	//VVVVV Attributes VVVVV
	private Card room;
	private Card person;
	private Card weapon;

	//VVVVV Constuctor's VVVVV
	
	public Solution(Card room, Card person, Card weapon) {
		this.room = room;
		this.person = person;
		this.weapon = weapon;
	}

	public Solution() {
		this.room = new Card("blank", CardType.ROOM);
		this.person = new Card("blank", CardType.ROOM);
		this.weapon = new Card("blank", CardType.ROOM);
	}

	//VVVVV Functionality Methods VVVVV
	
	// adds Card to the solution if the card it's replacing is blank
	public void addCard(Card newCard) {
		switch (newCard.getType()) {
		case ROOM:
			if (this.room.getCardName().equals("blank")) {
				this.room = newCard;
			}
			break;
		case PERSON:
			if (this.person.getCardName().equals("blank")) {
				this.person = newCard;
			}
			break;
		case WEAPON:
			if (this.weapon.getCardName().equals("blank")) {
				this.weapon = newCard;
			}
			break;
		}
	}
	
	//returns a list of the cards in the given solution that are different from this solution
	public ArrayList<Card> difference(Solution other){
		ArrayList<Card> difference = new ArrayList<Card>();
		if(!this.room.equals(other.getRoom())) {
			difference.add(other.getRoom());
		}
		if(!this.person.equals(other.getPerson())) {
			difference.add(other.getPerson());
		}
		if(!this.weapon.equals(other.getWeapon())) {
			difference.add(other.getWeapon());
		}
		return difference;
	}

	//VVVVV Getters and Setters VVVVV
	
	public Card getRoom() {
		return this.room;
	}

	public Card getPerson() {
		return this.person;
	}

	public Card getWeapon() {
		return this.weapon;
	}
}
