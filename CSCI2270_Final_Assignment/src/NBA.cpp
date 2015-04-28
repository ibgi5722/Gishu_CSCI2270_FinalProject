#include "../include/NBA.h"
#include <math.h>

using std::cout;
using std::endl;

NBA::NBA()
{
    nil = new BasketballTeams();
    nil->isRed = false;
    root = nil;
}

NBA::~NBA()
{
    //dtor
}

/*
Function Prototype:
void NBA::addTeam(string, string, float, string, float, float, float, float, float, float, float)

Function Description:
This method adds the teams to a red and black tree and calls a method to add the players to a hash table within the teams.
It also checks to see if the team has already been added

Example:
NBA *nba = new NBA();
nba->addTeam(strTeamName, strPlayerName, floatPlayerNumber, strPosition, floatGamesPlayed, floatPoints, floatRebounds, floatSteals, floatAssists, floatTurnovers, floatFouls);

Precondition: Must be called in while looping through the lines in the file after you have stored each
portion of the line. Unused spaces in tree are nil while unused spaces in hash table are NULL.
tName = Team Name
pName = Player Name
number = Player Number
position = Player Position
played = Game Played
points = Number of Points Scored
rebounds = Number of Rebounds Player has
steals = Number of Steals Player has
assists = Number of Assists Player has
turnovers = Number of Turnovers Player has
fouls = Number of Fouls Player has
Postconditions: The team has been added to the tree if not already there and the player has been added
to the hash table for the appropriate team.
*/

void NBA::addTeam(std::string tName, std::string pName, float number, std::string position, float played, float points, float rebounds, float steals, float assists, float turnovers, float fouls)
{
    BasketballPlayer *player = new BasketballPlayer(pName, number, position, played, points, rebounds, steals, assists, turnovers, fouls);
    bool added = false;
    BasketballTeams *rootTemp = root;
    BasketballTeams *team;
    if(!(searchVector(tName)))      //Checks if the team has already been added to the tree
    {
        hashTable = new BasketballPlayer*[10];
        for(int i = 0;i < 10; i++)
        {
            hashTable[i] = NULL;
        }
        teamNameVector.push_back(tName);        //adds tho vector to show that it has already been added to the tree
        team = new BasketballTeams(tName);
        team->left = nil;
        team->right = nil;
        team->hashPlayer = hashTable;
        if(root == nil)
        {
            team->parent = nil;
            root = team;
        }
        else
        {
            while(!added)
            {
                if(team->strName.compare(rootTemp->strName) < 0)
                {
                    if(rootTemp->left == nil)
                    {
                        rootTemp->left = team;
                        team->parent = rootTemp;
                        added = true;
                    }
                    else
                    {
                        rootTemp = rootTemp->left;
                    }
                }
                else
                {
                    if(rootTemp->right == nil)
                    {
                        rootTemp->right = team;
                        team->parent = rootTemp;
                        added = true;
                    }
                    else
                    {
                        rootTemp = rootTemp->right;
                    }
                }
            }
        }
        rbAddFixup(team);       //restores the r and black properties of the tree
    }
    insertPlayer(player, hashTable);        //adds the player to the hash table
}

/*
Function Prototype:
void NBA::insertPlayer(BasketballPlayer*, BasketballPlayer**)

Function Description:
This method adds the player to the hash table for the specific team and handles collisions through
a linked list.

Example:
insertPlayer(player, hashTable);

Precondition: Must be called after the player pointer has been created and after the hash table has
been initialized to NULL for empty spaces. also requires the HASH(string) method
p = Player pointer
hashTable = Hash table of players specific to team
Postconditions: The player has been added to the hash table at the proper location with collisions
creating a linked list.
*/

void NBA::insertPlayer(BasketballPlayer* p, BasketballPlayer** hashTable)
{
    int index = Hash(p->strName);       //hash's the string to determine the location int the array the player should be
    if(hashTable[index] == NULL)        //No collision
    {
        hashTable[index] = p;
    }
    else                                //Collision
    {
        BasketballPlayer *temp = hashTable[index];
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = p;
    }
}

