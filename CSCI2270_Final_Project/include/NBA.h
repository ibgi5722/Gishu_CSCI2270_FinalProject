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
    int intTurnovers;
    int intFouls;

    BasketballPlayer(std::string pName, int number, std::string position, int played, int points, int rebounds, int steals, int assists, int turnovers, int fouls)
    {
        strName = pName;
        intPlayerNumber = number;
        strPosition = position;
        intGamesPlayed = played;
        intPoints = points;
        intRebounds = rebounds;
        intSteals = steals;
        intAssists = assists;
        intTurnovers = turnovers;
        intFouls = fouls;
    }
};

struct BasketballTeams
{
    std::string strName;
    int intPoints;
    int intRebounds;
    int intSteals;
    int intAssists;
    int intTurnovers;
    int intFouls;
    std::vector<BasketballPlayer> vecPlayers;
};


class NBA
{
    public:
        NBA();
        ~NBA();
        void addTeam(std::string tName, std::string pName, int number, std::string position, int played, int points, int rebounds, int steals, int assists, int turnovers, int fouls);
    private:

};

#endif // NBA_H
