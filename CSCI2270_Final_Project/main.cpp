#include "NHL.h"
#include "NBA.h"
#include "MLS.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    string strFilename = argv[1];
    ifstream inFile;
    inFile.open(strFilename);
    string strLine;
    string parts;
    //Basketball
        string strTeamName;
        string strPlayerName;
        int intPlayerNumber;
        string strPosition;
        int intGamesPlayed;
        int intPoints;
        int intRebounds;
        int intSteals;
        int intAssists;
        int intTurnovers;
        int intFouls;
    //
    getline(inFile, strLine);
    if(inFile.fail())
    {
        cout<<"The file was not opened successfully"<<endl;
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
                    intPlayerNumber = std::stoi(parts);
                    i++;
                }
                else if(i == 3)
                {
                    strPosition = parts;
                    i++;
                }
                else if(i == 4)
                {
                    intGamesPlayed = std::stoi(parts);
                    i++;
                }
                else if(i == 5)
                {
                    intPoints = std::stoi(parts);
                    i++;
                }
                else if(i == 6)
                {
                    intRebounds = std::stoi(parts);
                    i++;
                }
                else if(i == 7)
                {
                    intSteals = std::stoi(parts);
                    i++;
                }
                else if(i == 8)
                {
                    intAssists = std::stoi(parts);
                    i++;
                }
                else if(i == 9)
                {
                    intTurnovers = std::stoi(parts);
                    i++;
                }
                else if(i == 10)
                {
                    intFouls = std::stoi(parts);
                    i++;
                }
                cout<<parts<<endl;
            }
            cout<<strLine<<endl;
        }
    }
    return 0;
}
