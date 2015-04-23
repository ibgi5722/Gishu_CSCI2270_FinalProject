#ifndef MLS_H
#define MLS_H
#include <iostream>
#include <vector>

struct SoccerPlayer
{
    std::string nameStr;
    int ageInt;
    int jerseyNumberInt;
    std::string positionStr;
    int minutesInt;
    int goalsInt;
    int assistsInt;
    int savePercentageInt;
    int yellowCardsInt;
    int redCardsInt;
};

struct SoccerTeam
{
    std::string nameStr;
    int goalsInt;
    int assistsInt;
    int yellowCardsInt;
    int redCardsInt;
    std::vector<SoccerPlayer> vecPlayers;
};

class MLS
{
    public:
        MLS();
        ~MLS();
    protected:
    private:
};

#endif // MLS_H
