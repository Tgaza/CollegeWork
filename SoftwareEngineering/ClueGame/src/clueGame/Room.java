/* 
 * Room class that houses data relevant to a room in clueGame, such as it's center and where to place the label.
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */
package clueGame;

public class Room {
	//VVVVV Attributes VVVVV
	private String name;
	private boolean isNotRealRoom;
	private BoardCell centerCell;
	private BoardCell labelCell;

	//VVVVV Constructors VVVVV
	public Room(String name) {
		this.name = name;
		this.centerCell = null;
		this.labelCell = null;
		this.isNotRealRoom = false;
	}

	//VVVVV Getters and Setters VVVVV
	public BoardCell getLabelCell() {
		return this.labelCell;
	}

	public BoardCell getCenterCell() {
		return this.centerCell;
	}

	public String getName() {
		return this.name;
	}

	public boolean isNotRealRoom() {
		return this.isNotRealRoom;
	}

	public void setLabelCell(BoardCell labelCell) {
		this.labelCell = labelCell;
	}

	public void setCenterCell(BoardCell centerCell) {
		this.centerCell = centerCell;
	}

	public void setNotRealRoom(boolean isNotRealRoom) {
		this.isNotRealRoom = isNotRealRoom;
	}
	
	
}
