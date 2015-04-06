/*******************************
Name: Andrew Gniadek
Date: 5/24/2014
Date Last Modified: 6/4/2014
File Name: Final_Project.cpp

Description: This is a text based MUD where the player is a mage that must find one's way out of the mage tower.
The player can move between rooms, get items in rooms where they are present, use objects in a room such as 
a portal or a mana well, and then 

Input:  get [item]. use [object], cast clarity, or cardinal directions (n, s, e, w)

Output: Game intro telling the player what's going on, respective room info based on the room where the player is,
the player's inventory, the amount of intelligence or magic points the player has


*******************************/


//preprocessor variables
#include <iostream>
#include <string>
#include <climits>
#include <ctime>
#include <cstdlib>

//using directive
using namespace std;


//Enumeration for the rooms
enum roomNames { MAIN_ENTRANCE, ICY_ROOM, STUDY, FIRE_ROOM, FROST_CAVERN, GOLDEN_HALL, INFERNO, VAULT_OF_LIGHT, NUM_ROOMS };
enum numName { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN };

//struct variable that stores room information for use in the array of struct variables

//=====REQUIREMENT 20=====
struct Room
{

	//=====REQUIREMENT 15=====
	string sName;
	string sDescription;
	bool bBookOfMinds;
	bool bManaWell;
	bool bSpellBook;
	bool bPortal;
	bool bRuneOfWater;
	bool bRuneOfFire;
	int iDirS;
	int iDirN;
	int iDirE;
	int iDirW;
	string sPlayerHint;

	bool getBookOfMinds()
	{
		return bBookOfMinds;
	}

	void setBookOfMinds(bool setMinds)
	{
		bBookOfMinds = setMinds;
	}

	bool getManaWell()
	{
		return bManaWell;
	}

	void setManaWell(bool setWell)
	{
		bManaWell = setWell;
	}

	bool getSpellBook()
	{
		return bSpellBook;
	}

	void setSpellBook(bool setSpell)
	{
		bSpellBook = setSpell;
	}

	bool getPortal()
	{
		return bPortal;
	}

	void setPortal(bool setPort)
	{
		bPortal = setPort;
	}

	bool getRuneOfWater()
	{
		return bRuneOfWater;
	}

	void setRuneOfWater(bool runeWater)
	{
		bRuneOfWater = runeWater;
	}

	bool getRuneOfFire()
	{
		return bRuneOfFire;
	}

	void setRuneOfFire(bool setFire)
	{
		bRuneOfFire = setFire;
	}

	int getDirS()
	{
		return iDirS;
	}

	void setDirS(int newDir)
	{
		iDirS = newDir;
	}

	int getDirN()
	{
		return iDirN;
	}

	void setDirN(int newDir)
	{
		iDirN = newDir;
	}

	int getDirW()
	{
		return iDirW;
	}

	void setDirW(int newDir)
	{
		iDirW = newDir;
	}

	int getDirE()
	{
		return iDirE;
	}

	void setDirE(int newDir)
	{
		iDirE = newDir;
	}

	string getHint()
	{
		return sPlayerHint;
	}

	void setHint(string playHint)
	{
		sPlayerHint = playHint;
	}

};

//=====REQUIREMENT 21=====

class Player
{
public:
	int getIntel();
	void setIntel(int newIntel);
	int getMagicPoints();
	void setMagicPoints(int newMagic);
	int getCurrentRoom();
	void setCurrentRoom(int newRoom);
	bool getRuneOfWater();
	void setRuneOfWater(bool newWater);
	bool getRuneOfFire();
	void setRuneOfFire(bool newFire);
	bool getSpellBook();
	void setSpellBook(bool newSpell);

private:
	int iIntel;
	int iMagicPoints;
	int iCurrentRoom;
	bool bRuneOfWater;
	bool bRuneOfFire;
	bool bSpellBook;
};

//GLOBAL CONSTANTS
const int NO_DIR = -1; //sets directions to -1 in order to tell the player he/she can't go in that direction

//**********FUNCTION DECLARATIONS**********
void gameState(int argc, char* argv[]); //starts the game program and manages the state of the program
void gameState(); //overloaded function that concludes the game
//All the mutator functions that manage the room data in the room dynamic array
void setRoom(Room* myRooms, int size); //recursive function that sets the initial values of the room by calling the other eight room functions 

