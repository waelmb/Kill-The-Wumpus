/* prog5Wumpus.cpp
 
 Description: Navigate a maze to kill the Wumpus.
 Implementation of a 1972 game by Gregory Yob.
 
 Results of a program run are shown below:
// Author: Wael Mobeirek
// Class:  UIC CS-141, Fall 2018
// System: C++ on cloud-based Codio.com 
//    
//     45 points Grading Rubric for Programming Style
//    
//        10 Meaningful identifier names
//        10 Comments: Has header.  Comments on each block of code
//        10 Functional Decomposition
//        10 Appropriate data and control structures
//         5 Code Layout: Appropriate indentation and blank lines
      
   The 16 assessments cover all the various output messages and many of the game conditions.  Each assessment is worth between 2 to 6 points as follows:
       Points   Condition                                                            
           2 R to reset and M to move  
           3     R to reset and M to move to invalid room
           3 Move into even-numbered Wumpus Room 
           3 Shoot arrow and cause Wumpus to move 
           3 Shoot Wumpus from 1 room away 
           4 Shoot Wumpus from 2 rooms away
           4 Shoot Wumpus from 3 rooms away 
           3 Sense Pit and Bats 
           2 Move into Pit 
           5 Move into Bats 
           3 Move into Wumpus Odd-numbered Room
           3 Shoot arrow ricochet 1 room
           4 Shoot arrow ricochet on 2nd room and kills person
           3 Attempt to shoot arrow you don't have
           4 Shoot arrow back into self room, killing person
           6 Pick up arrow, Ricochet 3rd room kill Wumpus
          ===
          55 <- Total points     
          
    Needed notes for the animation:
      #include <bits/stdc++.h> 
        #include <unistd.h>
        cout << "Hey." << flush;
        system("clear");
        cout << "\t\tHi, there!\n\n";
        sleep(2);
        cout << "\n\tComputers are ";
        cout << "great!\n"; 
        cout << "" << endl << flush;
 */
#include <iostream>
#include <iomanip>   // for setw()
#include <cctype>    // for toupper()
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // to seed random number generator with time(0)
#include <cstdlib>   // for exit()
#include <bits/stdc++.h> // for system()
#include <unistd.h>  // for sleep()

using namespace std;

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

// global variables
  int player;
  int wumpus;
  int bats1;
  int bats2;
  int pit1;
  int pit2;
  int arrow = -1;
  int moves = 1;
  bool isArrowRicochets = false;
  bool first = true;
  bool printed = false;

//--------------------------------------------------------------------------------
// Displayed at the start of the game
void animationStart() {
  system("clear");
  cout << "\t\t\t||  || ||    || ||\\    || ||||||||" << endl << flush;
  cout << "\t\t\t||  || ||    || || \\   ||    ||" << endl << flush;
  cout << "\t\t\t|||||| ||    || ||  \\  ||    ||" << endl << flush;
  cout << "\t\t\t||  || ||    || ||   \\ ||    ||" << endl << flush;
  cout << "\t\t\t||  || |||||||| ||    \\||    ||" << endl << flush;
  sleep(1);
  system("clear");
  cout << "\t\t\t|||||||| ||  || ||||||" << endl << flush;
  cout << "\t\t\t   ||    ||  || ||" << endl << flush;
  cout << "\t\t\t   ||    |||||| ||||||" << endl << flush;
  cout << "\t\t\t   ||    ||  || ||" << endl << flush;
  cout << "\t\t\t   ||    ||  || ||||||" << endl << flush;
  sleep(1);
  system("clear");
  cout << "\\\\        //\\\\       // ||    || ||\\\\        //|| |||||\\ ||    || ||||||||" << endl << flush;
  cout << " \\\\      //  \\\\     //  ||    || || \\\\      // || ||   | ||    || ||" << endl << flush;
  cout << "  \\\\    //    \\\\   //   ||    || ||  \\\\    //  || |||||/ ||    || ||||||||" << endl << flush;
  cout << "   \\\\  //      \\\\ //    ||    || ||   \\\\  //   || ||     ||    ||       ||" << endl << flush;
  cout << "    \\\\//        \\//     |||||||| ||    \\\\//    || ||     |||||||| ||||||||" << endl << flush;
  sleep(3);
  system("clear");
}