/*
Function Prototype:
void NBA::rbAddFixup(BasketballTeams*)

Function Description:
This method resets the red and black properties for the tree of teams.

Example:
rbAddFixup(team);

Precondition: Must be called in the addTeam(); method after the team has been added to the tree.
requires that at least one team be in the tree and that leftRotate() and rightRotate() be defined.
x = The basketball team most recently added to the tree
Postconditions: The red and black properties of the tree are restored and the tree is balanced.
*/

void NBA::rbAddFixup(BasketballTeams *x)
{
    x->left = nil;
    x->right = nil;
    x->isRed = true;
    while ( (x != root) && (x->parent->isRed == true) )
    {
        if (x->parent == x->parent->parent->left)
        {
            BasketballTeams *y = x->parent->parent->right;
            if (y->isRed == true)
            {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    leftRotate(x);
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            BasketballTeams *y = x->parent->parent->left;
            if ( y->isRed == true)
            {
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            }
            else
            {
                if ( x == x->parent->left)
                {
                    x = x->parent;
                    rightRotate(x);
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);
            }
        }
    }
    root->isRed = false;
}

/*
Function Prototype:
void NBA::leftRotate(BasketballTeams*)

Function Description:
Shifts the tree to the left and balances it if the tree is heavier on the right

Example:
leftRotate(team);

Precondition: Must be called in rbAddFixup and meet the conditons for rbAddFixup.
Must be more than one item in tree.
x = Pointer of team to rotate about
Postconditions: The x pointer will become the left pointer of the x->right while maintaining
BST and red and black tree properties.
*/

void NBA::leftRotate(BasketballTeams *x)
{
    BasketballTeams *w = x->right;
    x->right = w->left;
    if(w->left != nil)
    {
        w->left->parent = x;
    }
    w->parent = x->parent;
    if(x->parent == nil)
    {
        root = w;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = w;
    }
    else
    {
        x->parent->right = w;
    }
    w->left = x;
    x->parent = w;
}

/*
Function Prototype:
void NBA::rightRotate(BasketballTeams*)

Function Description:
Shifts the tree to the right and balances it if the tree is heavier on the left

Example:
rightRotate(team);

Precondition: Must be called in rbAddFixup and meet the conditons for rbAddFixup.
Must be more than one item in tree.
x = Pointer of team to rotate about
Postconditions: The x pointer will become the right pointer of the x->left while maintaining
BST and red and black tree properties.
*/

void NBA::rightRotate(BasketballTeams *x)
{
    BasketballTeams *w = x->left;
    x->left = w->right;
    if(w->right != nil)
    {
        w->right->parent = x;
    }
    w->parent = x->parent;
    if(x->parent == nil)
    {
        root = w;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = w;
    }
    else
    {
        x->parent->right = w;
    }
    w->right = x;
    x->parent = w;
}

/*
Function Prototype:
bool NBA::searchVector(string)

Function Description:
Searches a vector of team names that have been added to the tree and returns true if tName is equal
to any of the strings

Example:
searchVector(teamName);

Precondition: Must be called in addTeam() method to check if a new team needs to be added to the tree
or just a player to the hash table
tName = Team Name
Postconditions: Verification that the team has or has not been added to the tree
*/

bool NBA::searchVector(std::string tName)
{
    bool found = false;
    for(int i = 0; i<teamNameVector.size(); i++)
    {
        if(teamNameVector[i] == tName)
        {
            found = true;
            break;
        }
    }
    return found;
}

/*
Function Prototype:
void NBA::printTeams()

Function Description:
Calls the private printTeams() method

Example:
NBA *nba = new NBA();
nba->printTeams();

Precondition: The tree must be built and the user must select print teams
Postconditions: The Team names have been printed in the console
*/

void NBA::printTeams()
{
    printTeams(root);
}

/*
Function Prototype:
void NBA::printTeams(BasketballTeams*)

Function Description:
Recursively prints the team names from the tree

Example:
printTeams(team);

Precondition: The tree must be built and the user must select print teams
Also called within public printTeams()
Postconditions: The Team names have been printed in the console
*/

void NBA::printTeams(BasketballTeams *rootTemp)
{
    if(rootTemp->left != nil)
    {
        printTeams(rootTemp->left);
    }
    std::cout<<rootTemp->strName<<std::endl;
    if(rootTemp->right != nil)
    {
        printTeams(rootTemp->right);
    }
}

/*
Function Prototype:
BasketballTeams* NBA::selectTeam(string)

Function Description:
Searches the tree for the team specified by the string inputed from the user

Example:
NBA *nba = new NBA();
BasketballTeams *team;
team = nba->selectTeam(tName);

Precondition: Tree must be built and have empty spaces signified by nil
tName = Team Name
Postconditions: Search the tree and returns the team pointer that has the same name as tName
*/

BasketballTeams* NBA::selectTeam(std::string tName)
{
    BasketballTeams* base = root;
    while(base != nil)
    {
        if(base->strName == tName)
        {
            return base;
        }
        else
        {
            if(tName.compare(base->strName) < 0)
            {
                base = base->left;
            }
            else
            {
                base = base->right;
            }
        }
    }
    cout<<"Not found"<<endl;
    return NULL;        //returns NULL if not found so that menu can reprint
}

/*
Function Prototype:
void NBA::printRoster(BasketballTeams*)

Function Description:
This method goes through the hash table of the user specified team and adds them to a vector to be sorted

Example:
NBA *nba = new NBA();
nba->printRoster(team);

Precondition: Tree must be built and hash table must be built.
Must be called after selectTeam() and passed in what is returned from that method
team = pointer to a team in the tree
Postconditions: The roster for the specified team will be printed in alphabetical order
*/

void NBA::printRoster(BasketballTeams* team)
{
    bool emp = true;
    std::vector<BasketballPlayer*> collisions;
    for(int i = 0; i<10; i++)
    {
        if(team->hashPlayer[i] != NULL)
        {
            BasketballPlayer *temp = team->hashPlayer[i];
            while(temp != NULL)
            {
                collisions.push_back(temp);
                temp = temp->next;
            }
            emp = false;
        }
    }
    if(emp)
    {
        cout<<"empty"<<endl;
    }
    sortPlayers(collisions);
}

/*
Function Prototype:
void NBA::sortPlayers(vector<BasketballPlayer*>)

Function Description:
Sorts the vector passed into alphabetical order and then prints it

Example:
sortPlayers(collisions);

Precondition: Called in printRoster() method after the players have been added to the collisions vector
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed
*/

void NBA::sortPlayers(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->strName.compare(collisions[i]->strName) < 0) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<std::endl;
    }
}