//the eight room functions that set the initial values of the room array
void setMageBase(Room* myRooms, const int size);
void setIcyRoom(Room* myRooms, const int size);
void setStudy(Room* myRooms, const int size);
void setFireRoom(Room* myRooms, const int size);
void setFrostCavern(Room* myRooms, const int size);
void setGoldenHall(Room* myRooms, const int size);
void setInferno(Room* myRooms, const int size);
void setVaultOfLight(Room* myRooms, const int size);

//**********FUNCTION DECLARATIONS FOR GAME STATES**********
void gameIntro(char* argv[], int argc); //the introduction to the MUD
void roomCreator(Room* currentRoom, Player* player, int currentNumber); //processes the data to switch rooms
bool playerAction(Player* player, Room* myRooms); //determines from the string what the player wants to do next
bool validateInput(string userInput, Player* player, Room* myRooms); //validates player input


int main(int argc, char* argv[])
{
	gameState(argc, argv);
	return 0;
}

void gameState(int argc, char* argv[])
{
	//generate the random numbers for the player's intelligence and magic points
	//=====REQUIREMENT 7=====
	srand(static_cast<unsigned int>(time(0))); //seed the random number generator

	bool stillPlaying = true; //boolean value that determines whether the player still wants to play
	//=====REQUIREMENT 24=====
	Player thePlayer; //initializes a player class object
	Player *pPlayer = &thePlayer; //creates a player object pointer and assigns it the address of the player object

	pPlayer->setCurrentRoom(ZERO); //sets the player's room to the main entrance
	pPlayer->setIntel(((rand()) % ((22 - 20) + 1) + 20)); //randomly assigns an intelligence point value to the player at the beginning of the game
	pPlayer->setMagicPoints(TWO * ((rand()) % ((12 - 10) + 1) + 10)); //randomly assigns a magic point value to the player at the beginning of the game

	//=====REQUIREMENT 18,22,23=====
	Room *pMyRooms = new Room[EIGHT];

	//=====REQUIREMENT 6=====
	//This for loop sets all the doors to closed using the const int NO_DIR at the beginning of the game
	for (int i = 0; i < EIGHT; ++i)
	{
		pMyRooms[i].setDirS(NO_DIR);
		pMyRooms[i].setDirW(NO_DIR);
		pMyRooms[i].setDirN(NO_DIR);
		pMyRooms[i].setDirE(NO_DIR);
	}

	setRoom(pMyRooms, SEVEN);//sets the initial values of the rooms
	gameIntro(argv, argc);

	while(stillPlaying)
	{

		stillPlaying = playerAction(pPlayer, pMyRooms);

	}

	//DELETE FOR THE DYNAMIC ARRAY
	//==REQUIREMENT 8==
	//If I had wrote delete []pMyRooms without a semicolon, I would have two SYNTAX errors
	//If I never delete the dynamic array, it will linger on during RUNTIME, and could cause a problem if this program was larger (memory leak)
	//If I had a conditional above the delete statement that I could never meet, and then the program never 
	//deletes the dynamic array, this would be a LOGIC ERROR
	delete[] pMyRooms;
	//create a null pointer
	pMyRooms = 0;

	//==REQUIREMENT 9==
	//Print the address of the pMyRooms pointer to make sure it's null
	//cout << pMyRooms;
	gameState();
}

//==REQUIREMENT 14==
//this function prints out to the user the conclusion of the game with a valediction
void gameState()
{
	cout << "\nThanks for playing!!\n";
}



//**********FUNCTION DEFINITIONS**********

//FUNCTION DEFINITIONS FOR THE PLAYER CLASS
//These mutator and accessor functions allow access to private member variables in the Player class
int Player::getIntel()
{
	return iIntel;
}


void Player::setIntel(int newIntel)
{
	iIntel = newIntel;
}

int Player::getMagicPoints()
{
	return iMagicPoints;
}

void Player::setMagicPoints(int newMagic)
{
	iMagicPoints = newMagic;
}

int Player::getCurrentRoom()
{
	return iCurrentRoom;
}

void Player::setCurrentRoom(int newRoom)
{
	iCurrentRoom = newRoom;
}

bool Player::getRuneOfWater()
{
	return bRuneOfWater;
}


