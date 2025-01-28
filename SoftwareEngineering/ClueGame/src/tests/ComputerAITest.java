/* 
 * Junit test class that tests the computer player's decision making ability, i.e. selectTargets() and createSuggestion().
 * 
 * Author: Ty Gazaway
 * Date: 11/5/2024
 * 
 * */
package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import clueGame.Board;
import clueGame.BoardCell;
import clueGame.Card;
import clueGame.CardType;
import clueGame.Solution;
import clueGame.ComputerPlayer;
import clueGame.Player;

public class ComputerAITest {
	private static Card testRoom1;
	private static Card testPerson1;
	private static Card testWeapon1;
	private static Card testRoom2;
	private static Card testPerson2;
	private static Card testWeapon2;
	private static Card testRoom3;
	private static Card testPerson3;
	private static Card testWeapon3;
	private static Card defenceTowerCard;
	private static ArrayList<Card> deck;
	private static ComputerPlayer testPlayer;
	private static Board board;
	
	@BeforeAll
	public static void setUp() {
		testRoom1 = new Card("test Room1", CardType.ROOM);
		testPerson1 = new Card("test Person1", CardType.PERSON);
		testWeapon1 = new Card("test Weapon1", CardType.WEAPON);
		testRoom2 = new Card("test Room2", CardType.ROOM);
		testPerson2 = new Card("test Person2", CardType.PERSON);
		testWeapon2 = new Card("test Weapon2", CardType.WEAPON);
		testRoom3 = new Card("test Room3", CardType.ROOM);
		testPerson3 = new Card("test Person3", CardType.PERSON);
		testWeapon3 = new Card("test Weapon3", CardType.WEAPON);
		defenceTowerCard = new Card("Defence Tower", CardType.ROOM);

		board = Board.getInstance();
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		board.initialize();
		
		deck = board.getDeck();
		deck.clear();
		deck.add(testRoom1);
		deck.add(testRoom2);
		deck.add(testRoom3);
		deck.add(testPerson1);
		deck.add(testPerson2);
		deck.add(testPerson3);
		deck.add(testWeapon1);
		deck.add(testWeapon2);
		deck.add(testWeapon3);
		deck.add(defenceTowerCard);
		
		testPlayer = new ComputerPlayer("testPlayer", Color.black, 2, 24, board.getRoom('D'));
	}
	
	@Test
	public void testCreateSuggestion() {
		//Setup so player has room1, person1, and weapon1 in hand
		// and person2 in seen
		//Also set player in the defence tower
		//Unseen Cards include: room2, room3, person3, weapon2, weapon3
		testPlayer.setLocation(2, 24, board.getRoom('D'));
		testPlayer.updateHand(testRoom1);
		testPlayer.updateHand(testPerson1);
		testPlayer.updateHand(testWeapon1);
		testPlayer.updateSeen(testPerson2);
		testPlayer.updateRoom(board);
		
		Solution suggestion;
		int defenceTCount = 0;
		int person3Count = 0;
		int weapon1Count = 0;
		int weapon2Count = 0;
		int weapon3Count = 0;
		
		//Loop through and count all appearances of cards that should or shouldn't appear
		for(int i = 0;i < 10; i++) {
			suggestion = testPlayer.createSuggestion(deck);
			if(suggestion.getWeapon().equals(testWeapon1)) {
				weapon1Count++;
			}
			if(suggestion.getWeapon().equals(testWeapon2)) {
				weapon2Count++;
			}
			if(suggestion.getWeapon().equals(testWeapon3)) {
				weapon3Count++;
			}
			if(suggestion.getRoom().equals(defenceTowerCard)) {
				defenceTCount++;
			}
			if(suggestion.getPerson().equals(testPerson3)) {
				person3Count++;
			}
		}
		
		//make sure defenceTowerCard and person3 appeared every time
		assertEquals(10, defenceTCount);
		assertEquals(10, person3Count);
		assertEquals("Defence Tower" ,board.getRoom(board.getCell(2, 24)).getName());
		
		//make sure weapon1 never appeared
		assertEquals(0, weapon1Count);
		
		//make sure weapon2 and weapon3 both appeared at least once
		assertTrue(weapon2Count >= 1);
		assertTrue(weapon3Count >= 1);
	}
	
	@Test
	public void testSelectTarget() {
		//Place player inbetween gryffindor and defense tower doors
		testPlayer.setLocation(6, 19, board.getRoom('W'));
		//add defense tower to seen cards
		testPlayer.updateSeen(new Card("Defence Tower", CardType.ROOM));
		board.calcTargets(board.getCell(6, 19), 4);
		//test to make sure gryffindor tower is selected
		assertEquals(board.getCell(3, 16),testPlayer.selectTarget(board.getTargets(), board));
		
		//Place player away from rooms with a roll that includes no doors
		testPlayer.setLocation(12, 9, board.getRoom('W'));
		board.calcTargets(board.getCell(12, 9), 3);
		Set<BoardCell> targets = board.getTargets();
		Set<BoardCell> chosenTargets = new HashSet<>();
		
		for(int i = 0; i < 100; i++) {
			chosenTargets.add(testPlayer.selectTarget(targets, board));
		}
		//make sure all potential targets show at least once
		assertTrue(targets.equals(chosenTargets));
	}

}
