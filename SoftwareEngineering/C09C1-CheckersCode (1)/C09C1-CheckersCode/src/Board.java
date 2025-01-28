/** 
 * Board: Creates tiles, pieces, and draws the board
 * Author: Caleb Bartel and Ty Gazaway
 */

import java.util.ArrayList;

public class Board {
	static final int BOARD_DIMENSION = 8;d
	static final int NUM_PIECE_ROWS = 3; // num of rows of pieces each player starts with
	private Tile[][] tiles;
	private ArrayList<Piece> boardPieces;
	
	/** 
	 * Default Constructor: Initializes tiles and pieces to default orientation
	 */
	public Board() {
		super();
		tiles = new Tile[BOARD_DIMENSION][BOARD_DIMENSION];
		boardPieces = new ArrayList<Piece>();
		
		Color curTileColor = Color.RED;
		for (int row = 0; row < BOARD_DIMENSION; row++){
			for (int col = 0; col < BOARD_DIMENSION; col++){
				tiles[row][col] = new Tile(row,col, curTileColor);
				if (curTileColor == Color.BLACK && row < NUM_PIECE_ROWS) {
					Piece redPiece = new Piece(row, col, Color.RED);
					boardPieces.add(redPiece);
					tiles[row][col].setPiece(redPiece);
				}
				if (curTileColor == Color.BLACK && row > BOARD_DIMENSION - NUM_PIECE_ROWS - 1) {
					Piece blackPiece = new Piece(row, col, Color.BLACK);
					boardPieces.add(blackPiece);
					tiles[row][col].setPiece(blackPiece);
				}
				curTileColor = switchColor(curTileColor);
			}
			curTileColor = switchColor(curTileColor);
		}
	}
	
	private Color switchColor(Color curColor) {
		if (curColor == Color.RED) {
			return Color.BLACK;
		}
		else {
			return Color.RED;
		}
	}

	/** 
	 * drawBoard: loops through the tiles and draws them with added styling
	 * 
	 * Drawing contract: 
	 * Print a single character to standard out
	 */
	private void drawBoard() {
		for (int i = 0; i < BOARD_DIMENSION; i++){
			System.out.println("");
			for (int j = 0; j < BOARD_DIMENSION; j++){
				System.out.print("----");
			}
			System.out.println("");
			for (int j = 0; j < BOARD_DIMENSION; j++){
				System.out.print("| ");
				tiles[i][j].draw();
				System.out.print(" ");
			}	
		}
	}

	/** 
	 * main: test main to draw initial board arrangement
	 */
	public static void main(String[] args) {
		Board board = new Board();
		board.drawBoard();
	}

}