void Player::setRuneOfWater(bool newWater)
{
	bRuneOfWater = newWater;
}

bool Player::getRuneOfFire()
{
	return bRuneOfFire;
}

void Player::setRuneOfFire(bool newFire)
{
	bRuneOfFire = newFire;
}


bool Player::getSpellBook()
{
	return bSpellBook;
}

void  Player::setSpellBook(bool newSpell)
{
	bSpellBook = newSpell;
}


//this function validates the string input from the user
bool validateInput(string userInput, Player* player, Room* myRooms)
{
	
	if(userInput.compare("south") == 0 || userInput.compare("s") == 0)
	{
		if(myRooms[player->getCurrentRoom()].getDirS() == -1)
		{
				
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "*You can't go south here!*\n\n";
		} 
		else 
		{
			player->setCurrentRoom(myRooms[player->getCurrentRoom()].getDirS());
			roomCreator(myRooms, player, player->getCurrentRoom());
		}
	}
	else if(userInput.compare("north") == 0 || userInput.compare("n") == 0)
	{		
		
			
		if(myRooms[player->getCurrentRoom()].getDirN() == -1)
		{
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "*You can't go north here!*\n\n";
		}
		else 
		{
			player->setCurrentRoom(myRooms[player->getCurrentRoom()].getDirN());
			roomCreator(myRooms, player, player->getCurrentRoom());
		}
	}
	else if(userInput.compare("west") == 0 || userInput.compare("w") == 0)
	{		
		
			
		if(myRooms[player->getCurrentRoom()].getDirW() == -1)
		{
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "*You can't go west here!*\n\n";
		}
		else 
		{
			player->setCurrentRoom(myRooms[player->getCurrentRoom()].getDirW());
			roomCreator(myRooms, player, player->getCurrentRoom());
		}
	}
	else if (userInput.compare("east") == 0 || userInput.compare("e") == 0)
	{		
		
			
		if(myRooms[player->getCurrentRoom()].getDirE() == -1)
		{
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "*You can't go east here!*\n\n";
		}
		else 
		{
			player->setCurrentRoom(myRooms[player->getCurrentRoom()].getDirE());
			roomCreator(myRooms, player, player->getCurrentRoom());
		}
	}
	else if (userInput.compare("cast clarity") == 0 || userInput.compare("cast") == 0)
	{
		if(player->getMagicPoints() >= TWO)
		{
			int newMagicPoints;
			newMagicPoints = player->getMagicPoints() - TWO;
			player->setMagicPoints(newMagicPoints);
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << myRooms[player->getCurrentRoom()].getHint() << endl;
		}
		else
		{
			
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "You do not have enough magic points to cast clarity." << endl;
		}
	}
	else if(userInput.compare("get rune of water") == 0)
	{
		player->setRuneOfWater(true);
		myRooms[player->getCurrentRoom()].setRuneOfWater(false);
		roomCreator(myRooms, player, player->getCurrentRoom());
		cout << "You found the Rune of Water!!!\nThis is needed to open the portal!" << endl;
	}
	else if(userInput.compare("get rune of fire") == 0)
	{
		player->setRuneOfFire(true);
		myRooms[player->getCurrentRoom()].setRuneOfFire(false);
		roomCreator(myRooms, player, player->getCurrentRoom());
		cout << "You found the Rune of Fire!!!\nThis will help you open the portal!" << endl;
	}
	else if(userInput.compare("get book of minds") == 0)
	{
		int oldIntel = 0;
		oldIntel = player->getIntel() + TWO;
		player->setIntel(oldIntel);
		myRooms[player->getCurrentRoom()].setBookOfMinds(false);
		roomCreator(myRooms, player, player->getCurrentRoom());
		cout << "The Book of Minds increased your Intelligence score by two!" << endl;
	}
	else if(userInput.compare("get spellbook") == 0)
	{
		if(myRooms[player->getCurrentRoom()].getSpellBook() == true)
		{
			player->setSpellBook(true);
			myRooms[player->getCurrentRoom()].setSpellBook(false);
			roomCreator(myRooms, player, player->getCurrentRoom());
		}
	}
	else if(userInput.compare("use mana well") == 0)
	{
		int iMagicPoints;
		if(player->getMagicPoints() >= 30)
		{
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "You cannot gain any more magic points beyond what you currently have.\n";
		}
		else
		{
			iMagicPoints = player->getMagicPoints() + TWO;
			player->setMagicPoints(iMagicPoints);
			roomCreator(myRooms, player, player->getCurrentRoom());
			cout << "You feel slightly better.  You gain two magic points." << endl;
		}
	}
	else if(userInput.compare("use portal") == 0)
	{
		if(player->getSpellBook() == true && player->getRuneOfWater() == true && player->getRuneOfFire() == true)
		{
			return false;
		}
		else if (player->getIntel() >= 24)
		{
			return false;
		}
		else
		{
			cout << "\nThe portal does not react to your touch.\n" << "You realize either you are not intelligent enough or you do not have items required." << endl;
		}
	}
	else 
	{
		roomCreator(myRooms, player, player->getCurrentRoom());
		cout << "\n*Please enter n, s, w, or e to move through the tower.*\n" << "Possible action commands are:\nget [item in a room], cast clarity, use [object in room]\n";
	}

}


		

