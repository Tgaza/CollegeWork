1. How did you structure your player?
- I made my player so that it contained all of the actions that involved messing with a players chips.
- give chips to players both left and right
- giving chips to the center
- taking chips in
- additionally I had getter methods for both the name and chips variables]

2. How did you structure your game?
- I made the game so that it first calculated how many dice to role
- then prints out what player and how many dice they will role
- then has a for loop that runs a roll die function that a number of times equal to the amount of dice that need to be rolled
- within the roll die function, it automatically calls the proper methods of the player in order to shift chips as necessary
- additionally it calls the reversedirection method or increments the move counter if neccessary]
- then it checks if the current player has run out of chips and removes them from the list if neccesary
- then it theres a for loop the calls the move method within CircularLinkedList, which shifts whos turn it is, a number of times equal to the movecounter
   + the move counter start with a base of 1 and is increased for every skip action was rolled
- then movecounter is reset back to 1, currPlayer variable is reset to the new player, and turnNumber is incremented
- then the while loop checks if there are still two or more players left and it loops over again

3. How did you make use of classes and functions? What went where
- I made use of classes to house the blueprints for a Player Object and CircularLinkedList object. The classes housed the
main behaviors of the Players and the List of Players Left. For example the player behavior of giving a chip to the left-center-right.
Player object where used whenever an action that would involve a player was performed. On the other hand, I used functions for algorithms that 
are repeated consistently and affect all objects and variables equally. The only function I used was a function for rolling the dice, 
due to the fact that all players have to roll the dice, and the result of the rolls doesn't change depending on player to player.