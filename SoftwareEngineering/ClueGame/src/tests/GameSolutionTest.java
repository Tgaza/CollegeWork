/* 
 * Junit test class that tests the game's card processing, i.e. checkAccusation(), disproveSuggestion() and handleSuggestion().
 * 
 * Author: Ty Gazaway
 * Date: 11/5/2024
 * 
 * */
package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import clueGame.Board;
import clueGame.Card;
import clueGame.CardType;
import clueGame.ComputerPlayer;
import clueGame.HumanPlayer;
import clueGame.Player;
import clueGame.Solution;

class GameSolutionTest {
	private static Card wrongRoom1;
	private static Card wrongPerson1;
	private static Card wrongWeapon1;
	private static Card wrongRoom2;
	private static Card wrongPerson2;
	private static Card wrongWeapon2;
	private static Solution boardAnswer;
	private static Card bRoom;
	private static Card bPerson;
	private static Card bWeapon;
	private static Board board;

	//Gets the instance and loads the game data
	//Also creates custom cards for testing
	@BeforeAll
	public static void setUp() {
		wrongRoom1 = new Card("Wrong Room1", CardType.ROOM);
		wrongPerson1 = new Card("Wrong Person1", CardType.PERSON);
		wrongWeapon1 = new Card("Wrong Weapon1", CardType.WEAPON);
		wrongRoom2 = new Card("Wrong Room2", CardType.ROOM);
		wrongPerson2 = new Card("Wrong Person2", CardType.PERSON);
		wrongWeapon2 = new Card("Wrong Weapon2", CardType.WEAPON);

		board = Board.getInstance();
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		board.initialize();
		
		boardAnswer = board.getAnswer();
		bRoom = boardAnswer.getRoom();
		bPerson = boardAnswer.getPerson();
		bWeapon = boardAnswer.getWeapon();
	}
	
	//test checkAccusation() method for functionality
	@Test
	public void testCheckAccusation() {
		//test wrong room
		assertFalse(board.checkAccusation(new Solution(wrongRoom1, bPerson, bWeapon)));
		
		//test wrong person
		assertFalse(board.checkAccusation(new Solution(bRoom, wrongPerson1, bWeapon)));
		
		//test wrong weapon
		assertFalse(board.checkAccusation(new Solution(bRoom, bPerson, wrongWeapon1)));
		
		//test correct accusation
		assertTrue(board.checkAccusation(boardAnswer));
	}
	
	//test disproveSuggestion() method for functionality
	@Test
	public void testDisproveSuggestion() {
		Player player = new ComputerPlayer("Test Player", null, 0, 0, board.getRoom('W'));
		player.updateHand(bRoom);
		player.updateHand(bPerson);
		player.updateHand(bWeapon);
		//test can't disprove
		assertEquals(player.disproveSuggestion(new Solution(wrongRoom1, wrongPerson1, wrongWeapon1)), null);
		
		//test can disprove with 1 card
		assertEquals(player.disproveSuggestion(new Solution(bRoom, wrongPerson1, wrongWeapon1)), bRoom);
		assertEquals(player.disproveSuggestion(new Solution(wrongRoom1, bPerson, wrongWeapon1)), bPerson);
		assertEquals(player.disproveSuggestion(new Solution(wrongRoom1, wrongPerson1, bWeapon)), bWeapon);
		
		//test can disprove with more than 1 cards
		int roomCount = 0;
		int personCount = 0;
		int weaponCount = 0;
		Card temp;
		for(int test = 0; test < 90; test++) {
			temp = player.disproveSuggestion(new Solution(bRoom, bPerson, bWeapon));
			switch(temp.getType()) {
			case ROOM:
				roomCount++;
				break;
			case PERSON:
				personCount++;
				break;
			case WEAPON:
				weaponCount++;
				break;
			}
		}
		//each card the can be used to disproved should appear at least once
		assertTrue(roomCount > 0);
		assertTrue(personCount > 0);
		assertTrue(weaponCount > 0);
	}
	
	//test handleSuggestion() method for functionality
	@Test
	public void testHandleSuggestion() {
		Player player0 = new ComputerPlayer("Test Player", null, 0, 0, board.getRoom('W'));
		player0.updateHand(wrongRoom1);
		player0.updateHand(wrongPerson1);
		player0.updateHand(wrongWeapon1);
		Player player1= new ComputerPlayer("Test Player", null, 0, 0, board.getRoom('W'));
		player1.updateHand(bRoom);
		player1.updateHand(wrongPerson1);
		player1.updateHand(bWeapon);
		Player player2 = new HumanPlayer("Test Player", null, 0, 0, board.getRoom('W'));
		player2.updateHand(bRoom);
		player2.updateHand(bPerson);
		player2.updateHand(bWeapon);
		ArrayList<Player> players = board.getPlayers();
		players.clear();
		players.add(player0);
		players.add(player1);
		players.add(player2);
		
		//test no one can disprove
		assertEquals(board.handleSuggestion(new Solution(wrongRoom2, wrongPerson2, wrongWeapon2), 0), null);
		
		//test suggestor can disprove
		assertEquals(board.handleSuggestion(new Solution(wrongRoom1, wrongPerson2, wrongWeapon1), 0), null);
		
		//test multiple can disprove
		assertEquals(board.handleSuggestion(new Solution(bRoom, bPerson, wrongWeapon2), 0), bRoom);
		assertEquals(board.handleSuggestion(new Solution(wrongRoom1, bPerson, wrongWeapon1), 0), bPerson);
		
		//test wrap around player can disprove
		assertEquals(board.handleSuggestion(new Solution(wrongRoom1, wrongPerson2, wrongWeapon2), 1), wrongRoom1);
	}

}
