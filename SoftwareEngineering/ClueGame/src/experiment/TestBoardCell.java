/* Experimental BoardCell class for testing code to find what should be used in the final clue game BoardCell class.
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */

package experiment;

import java.util.HashSet;
import java.util.Set;

public class TestBoardCell {
	private int row;
	private int col;
	private Set<TestBoardCell> adjList;
	private boolean isRoom;
	private boolean isOccupied;
	 
	
	public TestBoardCell(int row, int col) {
		isRoom = false;
		isOccupied = false;
		this.row = row;
		this.col = col;
		adjList = new HashSet<TestBoardCell>();
	}

	public int getCol() {
		return col;
	}

	public int getRow() {
		return row;
	}
	
	public Set<TestBoardCell> getAdjList(){
		return adjList;
	}

	public boolean isOccupied() {
		return isOccupied;
	}

	public void setIsOccupied(boolean isOccupied) {
		this.isOccupied = isOccupied;
	}

	public boolean isRoom() {
		return isRoom;
	}

	public void setIsRoom(boolean isRoom) {
		this.isRoom = isRoom;
	}

}