// Dispalyed when the player dies
void animationDeath() { 
  sleep(3);
  system("clear");
  cout << "\t\t\t||||||\\" << endl << flush;
  cout << "\t\t\t||   ||" << endl << flush;
  cout << "\t\t\t||||||/" << endl << flush;
  cout << "\t\t\t||  \\\\" << endl << flush;
  cout << "\t\t\t||   \\\\" << endl << flush;
  sleep(1);
  cout << endl << flush;
  cout << "\t\t\t  ||" << endl << flush;
  cout << "\t\t\t  ||" << endl << flush;
  cout << "\t\t\t  ||" << endl << flush;
  cout << "\t\t\t  ||" << endl << flush;
  cout << "\t\t\t  ||" << endl << flush;
  sleep(1);
  cout << endl << flush;
  cout << "\t\t\t|||||\\" << endl << flush;
  cout << "\t\t\t||   |" << endl << flush;
  cout << "\t\t\t|||||/" << endl << flush;
  cout << "\t\t\t||" << endl << flush;
  cout << "\t\t\t||" << endl << flush;
  sleep(3);
  system("clear");
}

// Displayed when the wumpus dies
void animationVictory() {   
  sleep(3);
  system("clear");

  for(int i = 0; i < 4; i++) {
    cout << "\\\\        //\\\\       // |||||| ||  || |||||| || || ||" << endl;
    cout << " \\\\      //  \\\\     //  ||  || ||  || ||  || || || ||" << endl;
    cout << "  \\\\    //    \\\\   //   ||  || |||||| ||  || || || ||" << endl;
    cout << "   \\\\  //      \\\\ //    ||  || ||  || ||  || " << endl;
    cout << "    \\\\//        \\//     |||||| ||  || |||||| || || ||" << endl;
    cout << "\t\\\\" << endl << flush;
    cout << "\t \\\\" << endl << flush;
    cout << "\t  \\\\   /|||\\" << endl << flush;
    cout << "\t   \\\\  |||||" << endl << flush;
    cout << "\t    \\\\ \\|||/" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    sleep(1);
    system("clear");
    cout << "\\\\        //\\\\       // |||||| ||  || |||||| || || ||" << endl;
    cout << " \\\\      //  \\\\     //  ||  || ||  || ||  || || || ||" << endl;
    cout << "  \\\\    //    \\\\   //   ||  || |||||| ||  || || || ||" << endl;
    cout << "   \\\\  //      \\\\ //    ||  || ||  || ||  || " << endl;
    cout << "    \\\\//        \\//     |||||| ||  || |||||| || || ||" << endl;
    cout << "\t                  //" << endl << flush;
    cout << "\t                 //" << endl << flush;
    cout << "\t       /|||\\    //" << endl << flush;
    cout << "\t       |||||   //" << endl << flush;
    cout << "\t       \\|||/  //" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     ||||||||||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    cout << "\t     |||    |||" << endl << flush;
    sleep(1);
    system("clear");
  }
}

void displayCave()
{
        cout<< "       ______18______             \n"
            << "      /      |       \\           \n"
            << "     /      _9__      \\          \n"
            << "    /      /    \\      \\        \n"
            << "   /      /      \\      \\       \n"
            << "  17     8        10     19       \n"
            << "  | \\   / \\      /  \\   / |    \n"
            << "  |  \\ /   \\    /    \\ /  |    \n"
            << "  |   7     1---2     11  |       \n"
            << "  |   |    /     \\    |   |      \n"
            << "  |   6----5     3---12   |       \n"
            << "  |   |     \\   /     |   |      \n"
            << "  |   \\       4      /    |      \n"
            << "  |    \\      |     /     |      \n"
            << "  \\     15---14---13     /       \n"
            << "   \\   /            \\   /       \n"
            << "    \\ /              \\ /        \n"
            << "    16---------------20           \n"
            << endl;
}//end displayCave()


