/*
 * BoardPanel is a child of JPanel and displays the entire board including players
 * Author: Ty Gazaway
 * 
 * */
package clueGame;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

public class BoardPanel extends JPanel {
	// VVVVV Attributes VVVVV
	private Board gameBoard;
	private int rows;
	private int cols;
	// Constants

	// VVVVV Constructors VVVVV
	// main constructor
	public BoardPanel(Board gameBoard) {
		// Initialize items
		this.gameBoard = gameBoard;
		this.rows = gameBoard.getNumRows();
		this.cols = gameBoard.getNumColumns();
		setup();
	}

	// VVVVV private helper methods VVVVV
	private void setup() {
		// configure BoardPanel
		this.setLayout(new GridLayout(this.rows, this.cols));
		// configure settings
		this.addMouseListener(gameBoard);
	}

	// VVVVV Functionality Methods VVVVV

	// main method for testing
	public static void main(String[] args) {
		// setup panel
		// Board is singleton, get the only instance
		Board board = Board.getInstance();
		// set the file names to use my config files
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		// Initialize will load config files
		board.initialize();
		BoardPanel panel = new BoardPanel(board);
		JFrame frame = new JFrame();
		frame.setContentPane(panel);
		frame.setSize(750, 750);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.setTitle("Game Board");
		frame.setVisible(true);

		// testing code
	}

	//Paints the current board onto the screen
	@Override
	public void paintComponent(Graphics graphics) {
		super.paintComponent(graphics);
		int cellWidth = this.getWidth() / cols;
		int cellHeight = this.getHeight() / rows;
		int xOffSet = 0;
		int yOffSet = 0;
		// Draw all cells
		Set<BoardCell> labelCells = new HashSet<>();
		Set<BoardCell> doorCells = new HashSet<>();
		// Loop through all cells
		for (int row = 0; row < rows; row++) {
			// reset xOffset every new row
			xOffSet = 0;
			for (int col = 0; col < cols; col++) {
				// get cell
				BoardCell curCell = this.gameBoard.getCell(row, col);
				// draw the base cell
				curCell.draw(graphics, xOffSet, yOffSet, cellWidth, cellHeight);
				// check if cell is a label or doorway and keep track of it if yes
				if (curCell.isLabel()) {
					labelCells.add(curCell);
				} else if (curCell.isDoorway()) {
					doorCells.add(curCell);
				}
				// Move to where next cell is to be drawn along x axis
				xOffSet += cellWidth;
			}
			// Move to where next row is to be drawn along y axis
			yOffSet += cellHeight;
		}
		// Draw doorways over base cells
		for (BoardCell doorCell : doorCells) {
			xOffSet = cellWidth * doorCell.getCol();
			yOffSet = cellHeight * doorCell.getRow();
			doorCell.drawDoor(graphics, xOffSet, yOffSet, cellWidth, cellHeight);
		}
		// Draw room labels over base cells
		for (BoardCell labelCell : labelCells) {
			xOffSet = cellWidth * labelCell.getCol();
			yOffSet = cellHeight * labelCell.getRow();
			labelCell.drawLabel(gameBoard, graphics, xOffSet, yOffSet, cellWidth, cellHeight);
		}
		// Draw Players
		ArrayList<Player> players = this.gameBoard.getPlayers();
		ArrayList<BoardCell> placedLocations = new ArrayList<>();
		for (Player player : players) {
			int playersStacked = 0;
			xOffSet = cellWidth * player.getCol();
			yOffSet = cellHeight * player.getRow();
			for (BoardCell prevLoc : placedLocations) {
				if (prevLoc == this.gameBoard.getCell(player.getRow(), player.getCol())) {
					playersStacked++;
				}
			}
			xOffSet = xOffSet - cellWidth / 4 * playersStacked;
			player.draw(gameBoard, graphics, xOffSet, yOffSet, cellWidth, cellHeight);
			placedLocations.add(this.gameBoard.getCell(player.getRow(), player.getCol()));
		}
		// Draws targets
		for (BoardCell target : this.gameBoard.getTargets()) {
			if (target.isSelected()) {
				target.drawTarget(graphics, cellWidth, cellHeight, players.get(this.gameBoard.getCurTurn()).getColor());
			} else {
				target.drawTarget(graphics, cellWidth, cellHeight, null);
			}
		}
	}

	// VVVVV Getters and Setters VVVVV
}
