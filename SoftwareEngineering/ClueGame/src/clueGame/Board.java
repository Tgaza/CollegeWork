/* 
 * Board class that stores the game board, other relevant data, and the necessary functions in order for the clue game to function.
 * Stores the game board as a single static instance so that it can fully control and protect the game board.
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */
package clueGame;

import java.awt.Color;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

public class Board implements MouseListener{
	// VVVVV Attributes VVVVV
	private int rows;
	private int cols;
	private String layoutConfigFile;
	private String setupConfigFile;
	private BoardCell[][] gameBoard;
	private Set<BoardCell> targets;
	private ArrayList<BoardCell> startingLocations;
	private Map<Character, Room> roomMap;
	private Map<String, Color> peopleMap;
	private Set<String> weapons;
	private ArrayList<Player> players;
	private ArrayList<Card> deck;
	private HumanPlayer humanPlayer;
	private Solution theAnswer;

	// VVVVV Game Variables VVVVV
	private int curPlayerTurn;
	private int curDiceRoll;
	private boolean isHumanTurnOver;
	private ClueGame clueGameGui;
	private BoardCell lastSelectedTarget;
	private Player curPlayer;

	// VVVVV CONSTANTS VVVVV
	private static final int MAX_PLAYERS = 6;
	private static final int MAX_CONFIG_COLS = 3;
	private static final int MAX_ROOM_INITIALS = 1;
	private static final int MAX_HEX_LEN = 7;

	// VVVVV Singleton design VVVVV
	private static Board theInstance = new Board();

	private Board() {
		super();
	}

	// VVVVVVV Initialize the game components VVVVVVV
	public void initialize() {
		this.targets = new HashSet<>();
		this.startingLocations = new ArrayList<>();
		this.roomMap = new HashMap<>();
		this.peopleMap = new HashMap<>();
		this.players = new ArrayList<>();
		this.deck = new ArrayList<>();
		this.weapons = new HashSet<>();
		this.theAnswer = new Solution();
		this.clueGameGui = null;
		this.isHumanTurnOver = true;
		this.curPlayerTurn = 0;
		try {
			loadSetupConfig();
			loadLayoutConfig();
			updateAdjLists();
			createPlayers();
			if (this.players.size() == MAX_PLAYERS) {
				dealCards();
			} else {
				throw new BadConfigFormatException();
			}
		} catch (FileNotFoundException | BadConfigFormatException e) {
			System.out.println(e);
		}
	}

	/*
	 * updateAdjLists is a helper method for initialize that updates the adjLists
	 * for the newly filled boardCells
	 */
	private void updateAdjLists() throws BadConfigFormatException {
		// Loop through board
		for (int row = 0; row < this.rows; row++) {
			for (int col = 0; col < this.cols; col++) {
				BoardCell tempCell = this.gameBoard[row][col];
				// Check if the cell is a cell that should have adjacencies
				if (tempCell.getInitial() != 'W' && tempCell.getSecretPassage() == '!') {
					continue;
					// Check if doorway
				} else if (tempCell.isDoorway()) {
					BoardCell roomCell = null;
					// Check doorway direction and get room center cell
					switch (tempCell.getDoorDirection()) {
					case UP:
						roomCell = getRoom(this.gameBoard[row - 1][col]).getCenterCell();
						break;
					case DOWN:
						roomCell = getRoom(this.gameBoard[row + 1][col]).getCenterCell();
						break;
					case RIGHT:
						roomCell = getRoom(this.gameBoard[row][col + 1]).getCenterCell();
						break;
					case LEFT:
						roomCell = getRoom(this.gameBoard[row][col - 1]).getCenterCell();
						break;
					default:
						throw new BadConfigFormatException();
					}
					tempCell.getAdjList().add(roomCell);
					roomCell.getAdjList().add(tempCell);
					// Check if secretPassage and assign room center cells to each others adj lists
				} else if (tempCell.getSecretPassage() != '!') {
					BoardCell curRoom = getRoom(tempCell).getCenterCell();
					BoardCell passageRoom = getRoom(tempCell.getSecretPassage()).getCenterCell();
					curRoom.getAdjList().add(passageRoom);
					passageRoom.getAdjList().add(curRoom);
				}
				// Check if previous cell exists and if it is a walkway
				if (row - 1 >= 0 && this.gameBoard[row - 1][col].getInitial() == 'W') {
					tempCell.getAdjList().add(this.gameBoard[row - 1][col]);
					this.gameBoard[row - 1][col].getAdjList().add(tempCell);
				}
				// Check if the cell above exists and if it is a walkway
				if (col - 1 >= 0 && this.gameBoard[row][col - 1].getInitial() == 'W') {
					tempCell.getAdjList().add(this.gameBoard[row][col - 1]);
					this.gameBoard[row][col - 1].getAdjList().add(tempCell);
				}
			}
		}
	}

