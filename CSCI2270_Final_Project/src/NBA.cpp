#include "NBA.h"

NBA::NBA()
{
    //ctor
}

NBA::~NBA()
{
    //dtor
}

void NBA::addTeam(std::string tName, std::string pName, int number, std::string position, int played, int points, int rebounds, int steals, int assists, int turnovers, int fouls)
{
    BasketballPlayer *player = new BasketballPlayer(pName, number, position, played, points, rebounds, steals, assists, turnovers, fouls);

}
