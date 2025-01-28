/* Junit test class for testing the experimental TestBoard and TestBoardCell Classes
 * 
 * Author: Ty Gazaway
 * Date: 10/11/2024
 * 
 * */

package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Set;

import org.junit.Assert;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import experiment.TestBoard;
import experiment.TestBoardCell;

class BoardTestsExp {
	private TestBoard board;
	
	@BeforeEach
	public void setup() {
		/* Board of size 4x4
		 * X|X|X|X
		 * X|X|X|X
		 * X|X|X|X
		 * X|X|X|X
		*/
		board = new TestBoard();
	}
	
	@Test
	public void testAdjacency() {
		//To left corner
		/*
		 * P|A|X|X
		 * A|X|X|X
		 * X|X|X|X
		 * X|X|X|X
		*/
		TestBoardCell cell = board.getCell(0, 0);
		Set<TestBoardCell> testList = cell.getAdjList();
		Assert.assertTrue(testList.contains(board.getCell(1, 0)));
		Assert.assertTrue(testList.contains(board.getCell(0, 1)));
		Assert.assertEquals(2, testList.size());

		//To right corner
		/*
		 * X|X|A|P
		 * X|X|X|A
		 * X|X|X|X
		 * X|X|X|X
		*/
		cell = board.getCell(0, 3);
		testList = cell.getAdjList();
		Assert.assertTrue(testList.contains(board.getCell(1, 3)));
		Assert.assertTrue(testList.contains(board.getCell(0, 2)));
		Assert.assertEquals(2, testList.size());

		//Bottom left corner
		/*
		 * X|X|X|X
		 * X|X|X|X
		 * A|X|X|X
		 * P|A|X|X
		*/
		cell = board.getCell(3, 0);
		testList = cell.getAdjList();
		Assert.assertTrue(testList.contains(board.getCell(2, 0)));
		Assert.assertTrue(testList.contains(board.getCell(3, 1)));
		Assert.assertEquals(2, testList.size());

		//Bottom right corner
		/*
		 * X|X|X|X
		 * X|X|X|X
		 * X|X|X|A
		 * X|X|A|P
		*/
		cell = board.getCell(3, 3);
		testList = cell.getAdjList();
		Assert.assertTrue(testList.contains(board.getCell(3, 2)));
		Assert.assertTrue(testList.contains(board.getCell(2, 3)));
		Assert.assertEquals(2, testList.size());
		
		//Middle
		/*
		 * X|X|X|X
		 * X|X|A|X
		 * X|A|P|A
		 * X|X|A|X
		*/
		cell = board.getCell(2, 2);
		testList = cell.getAdjList();
		Assert.assertTrue(testList.contains(board.getCell(1, 2)));
		Assert.assertTrue(testList.contains(board.getCell(2, 1)));
		Assert.assertTrue(testList.contains(board.getCell(2, 3)));
		Assert.assertTrue(testList.contains(board.getCell(3, 2)));
		Assert.assertEquals(4, testList.size());
	}
	