	// creates the players using people data
	private void createPlayers() {
		boolean humanCreated = false;
		// Loop through people data using the entrySet of peopleMap
		// entry<Name,Color>
		Collections.shuffle(startingLocations);
		for (Map.Entry<String, Color> person : this.peopleMap.entrySet()) {
			BoardCell startingLocation = startingLocations.remove(0);
			if (!humanCreated) {
				// Add new human player to players
				this.players.add(new HumanPlayer(person.getKey(), person.getValue(), startingLocation.getRow(),
						startingLocation.getCol(), this.getRoom(startingLocation)));
				humanPlayer = (HumanPlayer) this.players.get(0);
				humanCreated = true;
			} else {
				// Add new computer player to players
				this.players.add(new ComputerPlayer(person.getKey(), person.getValue(), startingLocation.getRow(),
						startingLocation.getCol(), this.getRoom(startingLocation)));
			}
		}
	}

	// Deals out cards to the players
	private void dealCards() {
		ArrayList<Player> playersNeeding = new ArrayList<>(this.players);
		Set<CardType> ansCards = new HashSet<>();
		int curPlayer = 0;
		// Shuffle deck and then deal cards
		Collections.shuffle(this.deck);
		for (Card card : this.deck) {
			// loop back through players after giving 1 to all
			curPlayer = curPlayer % MAX_PLAYERS;
			// if answer doesn't contain the current cards type then add it else deal
			if (!ansCards.contains(card.getType())) {
				this.theAnswer.addCard(card);
				ansCards.add(card.getType());
			} else {
				playersNeeding.get(curPlayer).updateHand(card);
				curPlayer++;
			}
		}
	}

	// VVVVVVV Load Config Data VVVVVVV

	public void setConfigFiles(String layoutConfigFile, String setupConfigFile) {
		this.layoutConfigFile = layoutConfigFile;
		this.setupConfigFile = setupConfigFile;
	}

	// Load file and scan in the data for roomMap(legend)
	public void loadSetupConfig() throws FileNotFoundException, BadConfigFormatException {
		// Setup necessary variables and file interacting objects
		FileReader fileReader = new FileReader("data/" + this.setupConfigFile);
		Scanner scan = new Scanner(fileReader);
		String[] cellData;
		// loop whole file
		while (scan.hasNextLine()) {
			// Split up the line into an array of it's components
			// Format should be [0]Category,[1]Name,[2]Symbol
			cellData = scan.nextLine().split(", ");

			// Skip line if the first item of the array is the comment identifier
			if (cellData[0].substring(0, 2).equals("//")) {
				continue;
				// bad format if the line is not a comment
				// and has improper format:
				// Incorrect number of columns
			} else if (cellData.length != MAX_CONFIG_COLS
					// Incorrect string length in 3rd column
					|| (cellData[2].length() != MAX_ROOM_INITIALS
							&& (cellData[0].equals("Room") || cellData[0].equals("Space")))
					// Incorrect string length in 3rd column
					|| (cellData[2].length() != MAX_HEX_LEN && cellData[0].equals("Person"))
					// Incorrect category name
					|| (!cellData[0].equals("Space")
							&& !cellData[0].equals("Room")
							&& !cellData[0].equals("Person")
							&& !cellData[0].equals("Weapon"))) {

				scan.close();
				throw new BadConfigFormatException();
			}
			if (cellData[0].equals("Room") || cellData[0].equals("Space")) {
				// create temp var to store current room
				Room temp = new Room(cellData[1]);
				// Set NotRealRoom boolean to be true if [0]category is Space
				if (cellData[0].equals("Space")) {
					temp.setNotRealRoom(true);
				} else {
					// add new card to the deck
					this.deck.add(new Card(cellData[1], CardType.ROOM));
				}
				// store room and it's [2]symbol into roomMap
				this.roomMap.put(cellData[2].charAt(0), temp);
			}
			if (cellData[0].equals("Person")) {
				// put the character name[1] and hex code[2], converted into color, into
				// peopleMap
				this.peopleMap.put(cellData[1], Color.decode(cellData[2]));
				// add new card to the deck
				this.deck.add(new Card(cellData[1], CardType.PERSON));
			}
			if (cellData[0].equals("Weapon")) {
				// record weapon
				this.weapons.add(cellData[1]);
				// add new card to the deck
				this.deck.add(new Card(cellData[1], CardType.WEAPON));
			}
		}
		scan.close();
	}

