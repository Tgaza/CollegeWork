package experiment;
/* Experimental board class for testing code to find what should be used in the final clue game board class.
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */

import java.util.HashSet;
import java.util.Set;

public class TestBoard {
	private TestBoardCell[][] board;
	private Set<TestBoardCell> targets;
	private static final int ROWS = 4;
	private static final int COLS = 4;

	public TestBoard() {
		board = new TestBoardCell[ROWS][ROWS];
		targets = new HashSet<TestBoardCell>();
		initializeCells();
	}

	/*
	 * initializeCells traverses over the empty board array and initializes a new TestBoardCell at
	 * each position. It also updates the adjacency lists of the created cells as it traverses.
	 * */
	private void initializeCells() {
		for(int row = 0; row < ROWS; row++) {
			for(int col = 0; col < COLS; col++) {
				board[row][col] = new TestBoardCell(row, col);
				Set<TestBoardCell> adjList = board[row][col].getAdjList();
				//Checks if cell to there is a cell to the left then updates adjList for both cells
				if(row-1 >= 0) {
					adjList.add(board[row-1][col]);
					board[row-1][col].getAdjList().add(board[row][col]);
				}
				//Checks if there is a cell above then updates adjList for both cells
				if(col-1 >= 0) {
					adjList.add(board[row][col-1]);
					board[row][col-1].getAdjList().add(board[row][col]);
				}
			}
		}
	}

	/*
	 * calcTargets clears the target set and then calls it's helper to find all targets.
	 * */
	public void calcTargets(TestBoardCell startCell, int pathlength) {
		targets.clear();
		calcTargetsHelper(startCell, pathlength, new HashSet<TestBoardCell>());
	}
	
	/*
	 * calcTargetsHelper recursively travels down paths until it runs out of movement or enters a room, 
	 * then adds the cell at the end of the path to targets. It also keeps track of visited cells via a 
	 * hashset.
	 * */
	private void calcTargetsHelper(TestBoardCell startCell, int pathlength, Set<TestBoardCell> visited) {
		//Base Case
		if(pathlength <= 0 || startCell.isRoom()) {
			targets.add(startCell);
			return;
		}
		visited.add(startCell);
		
		//Loop through adjacent cells and starts a new branch on each valid cell
		for(TestBoardCell cell: startCell.getAdjList()) {
			if(visited.contains(cell) || cell.isOccupied()) {
				continue;
			}
			//New set instance to avoid overlap between branches
			Set<TestBoardCell> newBranchSet = new HashSet<TestBoardCell>(visited);
			calcTargetsHelper(cell, pathlength-1, newBranchSet);
		}
	}

	public TestBoardCell getCell(int row, int col) {
		return board[row][col];
	}

	public Set<TestBoardCell> getTargets(){
		return targets;
	}

}
