#ifndef NBA_H
#define NBA_H
#include <iostream>
#include <vector>

struct BasketballPlayer
{
    std::string strName;
    float floatPlayerNumber;
    std::string strPosition;
    float floatGamesPlayed;
    float floatPoints;
    float floatRebounds;
    float floatSteals;
    float floatAssists;
    float floatTurnovers;
    float floatFouls;
    BasketballPlayer* next;

    BasketballPlayer(std::string pName, float number, std::string position, float played, float points, float rebounds, float steals, float assists, float turnovers, float fouls)
    {
        strName = pName;
        floatPlayerNumber = number;
        strPosition = position;
        floatGamesPlayed = played;
        floatPoints = points;
        floatRebounds = rebounds;
        floatSteals = steals;
        floatAssists = assists;
        floatTurnovers = turnovers;
        floatFouls = fouls;
        next = NULL;
    }
};

struct BasketballTeams
{
    std::string strName;
    float floatPoints;
    float floatRebounds;
    float floatSteals;
    float floatAssists;
    float floatTurnovers;
    float floatFouls;
    std::vector<BasketballPlayer*> vecPlayers;
    BasketballPlayer** hashPlayer;
    BasketballTeams *parent;
    BasketballTeams *left;
    BasketballTeams *right;
    bool isRed;

    BasketballTeams(){};

    BasketballTeams(std::string tName)
    {
        strName = tName;
        parent = NULL;
        left = NULL;
        right = NULL;
        isRed = true;
    }
};


class NBA
{
    public:
        NBA();
        ~NBA();
        void addTeam(std::string tName, std::string pName, float number, std::string position, float played, float pofloats, float rebounds, float steals, float assists, float turnovers, float fouls);
        bool searchVector(std::string tName);
        BasketballTeams* searchTree(std::string tName);
        void printTeams();
        BasketballTeams* selectTeam(std::string tName);
        void printRoster(BasketballTeams* team);
        void printPlayerInfo(BasketballTeams* team, std::string pName);
        void rankBy(BasketballTeams* team, int x);
        void printTeamStats(BasketballTeams* team);
        //BasketballTeams* sTeam(std::string tName);
    private:
        //BasketballTeams* findTeam(std::string tName);
        void rankPlayers(std::vector<float> stat);
        void sortPlayers(std::vector<BasketballPlayer*> collisons);
        void printTeams(BasketballTeams *rootTemp);
        void rbAddFixup(BasketballTeams *x);
        void rightRotate(BasketballTeams *x);
        void leftRotate(BasketballTeams *x);
        void insertPlayer(BasketballPlayer *p, BasketballPlayer** hashTable);
        int Hash(std::string pName);
        BasketballTeams *root;
        std::vector<std::string> teamNameVector;
        BasketballTeams *nil;
        BasketballPlayer **hashTable;

        //Ranking Methods
            void rankByPlayerNumber(std::vector<BasketballPlayer*> collisions);
            void rankByGamesPlayed(std::vector<BasketballPlayer*> collisions);
            void rankByPoints(std::vector<BasketballPlayer*> collisions);
            void rankByRebounds(std::vector<BasketballPlayer*> collisions);
            void rankBySteals(std::vector<BasketballPlayer*> collisions);
            void rankByAssists(std::vector<BasketballPlayer*> collisions);
            void rankByTurnovers(std::vector<BasketballPlayer*> collisions);
            void rankByFouls(std::vector<BasketballPlayer*> collisions);

};

#endif // NBA_H
