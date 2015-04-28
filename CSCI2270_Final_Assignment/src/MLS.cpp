
#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/MLS.h"
MLS::MLS()
{
    nil = new SoccerTeam();
    nil->isRed = false;
    root = nil;
}

MLS::~MLS()
{
    //dtor
}

/*
1.bool searchVector(std::string tName);
2.This method gets passed in a team name, and it loops through the vector of team names until a matching string is found. The function returns a boolean that determines whether or not a team is in the vector.
3.An example of how to call this method is to set it equal to a boolean: bool isTeamInVector = searchVector(teamName)
4.The pre-condition for this method requires that the vector of team names must already be created
5.There are no post-conditions for this method, as it simply returns a boolean
*/
bool MLS::searchVector(std::string tName)
{
    bool foundTeam = false; //initializes a boolean that stores if a team is in the vector to false
    for(int i = 0; i < teamVector.size(); i++) //loops through the vector that stores all of the teams in the MLS
    {
        if(tName == teamVector[i]) //if the team name that the user is searching for is in the vector
        {
            foundTeam = true; //a boolean is set to true
        }
    }
    return foundTeam; //returns the boolean
}

/*
1.void insertTeam(std::string tName, std::string pName, int pAge, int pNumber, std::string pPosition, int minutes, int goals, int assists, int savePercent, int yellowCards, int redCards);
2.This method gets passed in a team name, and all the player stats and details from the file. This method initializes the hash table, as well as adding all the teams to a tree before passing the tree
on to the rbAddFixup and passing the players into another method to be added to the hash table.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls;
mls->insertTeam(strTeamName, strPlayerName, intPlayerAge, floatPlayerNumber, strPosition, intMinutes, intGoals, floatAssists, intSavePercentage, intYellowCards, intRedCards);
This should be done as each line is read in from the file and the data is separated into its appropriate type.
4.The pre-condition for this method requires that the searchVector function be called to ensure each team is only added to the vector once.
5.Once this function is completed, the red black tree will be built (and balanced after other functions are called within this method), and the hash table will be built (and filled out after
calling separate functions within this function). Also,every team will point to a hash table, and every player will have the information necessary to fill out the struct.
*/
void MLS::insertTeam(std::string tName, std::string pName, int pAge, int pNumber, std::string pPosition, int minutes, int goals, int assists, int savePercent, int yellowCards, int redCards)
{
    bool addedToTree = false;
    SoccerTeam *newTeam;
    SoccerPlayer *newPlayer = new SoccerPlayer(pName, pAge, pNumber, pPosition, minutes, goals, assists, savePercent, yellowCards, redCards);
    SoccerTeam *tempRoot = root;
    if(!(searchVector(tName))) //calls the search vector method, and only enters the if statement if the method returns false
    {
        hashTable = new SoccerPlayer*[10];
        for(int i = 0; i < 10; i++)
        {
            hashTable[i] = NULL; //initializes the first row of the hash table to be NULL
        }
        teamVector.push_back(tName); //adds a team to the team vector
        newTeam = new SoccerTeam(tName); //creates a new team of type SoccerTeam (struct defined in the header file)
        newTeam->leftChild = nil; //initializes the left child to nil
        newTeam->rightChild = nil; //initializes the teams right child to nil
        newTeam->playerHashTable = hashTable; //points the team to a hash table that will store the players

        if(root == nil) //if the tree has not been built then the first team is set as the root
        {
            newTeam->parent = nil;
            root = newTeam;
        }
        else
        {
            while(addedToTree == false)
            {
                if(newTeam->nameStr.compare(tempRoot->nameStr) < 0) //compares team names to see which comes first alphabetically
                {
                    if(tempRoot->leftChild == nil) //if the node has no left child
                    {
                        tempRoot->leftChild = newTeam; //sets the node's left child to the team being added to the tree
                        newTeam->parent = tempRoot; //sets the new teams parent to the node
                        addedToTree = true; //informs the program that the new team has been added to the tree
                    }
                    else
                    {
                        tempRoot = tempRoot->leftChild; //moves the temporary node to its left child
                    }

                }
                else
                {
                    if(tempRoot->rightChild == nil) //if the right child of the node is nil
                    {
                        tempRoot->rightChild = newTeam; //sets the teams right child to the new team
                        newTeam->parent = tempRoot; //sets the new teams parent to the node
                        addedToTree = true; //sets the boolean to true
                    }
                    else
                    {
                        tempRoot = tempRoot->rightChild; //move the temporary node to its right child
                    }
                }
            }
        }
        rbAddFixup(newTeam); //calls the rbAddFixup method which balances the red black tree
    }
    insertPlayer(newPlayer, hashTable);
    newTeam = searchTree(tName);
}