//--------------------------------------------------------------------------------
void displayInstructions()
{
    displayCave();
    cout<< "Hunt the Wumpus:                                             \n"
        << "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
        << "room has 3 tunnels leading to other rooms.                   \n"
        << "                                                             \n"
        << "Hazards:                                                     \n"
        << "1. Two rooms have bottomless pits in them.  If you go there you fall and die.  \n"
        << "2. Two other rooms have super-bats.  If you go there, the bats grab you and    \n"
        << "   fly you to some random room, which could be troublesome.  Then those bats go\n"
        << "   to a new room different from where they came from and from the other bats.  \n"
        << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and   \n"
        << "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake      \n"
        << "   him up: Anytime you shoot an arrow, or you entering his room.  When he      \n"
        << "   wakes he moves if he is in an odd-numbered room, but stays still otherwise. \n"
        << "   After that, if he is in your room, he eats you and you die!                 \n"
        << "                                                                               \n"
        << "Moves:                                                                         \n"
        << "On each move you can do the following, where input can be upper or lower-case: \n"
        << "1. Move into an adjacent room.  To move enter 'M' followed by a space and      \n"
        << "   then a room number.                                                         \n"
        << "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
        << "   you specify.  Your arrow ends up in the final room.                         \n"
        << "   To shoot enter 'S' followed by the number of rooms (1..3), and then the     \n"
        << "   list of the desired number (up to 3) of adjacent room numbers, separated    \n"
        << "   by spaces. If an arrow can't go a direction because there is no connecting  \n"
        << "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and     \n"
        << "   continues doing this until it has traveled the designated number of rooms.  \n"
        << "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You \n"
        << "   automatically pick up the arrow if you go through a room with the arrow in  \n"
        << "   it.                                                                         \n"
        << "3. Enter 'R' to reset the person and hazard locations, useful for testing.     \n"
        << "4. Enter 'C' to cheat and display current board positions.                     \n"
        << "5. Enter 'D' to display this set of instructions.                              \n"
        << "6. Enter 'P' to print the maze room layout.                                    \n"
        << "7. Enter 'X' to exit the game.                                                 \n"
        << "                                                                               \n"
        << "Good luck!                                                                     \n"
        << " \n"
        << endl;
}//end displayInstructions()

// class adjacentRoom
class adjacentRoom {
  public:
  
    //Default constructor
    adjacentRoom()
      {
        room1 = 0;
        room2 = 0;
        room3 = 0;
      }
  
    //Constructor
    adjacentRoom(int theRoom1,
                 int theRoom2,
                 int theRoom3)  {
       room1 = theRoom1;
       room2 = theRoom2;
       room3 = theRoom2;
    }
  
    //Accessors
    int getAdjacentRoom1() {
      return room1;
    }
    int getAdjacentRoom2() {
      return room2;
    }
    int getAdjacentRoom3() {
      return room3;
    }

    //Mutators
    void setAdjacentRoom1(int inputRoom) {
      this->room1 = inputRoom;
    }
    void setAdjacentRoom2(int inputRoom) {
      this->room2 = inputRoom;
    }
    void setAdjacentRoom3(int inputRoom) {
      this->room3 = inputRoom;
    }
    bool isAdjacent(int inputRoom) {
      if(inputRoom == room1 || inputRoom == room3 || inputRoom == room2) {
        return true;
      }
      else{
        return false;
      }
    }
  
  private:
    int room1;
    int room2;
    int room3;
  
};


