
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
            while(addedToTree == false)
            {
                if(newTeam->nameStr.compare(tempRoot->nameStr) < 0)
                {
                    if(tempRoot->leftChild == nil)
                    {
                        tempRoot->leftChild = newTeam;
                        newTeam->parent = tempRoot;
                        addedToTree = true;
                    }
                    else
                    {
                        tempRoot = tempRoot->leftChild;
                    }

                }
                else
                {
                    if(tempRoot->rightChild == nil)
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
                tempRoot = tempRoot->leftChild;
            }
            else
            {
                tempRoot = tempRoot->rightChild;
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
    if(tempRoot->leftChild != nil)
    {
        printTeams(tempRoot->leftChild);
    }
    std::cout <<  tempRoot->nameStr << std::endl;
    if(tempRoot->rightChild != nil)
    {
        printTeams(tempRoot->rightChild);
    }
}

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
                collisions.push_back(index);
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
    std::vector<SoccerPlayer*> playersVector;
    for(int i = 0; i < 10; i++)
    {
        if(team->playerHashTable[i] != NULL)
        {
            SoccerPlayer *temp = team->playerHashTable[i];
            while(temp != NULL)
            {
                playersVector.push_back(temp);
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
