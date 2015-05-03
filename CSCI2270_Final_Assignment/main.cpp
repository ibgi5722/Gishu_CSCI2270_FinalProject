#include "include/NBA.h"
#include "include/MLS.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argv[1] == NULL || argv[2] == NULL){
        cout<<"Please enter two filenames as command line arguments."<<endl;
    }
    else{
        string strFilename = argv[1];
        ifstream inFile;
        inFile.open(strFilename);
        string strLine;
        string parts;
        //Basketball
            NBA *nba = new NBA();
            string strTeamName;
            string strPlayerName;
            float floatPlayerNumber;
            string strPosition;
            float floatGamesPlayed;
            float floatPoints;
            float floatRebounds;
            float floatSteals;
            float floatAssists;
            float floatTurnovers;
            float floatFouls;
        //
        getline(inFile, strLine);
        if(inFile.fail())
        {
            cout << "The first file (NBA) failed to open. Exiting program." << endl;
            return 0;
        }
        else
        {
            int i = 0;
            while(getline(inFile, strLine))
            {
                i = 0;
                istringstream ss(strLine);
                while(getline(ss, parts, ','))
                {
                    if(i == 0)
                    {
                        strTeamName = parts;
                        i++;
                    }
                    else if(i == 1)
                    {
                        strPlayerName = parts;
                        i++;
                    }
                    else if(i == 2)
                    {
                        floatPlayerNumber = stof(parts);
                        i++;
                    }
                    else if(i == 3)
                    {
                        strPosition = parts;
                        i++;
                    }
                    else if(i == 4)
                    {
                        floatGamesPlayed = stof(parts);
                        i++;
                    }
                    else if(i == 5)
                    {
                        floatPoints = stof(parts);
                        i++;
                    }
                    else if(i == 6)
                    {
                        floatRebounds = stof(parts);
                        i++;
                    }
                    else if(i == 7)
                    {
                        floatSteals = stof(parts);
                        i++;
                    }
                    else if(i == 8)
                    {
                        floatAssists = stof(parts);
                        i++;
                    }
                    else if(i == 9)
                    {
                        floatTurnovers = stof(parts);
                        i++;
                    }
                    else if(i == 10)
                    {
                        floatFouls = stof(parts);
                        i++;
                    }
                }
                nba->addTeam(strTeamName, strPlayerName, floatPlayerNumber, strPosition, floatGamesPlayed, floatPoints, floatRebounds, floatSteals, floatAssists, floatTurnovers, floatFouls);
            }
        }
        inFile.close();
        string strMLSFile = argv[2];
        ifstream MLSinFile;
        MLSinFile.open(strMLSFile);
        string firstLine;
        getline(MLSinFile, firstLine);
        string strDataLine;
        //Soccer
            MLS *mls = new MLS();
            string strLeague;
            int intPlayerAge;
            int intMinutes;
            int intGoals;
            int intSavePercentage;
            int intYellowCards;
            int intRedCards;
        //
        if(MLSinFile.fail())
        {
            cout << "The second file (MLS) failed to open. Exiting program." << endl;
            return 0;
        }
        else
        {
            int j = 0;
            while(getline(MLSinFile, strDataLine))
            {
                j = 0;
                istringstream ss(strDataLine);
                while(getline(ss, parts, ','))
                {
                    if(j == 0)
                    {
                        strLeague = parts;
                        j++;
                    }
                    else if(j == 1)
                    {
                        strTeamName = parts;
                        j++;
                    }
                    else if(j == 2)
                    {
                        strPlayerName = parts;
                        j++;
                    }
                    else if(j == 3)
                    {
                        intPlayerAge = stoi(parts);
                        j++;
                    }
                    else if(j == 4)
                    {
                        floatPlayerNumber = stoi(parts);
                        j++;
                    }
                    else if(j == 5)
                    {
                        strPosition = parts;
                        j++;
                    }
                    else if(j == 6)
                    {
                        intMinutes = stoi(parts);
                        j++;
                    }
                    else if(j == 7)
                    {
                        intGoals = stoi(parts);
                        j++;
                    }
                    else if(j == 8)
                    {
                        floatAssists = stoi(parts);
                        j++;
                    }
                    else if(j == 9)
                    {
                        intSavePercentage = stoi(parts);
                        j++;
                    }
                    else if(j == 10)
                    {
                        intYellowCards = stoi(parts);
                        j++;
                    }
                    else if(j == 11)
                    {
                        intRedCards = stoi(parts);
                        j++;
                    }
                }
                mls->insertTeam(strTeamName, strPlayerName, intPlayerAge, floatPlayerNumber, strPosition, intMinutes, intGoals, floatAssists, intSavePercentage, intYellowCards, intRedCards);
            }
        }
        MLSinFile.close();
        //User Data
            BasketballTeams *teamPointer;
            string team;
            string player;
            SoccerTeam *sTeamPointer;
            string sortBy;
            int sortByThis;
        string userInput;
        int intUserInput = 0;
        string menuSelectionstr;
        string menuSelection2Str;
        int menuSelection;
        string menuOptionStr;
        int menuOptionInt;
        int menuSelection2;
        while(intUserInput != 3)
        {
            cout << "Please Select a League" << endl;
            cout << "1. NBA" << endl;
            cout << "2. MLS" << endl;
            cout << "3. Quit" << endl;
            cout << "Enter a Number: ";
            getline(cin, userInput);//reads in the command that the user wants to do
            intUserInput = stoi(userInput);
            cout << endl;
            switch(intUserInput)
            {
                case 1:
                    while(menuSelection != 3)
                    {
                        cout << "======Main Menu======" << endl;
                        cout << "1. List Teams" << endl;
                        cout << "2. Select Team" << endl;
                        cout << "3. Select New League" << endl;
                        getline(cin, menuSelectionstr);
                        menuSelection = stoi(menuSelectionstr);
                        switch(menuSelection)
                        {
                            case 1:
                                nba->printTeams();
                                break;
                            case 2:
                                cout << endl;
                                cout<<"Enter Team Name: ";
                                getline(cin, team);
                                cout << endl;
                                teamPointer = nba->selectTeam(team);
                                if(teamPointer != NULL)
                                {
                                    while(menuSelection2 != 5)
                                    {
                                        cout << "======Main Menu======" << endl;
                                        cout << "1. Print Roster" << endl;
                                        cout << "2. Print Player Information" <<endl;
                                        cout << "3. Rank Players" << endl;
                                        cout << "4. Print Team Stats" << endl;
                                        cout << "5. Choose New Team" << endl;
                                        getline(cin, menuSelectionstr);
                                        menuSelection2 = stoi(menuSelectionstr);
                                        switch(menuSelection2)
                                        {
                                            case 1:
                                                nba->printRoster(teamPointer);
                                                break;
                                            case 2:
                                                cout << endl;
                                                cout<<"Enter Player Name: ";
                                                getline(cin, player);
                                                cout << endl;
                                                nba->printPlayerInfo(teamPointer, player);
                                                break;
                                            case 3:
                                                cout << "======Sort Players BY======" << endl;
                                                cout << "1. Player Number" << endl;
                                                cout << "2. Games Played" <<endl;
                                                cout << "3. Points" << endl;
                                                cout << "4. Rebouds" << endl;
                                                cout << "5. Steals" << endl;
                                                cout << "6. Assists" << endl;
                                                cout << "7. Turnovers" <<endl;
                                                cout << "8. Fouls" << endl;
                                                getline(cin, sortBy);
                                                sortByThis = stoi(sortBy);
                                                nba->rankBy(teamPointer, sortByThis);
                                                break;
                                            case 4:
                                                nba->printTeamStats(teamPointer);
                                                break;
                                            case 5:
                                                break;
                                            default:
                                                cout << "Not a Menu Option" <<endl;
                                        }
                                    }
                                    menuSelection2 = 0;
                                }
                                break;
                            case 3:
                                break;
                            default:
                                cout << "Not a Menu Option" <<endl;
                        }
                    }
                    menuSelection = 0;
                    break;
                case 2:
                    while(menuSelection != 3)
                    {
                        cout << "======Main Menu======" << endl;
                        cout << "1. List Teams" << endl;
                        cout << "2. Select Team" << endl;
                        cout << "3. Select New League" << endl;
                        getline(cin, menuSelectionstr);
                        menuSelection = stoi(menuSelectionstr);
                        switch(menuSelection)
                        {
                            case 1:
                                mls->printTeams();
                                break;
                            case 2:
                                cout << endl;
                                cout << "Enter a Team Name: ";
                                getline(cin, team);
                                cout << endl;
                                sTeamPointer = mls->selectTeam(team);
                                if(sTeamPointer != NULL)
                                {
                                    while(menuSelection2 != 5)
                                    {
                                        cout << "======Main Menu======" << endl;
                                        cout << "1. Print Roster" << endl;
                                        cout << "2. Print Player Information" <<endl;
                                        cout << "3. Rank Players" << endl;
                                        cout << "4. Print Team Stats" << endl;
                                        cout << "5. Choose New Team" << endl;
                                        getline(cin, menuSelectionstr);
                                        menuSelection2 = stoi(menuSelectionstr);
                                        switch(menuSelection2)
                                        {
                                            case 1:
                                                mls->printRoster(sTeamPointer);
                                                break;
                                            case 2:
                                                cout << endl;
                                                cout << "Enter a Player's Name: ";
                                                getline(cin, player);
                                                cout << endl;
                                                mls->printPlayerInfo(player, sTeamPointer);
                                                break;
                                            case 3:
                                                cout << "=====Sort Players By=====" << endl;
                                                cout << "1. Age" << endl;
                                                cout << "2. Goals" << endl;
                                                cout << "3. Assists" << endl;
                                                cout << "4. Minutes" << endl;
                                                cout << "5. Save Percentage" << endl;
                                                cout << "6. Yellow Cards" << endl;
                                                cout << "7. Red Cards" << endl;
                                                getline(cin, menuOptionStr);
                                                menuOptionInt = stoi(menuOptionStr);
                                                mls->sortPlayers(menuOptionInt, sTeamPointer);
                                                break;
                                            case 4:
                                                mls->printTeamStats(sTeamPointer);
                                                break;
                                            case 5:
                                                break;
                                            default:
                                                cout << "Not a Menu Option" <<endl;
                                        }
                                    }
                                    menuSelection2 = 0;
                                }
                                break;
                            case 3:
                                break;
                            default:
                                cout << "Not a Menu Option" <<endl;
                        }
                    }
                    menuSelection = 0;
                    break;
                case 3:
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Not a Menu Option" <<endl;
            }
        }
    }

    return 0;
}
