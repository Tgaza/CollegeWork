/* 
 * HumanPlayer class adds the necessary implementation for a human player to interact with the game.
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package clueGame;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Set;

public class HumanPlayer extends Player {

	// VVVVV Constructors VVVVV
	public HumanPlayer(String name, Color color, int row, int col, Room curRoom) {
		super(name, color, row, col, curRoom);
		// TODO Auto-generated constructor stub
	}

	// VVVVV Functionality Methods VVVVV

	public void updateSeen(Card card, KnownCardsPanel cardsDisplay, Color providingPlayerColor) {
		super.updateSeen(card);
		cardsDisplay.addCard(false, card, providingPlayerColor);
	}

}
