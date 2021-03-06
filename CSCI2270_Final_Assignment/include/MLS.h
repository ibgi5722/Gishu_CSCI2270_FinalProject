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
    SoccerPlayer *next;

    SoccerPlayer(std::string pName, int pAge, int pNumber, std::string pPosition, int minutes, int goals, int assists, int savePercent, int yellowCards, int redCards)
    {
        nameStr = pName;
        ageInt = pAge;
        jerseyNumberInt = pNumber;
        positionStr = pPosition;
        minutesInt = minutes;
        goalsInt = goals;
        assistsInt = assists;
        savePercentageInt = savePercent;
        yellowCardsInt = yellowCards;
        redCardsInt = redCards;
        next = NULL;
    }
};

struct SoccerTeam
{
    std::string nameStr;
    int goalsInt;
    int assistsInt;
    int yellowCardsInt;
    int redCardsInt;
    std::vector<SoccerPlayer*> vecPlayers;
    SoccerTeam *parent;
    SoccerTeam *leftChild;
    SoccerTeam *rightChild;
    SoccerPlayer **playerHashTable;
    bool isRed;

    SoccerTeam(){};

    SoccerTeam(std::string tName)
    {
        nameStr = tName;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
        isRed = true;
    }
};

class MLS
{
    public:
        MLS();
        ~MLS();
        void insertTeam(std::string tName, std::string pName, int pAge, int pNumber, std::string pPosition, int minutes, int goals, int assists, int savePercent, int yellowCards, int redCards);
        bool searchVector(std::string tName);
        SoccerTeam* searchTree(std::string tName);
        void printTeams();
        void rbAddFixup(SoccerTeam * x);
        void leftRotate(SoccerTeam * x);
        void rightRotate(SoccerTeam * y);
        int hashSum(std::string playerName);
        void insertPlayer(SoccerPlayer *player, SoccerPlayer **hashTable);
        void findPlayer(std::string playerName);
        void printPlayers();
        SoccerTeam* selectTeam(std::string tName);
        void printRoster(SoccerTeam *temp);
        void sortRoster(std::vector<SoccerPlayer*> collisions);
        void printPlayerInfo(std::string player, SoccerTeam *team);
        void sortPlayers(int menuOption, SoccerTeam *team);
        void printTeamStats(SoccerTeam *team);
    protected:
    private:
        void printTeams(SoccerTeam *temp);
        SoccerTeam *root;
        SoccerTeam *nil;
        std::vector<std::string> teamVector;
        SoccerPlayer **hashTable;
};

#endif // MLS_H