/*
1.SoccerTeam* searchTree(std::string tName);
2.This method gets passed in a team name, and it traverses through the tree until it finds a match for the team name in the tree. Once a match is found, the method returns the team
3.An example of how to call this method is to set it equal to a variable of type SoccerTeam: SoccerTeam *newTeam = searchTree(teamName);
4.The pre-condition for this method requires that the red black tree of all the team names already exist
5.There are no post-conditions for this method, as it simply returns a SoccerTeam
*/
SoccerTeam* MLS::searchTree(std::string tName)
{
    SoccerTeam *tempRoot = root; //sets a temporary node to the root
    while(tempRoot != nil)
    {
        if(tName == tempRoot->nameStr) //if the temp root is the team being searched for
        {
            return tempRoot; //return the node
        }
        else
        {
            if(tName.compare(tempRoot->nameStr) < 0) //if the team being searched for is before the current node alphabetically
            {
                tempRoot = tempRoot->leftChild; //moves the node to the left
            }
            else
            {
                tempRoot = tempRoot->rightChild; //else the node moves to the right
            }
        }
    }
    return tempRoot; //returns the team once it is found in the tree
}

/*
1.void printTeams();
2.This method is the public print team method that is called from the main. It simply calls the private method on the root.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls; Then, the function can be called by calling mls->printTeams();
4.The pre-condition for this method requires that the tree exist so that the root exists and the program isn't trying to print NULL
5.There are no post-conditions for this method, as it simply calls another method
*/
void MLS::printTeams()
{
    printTeams(root); //calls the private print team method on the root
}

/*
1.void printTeams(SoccerTeam *temp);
2.This method is a private method that recursively calls itself starting at the root of the red black tree and printing all the team names in alphabetical order.
3.An example of how to call this method is to use a public function by calling: printTeams(root);
4.The pre-condition for this method requires that the public method printTeams() be called so that this function can be called on the root.
5.There are no post-conditions for this method, as it simply prints team names from the tree.
*/
void MLS::printTeams(SoccerTeam *tempRoot)
{
    if(tempRoot->leftChild != nil)
    {
        printTeams(tempRoot->leftChild); //recursively calls the print teams function on the left child
    }
    std::cout <<  tempRoot->nameStr << std::endl; //prints the team name
    if(tempRoot->rightChild != nil)
    {
        printTeams(tempRoot->rightChild); //recursively calls the print teams function on the right child
    }
}

