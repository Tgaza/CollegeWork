/* 
 * BoardCell class that houses the necessary data to create the gameboard
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */

package clueGame;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.util.HashSet;
import java.util.Set;

public class BoardCell {
	// VVVVV Attributes VVVVV
	private int row;
	private int col;
	private Set<BoardCell> adjList;
	private boolean isRoom;
	private boolean isOccupied;
	private boolean isDoorway;
	private boolean roomLabel;
	private boolean roomCenter;
	private boolean isSelected;
	private char initial;
	private char secretPassage;
	private DoorDirection doorDirection;
	// Constants
	private static final Color ROOM_COLOR = Color.decode("#dac0a1");
	private static final Color WALKWAY_COLOR = Color.decode("#e2cdb9");

	// VVVVV Constructors VVVVV
	public BoardCell(int row, int col, char initial) {
		this.isRoom = false;
		this.isOccupied = false;
		this.isDoorway = false;
		this.roomLabel = false;
		this.roomCenter = false;
		this.isSelected = false;
		this.row = row;
		this.col = col;
		this.initial = initial;
		this.doorDirection = DoorDirection.NONE;
		this.secretPassage = '!';
		this.adjList = new HashSet<BoardCell>();
	}

	// VVVVV GUI methods VVVVV

	//Draws the basic cell with its background color depending on the type of room
	public void draw(Graphics graphics, int xOffSet, int yOffSet, int cellWidth, int cellHeight) {
		if (this.initial != 'X' && this.initial != 'W') {
			graphics.setColor(ROOM_COLOR);
		} else if (this.initial != 'X') {
			graphics.setColor(WALKWAY_COLOR);
		} else {
			graphics.setColor(Color.BLACK);
		}
		graphics.fillRect(xOffSet, yOffSet, cellWidth, cellHeight);
		graphics.setColor(Color.BLACK);
		if (!this.isRoom) {
			graphics.drawRect(xOffSet, yOffSet, cellWidth, cellHeight);
			graphics.drawRect(xOffSet, yOffSet, cellWidth - 1, cellHeight - 1);
		}
	}

	//Draws the room label ontop of the label cell
	public void drawLabel(Board gameBoard, Graphics graphics, int xOffSet, int yOffSet, int cellWidth, int cellHeight) {
		graphics.setColor(Color.BLACK);
		String label = gameBoard.getRoom(this).getName();
		int charSize = (int) Math.ceil(cellWidth / 1.6);
		graphics.setFont(new Font("Times New Roman", Font.BOLD | Font.ITALIC, charSize));
		graphics.drawString(label, xOffSet, yOffSet + cellHeight);
	}

	//Draws the door in the direction it opens
	public void drawDoor(Graphics graphics, int xOffSet, int yOffSet, int cellWidth, int cellHeight) {
		graphics.setColor(Color.BLACK);
		int doorwaySizeWeight = 8; // 1/weight gives true weight
		int[] doorwayArcParameters = {(int)(cellWidth*1.5), (int)(cellHeight*1.5), 180, -90};
		switch (this.doorDirection) {
		case UP:
			graphics.fillRect(xOffSet, yOffSet - cellHeight / doorwaySizeWeight, cellWidth, cellHeight / doorwaySizeWeight);
			graphics.drawArc(xOffSet-cellWidth/2, yOffSet-cellHeight/doorwaySizeWeight*7, doorwayArcParameters[0],
					doorwayArcParameters[1], doorwayArcParameters[2]-90, doorwayArcParameters[3]);
			break;
		case DOWN:
			graphics.fillRect(xOffSet, yOffSet + cellHeight, cellWidth, cellHeight / doorwaySizeWeight);
			graphics.drawArc(xOffSet, yOffSet+cellHeight/doorwaySizeWeight*3, doorwayArcParameters[0],
					doorwayArcParameters[1], doorwayArcParameters[2]+90, doorwayArcParameters[3]);
			break;
		case LEFT:
			graphics.fillRect(xOffSet - cellWidth / doorwaySizeWeight, yOffSet, cellWidth / doorwaySizeWeight, cellHeight);
			graphics.drawArc(xOffSet-cellWidth / doorwaySizeWeight*7, yOffSet-cellHeight/2-cellHeight/10, doorwayArcParameters[0],
					doorwayArcParameters[1], doorwayArcParameters[2]+90, doorwayArcParameters[3]);
			break;
		case RIGHT:
			graphics.fillRect(xOffSet + cellWidth, yOffSet, cellWidth / doorwaySizeWeight, cellHeight);
			graphics.drawArc(xOffSet+cellWidth/doorwaySizeWeight, yOffSet, doorwayArcParameters[0],
					doorwayArcParameters[1], doorwayArcParameters[2]-90, doorwayArcParameters[3]);
			break;
		default:
			//do nothing for now
		}
	}
	
	//draws a target circle on the cell, with it's color depending on if the player selected it or not
	public void drawTarget(Graphics graphics, int cellWidth, int cellHeight, Color color) {
		int xOffSet = cellWidth * this.col;
		int yOffSet = cellHeight * this.row;
		if(color == null) {
			graphics.setColor(Color.white);
		}else {
			graphics.setColor(color.brighter());
		}
		graphics.fillOval(xOffSet, yOffSet, cellWidth, cellHeight);
		graphics.setColor(Color.BLACK);
		graphics.drawOval(xOffSet, yOffSet, cellWidth, cellHeight);
	}
	
	//returns true if the mouse was within the cell when it clicked
	public boolean containsClick(int mouseX, int mouseY, int cellWidth, int cellHeight) {
		int xOffSet = cellWidth * this.col;
		int yOffSet = cellHeight * this.row;
		return (xOffSet < mouseX && mouseX < xOffSet+cellWidth) && (yOffSet < mouseY && mouseY < yOffSet+cellHeight);
	}

	// VVVVV Getters and Setters VVVVV
	public char getInitial() {
		return this.initial;
	}

	public int getCol() {
		return this.col;
	}

	public int getRow() {
		return this.row;
	}

	public Set<BoardCell> getAdjList() {
		return this.adjList;
	}

	public boolean isOccupied() {
		return this.isOccupied;
	}

	public void setOccupied(boolean isOccupied) {
		this.isOccupied = isOccupied;
	}

	public boolean isRoom() {
		return this.isRoom;
	}

	public void setIsRoom(boolean isRoom) {
		this.isRoom = isRoom;
	}

	public boolean isRoomCenter() {
		return this.roomCenter;
	}

	public void setRoomCenter(boolean roomCenter) {
		this.isRoom = roomCenter;
		this.roomCenter = roomCenter;
	}

	public boolean isLabel() {
		return this.roomLabel;
	}

	public void setRoomLabel(boolean roomLabel) {
		this.isRoom = roomLabel;
		this.roomLabel = roomLabel;
	}

	public boolean isDoorway() {
		return this.isDoorway;
	}

	public void setDoorway(boolean isDoorway) {
		this.isDoorway = isDoorway;
	}

	public DoorDirection getDoorDirection() {
		return this.doorDirection;
	}

	public void setDoorDirection(DoorDirection doorDirection) {
		this.doorDirection = doorDirection;
	}

	public char getSecretPassage() {
		return this.secretPassage;
	}

	public void setSecretPassage(char secretPassage) {
		this.secretPassage = secretPassage;
	}

	public void setSelected(boolean selected) {
		this.isSelected = selected;
	}

	public boolean isSelected() {
		return this.isSelected;
	}

}