	// Load file and scan in the data for the game board
	public void loadLayoutConfig() throws FileNotFoundException, BadConfigFormatException {
		// Setup necessary variables and file interacting objects
		FileReader fileReader = new FileReader("data/" + this.layoutConfigFile);
		Scanner scan = new Scanner(fileReader);
		String[] cellData;
		this.rows = 0;
		this.cols = 0;
		int curRow = 0;
		// ArrayList to store the board as it is being built row by row
		ArrayList<BoardCell[]> tempBoard = new ArrayList<BoardCell[]>();
		// Loop through whole file
		while (scan.hasNextLine()) {
			// Split each line into an array of individual cells
			cellData = scan.nextLine().split(",");
			// If total number of columns has not been set, set it to current length
			// of the line array
			if (this.cols == 0) {
				this.cols = cellData.length;
			}
			// Add a new empty row to the tempBoard
			tempBoard.add(new BoardCell[this.cols]);

			// bad format if current line does not have the same
			// number of columns as cols
			if (cellData.length != this.cols) {
				scan.close();
				throw new BadConfigFormatException();
			}
			BoardCell cell;
			// loop through all the cells of the current line and add them to the board
			for (int i = 0; i < cellData.length; i++) {
				// bad format if current cell's initial does not exist in roomMap
				if (this.roomMap.get(cellData[i].charAt(0)) == null) {
					scan.close();
					throw new BadConfigFormatException();
				}
				// initialize current cell(row, col, initial)
				cell = new BoardCell(curRow, i, cellData[i].charAt(0));
				// Set isRoom boolean to be true if room's, of the cell, NotRealRoom boolean is
				// false
				if (!this.roomMap.get(cellData[i].charAt(0)).isNotRealRoom()) {
					cell.setIsRoom(true);
				}

				// if number of symbols given in the config for the cell is 2, ..,L^,..
				// there is more information to be added
				if (cellData[i].length() == 2) {
					// update secretPassage boolean if second char is a room symbol
					if (this.roomMap.get(cellData[i].charAt(1)) != null) {
						cell.setSecretPassage(cellData[i].charAt(1));
					} else {
						// Update cell based on what second char is
						switch (cellData[i].charAt(1)) {
						// room center symbol
						case '*':
							cell.setRoomCenter(true);
							this.roomMap.get(cellData[i].charAt(0)).setCenterCell(cell);
							break;
						// room label symbol
						case '#':
							cell.setRoomLabel(true);
							this.roomMap.get(cellData[i].charAt(0)).setLabelCell(cell);
							break;
						// startingLocation
						case '+':
							this.startingLocations.add(cell);
							break;
						// doorway opening up symbol
						case '^':
							cell.setDoorway(true);
							cell.setDoorDirection(DoorDirection.UP);
							break;
						// doorway opening down
						case 'v':
							cell.setDoorway(true);
							cell.setDoorDirection(DoorDirection.DOWN);
							break;
						// doorway opening left
						case '<':
							cell.setDoorway(true);
							cell.setDoorDirection(DoorDirection.LEFT);
							break;
						// doorway opening right
						case '>':
							cell.setDoorway(true);
							cell.setDoorDirection(DoorDirection.RIGHT);
							break;
						// char doesn't match any known symbol, bad format
						default:
							scan.close();
							throw new BadConfigFormatException();
						}
					}
				}
				// update tempboard with fully initialized cell
				tempBoard.get(curRow)[i] = cell;
			}
			curRow++;
		}
		this.rows = curRow;
		// create empty board of desired size and convert tempBoard into
		// a 2D array of the same size
		this.gameBoard = new BoardCell[this.rows][this.cols];
		this.gameBoard = tempBoard.toArray(this.gameBoard);

		scan.close();
	}

