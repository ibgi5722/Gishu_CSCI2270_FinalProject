#include "NBA.h"
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

void NBA::addTeam(std::string tName, std::string pName, float number, std::string position, float played, float points, float rebounds, float steals, float assists, float turnovers, float fouls)
{
    /*for(int i = 0; i<teamNameVector.size(); i++)
    {
        std::cout<<teamNameVector[i];
    }
    std::cout<<std::endl;*/
    //cout<<"x"<<endl;
    BasketballPlayer *player = new BasketballPlayer(pName, number, position, played, points, rebounds, steals, assists, turnovers, fouls);
    bool added = false;
    BasketballTeams *rootTemp = root;
    BasketballTeams *team;
    if(!(searchVector(tName)))
    {
        hashTable = new BasketballPlayer*[12];
        for(int i = 0;i < 12; i++)
        {
            hashTable[i] = NULL;
        }
        teamNameVector.push_back(tName);
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
        rbAddFixup(team);
    }
    insertPlayer(player, hashTable);
    //cout<<"x"<<endl;
    //team = searchTree(tName);
    //team->vecPlayers.push_back(player);
    //cout<<"x"<<endl;
}

void NBA::insertPlayer(BasketballPlayer* p, BasketballPlayer** hashTable)
{
    //cout<<p->strName<<endl;
    int index = Hash(p->strName);
    //cout<<p->strName<<" - "<<index<<endl;
    if(hashTable[index] == NULL)
    {
        hashTable[index] = p;
    }
    else
    {
        BasketballPlayer *temp = hashTable[index];
        //cout<<temp->strName<<" - "<<index<<endl;
        while(temp->next != NULL)
        {
            //cout<<temp->strName<<" - "<<index<<endl;
            temp = temp->next;
        }
        temp->next = p;
    }
}

