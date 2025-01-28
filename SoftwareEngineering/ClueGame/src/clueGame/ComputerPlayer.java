/* 
 * ComputerPlaer class adds the necessary implementation for non player controlled character to interact with the game.
 * 
 * Author: Ty Gazaway
 * Date: 11/3/2024
 * 
 * */
package clueGame;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class ComputerPlayer extends Player{

	//VVVVV Constructors VVVVV
	public ComputerPlayer(String name, Color color, int row, int col, Room curRoom) {
		super(name, color, row, col, curRoom);
	}

	//VVVVV Functionality Methods VVVVV
	//creates a suggestion from unseen cards and given room
	public Solution createSuggestion(ArrayList<Card> deck) {
		//setup suggestion and add room card
		Solution suggestion = new Solution();
		suggestion.addCard(new Card(this.getRoom().getName(), CardType.ROOM));
		
		//figure out unseen cards
		ArrayList<Card> unseen = new ArrayList<>(deck);
		unseen.removeAll(this.getSeen());
		
		//shuffle unseen cards and grab first person and weapon found
		Collections.shuffle(unseen);
		boolean foundPerson = false;
		boolean foundWeapon = false;
		for(Card curCard: unseen) {
			if(curCard.getType() == CardType.PERSON && !foundPerson) {
				suggestion.addCard(curCard);
				foundPerson = true;
			}else if(curCard.getType() == CardType.WEAPON && !foundWeapon) {
				suggestion.addCard(curCard);
				foundWeapon = true;
			}else if(foundPerson && foundWeapon) 
				break;
		}
		return suggestion;
	}
	
	//takes in a calculated target list and determines what target the computer player should choose
	public BoardCell selectTarget(Set<BoardCell> targets, Board board) {
		ArrayList<BoardCell> validTargets = new ArrayList<BoardCell>();
		//loops through target list checking for unseen rooms
		for(BoardCell target: targets) {
			Room curRoom = board.getRoom(target);
			if(!curRoom.isNotRealRoom() && !this.getSeen().contains(new Card(curRoom.getName(), CardType.ROOM))) {
				validTargets.add(target);
			}
		}
		//if no unseen rooms all targets are valid
		if(validTargets.size() == 0) {
			validTargets.addAll(targets);
		}
		//shuffle list randomly and return first element
		Collections.shuffle(validTargets);
		return validTargets.get(0);
	}
}
