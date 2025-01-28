/* 
 * Card class stores data for a card including it's type and name.
 * The Types are ROOM, PERSON, and WEAPON;
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package clueGame;

public class Card {
	//VVVVV Attributes VVVVV
	private String cardName;
	private CardType type;
	
	//VVVVV Constuctors VVVVV
	public Card(String cardName, CardType type) {
		this.cardName = cardName;
		this.type = type;
	}
	
	//VVVVV Functionality methods VVVVV
	public boolean equals(Card target) {
		return this.cardName.equals(target.getCardName()) && this.type == target.getType();
	}

	//VVVVV Getters and Setters VVVVV
	public String getCardName() {
		return this.cardName;
	}

	public CardType getType() {
		return this.type;
	}
}