/*
1.void rbAddFixup(SoccerTeam * x);
2.This method gets passed in a team and sets the red black properties for the tree. It also calls for left and right rotations so that the red black tree ends up balanced and follows the rules of red black trees.
3.This method should be called after a team is added to the tree in a way such as this: rbAddFixup(newTeam);
4.The pre-condition for this method requires that there is at least one team in the red black tree. For that to happen, the insertTeam method must be called before the rbAddFixup.
5.Once the rbAddFixup method finished running, the red black tree will be balanced in such a way that it fulfills the standard properties and rules of a red black tree.
*/
void MLS::rbAddFixup(SoccerTeam * x)
{
    x->leftChild = nil;
    x->rightChild = nil;
    x->isRed = true;
    while ( (x != root) && (x->parent->isRed == true) )
    {
        if ( x->parent == x->parent->parent->leftChild )
        {
           SoccerTeam *y = x->parent->parent->rightChild;
           if ( y->isRed == true )
           {
              x->parent->isRed = false;
              y->isRed = false;
              x->parent->parent->isRed = true;
              x = x->parent->parent;
            }
            else
            {
                if ( x == x->parent->rightChild )
                {
                    x = x->parent;
                    leftRotate(x);

                }
              x->parent->isRed = false;
              x->parent->parent->isRed = true;
              rightRotate(x->parent->parent );
            }
        }
      else
      {
          SoccerTeam *y = x->parent->parent->leftChild;
          if ( y->isRed == true )
          {
             x->parent->isRed = false;
             y->isRed = false;
             x->parent->parent->isRed = true;
             x = x->parent->parent;
           }
           else
           {
               if ( x == x->parent->leftChild )
               {
                   x = x->parent;
                   rightRotate(x);
               }
             x->parent->isRed = false;
             x->parent->parent->isRed = true;
             leftRotate(x->parent->parent );
           }
      }
    }
    root->isRed = false;
}

/*
1.void leftRotate(SoccerTeam * x);
2.This method gets passed in a team from the red black tree, and manipulates the nodes in the tree in such a way that the tree is rotated to the left, in an attempt to follow the rules of red black trees,
thus balancing the tree.
3.This method should just be called inside another method: leftRotate(team);
4.The pre-condition for this method requires that the rbAddFunction call for a left rotation, and that the red black tree must already exist.
5.The post-conditions of this method are that the teams in the red black tree will be rotated to the left
*/
void MLS::leftRotate(SoccerTeam * x)
{
    SoccerTeam *y;
    y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild != nil )
    {
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    if ( x->parent == nil )
    {
        root = y;
    }
    else if ( x == x->parent->leftChild )
    {
        x->parent->leftChild = y;
    }
    else
    {
        x->parent->rightChild = y;
    }
    y->leftChild = x;
    x->parent = y;
}

/*
1.void rightRotate(SoccerTeam * y);
2.This method gets passed in a team from the red black tree, and manipulates the nodes in the tree in such a way that the tree is rotated to the right, in an attempt to follow the rules of red black trees,
thus balancing the tree.
3.This method should just be called inside another method: rightRotate(team);
4.The pre-condition for this method requires that the rbAddFunction call for a right rotation, and that the red black tree must already exist.
5.The post-conditions of this method are that the teams in the red black tree will be rotated to the right
*/
void MLS::rightRotate(SoccerTeam * y)
{
    SoccerTeam *x = y->leftChild;
    y->leftChild = x->rightChild;
    if(x->rightChild != nil)
    {
        x->rightChild->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nil)
    {
        root = x;
    }
    else if (y == y->parent->leftChild)
    {
        y->parent->leftChild = x;
    }
    else
    {
        y->parent->rightChild = x;
    }
    x->rightChild = y;
    y->parent = x;
}

/*
1.bool searchVector(std::string tName);
2.This method gets passed in a players name, and calculates the hash sum of that name by looping through the string. The remainder of this sum when divided by 10 is returned.
3.An example of how to call this method is to set it equal to an integer: int sum = hashSum(playerName);
4.The pre-condition for this method requires that the insertPlayer function be called, as that is where players are added to the hash table and where the hash sum is needed.
5.There are no post-conditions for this method, as it simply returns an integer that will be used to determine the placement of a player in the hash table.
*/
int MLS::hashSum(std::string playerName)
{
    int i = 0;
    for(int j = 0; j < playerName.size(); j++) //loops through the string that is passed into the function
    {
        i = i + playerName[j]; //calculates the hash sum
    }
    return i%10; //returns the remainder when dividing the sum by 10
}

