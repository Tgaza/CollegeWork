/* 
   * Junit test class that tests the setup of the game and whether it was done correctly.
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package tests;

import static org.junit.jupiter.api.Assertions.*;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import clueGame.Board;
import clueGame.Card;
import clueGame.HumanPlayer;
import clueGame.Player;
import clueGame.Solution;

class GameSetupTests {
	private static Board board;

	// get the instance of board and load data
	@BeforeAll
	public static void setUp() {
		board = Board.getInstance();
		board.setConfigFiles("ClueLayout.csv", "ClueSetup.txt");
		board.initialize();
	}

	// Test if the people are loaded in correctly
	@Test
	public void testPeopleData() {
		Map<String, Color> peopleMap = board.getPeopleMap();
		assertEquals(peopleMap.size(), 6);
		// Tests two things with each assert
		// Does the correct name exist in the map and is the correct color associated
		assertEquals(Color.decode("#CC3300"), peopleMap.get("Harry Potter"));
		assertEquals(Color.decode("#FF9933"), peopleMap.get("Ron Weasley"));
		assertEquals(Color.decode("#006600"), peopleMap.get("Draco Malfoy"));
		assertEquals(Color.decode("#663300"), peopleMap.get("Hermione Granger"));
		assertEquals(Color.decode("#0000CC"), peopleMap.get("Luna Lovegood"));
		assertEquals(Color.decode("#F8F200"), peopleMap.get("Cedric Diggory"));
	}

	// Test if the weapons are loaded in correctly
	@Test
	public void testWeaponData() {
		Set<String> weapons = board.getWeapons();
		assertEquals(weapons.size(), 6);
		assertTrue(weapons.contains("Elder Wand"));
		assertTrue(weapons.contains("Sword of Gryffindor"));
		assertTrue(weapons.contains("Hagrid's Crossbow"));
		assertTrue(weapons.contains("Basilisk Venom"));
		assertTrue(weapons.contains("Centaur Bow"));
		assertTrue(weapons.contains("Silver Dagger"));
	}

	// Test if the people are loaded in correctly
	@Test
	public void testPlayerData() {
		ArrayList<Player> players = board.getPlayers();
		assertEquals(players.size(), 6);
		boolean humanFound = false;
		// Loop through all players
		for (Player player : players) {
			// Check which character this player is and if their data is correct
			switch (player.getName()) {
			case "Harry Potter":
				assertEquals(Color.decode("#CC3300"), player.getColor());
				break;
			case "Ron Weasley":
				assertEquals(Color.decode("#FF9933"), player.getColor());
				break;
			case "Draco Malfoy":
				assertEquals(Color.decode("#006600"), player.getColor());
				break;
			case "Hermione Granger":
				assertEquals(Color.decode("#663300"), player.getColor());
				break;
			case "Luna Lovegood":
				assertEquals(Color.decode("#0000CC"), player.getColor());
				break;
			case "Cedric Diggory":
				assertEquals(Color.decode("#F8F200"), player.getColor());
				break;
			default:
				// Only reaches this point if Player's character name does not match any above
				fail("Improperly Named Player");
			}
			// Check if Player is human or not
			if (player instanceof HumanPlayer && !humanFound) {
				humanFound = true;
			} else if (player instanceof HumanPlayer && humanFound) {
				fail("More than one Human Player");
			}
		}
		// Make sure a human player was found
		assertTrue(humanFound);
	}

	// Test if the deck is properly loaded
	@Test
	public void testCardDeck() {
		ArrayList<Card> deck = board.getDeck();
		assertEquals(deck.size(), 21);
		int roomCount = 0, peopleCount = 0, weaponCount = 0;
		for (Card card : deck) {
			switch (card.getType()) {
			case ROOM:
				roomCount++;
				break;
			case PERSON:
				peopleCount++;
				break;
			case WEAPON:
				weaponCount++;
				break;
			}
		}
		assertEquals(roomCount + peopleCount + weaponCount, 21);
		assertEquals(roomCount, 9);
		assertEquals(peopleCount, 6);
		assertEquals(weaponCount, 6);
	}

	// Test if the cards were properly dealt out and answer created
	@Test
	public void testDealCards() {
		ArrayList<Player> players = board.getPlayers();
		Set<Card> dealtCards = new HashSet<>();
		int maxCardsPerPlayer = (int) Math.ceil((21.0-3.0)/6.0);
		for(Player player: players) {
			assertTrue(player.getHand().size() <= maxCardsPerPlayer);
			dealtCards.addAll(player.getHand());
		}
		assertEquals(21-3, dealtCards.size());
		Solution answer = board.getAnswer();
		assertNotEquals(answer.getRoom().getType(), answer.getPerson().getType());
		assertNotEquals(answer.getRoom().getType(), answer.getWeapon().getType());
		assertNotEquals(answer.getWeapon().getType(), answer.getPerson().getType());
	}

}
