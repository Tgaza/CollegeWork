/** 
 * Piece: Stores piece information 
 * Author: Caleb Bartel and Ty Gazaway
 */

public class Piece {
	private int row;
	private int col;
	private Color color;
	private boolean king = false;
	
	public Piece(int row, int col, Color color) {
		super();
		this.row = row;
		this.col = col;
		this.color = color;
	}
	
	/** 
	 * draw: Draws the piece depending on the color. And if the piece is a king
	 * , then the letter is capitalized.
	 * Following the contract described in the drawBoard method of the Board class
	 */
	public void draw() {
		String symbol;
		if (color == Color.RED) {
			symbol = "r";
		}
		else {
			symbol = "b";
		}
		if (king) {
			symbol = symbol.toUpperCase();
		}
		System.out.print(symbol);
	}
}