//**********FUNCTION DEFINITIONS FOR GAME STATE
//==REQUIREMENT 13==
//These pointers allow me to reference the player class object and the dynamic array for the rooms outside
//of the function and mutate or access various aspects of those variables.  In this case, the pointer is being passed
//by value, but it's a value of the address to the variables each respectively refers to.
bool playerAction(Player* player, Room* myRooms)
{
	string userInput;
	
	//==REQUIREMENT 12==
	//if I created a bool called stillPlaying, it wouldn't conflict with the one in the start function
	// because the scope of this hypothetical boolean would be only within this function, and once
	//the function ended, it would go out of scope since the function terminated
	bool inGame = true;
	roomCreator(myRooms, player, 0);

	while(inGame)
	{
		
		cout << "What next?";
		//==REQUIREMENT 2==
		getline(cin, userInput);
		inGame = validateInput(userInput, player, myRooms);
	}

	return inGame;
}



void roomCreator(Room* currentRoom, Player* player, int currentNumber)
{

		cout << "\n\n" << endl;
	    cout << currentRoom[player->getCurrentRoom()].sName << endl;
	    cout << currentRoom[player->getCurrentRoom()].sDescription << endl;

	    if(currentRoom[player->getCurrentRoom()].getSpellBook() == true)
	    {
		    cout << "A glowing [spellbook] sits on the floor of the room.\n" << endl;
	    }
	    if(currentRoom[player->getCurrentRoom()].getManaWell() == true)
	    {
		    cout << "A [mana well] sits in the room.\nUse the mana well if you want to restore magic points.\n" << endl;
	    }
	    if(currentRoom[player->getCurrentRoom()].getRuneOfFire() == true)
	    {
		    cout << "The [rune of fire] sits on the floor.\nIt looks like it contains a seething inferno.\n" << endl;
	    }
	    if(currentRoom[player->getCurrentRoom()].getRuneOfWater() == true)
	    {
		    cout << "A [rune of water] sits on the floor.\nYou hear the rush of waves and the torrent of storms.\n" << endl;
	    }
	    if(currentRoom[player->getCurrentRoom()].getBookOfMinds() == true)   
	    {
			cout << "A dark purple book with a glowing eye sits on the floor.\nIt is one of the legendary [book of minds]\n" << endl;
	    }


		if (player->getSpellBook() == true || player->getRuneOfWater() == true || player->getRuneOfFire() == true)
		{
			cout << "\n**PLAYER INVENTORY**\n" << endl;
		}
	    if(player->getSpellBook() == true)
	    {
		    cout << "You have a glowing spellbook." << endl;
	    }
	    if(player->getRuneOfWater() == true)
	    {
		    cout << "The Rune of Water swirls with the power of the oceans and seas." << endl;
	    }
	    if(player->getRuneOfFire() == true)
	    {
		    cout << "The Rune of Fire lies in your pack smoldering, yet seething with intangible heat." << endl;
	    }
		if (player->getSpellBook() == true || player->getRuneOfWater() == true || player->getRuneOfFire() == true)
		{
			cout << "********************\n";
		}
	    
	    cout << "\nIntelligence: " << player->getIntel();
	    cout << "\nMagic Points: " << player->getMagicPoints() << "\n" << endl;

            
}