// Initalizes an array of adjacentRoom with the correct values according to the cave
void createAdjacentRooms(adjacentRoom* roomsArray) {
  //Room 0 is empty, since it doesn't exist
  //Room 1
  roomsArray[1].setAdjacentRoom1(2);
  roomsArray[1].setAdjacentRoom2(5);
  roomsArray[1].setAdjacentRoom3(8);
  //Room 2
  roomsArray[2].setAdjacentRoom1(1);
  roomsArray[2].setAdjacentRoom2(3);
  roomsArray[2].setAdjacentRoom3(10);
  //Room 3
  roomsArray[3].setAdjacentRoom1(2);
  roomsArray[3].setAdjacentRoom2(4);
  roomsArray[3].setAdjacentRoom3(12);
  //Room 4
  roomsArray[4].setAdjacentRoom1(3);
  roomsArray[4].setAdjacentRoom2(5);
  roomsArray[4].setAdjacentRoom3(14);
  //Room 5
  roomsArray[5].setAdjacentRoom1(1);
  roomsArray[5].setAdjacentRoom2(4);
  roomsArray[5].setAdjacentRoom3(6);
  //Room 6
  roomsArray[6].setAdjacentRoom1(5);
  roomsArray[6].setAdjacentRoom2(7);
  roomsArray[6].setAdjacentRoom3(15);
  //Room 7
  roomsArray[7].setAdjacentRoom1(6);
  roomsArray[7].setAdjacentRoom2(8);
  roomsArray[7].setAdjacentRoom3(17);
  //Room 8
  roomsArray[8].setAdjacentRoom1(1);
  roomsArray[8].setAdjacentRoom2(7);
  roomsArray[8].setAdjacentRoom3(9);
  //Room 9
  roomsArray[9].setAdjacentRoom1(8);
  roomsArray[9].setAdjacentRoom2(10);
  roomsArray[9].setAdjacentRoom3(18);
  //Room 10
  roomsArray[10].setAdjacentRoom1(2);
  roomsArray[10].setAdjacentRoom2(9);
  roomsArray[10].setAdjacentRoom3(11);
  //Room 11
  roomsArray[11].setAdjacentRoom1(10);
  roomsArray[11].setAdjacentRoom2(12);
  roomsArray[11].setAdjacentRoom3(19);
  //Room 12
  roomsArray[12].setAdjacentRoom1(3);
  roomsArray[12].setAdjacentRoom2(11);
  roomsArray[12].setAdjacentRoom3(13);
  //Room 13
  roomsArray[13].setAdjacentRoom1(12);
  roomsArray[13].setAdjacentRoom2(14);
  roomsArray[13].setAdjacentRoom3(20);
  //Room 14
  roomsArray[14].setAdjacentRoom1(4);
  roomsArray[14].setAdjacentRoom2(13);
  roomsArray[14].setAdjacentRoom3(15);
  //Room 15
  roomsArray[15].setAdjacentRoom1(6);
  roomsArray[15].setAdjacentRoom2(14);
  roomsArray[15].setAdjacentRoom3(16);
  //Room 16
  roomsArray[16].setAdjacentRoom1(15);
  roomsArray[16].setAdjacentRoom2(17);
  roomsArray[16].setAdjacentRoom3(20);
  //Room 17
  roomsArray[17].setAdjacentRoom1(7);
  roomsArray[17].setAdjacentRoom2(16);
  roomsArray[17].setAdjacentRoom3(18);
  //Room 18
  roomsArray[18].setAdjacentRoom1(9);
  roomsArray[18].setAdjacentRoom2(17);
  roomsArray[18].setAdjacentRoom3(19);
  //Room 19
  roomsArray[19].setAdjacentRoom1(11);
  roomsArray[19].setAdjacentRoom2(18);
  roomsArray[19].setAdjacentRoom3(20);
  //Room 20
  roomsArray[20].setAdjacentRoom1(13);
  roomsArray[20].setAdjacentRoom2(16);
  roomsArray[20].setAdjacentRoom3(19);
}

// Exits the game
void exitTheGame() {
  cout << "\nExiting Program ..." << endl;
  exit( -1);
}

// Returns a bool of the Wumpus' decision when the player enters the room it's at
bool wumpusDecision(adjacentRoom* roomsArray) {

  if(wumpus % 2 == 0) { 
    return true; //kill the player
  }
  else {
    return false; //go to another room
  }
}

// Relocates the player, since the bats transported him, then the bats relocate themselves as a variable passed by reference
void batsRelocate(int& bats) {
  do {
    player = rand() % NUMBER_OF_ROOMS + 1;
  } while(player == bats1 || player == bats2 || player == wumpus);
  cout << "Woah... you're flying! " << endl;
  cout << "You've just been transported by bats to room " << player << endl;
  cout << "You are in room " << player << ". " << endl;
  
  do {
    bats = rand() % NUMBER_OF_ROOMS + 1;
  } while(bats == player || bats == wumpus || bats == bats2 || bats == pit1 || bats == pit2); 
}

// Relocate wumpus to the smallest adjacentRoom
void wumpusRelocate(adjacentRoom* roomsArray) {
  wumpus = roomsArray[wumpus].getAdjacentRoom1();
}