void NBA::rbAddFixup(BasketballTeams *x)
{
    //cout<<"x"<<endl;
    x->left = nil;
    x->right = nil;
    x->isRed = true;
    while ( (x != root) && (x->parent->isRed == true) )
    {
        if (x->parent == x->parent->parent->left)
        {
            //cout<<"x"<<endl;
            /* If x's parent is a left, y is x's right 'uncle' */
            BasketballTeams *y = x->parent->parent->right;
            if (y->isRed == true)
            {
                /* case 1 - change the colors */
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else
            {
                /* y is a black node */
                if (x == x->parent->right)
                {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    leftRotate(x);
                }
                /* case 3 */
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            //cout<<"y"<<endl;
            /* If x's parent is a left, y is x's right 'uncle' */
            BasketballTeams *y = x->parent->parent->left;
            if ( y->isRed == true)
            {
                //cout<<"x"<<endl;
                /* case 1 - change the colors */
                x->parent->isRed = false;
                y->isRed = false;
                x->parent->parent->isRed = true;
                /* Move x up the tree */
                x = x->parent->parent;
            }
            else
            {
                //cout<<"y"<<endl;
                /* y is a black node */
                if ( x == x->parent->left)
                {
                    /* and x is to the right */
                    /* case 2 - move x up and rotate */
                    x = x->parent;
                    rightRotate(x);
                }
                /* case 3 */
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);
            }
        }
    }
    /* Color the root black */
    root->isRed = false;
}

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

BasketballTeams* NBA::searchTree(std::string tName)
{
    BasketballTeams *rootTemp = root;
    while(rootTemp != nil)
    {
        if(rootTemp->strName == tName)
        {
            return rootTemp;
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

void NBA::printTeams()
{
    printTeams(root);
}

void NBA::printTeams(BasketballTeams *rootTemp)
{
    if(rootTemp->left != nil)
    {
        printTeams(rootTemp->left);
    }
    std::cout<<"Team: "<<rootTemp->strName<<std::endl;
    /*for(int i = 0; i<12; i++)
    {
        if(rootTemp->hashPlayer[i] != NULL)
        {
            //cout<<" "<<rootTemp->hashPlayer[i]->strName<<endl;
            BasketballPlayer *temp = rootTemp->hashPlayer[i];
            while(temp != NULL)
            {
                //collisions.push_back(temp);
                cout<<" "<<temp->strName<<endl;
                temp = temp->next;
                //std::cout<<temp->title<<":"<<temp->year<<std::endl;
            }
        }
    }*/
    if(rootTemp->right != nil)
    {
        printTeams(rootTemp->right);
    }
}

BasketballTeams* NBA::selectTeam(std::string tName)
{
    BasketballTeams* base = root;
    while(base != nil)
    {
        if(base->strName == tName)
        {
            return base;
            //found = true;
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
    cout<<"not found"<<endl;
    return NULL;
}

void NBA::printRoster(BasketballTeams* team)
{
    bool emp = true;
    std::vector<BasketballPlayer*> collisions;
    for(int i = 0; i<10; i++)
    {
        if(team->hashPlayer[i] != NULL)
        {
            //cout<<" "<<team->hashPlayer[i]->strName<<endl;
            BasketballPlayer *temp = team->hashPlayer[i];
            //cout<<temp->next->strName<<endl;
            while(temp != NULL)
            {
                collisions.push_back(temp);
                //cout<<"y"<<endl;
                //cout<<" "<<temp->strName<<endl;
                temp = temp->next;
                //std::cout<<temp->title<<":"<<temp->year<<std::endl;
            }
            emp = false;
        }
    }
    if(emp)
    {
        cout<<"empty"<<endl;
    }
    /*for(int j = 0; j<collisions.size(); j++)
    {
        cout<<collisions[j]->strName<<endl;
    }*/
    sortPlayers(collisions);
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<std::endl;
    }
}

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
            std::cout<<"    "<<temp->strName<<" - "<<temp->floatPlayerNumber<<std::endl;
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

void NBA::rankBy(BasketballTeams* team, int x)
{
    bool emp = true;
    std::vector<BasketballPlayer*> collisions;
    for(int i = 0; i<10; i++)
    {
        if(team->hashPlayer[i] != NULL)
        {
            //cout<<" "<<team->hashPlayer[i]->strName<<endl;
            BasketballPlayer *temp = team->hashPlayer[i];
            //cout<<temp->next->strName<<endl;
            while(temp != NULL)
            {
                collisions.push_back(temp);
                //cout<<"y"<<endl;
                //cout<<" "<<temp->strName<<endl;
                temp = temp->next;
                //std::cout<<temp->title<<":"<<temp->year<<std::endl;
            }
            emp = false;
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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatPlayerNumber<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatGamesPlayed<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatPoints<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatRebounds<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatSteals<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatAssists<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatTurnovers<<std::endl;
    }
}

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
    int m;
    for(int x = 0; x<collisions.size(); x++)
    {
        //m = Hash(collisions[x]->strName);
        std::cout<<collisions[x]->strName<<" - "<<collisions[x]->floatFouls<<std::endl;
    }
}

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
            //cout<<" "<<team->hashPlayer[i]->strName<<endl;
            BasketballPlayer *temp = team->hashPlayer[i];
            //cout<<temp->next->strName<<endl;
            while(temp != NULL)
            {
                numOfPlayers++;
                points += temp->floatPoints;
                rebounds += temp->floatRebounds;
                steals += temp->floatSteals;
                assists += temp->floatAssists;
                turnovers += temp->floatTurnovers;
                fouls += temp->floatFouls;
                //collisions.push_back(temp);
                //cout<<"y"<<endl;
                //cout<<" "<<temp->floatSteals<<endl;
                temp = temp->next;
                //std::cout<<temp->title<<":"<<temp->year<<std::endl;
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

int NBA::Hash(std::string pName)
{
    int sum = 0;
    for(int i = 0; i<pName.size(); i++)
    {
        sum = sum + pName[i];
    }
    return sum%10;
}
