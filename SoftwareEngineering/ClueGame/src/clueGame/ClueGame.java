/*
 * ClueGame is a child of JFrame and is the main class that sets up and runs the game
 * Author: Ty Gazaway
 * 
 * */
package clueGame;

import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

public class ClueGame extends JFrame {
	// VVVVV Attributes VVVVV
	private Board gameBoard;
	private int rows;
	private int cols;
	private BoardPanel boardDisplay;
	private KnownCardsPanel knownCardsDisplay;
	private GameControlPanel gameControlsDisplay;
	private boolean isVisible;
	// Constants
	private static final int WINDOW_WIDTH = 1000;
	private static final int WINDOW_HEIGHT = 1000;

	// VVVVV Main method VVVVV
	public static void main(String[] args) {
		// setup ClueGame
		ClueGame theGame = new ClueGame();
		theGame.addInHandCardsToDisplay();
		theGame.toggleVisibility();
		theGame.displaySplashScreen();
		theGame.getBoard().startGame(theGame);
		//theGame.getBoard().runGame(theGame.getBoardDisplay(), theGame.getKnownCardsDisplay(), theGame.getGameControlsDisplay());
	}

	// VVVVV Constructors VVVVV
	// main constructor
	public ClueGame() {
		// initial game pieces
		// Board is singleton, get the only instance
		this.gameBoard = Board.getInstance();
		// set the file names to use my config files
		this.gameBoard.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		// Initialize will load config files
		this.gameBoard.initialize();

		// Initialize attributes
		this.rows = gameBoard.getNumRows();
		this.cols = gameBoard.getNumColumns();
		this.isVisible = false;

		// Initialize GUI
		this.boardDisplay = new BoardPanel(this.gameBoard);
		this.knownCardsDisplay = new KnownCardsPanel();
		this.gameControlsDisplay = new GameControlPanel(this.gameBoard);
		setup();
	}

	// VVVVV private helper methods VVVVV
	private void setup() {
		// configure ClueGame
		this.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		this.setTitle("Clue Game");
		this.setVisible(isVisible);
		// configure Layout settings
		this.setLayout(new GridBagLayout());
		GridBagConstraints boardConstraints = new GridBagConstraints();
		boardConstraints.fill = GridBagConstraints.BOTH;
		boardConstraints.gridx = 0;
		boardConstraints.gridy = 0;
		boardConstraints.weightx = 0.9;
		boardConstraints.weighty = 0.8;
		GridBagConstraints knownCardsConstraints = new GridBagConstraints();
		knownCardsConstraints.fill = GridBagConstraints.BOTH;
		knownCardsConstraints.gridx = 1;
		knownCardsConstraints.gridy = 0;
		knownCardsConstraints.weightx = 0.10;
		knownCardsConstraints.weighty = 0.15;
		knownCardsConstraints.gridwidth = 1;
		GridBagConstraints gameControlsConstraints = new GridBagConstraints();
		gameControlsConstraints.fill = GridBagConstraints.BOTH;
		gameControlsConstraints.gridx = 0;
		gameControlsConstraints.gridy = 1;
		gameControlsConstraints.weightx = 0.05;
		gameControlsConstraints.weighty = 0.05;
		gameControlsConstraints.gridwidth = 2;

		// add game content panels
		this.add(boardDisplay, boardConstraints);
		this.add(knownCardsDisplay, knownCardsConstraints);
		this.add(gameControlsDisplay, gameControlsConstraints);
	}

	// VVVVV Functionality Methods VVVVV
	//toggles the visibility of the game
	public void toggleVisibility() {
		this.isVisible = !this.isVisible;
		this.setVisible(isVisible);
	}

	//adds the human players hand to the known cards display
	private void addInHandCardsToDisplay() {
		Player human = this.gameBoard.getHumanPlayer();
		for(Card card: human.getHand()) {
			this.knownCardsDisplay.addCard(true, card, human.getColor());
		}
	}

	//Displays a splash screen on game startup, introducing the game to the player
	public void displaySplashScreen() {
		String msg1 = "You are " + this.gameBoard.getPlayers().get(0).getName() + ".\n";
		String msg2 = "Can you find the solution\n before the Computer players?";
		JOptionPane.showMessageDialog(this, msg1 + msg2, "Welcome to Clue", JOptionPane.INFORMATION_MESSAGE);
	}

	//Displays an error message with the passed in string as the message
	public void displayErrorMsg(String msg) {
		JOptionPane.showMessageDialog(this, msg, "Error", JOptionPane.ERROR_MESSAGE);
	}

	// VVVVV Getters and Setters VVVVV

	public Board getBoard() {
		return this.gameBoard;
	}

	public BoardPanel getBoardDisplay() {
		return this.boardDisplay;
	}

	public KnownCardsPanel getKnownCardsDisplay() {
		return this.knownCardsDisplay;
	}

	public GameControlPanel getGameControlsDisplay() {
		return this.gameControlsDisplay;
	}
}