//==REQUIREMENT 10, 11==
//This function could easily be in start(), however I wanted to demonstrate functional decomposition
void gameIntro(char *argv[], int argc)
{
	string introString1 = "Welcome to Mage Escape: Text Adventure!\n\nYou are an apprentice mage.\nYour master tasked you with activating an ancient portal\nwithin an abandoned mage tower.\n";
	string introString2 = "He said the tower was once the home to an eccentric wizard\nof extraordinary power.\n";
	string introString3 = "Your mission involves solving the mystery of the tower and getting out alive.\n";
	string introString4 = "\nYou, the player, can use the following commands to navigate this world:\n";
	string introString5 = "\nnorth(n),south(s),west(w),east(e), get [some item name], use [some object name],\ncast clarity\n\n";
	string introString6 = "Typing 'cast clarity'gives you hints on where to go next for your objectives!\n";
    string introString7 = "Keep in mind that casting clarity expends magic points!\n";
	string introString8 = "Your mage character's name is ";


	//==REQUIREMENT 4,19,5==
	if (argc == 1 || argc > 2)
	{

		//==REQUIREMENT 17==
		string sIntroArray[TWO][SEVEN];
		sIntroArray[ZERO][ZERO] = introString1;
		sIntroArray[ZERO][ONE] = introString2;
		sIntroArray[ZERO][TWO] = introString3;
		sIntroArray[ZERO][THREE] = introString4;
		sIntroArray[ZERO][FOUR] = introString5;
		sIntroArray[ZERO][FIVE] = introString6;
		sIntroArray[ZERO][SIX] = introString7;
		sIntroArray[ONE][ZERO] = "\n\nPress any key to enter the tower";

		for (int i = 0; i < TWO; ++i)
		{
			if (i == 0)
			{
				for (int j = 0; j < SEVEN; ++j)
				{
					//==REQUIREMENT 1 == 
					cout << sIntroArray[i][j];
				}
			}
			else
			{
				for (int j = 0; j < ONE; ++j)
				{
					cout << sIntroArray[i][j];
				}
			}
		}
	}
	else 
	{
		//==REQUIREMENT 3==
		string mageName = string(argv[ONE]);
		//==REQUIREMENT 17
		string sIntroArray[TWO][NINE];
		sIntroArray[ZERO][ZERO] = introString1;
		sIntroArray[ZERO][ONE] = introString2;
		sIntroArray[ZERO][TWO] = introString3;
		sIntroArray[ZERO][THREE] = introString4;
		sIntroArray[ZERO][FOUR] = introString5;
		sIntroArray[ZERO][FIVE] = introString6;
		sIntroArray[ZERO][SIX] = introString7;
		sIntroArray[ZERO][SEVEN] = introString8;
		sIntroArray[ZERO][EIGHT] = mageName;
		sIntroArray[ONE][ZERO] = "\n\nPress any key to enter the tower";

		for (int i = 0; i < TWO; ++i)
		{
			if (i == 0)
			{
				for (int j = 0; j < NINE; ++j)
				{
					cout << sIntroArray[i][j];
				}
			}
			else
			{
				for (int j = 0; j < ONE; ++j)
				{
					cout << sIntroArray[i][j];
				}
			}

		}
	}
	cin.get();
}