// Outputs the right message for the user
void outputMessage(adjacentRoom* roomsArray) {  
  if(player == wumpus) {
    //Result of entering a room with the Wumpus, where Wumpus stays
    if(wumpusDecision(roomsArray) == true){
      cout << "You briefly feel a slimy tentacled arm as your neck is snapped." << endl;
      cout << "It is over." << endl;
      animationDeath();
      exitTheGame();
    }
    //Result of entering a room with the Wumpus, where Wumpus exits the room
    else {
      cout << endl;
      cout << "You hear a slithering sound, as the Wumpus slips away." << endl;
      cout << "Whew, that was close!";

      //relocate wumpus
      wumpusRelocate(roomsArray);
    }
  }
   
  //Result of entering a room with a pit
  if(player == pit1 || player == pit2) {
    cout << "Aaaaaaaaahhhhhh...." << endl; 
    cout << "You fall into a pit and die." << endl;
    animationDeath();
    exitTheGame();
  }
  //Program indication that person entered a room with the arrow on the ground
  if(player == arrow) {
    arrow = -1;
    isArrowRicochets = false;
    cout << endl;
    cout << "Congratulations, you found the arrow and can once again shoot." << endl;
  } 
  
  //print an endl if not first
  if(!first) {
    cout << endl;
  }
  
  //Result of entering a room with bats1, taking you to some room x, where x is 1..20
  if(player == bats1) {
    batsRelocate(bats1);
  }
  //Result of entering a room with bats2, taking you to some room x, where x is 1..20
  else if(player == bats2) {
    batsRelocate(bats2);
  } else {
    cout << "You are in room " << player << ". ";
  }
  
  //Program response in room adjacent to the Wumpus.
  if(roomsArray[player].isAdjacent(wumpus)) {
    cout << "You smell a stench. ";
    printed = true;
  }
  //Program response in room adjacent to a pit
  if(roomsArray[player].isAdjacent(pit1) || roomsArray[player].isAdjacent(pit2)) {
    cout << "You feel a draft. ";
    printed = true;
  }
  //Program response in room adjacent to bats
  if(roomsArray[player].isAdjacent(bats1) || roomsArray[player].isAdjacent(bats2)) {
    cout << "You hear rustling of bat wings. ";
    printed = true;
  }
  //Prints an extra endl
  if(printed) {
    cout << endl;
  }
}


// Shoots the arrow, and output the right message to the player
void shoot(adjacentRoom* roomsArray) {
  int numRooms;
  int target1 = 0;
  int target2 = 0;
  int target3 = 0;
  moves++;
  
  //Program response to selecting 'S' to shoot arrow, when person does not have arrow
  if(arrow != -1) {
    cout << endl;
    cout << "Sorry, you can't shoot an arrow you don't have.  Go find it." << endl;
  }
  else {
    //Get user input
    cout << endl;
    cout << "Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ";
    cin >> numRooms;
    for(int i = 1; i <= numRooms; i++) {
      if(i == 1) {
        cin >> target1;
      }
      else if(i == 2) {
        cin >> target2;
      }
      else if(i == 3) {
        cin >> target3;
      }
    }
    
    //Check if the player didn't shoot their self
    // Notification of arrow rooms path going away and coming back to the person
    if(player == target1 || player == target2 || player == target3) {
        cout << "You just shot yourself. " << endl;
        cout << "Maybe Darwin was right.  You're dead." << endl;
        animationDeath();
        exitTheGame();
    }

    //Check if the targets are adjacent, if it is, make the arrow location equal to the target. If it's not, set the arrow location to the lowest room number which is adjacent
    if(roomsArray[player].isAdjacent(target1) == true) {
      if(target2 != 0 && roomsArray[target1].isAdjacent(target2) == true) {
        if(target3 != 0 && roomsArray[target2].isAdjacent(target3) == true) {
          arrow = target3;
        }
        else {
          if(target3 != 0) {
            cout << endl;
            cout << "Room " << target3 << " is not adjacent.  Arrow ricochets..." << endl;
            arrow = roomsArray[target2].getAdjacentRoom1();
            isArrowRicochets = true;
          }
          else {
            arrow = target2;
          }
        }
      }
      else { 
        if(target2 != 0) {
          cout << endl;
          cout << "Room " << target2 << " is not adjacent.  Arrow ricochets..." << endl;
          arrow = roomsArray[target1].getAdjacentRoom1();
          isArrowRicochets = true;
        }
        else {
          arrow = target1;
        }
      }
    }
    else {
      cout << endl;
      cout << "Room " << target1 << " is not adjacent.  Arrow ricochets..." << endl;
      arrow = roomsArray[player].getAdjacentRoom1();
      isArrowRicochets = true;
    }
    
    // Notification of arrow ricochet coming back and hitting player
    //Killing yourself by a ricochets happens when one of the targets is adjacent to player
    if(isArrowRicochets && arrow == player) {
      cout << "You just shot yourself, and are dying." << endl;
      cout << "It didn't take long, you're dead." << endl;
      animationDeath();
      exitTheGame();
    } 
    
    // Notification of having shot the Wumpus with an arrow
    if(arrow == wumpus && isArrowRicochets == false) {
      cout << "Wumpus has just been pierced by your deadly arrow!" << endl;
      cout << "Congratulations on your victory, you awesome hunter you." << endl;
      animationVictory();
      exitTheGame();
    }
    // Notification of arrow ricochet killing the Wumpus
    else if(arrow == wumpus && isArrowRicochets == true) {
      cout << "Your arrow ricochet killed the Wumpus, you lucky dog!" << endl;
      cout << "Accidental victory, but still you win!" << endl;
      animationVictory();
      exitTheGame();
    }
    //relocate wumpus
      wumpusRelocate(roomsArray);
  }
}


