#include "MLS.h"

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
    if(searchVector(tName) == false)
    {
        teamVector.push_back(tName);
    }
    /*for(int i = 0; i < teamVector.size(); i++)
    {
        std::cout << teamVector[i] << std::endl;
    }*/
    SoccerPlayer *newPlayer = new SoccerPlayer(pName, pAge, pNumber, pPosition, minutes, goals, assists, savePercent, yellowCards, redCards);
    if(!(searchVector(tName)))
    {
        SoccerTeam *tempRoot = root;
        SoccerTeam *newTeam = new SoccerTeam(tName);
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

    }
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
