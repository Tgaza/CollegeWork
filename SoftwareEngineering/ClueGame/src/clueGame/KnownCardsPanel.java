/*
 * KnownCardsPanel is a child of JPanel and displays all the cards that are known to the player
 * Author: Ty Gazaway
 * 
 * */
package clueGame;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

public class KnownCardsPanel extends JPanel{
	// VVVVV Attributes VVVVV
	//inHandPanel items
	private JPanel inHandPanel;
	private JLabel peopleInHandLabel;
	private JLabel weaponsInHandLabel;
	private JLabel roomsInHandLabel;
	private JPanel peopleInHandPanel;
	private JPanel weaponsInHandPanel;
	private JPanel roomsInHandPanel;
	//seenPanel items
	private JPanel seenPanel;
	private JLabel peopleSeenLabel;
	private JLabel weaponsSeenLabel;
	private JLabel roomsSeenLabel;
	private JPanel peopleSeenPanel;
	private JPanel weaponsSeenPanel;
	private JPanel roomsSeenPanel;
	//Constants
	private static final int MIN_WIDTH = 100;
	private static final int MIN_HEIGHT = 10;

	// VVVVV Constructors VVVVV
	// main constructor
	public KnownCardsPanel() {
		// Initialize items
		//inHandPanel
		this.inHandPanel = new JPanel();
		this.peopleInHandPanel = new JPanel(new GridLayout(0, 1));
		this.weaponsInHandPanel = new JPanel(new GridLayout(0, 1));
		this.roomsInHandPanel = new JPanel(new GridLayout(0, 1));
		this.peopleInHandLabel = new JLabel("people:");
		this.weaponsInHandLabel = new JLabel("weapons:");
		this.roomsInHandLabel = new JLabel("rooms:");
		//seenPanel
		this.seenPanel = new JPanel();
		this.peopleSeenPanel = new JPanel(new GridLayout(0, 1));
		this.weaponsSeenPanel = new JPanel(new GridLayout(0, 1));
		this.roomsSeenPanel = new JPanel(new GridLayout(0, 1));
		this.peopleSeenLabel = new JLabel("people:");
		this.weaponsSeenLabel = new JLabel("weapons:");
		this.roomsSeenLabel = new JLabel("rooms:");

		setup();
	}

	// VVVVV private helper methods VVVVV
	private void setup() {
		// configure CardsPanel
		this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		this.inHandPanel.setLayout(new BoxLayout(inHandPanel, BoxLayout.Y_AXIS));
		this.seenPanel.setLayout(new BoxLayout(seenPanel, BoxLayout.Y_AXIS));
		
		this.add(inHandPanel);
		this.add(seenPanel);
		
		//add items to inHandPanel
		this.inHandPanel.add(peopleInHandLabel);
		this.inHandPanel.add(peopleInHandPanel);
		this.inHandPanel.add(weaponsInHandLabel);
		this.inHandPanel.add(weaponsInHandPanel);
		this.inHandPanel.add(roomsInHandLabel);
		this.inHandPanel.add(roomsInHandPanel);
		this.peopleInHandPanel.add(new JTextField("None"));
		this.weaponsInHandPanel.add(new JTextField("None"));
		this.roomsInHandPanel.add(new JTextField("None"));
		
		//add items to seenPanel
		this.seenPanel.add(peopleSeenLabel);
		this.seenPanel.add(peopleSeenPanel);
		this.seenPanel.add(weaponsSeenLabel);
		this.seenPanel.add(weaponsSeenPanel);
		this.seenPanel.add(roomsSeenLabel);
		this.seenPanel.add(roomsSeenPanel);
		this.peopleSeenPanel.add(new JTextField("None"));
		this.weaponsSeenPanel.add(new JTextField("None"));
		this.roomsSeenPanel.add(new JTextField("None"));

		//configure settings
		this.inHandPanel.setBorder(new TitledBorder(new EtchedBorder(), "IN HAND"));
		this.peopleInHandLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.weaponsInHandLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.roomsInHandLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.seenPanel.setBorder(new TitledBorder(new EtchedBorder(), "SEEN"));
		this.peopleSeenLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.weaponsSeenLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.roomsSeenLabel.setAlignmentX(RIGHT_ALIGNMENT);
		this.setBorder(new TitledBorder(new EtchedBorder(), "Known Cards", TitledBorder.CENTER, TitledBorder.DEFAULT_POSITION));
	}

	// VVVVV Functionality Methods VVVVV

	// main method for testing
	public static void main(String[] args) {
		//setup panel
		KnownCardsPanel panel = new KnownCardsPanel();
		JFrame frame = new JFrame();
		frame.setContentPane(panel);
		frame.setSize(250, 750);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.setTitle("Cards Panel");
		frame.setVisible(true);

		// testing code
		panel.addCard(true, new Card("Bob", CardType.PERSON), Color.orange);
		panel.addCard(true, new Card("Library", CardType.ROOM), Color.orange);
		panel.addCard(true, new Card("Office", CardType.ROOM), Color.red);
		panel.addCard(false, new Card("Joe", CardType.PERSON), Color.orange);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Bat", CardType.WEAPON), Color.green);
		panel.addCard(false, new Card("Kitchen", CardType.ROOM), Color.pink);
		panel.addCard(false, new Card("Jessica", CardType.PERSON), Color.red);
		panel.addCard(false, new Card("Jessica", CardType.PERSON), Color.red);
		panel.addCard(false, new Card("Jessica", CardType.PERSON), Color.red);
		panel.addCard(false, new Card("Jessica", CardType.PERSON), Color.red);
		panel.addCard(false, new Card("Jessica", CardType.PERSON), Color.red);
		panel.addCard(false, new Card("Bathroom", CardType.ROOM), Color.yellow);
		panel.addCard(false, new Card("Bathroom", CardType.ROOM), Color.yellow);
		panel.addCard(false, new Card("Bathroom", CardType.ROOM), Color.yellow);
		panel.addCard(false, new Card("Bathroom", CardType.ROOM), Color.yellow);
		panel.addCard(false, new Card("Bathroom", CardType.ROOM), Color.yellow);
	}
	// add's a card to the gui
	public void addCard(boolean toHand, Card newCard, Color providingPlayerColor) {
		//create new Field
		JTextField card = new JTextField(newCard.getCardName());
		JPanel panel = new JPanel();
		//configure text field
		card.setHorizontalAlignment(SwingConstants.CENTER);
		card.setEditable(false);
		card.setMinimumSize(new Dimension(MIN_WIDTH, MIN_HEIGHT));
		//determine which panel we are adding a card to
		switch(newCard.getType()) {
		case PERSON:
			if(toHand) {
				panel = peopleInHandPanel;
			}else {
				panel = peopleSeenPanel;
			}
			break;
		case WEAPON:
			if(toHand) {
				panel = weaponsInHandPanel;
			}else {
				panel = weaponsSeenPanel;
			}
			break;
		case ROOM:
			if(toHand) {
				panel = roomsInHandPanel;
			}else {
				panel = roomsSeenPanel;
			}
			break;
		}
		//determine whether we need to add a color
		if(toHand) {
			card.setBackground(Color.white);
		}else {
			card.setBackground(providingPlayerColor);
		}
		//determine whether the panel contains no cards or not
		if(((JTextField)panel.getComponent(0)).getText().equals("None")){
			panel.removeAll();
			panel.add(card);
		}else {
			panel.add(card);
		}
		//revalidate panel to update gui
		panel.revalidate();
	}

	// VVVVV Getters and Setters VVVVV
}
