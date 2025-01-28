/* 
 * Junit test class that tests adjacency lists for cells and calculated targets with various locations and rolls
 * 
 * Author: Ty Gazaway
 * Date: 10/14/2024
 * 
 * */
package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Set;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import clueGame.Board;
import clueGame.BoardCell;

class BoardAdjTargetTest {
	
	private static Board board;
	
	@BeforeAll
	public static void set() {
		board = Board.getInstance();
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		board.initialize();
	}
	
	//Tests adjacencies from various room centers and a non center
	@Test
	public void testAdjacenciesRooms() {
		//Test adjList for Gryffindor Tower room center with 1 door and a secret passage
		Set<BoardCell> testList = board.getAdjList(3, 16);
		assertEquals(2, testList.size());
		assertTrue(testList.contains(board.getCell(6, 16)));
		assertTrue(testList.contains(board.getCell(19, 3)));

		//Test adjList for Great Hall room center with 2 doors and a secret passage
		testList = board.getAdjList(19, 3);
		assertEquals(3, testList.size());
		assertTrue(testList.contains(board.getCell(3, 16)));
		assertTrue(testList.contains(board.getCell(11, 3)));
		assertTrue(testList.contains(board.getCell(19, 7)));

		//Test adjList for Transformation court room center with 1 door and no secret passage
		testList = board.getAdjList(13, 22);
		assertEquals(1, testList.size());
		assertTrue(testList.contains(board.getCell(13, 19)));

		//Test adjList for a room cell that is not the center
		testList = board.getAdjList(5, 17);
		assertEquals(0, testList.size());
	}

