
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

bool MLS::searchVector(std::string tName)
{
    bool foundTeam = false;
    for(int i = 0; i < teamVector.size(); i++)
    {
        if(tName == teamVector[i])
        {
            foundTeam = true;
        }
    }
    return foundTeam;
}

void MLS::insertTeam(std::string tName, std::string pName, int pAge, int pNumber, std::string pPosition, int minutes, int goals, int assists, int savePercent, int yellowCards, int redCards)
{
    bool addedToTree = false;
    SoccerTeam *newTeam;
    /*for(int i = 0; i < teamVector.size(); i++)
    {
        std::cout << teamVector[i] << std::endl;
    }*/
    SoccerPlayer *newPlayer = new SoccerPlayer(pName, pAge, pNumber, pPosition, minutes, goals, assists, savePercent, yellowCards, redCards);
    SoccerTeam *tempRoot = root;
    if(!(searchVector(tName)))
    {
        hashTable = new SoccerPlayer*[10];
        for(int i = 0; i < 10; i++)
        {
            hashTable[i] = NULL;
        }
        teamVector.push_back(tName);
        newTeam = new SoccerTeam(tName);
        newTeam->leftChild = nil;
        newTeam->rightChild = nil;
        newTeam->playerHashTable = hashTable;

        if(root == nil)
        {
            newTeam->parent = nil;
            root = newTeam;
        }
        else
        {
            while(addedToTree == false) //if the tempRoot hasn't been added to the tree
            {
                if(newTeam->nameStr.compare(tempRoot->nameStr) < 0) //compares the nameStrs
                {
                    if(tempRoot->leftChild == nil) //if there is no left child
                    {
                        tempRoot->leftChild = newTeam;
                        newTeam->parent = tempRoot;
                        addedToTree = true;
                    }
                    else
                    {
                        tempRoot = tempRoot->leftChild; //moves the tempRoot until left child is nil
                    }

                }
                else
                {
                    if(tempRoot->rightChild == nil) //same for the right as the left
                    {
                        tempRoot->rightChild = newTeam;
                        newTeam->parent = tempRoot;
                        addedToTree = true;
                    }
                    else
                    {
                        tempRoot = tempRoot->rightChild;
                    }
                }
            }
        }
        rbAddFixup(newTeam);
    }
    insertPlayer(newPlayer, hashTable);
    newTeam = searchTree(tName);
    //newTeam->vecPlayers.push_back(newPlayer);
}

SoccerTeam* MLS::searchTree(std::string tName)
{
    SoccerTeam *tempRoot = root;
    while(tempRoot != nil)
    {
        if(tName == tempRoot->nameStr)
        {
            return tempRoot;
        }
        else
        {
            if(tName.compare(tempRoot->nameStr) < 0)
            {
                tempRoot = tempRoot->leftChild; //loops to the left
            }
            else
            {
                tempRoot = tempRoot->rightChild; //loops to the right
            }
        }
    }
    return tempRoot;
}

void MLS::printTeams()
{
    printTeams(root);
}
void MLS::printTeams(SoccerTeam *tempRoot)
{
    //std::cout << "x" << std::endl;
    if(tempRoot->leftChild != nil) //won't enter until left child is NULL
    {
        printTeams(tempRoot->leftChild);
    }
    std::cout <<  tempRoot->nameStr << std::endl; //starts when left child is null , which would be the first movie alphabetically
    if(tempRoot->rightChild != nil)
    {
        printTeams(tempRoot->rightChild);
    }
}

