/*
 * The Tile class stores the information for a tile.
 * Author: Caleb Bartel and Ty Gazaway
 * */
public class Tile {
	private int row;
	private int col;
	private Color color;
	private Piece piece;
	
	public Tile(int row, int col, Color color) {
		super();
		this.row = row;
		this.col = col;
		this.color = color;
	}
	

	/** 
	 * draw: Draws the tile depending on the color
	 * 		 If there is a piece on the tile, the piece's draw method is called
	 * Following the contract described in the drawBoard method of the Board class
	 */
	public void draw() {
		if (piece != null) {
			piece.draw();
			return;
		}
		if (color == Color.RED) {
			System.out.print("X");
		}
		else {
			System.out.print("O");
		}
	}
	
	public void setPiece(Piece piece) {
		this.piece = piece;
	}
	
}
