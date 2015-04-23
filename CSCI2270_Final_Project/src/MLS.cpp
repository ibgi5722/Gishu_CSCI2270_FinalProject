#include "MLS.h"
#include <iostream>
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
    if(searchVector(tName) == false)
    {
        teamVector.push_back(tName);
    }
    /*for(int i = 0; i < teamVector.size(); i++)
    {
        std::cout << teamVector[i] << std::endl;
    }*/
    SoccerPlayer *newPlayer = new SoccerPlayer(pName, pAge, pNumber, pPosition, minutes, goals, assists, savePercent, yellowCards, redCards);
    SoccerTeam *tempRoot = root;
    if(!(searchVector(tName)))
    {
        newTeam = new SoccerTeam(tName);
        newTeam->leftChild = nil;
        newTeam->rightChild = nil;
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
    newTeam = searchTree(tName);
    newTeam->vecPlayers.push_back(newPlayer);
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
    std::cout << "x" << std::endl;
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
    std::cout << "x" << std::endl;
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
