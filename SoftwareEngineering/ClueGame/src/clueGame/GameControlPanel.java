/*
 * GameControlPanel is a child of JPanel and hosts all the items necessary for the player to control the game
 * Author: Ty Gazaway
 * 
 * */
package clueGame;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public class GameControlPanel extends JPanel implements ActionListener{
	// VVVVV Attributes VVVVV
	//general
	private Board gameBoard;
	// upper panel items
	private JPanel upperPanel;
	private JPanel turnPanel;
	private JLabel whoseTurn;
	private JTextField curPlayer;
	private JPanel rollPanel;
	private JLabel rollLabel;
	private JTextField rollResult;
	private JButton makeAccuse;
	private JButton nextTurn;
	// lower panel items
	private JPanel lowerPanel;
	private JPanel guessPanel;
	private JTextField guess;
	private JPanel guessResultPanel;
	private JTextField guessResult;

	// VVVVV Constructors VVVVV
	// default constructor
	public GameControlPanel() {
		// Initialize items
		this.gameBoard = null;
		// upper panel items
		this.upperPanel = new JPanel(new GridLayout(1, 4));
		this.turnPanel = new JPanel(new GridLayout(2, 0));
		this.whoseTurn = new JLabel("Whose turn?");
		this.curPlayer = new JTextField();
		this.rollPanel = new JPanel();
		this.rollLabel = new JLabel("Roll:");
		this.rollResult = new JTextField("-1");
		this.makeAccuse = new JButton("Make Accusation");
		this.nextTurn = new JButton("NEXT!");
		// lower panel items
		this.lowerPanel = new JPanel(new GridLayout(1, 2));
		this.guessPanel = new JPanel(new GridLayout(1,0));
		this.guess = new JTextField("");
		this.guessResultPanel = new JPanel(new GridLayout(1,0));
		this.guessResult = new JTextField("");

		setup();
	}
	// main constructor
	public GameControlPanel(Board gameBoard) {
		// Initialize items
		this.gameBoard = gameBoard;
		// upper panel items
		this.upperPanel = new JPanel(new GridLayout(1, 4));
		this.turnPanel = new JPanel(new GridLayout(2, 0));
		this.whoseTurn = new JLabel("Whose turn?");
		this.curPlayer = new JTextField();
		this.rollPanel = new JPanel();
		this.rollLabel = new JLabel("Roll:");
		this.rollResult = new JTextField("-1");
		this.makeAccuse = new JButton("Make Accusation");
		this.nextTurn = new JButton("NEXT!");
		// lower panel items
		this.lowerPanel = new JPanel(new GridLayout(1, 2));
		this.guessPanel = new JPanel(new GridLayout(1,0));
		this.guess = new JTextField("");
		this.guessResultPanel = new JPanel(new GridLayout(1,0));
		this.guessResult = new JTextField("");

		setup();
	}

	// VVVVV private helper methods VVVVV
	private void setup() {
		// configure GameControlPanel
		this.add(upperPanel);
		this.add(lowerPanel);
		this.setLayout(new GridLayout(2,0));
		// add items to upper panel
		upperPanel.add(turnPanel);
		turnPanel.add(whoseTurn);
		turnPanel.add(curPlayer);

		upperPanel.add(rollPanel);
		rollPanel.add(rollLabel);
		rollPanel.add(rollResult);

		upperPanel.add(makeAccuse);
		upperPanel.add(nextTurn);

		// add items to lower panel
		lowerPanel.add(guessPanel);
		guessPanel.add(guess);

		lowerPanel.add(guessResultPanel);
		guessResultPanel.add(guessResult);

		//configure settings
		//upper panel items
		whoseTurn.setHorizontalAlignment(SwingConstants.CENTER);
		curPlayer.setHorizontalAlignment(SwingConstants.CENTER);
		curPlayer.setEditable(false);
		nextTurn.addActionListener(this);
		makeAccuse.addActionListener(this);
		//lower panel
		guessPanel.setBorder(new TitledBorder(new EtchedBorder(), "Guess"));
		guessResultPanel.setBorder(new TitledBorder(new EtchedBorder(), "Guess Result"));
		guess.setEditable(false);
		guessResult.setEditable(false);
	}

	// VVVVV Functionality Methods VVVVV

	//listen for buttons being pressed then call corresponding methods
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == nextTurn) {
			this.gameBoard.nextPressed();
		}else if(e.getSource() == makeAccuse) {
			this.gameBoard.makeAccusationPressed();
		}
	}
	// main method for testing
	public static void main(String[] args) {
		//setup panel
		GameControlPanel panel = new GameControlPanel();
		JFrame frame = new JFrame();
		frame.setContentPane(panel);
		frame.setSize(750, 180);
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.setTitle("Control Panel");
		frame.setVisible(true);

		// testing code
		panel.setTurn(new ComputerPlayer("Draco Malfoy", Color.green, 0, 0, null), 3);
		panel.setGuess("Harry Pahtter!");
		panel.setGuessResult("Malfoyyy!!");
	}

	// VVVVV Getters and Setters VVVVV
	public void setGuess(String guess) {
		this.guess.setText(guess);
	}

	public void setGuessResult(String guessResult) {
		this.guessResult.setText(guessResult);
	}

	public void setTurn(Player newPlayer, int diceRoll) {
		this.curPlayer.setText(newPlayer.getName());
		this.curPlayer.setBackground(newPlayer.getColor());
		this.rollResult.setText(Integer.toString(diceRoll));
	}

}