	@Test
	public void testTargetsNormal() {
		//To left corner roll 1
		/*
		 * P|T|X|X
		 * T|X|X|X
		 * X|X|X|X
		 * X|X|X|X
		*/
		TestBoardCell cell = board.getCell(0, 0);
		board.calcTargets(cell,  1);
		Set<TestBoardCell> targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 0)));
		Assert.assertEquals(2, targets.size());
		
		//To left corner roll 2
		/*
		 * P|X|T|X
		 * X|T|X|X
		 * T|X|X|X
		 * X|X|X|X
		*/
		cell = board.getCell(0, 0);
		board.calcTargets(cell,  2);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertEquals(3, targets.size());
		
		//To left corner roll 3
		/*
		 * P|T|X|T
		 * T|X|T|X
		 * X|T|X|X
		 * T|X|X|X
		*/
		cell = board.getCell(0, 0);
		board.calcTargets(cell,  3);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(3, 0)));
		Assert.assertTrue(targets.contains(board.getCell(2, 1)));
		Assert.assertTrue(targets.contains(board.getCell(0, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(0, 3)));
		Assert.assertTrue(targets.contains(board.getCell(1, 0)));
		Assert.assertEquals(6, targets.size());
		
		//To left corner roll 4
		/*
		 * P|X|T|X
		 * X|T|X|T
		 * T|X|T|X
		 * X|T|X|X
		*/
		cell = board.getCell(0, 0);
		board.calcTargets(cell,  4);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 3)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(2, 2)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertEquals(6, targets.size());
		
		//Middle roll 1
		/*
		 * X|X|X|X
		 * X|X|T|X
		 * X|T|P|T
		 * X|X|T|X
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  1);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(2, 1)));
		Assert.assertTrue(targets.contains(board.getCell(2, 3)));
		Assert.assertTrue(targets.contains(board.getCell(3, 2)));
		Assert.assertEquals(4, targets.size());
		
		//Middle roll 2
		/*
		 * X|X|T|X
		 * X|T|X|T
		 * T|X|P|X
		 * X|T|X|T
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  2);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 3)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertTrue(targets.contains(board.getCell(3, 3)));
		Assert.assertEquals(6, targets.size());
		
		//Middle roll 3
		/*
		 * X|T|X|T
		 * T|X|T|X
		 * X|T|P|T
		 * T|X|T|X
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  3);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 1)));
		Assert.assertTrue(targets.contains(board.getCell(0, 3)));
		Assert.assertTrue(targets.contains(board.getCell(1, 0)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(2, 1)));
		Assert.assertTrue(targets.contains(board.getCell(2, 3)));
		Assert.assertTrue(targets.contains(board.getCell(3, 0)));
		Assert.assertTrue(targets.contains(board.getCell(3, 2)));
		Assert.assertEquals(8, targets.size());
		
		//Middle roll 4
		/*
		 * T|X|T|X
		 * X|T|X|T
		 * T|X|P|X
		 * X|T|X|T
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  4);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 0)));
		Assert.assertTrue(targets.contains(board.getCell(0, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 3)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertTrue(targets.contains(board.getCell(3, 3)));
		Assert.assertEquals(7, targets.size());

	}
	
	@Test
	public void testTargetsMixed() {
		//Occupied/Room Locations no Player
		/*
		 * X|X|O|X
		 * X|X|R|X
		 * X|X|X|X
		 * X|X|X|X
		*/
		board.getCell(0, 2).setIsOccupied(true);
		board.getCell(1, 2).setIsRoom(true);
		
		//To left corner roll 2
		/*
		 * P|X|O|X
		 * X|T|R|X
		 * T|X|X|X
		 * X|X|X|X
		*/
		TestBoardCell cell = board.getCell(0, 0);
		board.calcTargets(cell,  2);
		Set<TestBoardCell> targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertEquals(2, targets.size());
		
		//To left corner roll 3
		/*
		 * P|T|O|X
		 * T|X|T-R|X
		 * X|T|X|X
		 * T|X|X|X
		*/
		cell = board.getCell(0, 0);
		board.calcTargets(cell,  3);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 0)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(2, 1)));
		Assert.assertTrue(targets.contains(board.getCell(3, 0)));
		Assert.assertEquals(5, targets.size());
		
		//To left corner roll 4
		/*
		 * P|X|O|X
		 * X|T|T-R|X
		 * T|X|T|X
		 * X|T|X|X
		*/
		cell = board.getCell(0, 0);
		board.calcTargets(cell,  4);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(2, 2)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertEquals(5, targets.size());
		
		//Middle roll 1
		/*
		 * X|X|O|X
		 * X|X|T-R|X
		 * X|T|P|T
		 * X|X|T|X
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  1);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(2, 1)));
		Assert.assertTrue(targets.contains(board.getCell(2, 3)));
		Assert.assertTrue(targets.contains(board.getCell(3, 2)));
		Assert.assertEquals(4, targets.size());
		
		//Middle roll 2
		/*
		 * X|X|O|X
		 * X|T|T-R|T
		 * T|X|P|X
		 * X|T|X|T
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  2);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 3)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertTrue(targets.contains(board.getCell(3, 3)));
		Assert.assertEquals(6, targets.size());
		
		//Middle roll 4
		/*
		 * T|X|O|X
		 * X|T|T-R|T
		 * T|X|P|X
		 * X|T|X|T
		*/
		cell = board.getCell(2, 2);
		board.calcTargets(cell,  4);
		targets = board.getTargets();
		Assert.assertTrue(targets.contains(board.getCell(0, 0)));
		Assert.assertTrue(targets.contains(board.getCell(1, 1)));
		Assert.assertTrue(targets.contains(board.getCell(1, 2)));
		Assert.assertTrue(targets.contains(board.getCell(1, 3)));
		Assert.assertTrue(targets.contains(board.getCell(2, 0)));
		Assert.assertTrue(targets.contains(board.getCell(3, 1)));
		Assert.assertTrue(targets.contains(board.getCell(3, 3)));
		Assert.assertEquals(7, targets.size());

	}

}
