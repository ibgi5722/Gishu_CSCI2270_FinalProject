#ifndef NBA_H
#define NBA_H
#include <iostream>
#include <vector>

struct BasketballPlayer
{
    std::string strName;
    int intPlayerNumber;
    std::string strPosition;
    int intGamesPlayed;
    int intPoints;
    int intRebounds;
    int intSteals;
    int intAssists;
    int intTurnOvers;
    int intFouls;
};

struct BasketballTeams
{
    std::string strName;
    int intPoints;
    int intRebounds;
    int intSteals;
    int intAssists;
    int intTurnOvers;
    int intFouls;
    std::vector<BasketballPlayer> vecPlayers;
};


class NBA
{
    public:
        NBA();
        ~NBA();
    private:

};

#endif // NBA_H