// Moves the player's position after making sure it's valid
void makeMove(adjacentRoom* roomsArray) {
  int move;
  cin >> move;
  if(roomsArray[player].isAdjacent(move)) {
    player = move;
    moves++;
  }
  else {
    //Program indication that selected room is not adjacent to current room
    cout << "Invalid move.  Please retry." << endl;
  }
}


// Displays needed information
void displayInfo(adjacentRoom* roomsArray) {
  outputMessage(roomsArray);
  cout << endl;
  cout << moves << ". Enter your move (or 'D' for directions): ";
}


// Displays current board positions
void cheat() {
  cout << endl;
  cout << "Cheating! Game elements are in the following rooms:" << endl;
  cout << "Player Wumpus Bats1 Bats2 Pit1 Pit2 Arrow" << endl;
  cout << "   " << player << "     " << wumpus << "      " << bats1 << "     " << bats2 << "   " << pit1 << "   " << pit2 << "    " << arrow << endl;
}


// Resets board positions according to user input
void reset() {
  cout << endl;
  cout << "(Remember arrow value of -1 means it is with the person.)" << endl;
  cout << "Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow:" << endl;
  cin >> player;
  cin >> wumpus;
  cin >> bats1;
  cin >> bats2;
  cin >> pit1;
  cin >> pit2;
  cin >> arrow;
}


// Calls the corresponding function for the user's menuChoice input after it makes sure it's valid
void action(adjacentRoom* roomsArray){
  char menuChoice;
  bool isValidMenuChoice = false;
  do {
    cin >> menuChoice;
    if(menuChoice == 'M' || menuChoice == 'm') {
      isValidMenuChoice = true;
      makeMove(roomsArray);
    }
    else if(menuChoice == 'S' || menuChoice == 's') {
      isValidMenuChoice = true;
      shoot(roomsArray);
    }
    else if(menuChoice == 'R' || menuChoice == 'r') {
      isValidMenuChoice = true;
      reset();
    }
    else if(menuChoice == 'C' || menuChoice == 'c') {
      isValidMenuChoice = true;
      cheat();
    }
    else if(menuChoice == 'D' || menuChoice == 'd') {
      isValidMenuChoice = true;
      displayInstructions();
    }
    else if(menuChoice == 'P' || menuChoice == 'p') {
      isValidMenuChoice = true;
      displayCave();
    }
    else if(menuChoice == 'X' || menuChoice == 'x') {
      exitTheGame();
    }
  } while(isValidMenuChoice == false);
}

//--------------------------------------------------------------------------------

int main()
{   
  // Seed the random number generator.  Change seed to time(0) to change output each time.
  // srand(time(0));
  srand(1);   // Use this version in what you turn in
  
  //start animation
  animationStart();
  
  //Initialize an array of type Room
  int roomsArraySize = NUMBER_OF_ROOMS+1;
  adjacentRoom roomsArray[roomsArraySize];
  createAdjacentRooms(roomsArray);
  
  //Initialize initial positions of player, wumpus, bats, and pits
  bats1 = rand() % NUMBER_OF_ROOMS + 1;
  do {
    bats2 = rand() % NUMBER_OF_ROOMS + 1;
  } while(bats2 == bats1);
  do {
    pit1 = rand() % NUMBER_OF_ROOMS + 1;
  } while(pit1 == bats1 || pit1 == bats2);
  do {
    pit2 = rand() % NUMBER_OF_ROOMS + 1;
  } while( pit2 == bats1 || pit2 == bats2 || pit2 == pit1);
  
  do {
    wumpus = rand() % NUMBER_OF_ROOMS + 1;
  } while(wumpus == bats1 || wumpus == bats2 || wumpus == pit1 || wumpus == pit2);

  do {
    player = rand() % NUMBER_OF_ROOMS + 1;
  } while(player == bats1 || player == bats2 || player == pit1 || player == pit2 || player == wumpus);
  
  // Displays initial information for the player
  displayInfo(roomsArray);
  first = false; //info was printed for the first time, so, we set this to false after that
  
  //Event loop
  while(true) {
    printed = false; // reset printed
    action(roomsArray);
    displayInfo(roomsArray);
  }
}//end main()
