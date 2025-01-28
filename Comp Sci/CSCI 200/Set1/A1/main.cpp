/* CSCI 200: Assignment 1 A1 : Rock Paper Scissors Throwdown!
 *
 * Author: Ty Gazaway
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <iomanip>

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

int computerDecision();

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
  int playerScore = 0;
  int computerScore = 0;
  int ties = 0;
  int playerChoice = 0;
  int computeChoice = 0;
  bool run = true;
  bool validInput = false;
  string answer;
  
  while(run){
    cout << "Welcome to the grueling game of Rock Paper Scissors! Please enter P, R, or S" << endl << "Player one:";
    validInput = false;
    cin >> answer;
    while(!validInput){
        if(answer == "P"){
            validInput = true;
            playerChoice = 0;
            cout << "\nPlayer chooses Paper" << endl;
        }else if(answer == "R"){
            validInput = true;
            playerChoice = 1;
            cout << "\nPlayer chooses Rock" << endl;
        }else if(answer == "S"){
            validInput = true;
            playerChoice = 2;
            cout << "\nPlayer chooses Scissors" << endl;
        }else{
            cout << "\nWelcome to the grueling game of Rock Paper Scissors! Please enter P, R, or S" << endl << "Player one:";
            cin >> answer;
        }
    }
    computeChoice = computerDecision();
    if(playerChoice == 0 && computeChoice == 1){
        cout << "Paper beats Rock \nPlayer Wins!\n" << endl;
        playerScore++;
    }else if(playerChoice == 1 && computeChoice == 2){
        cout << "Rock beats Scissors \nPlayer Wins!\n" << endl;
        playerScore++;
    }else if(playerChoice == 2 && computeChoice == 0){
        cout << "Scissors beats Paper \nPlayer Wins!\n" << endl;
        playerScore++;
    }else if(playerChoice == 1 && computeChoice == 0){
        cout << "Paper beats Rock \nComputer Wins!\n" << endl;
        computerScore++;
    }else if(playerChoice == 2 && computeChoice == 1){
        cout << "Rock beats Scissors \nComputer Wins!\n" << endl;
        computerScore++;
    }else if(playerChoice == 0 && computeChoice == 2){
        cout << "Scissors beats Paper \nComputer Wins!\n" << endl;
        computerScore++;
    }else{
        cout << "Its a Tie!\n" << endl;
        ties++;
    }
    validInput = false;
    cout << "Would you like to play again?(Y/N) ";
    cin >> answer;
    while(!validInput){
        if(answer == "Y"){
            validInput = true;
            run = true;
        }else if(answer == "N"){
            validInput = true;
            run = false;
        }else{
            cout << "Would you like another random value?(Y/N) ";
            cin >> answer;
        }
    }
  }

    cout << "You won " << playerScore << " game(s), lost "<< computerScore <<" game(s), and tied "<< ties <<" game(s)." << endl;

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}

int computerDecision(){
    int computerChoice = rand() % 3;
    if(computerChoice == 0){
        cout << "Computer chooses Paper\n" << endl;
    }else if(computerChoice == 1){
        cout << "Computer chooses Rock\n" << endl;
    }else{
        cout << "Computer chooses Scissors\n" << endl;
    }
    return computerChoice;
}