#include "NBA.h"

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

void NBA::addTeam(std::string tName, std::string pName, int number, std::string position, int played, int points, int rebounds, int steals, int assists, int turnovers, int fouls)
{
    for(int i = 0; i<teamNameVector.size(); i++)
    {
        std::cout<<teamNameVector[i];
    }
    std::cout<<std::endl;
    BasketballPlayer *player = new BasketballPlayer(pName, number, position, played, points, rebounds, steals, assists, turnovers, fouls);
    bool added = false;
    BasketballTeams *rootTemp = root;
    if(!(searchVector(tName)))
    {
        teamNameVector.push_back(tName);
        BasketballTeams *team = new BasketballTeams(tName);
        if(rootTemp == nil)
        {
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
    }
}

BasketballTeams* NBA::searchTree(std::string tName)
{
    bool found = false;
    BasketballTeams *rootTemp = root;
    while(rootTemp != nil)
    {
        if(rootTemp->strName == tName)
        {
            return rootTemp;
            found = true;
        }
        else
        {
            if(tName.compare(rootTemp->strName) < 0)
            {
                rootTemp = rootTemp->left;
            }
            else
            {
                rootTemp = rootTemp->right;
            }
        }
    }
    return rootTemp;
}

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
