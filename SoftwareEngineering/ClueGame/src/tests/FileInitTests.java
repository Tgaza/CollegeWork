/* 
 * Junit test class that tests Board's capability to load configuration files properly
 * 
 * Author: Ty Gazaway
 * Date: 10/12/2024
 * 
 * */

package tests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import clueGame.Board;
import clueGame.BoardCell;
import clueGame.DoorDirection;
import clueGame.Room;

class FileInitTests {
	
	public static final int LEGEND_SIZE = 11;
	public static final int NUM_ROWS = 27;
	public static final int NUM_COLS = 27;
	
	//allows one board instance to be created for use
	private static Board board;
	
	//Have the board instance created and load the data
	@BeforeAll
	public static void setUp() {
		board = Board.getInstance();
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		board.initialize();
	}

	//Tests whether the legend was loaded correctly
	@Test
	void testRoomLables() {
		assertEquals("Gryffindor Tower", board.getRoom('G').getName());
		assertEquals("Ravenclaw Tower", board.getRoom('R').getName());
		assertEquals("Slytherin Dungeon", board.getRoom('S').getName());
		assertEquals("Hufflepuff Commons", board.getRoom('H').getName());
		assertEquals("HeadMasters Office", board.getRoom('O').getName());
		assertEquals("Defence Tower", board.getRoom('D').getName());
		assertEquals("Transformation court", board.getRoom('T').getName());
		assertEquals("Library", board.getRoom('L').getName());
		assertEquals("Great Hall", board.getRoom('F').getName());
		assertEquals("Unused", board.getRoom('X').getName());
		assertEquals("Walkway", board.getRoom('W').getName());
	}
	
	//Tests whether the board was loaded correctly and has the right number of cells, columns, and rows
	@Test
	public void testBoardDimensions() {
		
		assertEquals(NUM_ROWS, board.getNumRows());
		assertEquals(NUM_COLS, board.getNumRows());
	}

	//Test whether the doors were loaded correctly and have the correct directions
	@Test
	public void FourDoorDirections() {
		//UP
		BoardCell cell = board.getCell(6, 16);
		assertTrue(cell.isDoorway());
		assertEquals(DoorDirection.UP, cell.getDoorDirection());
		
		//DOWN
		cell = board.getCell(11, 3);
		assertTrue(cell.isDoorway());
		assertEquals(DoorDirection.DOWN, cell.getDoorDirection());
		
		cell = board.getCell(1, 9);
		assertTrue(cell.isDoorway());
		assertEquals(DoorDirection.LEFT, cell.getDoorDirection());
		
		//RIGHT (left^)
		cell = board.getCell(13, 19);
		assertTrue(cell.isDoorway());
		assertEquals(DoorDirection.RIGHT, cell.getDoorDirection());
		//B,A,Start
		//if you know, you know
	}
	
	//Tests whether all doors successfully loaded
	@Test
	public void testNumberOfDoorWays() {
		int numDoors = 0; 
		for(int row = 0; row < board.getNumRows(); row++) {
			for(int col = 0; col < board.getNumRows(); col++) {
				BoardCell cell = board.getCell(row, col);
				if(cell.isDoorway()) {
					numDoors++;
				}
			}
		}
		assertEquals(14, numDoors);
	}
	
	/*
	 * Tests room cells and whether they have initialized correctly
	 * This test uses a cell from a different room for each case just in case
	 * one room was done correctly but another was not.
	*/
	@Test
	public void testRooms() {
		//test basic room cell - Uses Gryffindor Tower room cell
		//that is right next to the label and center cells
		BoardCell cell = board.getCell(3, 15);
		Room room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Gryffindor Tower");
		assertTrue(cell.getInitial() == 'G');
		assertFalse(cell.isLabel());
		assertFalse(cell.isRoomCenter());
		assertFalse(cell.isDoorway());

		//test center cell - uses Slytherin Dungeon center cell
		cell = board.getCell(23, 10);
		room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Slytherin Dungeon");
		assertTrue(cell.getInitial() == 'S');
		assertTrue(room.getCenterCell() == cell);
		assertFalse(cell.isLabel());
		assertTrue(cell.isRoomCenter());
		assertFalse(cell.isDoorway());

		//test label cell - uses Defense Tower Label cell
		cell = board.getCell(1, 22);
		room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Defence Tower");
		assertTrue(cell.getInitial() == 'D');
		assertTrue(room.getLabelCell() == cell);
		assertTrue(cell.isLabel());
		assertFalse(cell.isRoomCenter());
		assertFalse(cell.isDoorway());

		//test walkway cell - uses a walkway that is right between Defense Tower and some unused space
		//also is on the edge of the board
		cell = board.getCell(6, 26);
		room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Walkway");
		assertTrue(cell.getInitial() == 'W');
		assertFalse(cell.isLabel());
		assertFalse(cell.isRoomCenter());
		assertFalse(cell.isDoorway());

		//test secret passage cell - uses Great Hall(F) to Gryffindor Tower(G) secret passage
		cell = board.getCell(24, 0);
		room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Great Hall");
		assertTrue(cell.getInitial() == 'F');
		assertTrue(cell.getSecretPassage() == 'G');
		assertFalse(cell.isLabel());
		assertFalse(cell.isRoomCenter());
		assertFalse(cell.isDoorway());

		//test unused cell - uses a unused cell that is nested in the side of Defense Tower
		cell = board.getCell(2, 21);
		room = board.getRoom(cell);
		assertTrue(room != null);
		assertEquals(room.getName(), "Unused");
		assertTrue(cell.getInitial() == 'X');
		assertFalse(cell.isLabel());
		assertFalse(cell.isRoomCenter());
		assertFalse(cell.isDoorway());
	}
}