/*
1.void insertPlayer(SoccerPlayer *player, SoccerPlayer **hashTable);
2.This method gets passed in a player of the struct type SoccerPlayer and the hash table that the player will be added to. The player is added to the hash table if the index of that player is NULL, or
the player is added to a linked list at that index if there is already a player(or players) there.
3.An example of how to call this method is: insertPlayer(newPlayer, hashTable);
4.The pre-condition for this method requires that the hash table be initialized to NULL and a pointer from the team to hash table be established
5.The post-conditions are that once this method has been completed, a new player will have been added to a specific hash table that is pointed to by a team in the red black tree.
*/
void MLS::insertPlayer(SoccerPlayer *player, SoccerPlayer **hashTable)
{
    int i = hashSum(player->nameStr); //finds the hash sum of the players name
    if(hashTable[i] == NULL) //if the table is empty at the index of the players name
    {
        hashTable[i] = player; //adds the player to the hash table
    }
    else
    {
        SoccerPlayer *temp = hashTable[i];
        while(temp->next != NULL)
        {
            temp = temp->next; //loops through the linked list
        }
        temp->next = player; //adds the player to the end of the linked list
    }
}

/*
1.SoccerTeam* selectTeam(std::string tName);
2.This method gets passed in a team name, and it loops through the red black tree of teams until a match is found. Once the team is found, the node is returned.
3.An example of how to call this method is to set it equal to a variable of type SoccerTeam: SoccerTeam *TeamPointer = mls->selectTeam(team);
4.The pre-condition for this method requires that the user input a team name and that the red black tree of teams already be built
5.There are no post-conditions for this method, as it simply returns a node
*/
SoccerTeam* MLS::selectTeam(std::string tName)
{
    SoccerTeam *node = root;
    while(node != nil)
    {
        if(tName == node->nameStr)
        {
            return node;
        }
        else
        {
            if(tName.compare(node->nameStr) < 0)
            {
                node = node->leftChild;
            }
            else
            {
                node = node->rightChild;
            }
        }
    }
    std::cout<<"Team Not Found"<<std::endl;
    return NULL;
}

/*
1.void printRoster(SoccerTeam *temp);
2.This method gets passed in a team selected by the user and loops through that teams player has table, storing them all in a vector, and passing that vector into the sortRoster method.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls; Then, the function can be called by calling mls->printRoster(team)
4.The pre-condition for this method requires that the hash table of players already be built, and that the selectTeam method has already been called and stored a team to pass into the method.
5.There are no post-conditions for this method, as it simply stores the hash table in a temporary vector which is then passed into a new function to be sorted and printed
*/
void MLS::printRoster(SoccerTeam *temp)
{
    std::vector<SoccerPlayer*> collisions;
    bool isEmpty = true;
    for(int i = 0; i < 10; i++)
    {
        if(temp->playerHashTable[i] != NULL)
        {
            SoccerPlayer *index = temp->playerHashTable[i];
            while(index != NULL)
            {
                collisions.push_back(index); //the if statement and while loop and index = index-> next loop through the hash table and add the players to a vector
                index = index->next;
            }

            isEmpty = false;
        }
    }
    if(isEmpty == true)
    {
        std::cout << "empty" << std::endl;
    }
    sortRoster(collisions); //once the vector is created it will be sorted in the sort roster method
}

/*
1.void sortRoster(std::vector<SoccerPlayer*> collisions);
2.This method gets passed in a vector that contains a teams roster so that it may be sorted. The roster is sorted alphabetically and once the sort is finished, the method loops through
the vector and prints the player names.
3.An example of how to call this method is to simply call sortRoster(vectorName); as nothing is returned
4.The pre-condition for this method requires that the hash table of players already be stored in a temporary vector, and that the printRoster function be called, as that is where the sortRoster is called from.
5.There are no post-conditions for this method, as it stores the roster in a temporary vector and prints the sorted data
*/
void MLS::sortRoster(std::vector<SoccerPlayer*> collisions)
{
    bool newBool = true;
    int vectorsize = collisions.size();
    SoccerPlayer *temp;
    while(newBool || (vectorsize>1))
    {
        newBool = false;
        vectorsize = (vectorsize+1)/2;
        for(int i = 0; i < (collisions.size() - vectorsize); i++)
        {
            if(collisions[i+vectorsize]->nameStr.compare(collisions[i]->nameStr) < 0) //compares the player names so they can be sorted alphabetically
            {
                temp = collisions[i+vectorsize];
                collisions[i+vectorsize] = collisions[i];
                collisions[i] = temp;
                newBool = true;
            }
        }
    }
    int z;
    for(int j = 0; j < collisions.size(); j++) //loops through the sorted vector of the roster
    {
        std::cout << collisions[j]->nameStr << std::endl; //prints the team names
    }
}

