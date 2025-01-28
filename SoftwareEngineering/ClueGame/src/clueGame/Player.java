/* 
 * Payer class is an abstract class that ensures all player classes have the same necessary data while allowing them
 * to have different implementations for when it is a human player or computer player.
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package clueGame;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public abstract class Player {
	// VVVVV Attributes VVVVV
	private String name;
	private Color color;
	private int row, col;
	private ArrayList<Card> hand;
	private Set<Card> seen;
	private Room curRoom;

	// VVVVV Abstract methods VVVVV

	// VVVVV Constructors VVVVV
	protected Player(String name, Color color, int row, int col, Room curRoom) {
		this.name = name;
		this.color = color;
		this.row = row;
		this.col = col;
		this.curRoom = curRoom;
		this.hand = new ArrayList<>();
		this.seen = new HashSet<>();
	}

	// VVVVV Functionality Methods VVVVV
	
	/*
	 * Checks for which cards in hand can be used to disprove suggestion and returns: 
	 * - the card if theres only 1 
	 * - a random card among the valid cards if more than one 
	 * - null if no card can be used to disprove
	 */
	public Card disproveSuggestion(Solution suggestion) {
		ArrayList<Card> disprovableCards = new ArrayList<>();
		int returnIndex = 0;
		if (hand.contains(suggestion.getRoom())) {
			disprovableCards.add(suggestion.getRoom());
		}
		if (hand.contains(suggestion.getPerson())) {
			disprovableCards.add(suggestion.getPerson());
		}
		if (hand.contains(suggestion.getWeapon())) {
			disprovableCards.add(suggestion.getWeapon());
		}
		if (disprovableCards.size() > 1) {
			Random rand = new Random();
			returnIndex = rand.nextInt(0, disprovableCards.size());
		} else if (disprovableCards.size() == 0) {
			return null;
		}
		return disprovableCards.get(returnIndex);
	}

	public void updateHand(Card card) {
		this.seen.add(card);
		this.hand.add(card);
	}

	public void updateSeen(Card card) {
		this.seen.add(card);
	}

	public void updateRoom(Board board) {
		this.curRoom = board.getRoom(board.getCell(this.row,  this.col));
	}

	public boolean canAccuse() {
		return false;
	}
	
	// VVVVV GUI methods VVVVV

	//Draws the player at the given coordinates
	public void draw(Board gameBoard, Graphics graphics, int xOffSet, int yOffSet, int cellWidth, int cellHeight) {
		graphics.setColor(this.color);
		graphics.fillOval(xOffSet, yOffSet, cellWidth, cellHeight);
		graphics.setColor(Color.BLACK);
		graphics.drawOval(xOffSet, yOffSet, cellWidth, cellHeight);
	}

	// VVVVV Getters and Setters VVVVV
	public String getName() {
		return this.name;
	}

	public Color getColor() {
		return this.color;
	}

	public int getRow() {
		return this.row;
	}

	public int getCol() {
		return this.col;
	}

	public ArrayList<Card> getHand() {
		return this.hand;
	}

	public Set<Card> getSeen() {
		return this.seen;
	}
	
	public void setLocation(int row, int col, Room room) {
		this.row = row;
		this.col = col;
		this.curRoom = room;
	}

	public Room getRoom() {
		return curRoom;
	}
}