	// VVVVVVV InGame Methods VVVVVVV

	//Sets up the game for the first player and starts it
	public void startGame(ClueGame clueGameGui) {
		this.clueGameGui = clueGameGui;
		this.curPlayer = this.players.get(curPlayerTurn);
		this.rollDice();
		this.calcTargets(this.getCell(this.curPlayer.getRow(), this.curPlayer.getCol()), this.curDiceRoll);
		this.clueGameGui.getGameControlsDisplay().setTurn(this.curPlayer, this.curDiceRoll);
		this.setHumanTurnOverState(false);
		this.clueGameGui.repaint();
	}

	/*
	 * calcTargets clears the target set and then calls it's helper to find all
	 * targets.
	 */
	public void calcTargets(BoardCell startCell, int pathlength) {
		this.targets.clear();
		calcTargetsHelper(startCell, pathlength, new HashSet<BoardCell>());
	}

	/*
	 * calcTargetsHelper recursively travels down paths until it runs out of
	 * movement or enters a room, then adds the cell at the end of the path to
	 * targets. It also keeps track of visited cells via a hashset.
	 */
	private void calcTargetsHelper(BoardCell startCell, int pathlength, Set<BoardCell> visited) {
		// Base Case
		if (pathlength <= 0 || (startCell.isRoomCenter() && !visited.isEmpty() && !visited.contains(startCell))) {
			this.targets.add(startCell);
			return;
		}
		visited.add(startCell);

		// Loop through adjacent cells and starts a new branch on each valid cell
		for (BoardCell cell : startCell.getAdjList()) {
			if (visited.contains(cell) || (cell.isOccupied() && !cell.isRoomCenter())) {
				continue;
			}
			// New set instance to avoid overlap between branches
			Set<BoardCell> newBranchSet = new HashSet<BoardCell>(visited);
			calcTargetsHelper(cell, pathlength - 1, newBranchSet);
		}
	}

	// return true if there is no difference between accusation and theAnswer
	public boolean checkAccusation(Solution accusation) {
		return theAnswer.difference(accusation).isEmpty();
	}

	// checks if any players can disprove suggesting players suggestion and returns
	// their card if they can
	public Card handleSuggestion(Solution suggestion, int curPlayer) {
		// loop through players starting from the one that made the suggestion, not
		// including them
		Card disprovalCard = null;
		for (int playerIndex = curPlayer + 1; playerIndex != curPlayer; playerIndex = (playerIndex + 1)
				% players.size()) {
			// Check if player can disprove, break and return their card if they can
			disprovalCard = players.get(playerIndex).disproveSuggestion(suggestion);
			if (disprovalCard != null) {
				break;
			}
		}
		return disprovalCard;
	}

	//handle the make accusation button being pressed
	public void makeAccusationPressed() {
		//empty for now
	}