/*
1.void printPlayerInfo(std::string player, SoccerTeam *team);
2.This method gets passed in a team  pointer and a players name. The method loops through the teams roster to find the player specified by the user, and the players basic info and statistics are printed.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls; Then, the function can be called by calling mls->printPlayerInfo(playerName, team)
4.The pre-condition for this method requires that the hash table of a teams roster be created already, and that the selectTeam method has already been called and that team is being passed into the method
5.There are no post-conditions for this method, as it is just printing a players data and not affecting the pointers
*/
void MLS::printPlayerInfo(std::string player, SoccerTeam *team)
{
    bool boolfoundPlayer = false;
    SoccerPlayer *foundPlayer;
    for(int i = 0; i < 10; i++)
    {
        if(team->playerHashTable[i] != NULL)
        {
            SoccerPlayer *index = team->playerHashTable[i];
            while(index != NULL)
            {
                if(index->nameStr == player)
                {
                    foundPlayer = index;
                    boolfoundPlayer = true;
                }
                index = index->next;
            }
        }
    }
    if(boolfoundPlayer != true)
    {
        std::cout << "Player Not Found" << std::endl;
    }
    else
    {

        if(foundPlayer->positionStr == "GK") //if the player is a goalie, save percentage will be printed, and not goals and assists
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Name: " << foundPlayer->nameStr << std::endl;
            std::cout << "Team: " << team->nameStr << std::endl;
            std::cout << "Age: " << foundPlayer->ageInt << std::endl;
            std::cout << "Number: " << foundPlayer->jerseyNumberInt << std::endl;
            std::cout << "Position: " << foundPlayer->positionStr << std::endl;
            std::cout << "Minutes: " << foundPlayer->minutesInt << std::endl;
            std::cout << "Save Percentage: " << foundPlayer->savePercentageInt << "%" << std::endl;
            std::cout << "Yellow Cards: " << foundPlayer->yellowCardsInt << "  Red Cards: " << foundPlayer->redCardsInt << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else //if the player is not a goalie, goals and assists will be printed but not save percentage
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Name: " << foundPlayer->nameStr << std::endl;
            std::cout << "Team: " << team->nameStr << std::endl;
            std::cout << "Age: " << foundPlayer->ageInt << std::endl;
            std::cout << "Number: " << foundPlayer->jerseyNumberInt << std::endl;
            std::cout << "Position: " << foundPlayer->positionStr << std::endl;
            std::cout << "Minutes: " << foundPlayer->minutesInt << std::endl;
            std::cout << "Goals: " << foundPlayer->goalsInt << std::endl;
            std::cout << "Assists: " << foundPlayer->assistsInt << std::endl;
            std::cout << "Yellow Cards: " << foundPlayer->yellowCardsInt << "  Red Cards: " << foundPlayer->redCardsInt << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
}

/*
1.void sortPlayers(int menuOption, SoccerTeam *team);
2.This method gets passed in an integer called menuOption and a team. The integer will be read in from the terminal based on the statistic that the user wants to sort the roster by. There are 7
if statements and they each run the same sort, but use different sets of integers based on what the user selects.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls; Then, the function can be called by calling mls->(menuOption, team)
4.The pre-condition for this method requires that the hash table of players already be created, and that the selectTeam method has already been called, and that is what is being passed into the method
5.There are no post-conditions for this method, as it simply prints sorted data that is only stored in temporary variables
*/
void MLS::sortPlayers(int menuOption, SoccerTeam *team)
{
    std::vector<SoccerPlayer*> playersVector;
    for(int i = 0; i < 10; i++)
    {
        if(team->playerHashTable[i] != NULL)
        {
            SoccerPlayer *temp = team->playerHashTable[i];
            while(temp != NULL)
            {
                playersVector.push_back(temp); //adds all the players in the hash table to a vector
                temp = temp->next;
            }

        }
    }
    SoccerPlayer *temporary;
    if(menuOption == 1)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->ageInt < playersVector[i]->ageInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " <<  playersVector[i]->ageInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 2)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->goalsInt < playersVector[i]->goalsInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " << playersVector[i]->goalsInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 3)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->assistsInt < playersVector[i]->assistsInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " << playersVector[i]->assistsInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 4)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->minutesInt < playersVector[i]->minutesInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " <<  playersVector[i]->minutesInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 5)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->savePercentageInt < playersVector[i]->savePercentageInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr <<" - " <<  playersVector[i]->savePercentageInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 6)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->yellowCardsInt < playersVector[i]->yellowCardsInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " << playersVector[i]->yellowCardsInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else if(menuOption == 7)
    {
        int vectorsize = playersVector.size();
        bool newBool = true;
        while(newBool || (vectorsize>1))
        {
            newBool = false;
            vectorsize = (vectorsize+1)/2;
            for(int i = 0; i < (playersVector.size() - vectorsize); i++)
            {
                if(playersVector[i+vectorsize]->redCardsInt < playersVector[i]->redCardsInt)
                {
                    temporary = playersVector[i+vectorsize];
                    playersVector[i+vectorsize] = playersVector[i];
                    playersVector[i] = temporary;
                    newBool = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        for(int i = 0; i < playersVector.size(); i++)
        {
            std::cout << playersVector[i]->nameStr << " - " << playersVector[i]->redCardsInt << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

}


/*
1.void printTeamStats(SoccerTeam *team);
2.This method gets passed in a team of type SoccerTeam based on user input from the terminal. The function calculates the sum of the various stats of the players on a teams roster,
as well as average minutes and average age, which is all printed to the terminal.
3.To call this method, first a variable of the type of the class must be created, such as MLS mls; Then, the function can be called by calling mls->printTeamStats(team)
4.The pre-condition for this method requires that the hash table of players already be built, and that the selectTeam method has already been called and stored a team to pass into the method.
5.There are no post-conditions for this method, as it is only printing data
*/
void MLS::printTeamStats(SoccerTeam *team)
{
    int j = 0;
    int goals = 0;
    int assists = 0;
    float ageSum = 0;
    float averageAge = 0;
    int yellowCards = 0;
    int redCards = 0;
    float minutesSum = 0;
    float averageMinutes = 0;

    for(int i = 0; i < 10; i++)
    {
        if(team->playerHashTable[i] != NULL)
        {
            SoccerPlayer *temp = team->playerHashTable[i];
            while(temp != NULL)
            {
                goals += temp->goalsInt;
                assists += temp->assistsInt;
                ageSum += temp->ageInt;
                yellowCards += temp->yellowCardsInt;
                redCards += temp->redCardsInt;
                minutesSum += temp->minutesInt;
                j++;
                temp = temp->next;
            }
        }
    }
    averageAge = ageSum/j;
    averageMinutes = minutesSum/j;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Number of Goals: " << goals << std::endl;
    std::cout << "Number of Assists: " << assists << std::endl;
    std::cout << "Average Player Age: " << std::setprecision(3) << averageAge << std::endl;
    std::cout << "Number of Yellow Cards: " << yellowCards << std::endl;
    std::cout << "Number of Red Cards: " << redCards << std::endl;
    std::cout << "Average Minutes Per Player: " << std::setprecision(4) <<averageMinutes <<   std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}