/*
Function Prototype:
void NBA::printPlayerInfo(BasketballTeams*, string)

Function Description:
Finds the player name(from user) in the hashTable for the team and prints out the information for that player

Example:
NBA *nba = new NBA();
nba->printPlayerInfo(team, playerName);

Precondition: Tree must be built and hash table must be built. called selectTeam() method and passed in return
from that method as team.
team = pointer to team
pName = Player Name
Postconditions: The player info has been printed to the console
*/

void NBA::printPlayerInfo(BasketballTeams* team, std::string pName)
{
    int x = Hash(pName);
    bool found = false;
    BasketballPlayer *temp = team->hashPlayer[x];
    while(temp != NULL)
    {
        if(temp->strName == pName)
        {
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout<<"    "<<temp->strName<<" - #"<<temp->floatPlayerNumber<<std::endl;
            std::cout<<"Position:"<<" "<<temp->strPosition<<endl;
            std::cout<<"Games Played:"<<" "<<temp->floatGamesPlayed<<endl;
            std::cout<<"Points:"<<" "<<temp->floatPoints<<endl;
            std::cout<<"Rebounds:"<<" "<<temp->floatRebounds<<endl;
            std::cout<<"Steals:"<<" "<<temp->floatSteals<<endl;
            std::cout<<"Assists:"<<" "<<temp->floatAssists<<endl;
            std::cout<<"Turnovers:"<<" "<<temp->floatTurnovers<<endl;
            std::cout<<"Fouls:"<<" "<<temp->floatFouls<<endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if(found == false)
    {
        std::cout<<"not found"<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankBy(BasketballTeams*, int)

Function Description:
adds the player from the hash table of the specified team to a vector and sorts by what the user wants

Example:
NBA *nba = new NBA();
nba->rankBy(team, x);

Precondition: Tree and hash table must be built and selectTeam() called.
team = Pointer to user specified team
x = Menu Option
Postconditions: The roster of the specific team has been printed in sorted order by what the user specified
*/

void NBA::rankBy(BasketballTeams* team, int x)
{
    bool isEmpty = true;
    std::vector<BasketballPlayer*> collisions;
    for(int i = 0; i<10; i++)
    {
        if(team->hashPlayer[i] != NULL)
        {
            BasketballPlayer *temp = team->hashPlayer[i];
            while(temp != NULL)
            {
                collisions.push_back(temp);
                temp = temp->next;
            }
            isEmpty = false;
        }
    }
    switch(x)
    {
        case 1:
            rankByPlayerNumber(collisions);
            break;
        case 2:
            rankByGamesPlayed(collisions);
            break;
        case 3:
            rankByPoints(collisions);
            break;
        case 4:
            rankByRebounds(collisions);
            break;
        case 5:
            rankBySteals(collisions);
            break;
        case 6:
            rankByAssists(collisions);
            break;
        case 7:
            rankByTurnovers(collisions);
            break;
        case 8:
            rankByFouls(collisions);
            break;
    }
}

/*
Function Prototype:
void NBA::rankByPlayerNumber(vector<BasketballPlayer*>)

Function Description:
Rank the players ascending order by there number

Example:
rankByPlayerNumber(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 1
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in ascending order by number
*/

void NBA::rankByPlayerNumber(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatPlayerNumber < collisions[i]->floatPlayerNumber) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatPlayerNumber<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankByGamesPlayed(vector<BasketballPlayer*>)

Function Description:
Rank the players descending order by the number of games played

Example:
rankByGamesPlayed(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 2
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in descending order by games played
*/

void NBA::rankByGamesPlayed(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatGamesPlayed > collisions[i]->floatGamesPlayed) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatGamesPlayed<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankByPoints(vector<BasketballPlayer*>)

Function Description:
Rank the players descending order by the number of points

Example:
rankByPoints(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 3
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in descending order by points
*/

void NBA::rankByPoints(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatPoints > collisions[i]->floatPoints) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatPoints<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankByRebounds(vector<BasketballPlayer*>)

Function Description:
Rank the players descending order by the number of rebounds

Example:
rankByRebounds(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 4
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in descending order by rebounds
*/

void NBA::rankByRebounds(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatRebounds > collisions[i]->floatRebounds) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatRebounds<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankBySteals(vector<BasketballPlayer*>)

Function Description:
Rank the players descending order by the number of steals

Example:
rankBySteals(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 5
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in descending order by steals
*/

void NBA::rankBySteals(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatSteals > collisions[i]->floatSteals) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatSteals<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankByAssists(vector<BasketballPlayer*>)

Function Description:
Rank the players descending order by the number of assists

Example:
rankByAssists(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 6
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in descending order by assists
*/

void NBA::rankByAssists(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatAssists > collisions[i]->floatAssists) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatAssists<<std::endl;
    }
}


/*
Function Prototype:
void NBA::rankByTurnovers(vector<BasketballPlayer*>)

Function Description:
Rank the players ascending order by the number of turnovers

Example:
rankByTurnovers(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 7
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in ascending order by turnovers
*/

void NBA::rankByTurnovers(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatTurnovers < collisions[i]->floatTurnovers) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatTurnovers<<std::endl;
    }
}

/*
Function Prototype:
void NBA::rankByFouls(vector<BasketballPlayer*>)

Function Description:
Rank the players ascending order by the number of fouls

Example:
rankByFouls(collisions);

Precondition: Called in rankBy() method after the players have been added to the collisions vector if user selects 8
collisions = vector of all the items in the hash table
Postconditions: The Roster has been printed in ascending order by fouls
*/

void NBA::rankByFouls(std::vector<BasketballPlayer*> collisions)
{
    bool boolFlag = true;       //flag to see if any switches happened
    int intD = collisions.size();
    BasketballPlayer* wordTemp;     //creates temp class to store variables temporarily
    while( boolFlag || (intD > 1))      //if a switch has not occurred it must be sorted;
    {
        boolFlag = false;           //initialize flag to false to check for future switches
        intD = (intD+1) / 2;
        for (int i = 0; i < (collisions.size() - intD); i++)
        {
            if (collisions[i + intD]->floatFouls < collisions[i]->floatFouls) //compares the first item with another item halfway through the array
            {
                wordTemp = collisions[i + intD];      //switch positions i+d and i
                collisions[i + intD] = collisions[i];
                collisions[i] = wordTemp;
                boolFlag = true;                  //tells switch has occurred
            }
        }
    }
    for(int x = 0; x<collisions.size(); x++)
    {
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatFouls<<std::endl;
    }
}

/*
Function Prototype:
void NBA::printTeamStats(BasketballTeams*)

Function Description:
Averages out the values for each of the players int a specific team and prints out the values

Example:
NBA *nba = new NBA();
nba->printTeamStats(team);

Precondition: The tree and the hash table must be built and the user must select a team to pass through
selectTeam().
team = pointer to team in tree
Postconditions: The averages of the values are printed into the console and stored int the team pointer
*/

void NBA::printTeamStats(BasketballTeams* team)
{
    float points = 0;
    float rebounds = 0;
    float steals = 0;
    float assists = 0;
    float turnovers = 0;
    float fouls = 0;
    int numOfPlayers = 0;
    for(int i = 0; i<10; i++)
    {
        if(team->hashPlayer[i] != NULL)
        {
            BasketballPlayer *temp = team->hashPlayer[i];
            while(temp != NULL)
            {
                numOfPlayers++;
                points += temp->floatPoints;
                rebounds += temp->floatRebounds;
                steals += temp->floatSteals;
                assists += temp->floatAssists;
                turnovers += temp->floatTurnovers;
                fouls += temp->floatFouls;
                temp = temp->next;
            }
        }
    }
    team->floatPoints = points/numOfPlayers;
    team->floatRebounds = rebounds/numOfPlayers;
    team->floatSteals = steals/numOfPlayers;
    team->floatAssists = assists/numOfPlayers;
    team->floatTurnovers = turnovers/numOfPlayers;
    team->floatFouls = fouls/numOfPlayers;
    cout<<"Points: "<<floor((team->floatPoints)*10 + 0.5)/10<<endl;
    cout<<"Rebounds: "<<floor((team->floatRebounds)*10 + 0.5)/10<<endl;
    cout<<"Steals: "<<floor((team->floatSteals)*10 + 0.5)/10<<endl;
    cout<<"Assists: "<<floor((team->floatAssists)*10 + 0.5)/10<<endl;
    cout<<"Turnovers: "<<floor((team->floatTurnovers)*10 + 0.5)/10<<endl;
    cout<<"Fouls: "<<floor((team->floatFouls)*10 + 0.5)/10<<endl;
}

/*
Function Prototype:
int NBA::Hash(string)

Function Description:
After hashing the string by adding ASCII values and dividing by array size then
returns the value which is the position in an array that the string should be placed.

Example:
Hash(playerName);

Precondition: Hash table must be initialized to NULL with 10 spaces
pName = Player Name
Postconditions: Returns the position the string should be placed
*/

int NBA::Hash(std::string pName)
{
    int sum = 0;
    for(int i = 0; i<pName.size(); i++)
    {
        sum = sum + pName[i];
    }
    return sum%10;
}