//FUNCTION DEFINITIONS FOR SETTING THE ROOM VALUES   
//==REQUIREMENT 16, 10
//this function recursively sets the initial data for the rooms
void setRoom(Room* myRooms, int size)
{
	switch (size)
	{
	case MAIN_ENTRANCE:
		setMageBase(myRooms, size);
		break;
	case ICY_ROOM:
		setIcyRoom(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case STUDY:
		setStudy(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case FIRE_ROOM:
		setFireRoom(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case FROST_CAVERN:
		setFrostCavern(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case GOLDEN_HALL:
		setGoldenHall(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case INFERNO:
		setInferno(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	case VAULT_OF_LIGHT:
		setVaultOfLight(myRooms, size);
		setRoom(myRooms, size - 1);
		break;
	}
}

void setMageBase(Room *myRooms, const int size)
{
		myRooms[size].sName = "Base of the Mage Tower";
        myRooms[size].sDescription = "You are in a central chamber at the base of the tower.\nYou see three teleporters: a gold one north of you, blue one to your east,\nand a red one to your west.\nYou look up and see a door above each teleporter:\none gold, one blue, and one red.\nNone have platforms to stand on.\nThe [portal] in the room glows with an eerie green energy...";
		myRooms[size].setDirN(STUDY);
		myRooms[size].setDirW(FIRE_ROOM);
        myRooms[size].setDirE(ICY_ROOM);
        myRooms[size].setPortal(true);
		myRooms[size].setHint("This portal needs three items of some kind in order to open it.\nOr if you were somehow more intelligent...");
}

void setIcyRoom(Room* myRooms, const int size)
{
		myRooms[size].sName = "Icy Room";
		myRooms[size].sDescription = "A blue teleporter in this room leads back to the base of the tower.\nIcicles hang off the ceiling and bookshelves dotting the room.\nYou see your breath as it freezes midair.\nThe walls of the room ahead of you are broken leading to an ice cavern.\n";
		myRooms[size].setDirE(FROST_CAVERN);
		myRooms[size].setDirW(MAIN_ENTRANCE);
		myRooms[size].setRuneOfWater(true);
		myRooms[size].setHint("You feel that you need the Rune of Water to open the portal.");
}

void setStudy(Room* myRooms, const int size)
{
		myRooms[size].sName = "Study";
		myRooms[size].sDescription = "A gold teleporter in this room leads back to the base of the tower.\nYou see old bookshelves, cobwebs, and dusty books.\n";
		myRooms[size].setDirS(MAIN_ENTRANCE);
		myRooms[size].setDirN(GOLDEN_HALL);
		myRooms[size].setHint("You sense that an important item lies to the north.");
}

void setFireRoom(Room* myRooms, const int size)
{
		myRooms[size].sName = "Fire Room";
		myRooms[size].sDescription = "A red teleporter in this room leads back to the base of the tower.\nThe room's walls are on fire, yet it does not burn to the touch.\nBooks and papers keeps burning up and reappearing over and over again.\nThe room ahead of you emanates actual heat.\n";
		myRooms[size].setDirE(MAIN_ENTRANCE);
		myRooms[size].setDirW(INFERNO);
		myRooms[size].setBookOfMinds(true);
		myRooms[size].setManaWell(true);
		myRooms[size].setHint("You sense an important object might be west of you.");

}

void setFrostCavern(Room* myRooms, const int size)
{
		myRooms[size].sName = "Frost Cavern";
		myRooms[size].sDescription = "You step out into an ice covered cavern.\nThe stone walls of the tower disappear into pillars of ice.\n";
		myRooms[size].setDirW(ICY_ROOM);
		myRooms[size].setManaWell(true);
		myRooms[size].setHint("The mana well in this room is one of the few.");

}

void setGoldenHall(Room* myRooms, const int size)
{
		myRooms[size].sName = "Golden Hall";
		myRooms[size].sDescription = "The walls are covered in gold and cryptic symbols.\nThe symbols' glow changes between red, green, and blue\nYou see a large vault door to the north left ajar...\n";
		myRooms[size].setDirS(STUDY);
		myRooms[size].setDirN(VAULT_OF_LIGHT);
		myRooms[size].setHint("You sense the room north of you might contain something important");

}	

void setInferno(Room* myRooms, const int size)
{
		myRooms[size].sName = "Inferno";
		myRooms[size].sDescription = "The heat in this room bears down on you.\nThe walls look like a waterfall of molten lava,\nbut are clearly magical in nature.\nThe pools of magical lava coalesce around a center altar.\n";
		myRooms[size].setDirE(FIRE_ROOM);
		myRooms[size].setRuneOfFire(true);
		myRooms[size].setHint("You feel that you need the Rune of Fire to open the portal.");

}

void setVaultOfLight(Room* myRooms, const int size)
{
		myRooms[size].sName= "Vault of Light";
		myRooms[size].sDescription = "Bright light illuminates the vault\nThe beams reflect off the walls creating a prism\nTreasure lines the walls of the room, but each time you try and grab the coins, they disappear\n";
		myRooms[size].setDirS(GOLDEN_HALL);
		myRooms[size].setBookOfMinds(true);
		myRooms[size].setSpellBook(true);
		myRooms[size].setHint("You feel that if you can find two of the legendary books of minds,\nyou could open the portal without the three items.");

}