void MLS::rbAddFixup(SoccerTeam * x) // called after insert to fix tree
{
    //std::cout << "x" << std::endl;
    x->leftChild = nil;
    x->rightChild = nil;
    //Now restore the red-black property
    x->isRed = true;
    while ( (x != root) && (x->parent->isRed == true) )
    {
        if ( x->parent == x->parent->parent->leftChild )
        {
           //If x's parent is a left, y is x's right 'uncle'
           SoccerTeam *y = x->parent->parent->rightChild;
           if ( y->isRed == true )
           {
              //case 1 - change the colors
              x->parent->isRed = false;
              y->isRed = false;
              x->parent->parent->isRed = true;
              //Move x up the tree
              x = x->parent->parent;
            }
            else
            {
                //std::cout << "y" << std::endl;
                //y is a black node
                if ( x == x->parent->rightChild )
                {
                    //and x is to the right
                    //case 2 - move x up and rotate
                    x = x->parent;
                    leftRotate(x);

                }
              //case 3
              x->parent->isRed = false;
              x->parent->parent->isRed = true;
              rightRotate(x->parent->parent );
            }
        }
      else
      {
          //repeat the "if" part with right and left exchanged
          SoccerTeam *y = x->parent->parent->leftChild;
          if ( y->isRed == true )
          {
             //case 1 - change the colors
             x->parent->isRed = false;
             y->isRed = false;
             x->parent->parent->isRed = true;
             //Move x up the tree
             x = x->parent->parent;
           }
           else
           {
               //y is a black node
               if ( x == x->parent->leftChild )
               {
                   //and x is to the right
                   //case 2 - move x up and rotate
                   x = x->parent;
                   rightRotate(x);
               }
             //case 3
             x->parent->isRed = false;
             x->parent->parent->isRed = true;
             leftRotate(x->parent->parent );
           }
      }
    }

    //Color the root black
    root->isRed = false;
}

void MLS::leftRotate(SoccerTeam * x)
{
    SoccerTeam *y;
    y = x->rightChild;
    /* y's left subtree becomes x's right subtree */
    x->rightChild = y->leftChild;
    if (y->leftChild != nil )
    {
        y->leftChild->parent = x;
        /* y's new parent was x's parent */
    }
    y->parent = x->parent;
    /* Set the parent to point to y instead of x */
    /* First see whether we're at the root */
    if ( x->parent == nil )
    {
        root = y;
    }
    else if ( x == x->parent->leftChild )
    {
        /* x was on the left of its parent */
        x->parent->leftChild = y;
    }
    else
    {
        /* x must have been on the right */
        x->parent->rightChild = y;
    }
    /* Finally, put x on y's left */
    y->leftChild = x;
    x->parent = y;
}

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

int MLS::hashSum(std::string playerName)
{
    int i = 0;
    for(int j = 0; j < playerName.size(); j++)
    {
        i = i + playerName[j];
    }
    return i%10;
}

void MLS::insertPlayer(SoccerPlayer *player, SoccerPlayer **hashTable)
{
    int i = hashSum(player->nameStr);
    if(hashTable[i] == NULL)
    {
        hashTable[i] = player;
    }
    else
    {
        SoccerPlayer *temp = hashTable[i];
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = player;
    }
}

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
                node = node->leftChild; //loops to the left
            }
            else
            {
                node = node->rightChild; //loops to the right
            }
        }
    }
    std::cout<<"Team Not Found"<<std::endl;
    return NULL;
}

void MLS::printRoster(SoccerTeam *temp)
{
    //std::cout << temp->nameStr << std::endl;
    std::vector<SoccerPlayer*> collisions;
    bool isEmpty = true;
    for(int i = 0; i < 10; i++)
    {
        if(temp->playerHashTable[i] != NULL)
        {
            SoccerPlayer *index = temp->playerHashTable[i];
            while(index != NULL)
            {
                collisions.push_back(index);
                //std::cout << index->nameStr << std::endl;
                index = index->next;
            }

            isEmpty = false;
        }
    }
    if(isEmpty == true)
    {
        std::cout << "empty" << std::endl;
    }
    sortRoster(collisions);
}
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
            if(collisions[i+vectorsize]->nameStr.compare(collisions[i]->nameStr) < 0)
            {
                temp = collisions[i+vectorsize];
                collisions[i+vectorsize] = collisions[i];
                collisions[i] = temp;
                newBool = true;
            }
        }
    }
    int z;
    for(int j = 0; j < collisions.size(); j++)
    {
        std::cout << collisions[j]->nameStr << std::endl;
    }
}

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
                //std::cout << index->nameStr << std::endl;
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

        if(foundPlayer->positionStr == "GK")
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
        else
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

void MLS::sortPlayers(int menuOption, SoccerTeam *team)
{
    //std:: cout << "x" << std:: endl;
    std::vector<SoccerPlayer*> playersVector;
    for(int i = 0; i < 10; i++)
    {
        if(team->playerHashTable[i] != NULL)
        {
            SoccerPlayer *temp = team->playerHashTable[i];
            while(temp != NULL)
            {
                playersVector.push_back(temp);
                //std::cout << index->nameStr << std::endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
        //std:: cout << "t" << std:: endl;
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