	//Tests adjacencies from different doorways facing different directions
	@Test
	public void testAdjacencyDoor() {
		//Test adjList for Defense Tower doorway that opens up
		Set<BoardCell> testList = board.getAdjList(5, 22);
		assertEquals(3, testList.size());
		assertTrue(testList.contains(board.getCell(5, 21)));
		assertTrue(testList.contains(board.getCell(6, 22)));
		assertTrue(testList.contains(board.getCell(2, 24)));

		//Test adjList for Great Hall doorway that opens left
		testList = board.getAdjList(19, 7);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCell(19, 3)));
		assertTrue(testList.contains(board.getCell(18, 7)));
		assertTrue(testList.contains(board.getCell(20, 7)));
		assertTrue(testList.contains(board.getCell(19, 8)));

		//Test adjList for Slytherin Dungeon doorway that opens right
		testList = board.getAdjList(25, 8);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCell(25, 7)));
		assertTrue(testList.contains(board.getCell(24, 8)));
		assertTrue(testList.contains(board.getCell(26, 8)));
		assertTrue(testList.contains(board.getCell(23, 10)));
	}

	//Tests adjacencies in the walkway at various points
	@Test
	public void testAdjacencyWalkways() {
		//Test adjList for walkway on right edge with only an available walkway to the left
		Set<BoardCell> testList = board.getAdjList(10, 26);
		assertEquals(1, testList.size());
		assertTrue(testList.contains(board.getCell(10, 25)));

		//Test adjList for walkway on top edge with only 2 available spaces
		testList = board.getAdjList(0, 10);
		assertEquals(2, testList.size());
		assertTrue(testList.contains(board.getCell(0, 9)));
		assertTrue(testList.contains(board.getCell(1, 10)));

		//Test adjList for walkway on left edge with only an available walkway to the right
		testList = board.getAdjList(11, 0);
		assertEquals(1, testList.size());
		assertTrue(testList.contains(board.getCell(11, 1)));

		//Test adjList for walkway on bottom edge with only 2 available spaces
		testList = board.getAdjList(26, 7);
		assertEquals(2, testList.size());
		assertTrue(testList.contains(board.getCell(26, 8)));
		assertTrue(testList.contains(board.getCell(25, 7)));
		
		//Test adjList for walkway with all four spaces around available but 2 are doors
		testList = board.getAdjList(5, 21);
		assertEquals(4, testList.size());
		assertTrue(testList.contains(board.getCell(5, 22)));
		assertTrue(testList.contains(board.getCell(5, 20)));
		assertTrue(testList.contains(board.getCell(4, 21)));
		assertTrue(testList.contains(board.getCell(6, 21)));
	}

	//Tests calculated targets from the Defense Tower room center which has a secret passage
	@Test
	public void testTargetsInDefenseTower() {
		//Test a roll of 1
		board.calcTargets(board.getCell(2, 24), 1);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(3, targets.size());
		assertTrue(targets.contains(board.getCell(4, 21)));
		assertTrue(targets.contains(board.getCell(5, 22)));
		assertTrue(targets.contains(board.getCell(23, 23)));

		//Test a roll of 3
		board.calcTargets(board.getCell(2, 24), 3);
		targets = board.getTargets();
		assertEquals(7, targets.size());
		assertTrue(targets.contains(board.getCell(3, 20)));
		assertTrue(targets.contains(board.getCell(4, 21)));
		assertTrue(targets.contains(board.getCell(5, 20)));
		assertTrue(targets.contains(board.getCell(5, 22)));
		assertTrue(targets.contains(board.getCell(6, 21)));
		assertTrue(targets.contains(board.getCell(6, 23)));
		assertTrue(targets.contains(board.getCell(23, 23)));

		//Test a roll of 4
		board.calcTargets(board.getCell(2, 24), 4);
		targets = board.getTargets();
		assertEquals(7, targets.size());
		assertTrue(targets.contains(board.getCell(2, 20)));
		assertTrue(targets.contains(board.getCell(4, 20)));
		assertTrue(targets.contains(board.getCell(5, 21)));
		assertTrue(targets.contains(board.getCell(6, 20)));
		assertTrue(targets.contains(board.getCell(6, 22)));
		assertTrue(targets.contains(board.getCell(6, 24)));
		assertTrue(targets.contains(board.getCell(23, 23)));
	}

	//Tests calculated targets from the Ravenclaw Tower room center which has no secret passage
	@Test
	public void testTargetsInRavenclawTower() {
		//Test a roll of 1
		board.calcTargets(board.getCell(17, 17), 1);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(2, targets.size());
		assertTrue(targets.contains(board.getCell(16, 15)));
		assertTrue(targets.contains(board.getCell(21, 17)));

		//Test a roll of 3
		board.calcTargets(board.getCell(17, 17), 3);
		targets = board.getTargets();
		assertEquals(8, targets.size());
		assertTrue(targets.contains(board.getCell(15, 16)));
		assertTrue(targets.contains(board.getCell(17, 14)));
		assertTrue(targets.contains(board.getCell(21, 15)));
		assertTrue(targets.contains(board.getCell(22, 18)));

		//Test a roll of 4
		board.calcTargets(board.getCell(17, 17), 4);
		targets = board.getTargets();
		assertEquals(15, targets.size());
		assertTrue(targets.contains(board.getCell(16, 14)));
		assertTrue(targets.contains(board.getCell(18, 14)));
		assertTrue(targets.contains(board.getCell(21, 14)));
		assertTrue(targets.contains(board.getCell(22, 17)));
	}

	//Tests calculated targets from the door opens to the right, into the Defense Tower room
	@Test
	public void testTargetsAtDoor() {
		//Test a roll of 1
		board.calcTargets(board.getCell(4, 21), 1);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(3, targets.size());
		assertTrue(targets.contains(board.getCell(4, 20)));
		assertTrue(targets.contains(board.getCell(5, 21)));
		assertTrue(targets.contains(board.getCell(2, 24)));

		//Test a roll of 3
		board.calcTargets(board.getCell(4, 21), 3);
		targets = board.getTargets();
		assertEquals(6, targets.size());
		assertTrue(targets.contains(board.getCell(2, 20)));
		assertTrue(targets.contains(board.getCell(4, 20)));
		assertTrue(targets.contains(board.getCell(5, 21)));
		assertTrue(targets.contains(board.getCell(6, 20)));
		assertTrue(targets.contains(board.getCell(6, 22)));
		assertTrue(targets.contains(board.getCell(2, 24)));

		//Test a roll of 4
		board.calcTargets(board.getCell(4, 21), 4);
		targets = board.getTargets();
		assertEquals(8, targets.size());
		assertTrue(targets.contains(board.getCell(1, 20)));
		assertTrue(targets.contains(board.getCell(3, 20)));
		assertTrue(targets.contains(board.getCell(5, 20)));
		assertTrue(targets.contains(board.getCell(5, 22)));
		assertTrue(targets.contains(board.getCell(6, 19)));
		assertTrue(targets.contains(board.getCell(6, 21)));
		assertTrue(targets.contains(board.getCell(6, 23)));
		assertTrue(targets.contains(board.getCell(2, 24)));
	}

	//Tests calculated targets from the walkway sandwiched between Hufflepuff Tower and the Great Hall
	@Test
	public void testTargetsInWalkway1() {
		//Test a roll of 1
		board.calcTargets(board.getCell(11, 2), 1);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(2, targets.size());
		assertTrue(targets.contains(board.getCell(11, 1)));
		assertTrue(targets.contains(board.getCell(11, 3)));

		//Test a roll of 1
		board.calcTargets(board.getCell(11, 2), 3);
		targets = board.getTargets();
		assertEquals(2, targets.size());
		assertTrue(targets.contains(board.getCell(11, 5)));
		assertTrue(targets.contains(board.getCell(19, 3)));

		//Test a roll of 1
		board.calcTargets(board.getCell(11, 2), 4);
		targets = board.getTargets();
		assertEquals(2, targets.size());
		assertTrue(targets.contains(board.getCell(11, 6)));
		assertTrue(targets.contains(board.getCell(19, 3)));
	}

	//Tests calculated targets from a walkway that all four sides available to move in for the first step
	@Test
	public void testTargetsInWalkway2() {
		//Test a roll of 1
		board.calcTargets(board.getCell(16, 14), 1);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(4, targets.size());
		assertTrue(targets.contains(board.getCell(15, 14)));
		assertTrue(targets.contains(board.getCell(16, 13)));
		assertTrue(targets.contains(board.getCell(16, 15)));
		assertTrue(targets.contains(board.getCell(17, 14)));

		//Test a roll of 1
		board.calcTargets(board.getCell(16, 14), 3);
		targets = board.getTargets();
		assertEquals(8, targets.size());
		assertTrue(targets.contains(board.getCell(15, 14)));
		assertTrue(targets.contains(board.getCell(15, 16)));
		assertTrue(targets.contains(board.getCell(16, 13)));
		assertTrue(targets.contains(board.getCell(16, 15)));
		assertTrue(targets.contains(board.getCell(17, 14)));
		assertTrue(targets.contains(board.getCell(18, 13)));
		assertTrue(targets.contains(board.getCell(17, 17)));
		assertTrue(targets.contains(board.getCell(19, 14)));

		//Test a roll of 1
		board.calcTargets(board.getCell(16, 14), 4);
		targets = board.getTargets();
		assertEquals(8, targets.size());
		assertTrue(targets.contains(board.getCell(14, 16)));
		assertTrue(targets.contains(board.getCell(15, 17)));
		assertTrue(targets.contains(board.getCell(17, 13)));
		assertTrue(targets.contains(board.getCell(18, 12)));
		assertTrue(targets.contains(board.getCell(18, 14)));
		assertTrue(targets.contains(board.getCell(17, 17)));
		assertTrue(targets.contains(board.getCell(19, 13)));
		assertTrue(targets.contains(board.getCell(20, 14)));
	}

	//Tests calculated targets from various spots where occupied cells are involved
	@Test
	public void testTargetsOccupied() {
		//Tests a roll of 4 with an occupied cell 2 down from the initial
		board.getCell(18, 14).setOccupied(true);
		board.calcTargets(board.getCell(16, 14), 4);
		board.getCell(18, 14).setOccupied(false);
		Set<BoardCell> targets = board.getTargets();
		assertEquals(5, targets.size());
		assertTrue(targets.contains(board.getCell(14, 16)));
		assertTrue(targets.contains(board.getCell(15, 17)));
		assertTrue(targets.contains(board.getCell(18, 12)));
		assertTrue(targets.contains(board.getCell(17, 17)));
		assertTrue(targets.contains(board.getCell(19, 13)));
		
		//Tests a roll of 1 from a doorway with an occupied room center
		//which should not impede movement
		board.getCell(4, 20).setOccupied(true);
		board.getCell(2, 24).setOccupied(true);
		board.calcTargets(board.getCell(4, 21), 1);
		board.getCell(4, 20).setOccupied(false);
		board.getCell(2, 24).setOccupied(false);
		targets = board.getTargets();
		assertEquals(2, targets.size());
		assertTrue(targets.contains(board.getCell(5, 21)));
		assertTrue(targets.contains(board.getCell(2, 24)));
		
		//Tests a roll of 3 from a room center where one doorway is blocked
		board.getCell(23, 20).setOccupied(true);
		board.calcTargets(board.getCell(23, 23), 3);
		board.getCell(23, 20).setOccupied(false);
		targets = board.getTargets();
		assertEquals(6, targets.size());
		assertTrue(targets.contains(board.getCell(17, 24)));
		assertTrue(targets.contains(board.getCell(18, 23)));
		assertTrue(targets.contains(board.getCell(18, 25)));
		assertTrue(targets.contains(board.getCell(19, 22)));
		assertTrue(targets.contains(board.getCell(19, 26)));
	}
}
