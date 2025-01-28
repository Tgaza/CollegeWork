/* 
 * Junit test class that tests Board's capability to load configuration files properly
 * 
 * Author: Ty Gazaway
 * Date: 10/12/2024
 * Sources: ExceptionTests306.java
 * 
 * */
package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.io.FileNotFoundException;

import org.junit.jupiter.api.Test;

import clueGame.BadConfigFormatException;
import clueGame.Board;

class ExceptionsTests {

		// Test that an exception is thrown for a layout file that does not
		// have the same number of columns for each row
		@Test
		public void testBadColumns() throws BadConfigFormatException, FileNotFoundException {
			assertThrows(BadConfigFormatException.class, () -> {
				// Note that we are using a LOCAL Board variable, because each
				// test will load different files
				Board board = Board.getInstance();
				board.setConfigFiles("ClueLayoutBadCols.csv", "ClueSetup.txt");
				// Instead of initialize, we call the two load functions directly.
				// This is necessary because initialize contains a try-catch.
				board.loadSetupConfig();
				// This one should throw an exception
				board.loadLayoutConfig();
			});
		}

		// Test that an exception is thrown for a Layout file that specifies
		// a room that is not in the legend. 
		@Test
		public void testBadRoom() throws BadConfigFormatException, FileNotFoundException {
			assertThrows(BadConfigFormatException.class, () -> {
				Board board = Board.getInstance();
				board.setConfigFiles("ClueLayoutBadRoom.csv", "ClueSetup.txt");
				board.loadSetupConfig();
				board.loadLayoutConfig();
			});
		}

		// Test that an exception is thrown for a bad format Setup file
		@Test
		public void testBadRoomFormat() throws BadConfigFormatException, FileNotFoundException {
			//test if code catches a bad category
			assertThrows(BadConfigFormatException.class, () -> {
				Board board = Board.getInstance();
				board.setConfigFiles("ClueLayout.csv", "ClueSetupBadCategory.txt");
				board.loadSetupConfig();
				board.loadLayoutConfig();
			});

			//test if code catches a bad initial
			assertThrows(BadConfigFormatException.class, () -> {
				Board board = Board.getInstance();
				board.setConfigFiles("ClueLayout.csv", "ClueSetupBadInitial.txt");
				board.loadSetupConfig();
				board.loadLayoutConfig();
			});

			//test if code catches a improper column count
			assertThrows(BadConfigFormatException.class, () -> {
				Board board = Board.getInstance();
				board.setConfigFiles("ClueLayout.csv", "ClueSetupBadCols.txt");
				board.loadSetupConfig();
				board.loadLayoutConfig();
			});
		}

}