	//flow that occurs after the next turn button is pressed
	public void nextPressed() {
		//if current player is human and their turn is not over display error msg
		if (this.curPlayer instanceof HumanPlayer && !this.isHumanTurnOver && this.lastSelectedTarget == null) {
			this.clueGameGui.displayErrorMsg("Your turn is not complete yet,\n"
					+ " please make sure select a square to move your character to.");
			return;
		//if current player is human and they have selected a target, end their turn
		} else if (this.curPlayer instanceof HumanPlayer && this.lastSelectedTarget != null) {
			this.setHumanTurnOverState(true);
		}
		//update curPlayer then setup everything for the next player
		this.curPlayer.setLocation(this.lastSelectedTarget.getRow(), this.lastSelectedTarget.getCol(), this.getRoom(lastSelectedTarget));
		this.lastSelectedTarget.setSelected(false);
		this.lastSelectedTarget = null;
		this.curPlayerTurn = (this.curPlayerTurn + 1) % MAX_PLAYERS;
		this.curPlayer = this.players.get(this.curPlayerTurn);
		this.rollDice();
		this.calcTargets(this.getCell(this.curPlayer.getRow(), this.curPlayer.getCol()), this.curDiceRoll);
		this.clueGameGui.getGameControlsDisplay().setTurn(this.curPlayer, this.curDiceRoll);
		//check if new player is human, if true then set their turn to be incomplete
		if (this.curPlayer instanceof HumanPlayer) {
			this.setHumanTurnOverState(false);
		//otherwise perform all computer player actions
		} else {
			ComputerPlayer cpu = (ComputerPlayer) this.curPlayer;
			if (cpu.canAccuse()) {
				// do nothing for now
			}
			this.lastSelectedTarget = cpu.selectTarget(this.targets, theInstance);
			this.lastSelectedTarget.setSelected(true);
			this.targets.clear();
			this.targets.add(lastSelectedTarget);
			if (this.lastSelectedTarget.isRoomCenter()) {
				cpu.createSuggestion(this.deck);
			}
		}
		this.clueGameGui.repaint();
	}

	//alters whether it is the humans turn or not
	private void setHumanTurnOverState(boolean state) {
		this.isHumanTurnOver = state;
	}

	//Randomly assigns a number from 1-6 to curDiceRoll
	public void rollDice() {
		Random rand = new Random();
		curDiceRoll = rand.nextInt(1, 7);
	}
	
	// VVVVVVV mouseActions VVVVVVV
	//Respond to the player clicking on the board
	//Specifically for seeing which space the player wants to move to
	@Override
	public void mouseClicked(MouseEvent e) {
		if(isHumanTurnOver) {
			//this.clueGameGui.displayErrorMsg("Not your turn");
			return;
		}
		for(BoardCell target: this.targets) {
			int cellWidth = this.clueGameGui.getBoardDisplay().getWidth() / cols;
			int cellHeight = this.clueGameGui.getBoardDisplay().getHeight() / rows;
			if(target.containsClick(e.getX(), e.getY(), cellWidth, cellHeight)) {
				if(lastSelectedTarget != null) this.lastSelectedTarget.setSelected(false);
				this.lastSelectedTarget = target;
				this.lastSelectedTarget.setSelected(true);
				this.clueGameGui.repaint();
				return;
			}
		}
		this.clueGameGui.displayErrorMsg("Invalid Target, please click one of the white circles\n"
				+ " to select a square to move your piece to");
	}

	@Override
	public void mousePressed(MouseEvent e) {
		//do nothing
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		//do nothing
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		//do nothing
	}

	@Override
	public void mouseExited(MouseEvent e) {
		//do nothing
	}
	
	// VVVVVVV Getters and Setters VVVVVVV

	public BoardCell getCell(int row, int col) {
		return this.gameBoard[row][col];
	}

	public Set<BoardCell> getAdjList(int row, int col) {
		return this.gameBoard[row][col].getAdjList();
	}

	public Set<BoardCell> getTargets() {
		return this.targets;
	}

	public Room getRoom(char roomInitial) {
		return this.roomMap.get(roomInitial);
	}

	public Room getRoom(BoardCell cell) {
		return this.roomMap.get(cell.getInitial());
	}

	public static Board getInstance() {
		return theInstance;
	}

	public int getNumRows() {
		return this.rows;
	}

	public int getNumColumns() {
		return this.cols;
	}

	public ArrayList<Player> getPlayers() {
		return this.players;
	}

	public Set<String> getWeapons() {
		return this.weapons;
	}

	public Map<String, Color> getPeopleMap() {
		return this.peopleMap;
	}

	public ArrayList<Card> getDeck() {
		return this.deck;
	}

	public Solution getAnswer() {
		return this.theAnswer;
	}

	public HumanPlayer getHumanPlayer() {
		return this.humanPlayer;
	}

	public BoardCell getSelectedTarget() {
		return this.lastSelectedTarget;
	}

	public int getCurTurn() {
		return this.curPlayerTurn;
	}
}
