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
        NBA *nba = new NBA();
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
                    intPlayerNumber = stoi(parts);
                    i++;
                }
                else if(i == 3)
                {
                    strPosition = parts;
                    i++;
                }
                else if(i == 4)
                {
                    intGamesPlayed = stoi(parts);
                    i++;
                }
                else if(i == 5)
                {
                    intPoints = stoi(parts);
                    i++;
                }
                else if(i == 6)
                {
                    intRebounds = stoi(parts);
                    i++;
                }
                else if(i == 7)
                {
                    intSteals = stoi(parts);
                    i++;
                }
                else if(i == 8)
                {
                    intAssists = stoi(parts);
                    i++;
                }
                else if(i == 9)
                {
                    intTurnovers = stoi(parts);
                    i++;
                }
                else if(i == 10)
                {
                    intFouls = stoi(parts);
                    i++;
                }
                //cout<<parts<<endl;
            }
            nba->addTeam(strTeamName, strPlayerName, intPlayerNumber, strPosition, intGamesPlayed, intPoints, intRebounds, intSteals, intAssists, intTurnovers, intFouls);
            //cout<<strLine<<endl;
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
        cout << "The file failed to open." << endl;
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
                    intPlayerNumber = stoi(parts);
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
                    intAssists = stoi(parts);
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
                //cout<<parts<<endl;
            }
            mls->insertTeam(strTeamName, strPlayerName, intPlayerAge, intPlayerNumber, strPosition, intMinutes, intGoals, intAssists, intSavePercentage, intYellowCards, intRedCards);
            //cout<<strDataLine<<endl;
        }
    }
    MLSinFile.close();
    string userInput;
    int intUserInput = 0;
    string menuSelectionstr;
    string menuSelection2Str;
    int menuSelection;
    int menuSelection2;
    while(intUserInput != 4)
	{
		cout << "1. NHL" << endl;
		cout << "2. NBA" << endl;
		cout << "3. MLS" << endl;
		cout << "4. Quit" << endl;
		getline(cin, userInput);//reads in the command that the user wants to do
		intUserInput = stoi(userInput);
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
							break;
						case 2:
							while(menuSelection2 != 4)
							{
								cout << "======Main Menu======" << endl;
								cout << "1. Print Roster" << endl;
								cout << "2. Rank Players" << endl;
								cout << "3. Print Team Stats" << endl;
								cout << "4. Choose New Team" << endl;
								getline(cin, menuSelectionstr);
								menuSelection2 = stoi(menuSelectionstr);
								switch(menuSelection)
								{
									case 1:
										break;
									case 2:
										break;
									case 3:
										break;
									case 4:
									    cout<<"hello"<<endl;
										break;
								}
							}
							menuSelection2 = 0;
							break;
						case 3:
							break;
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
							break;
						case 2:
							while(menuSelection2 != 4)
							{
								cout << "======Main Menu======" << endl;
								cout << "1. Print Roster" << endl;
								cout << "2. Rank Players" << endl;
								cout << "3. Print Team Stats" << endl;
								cout << "4. Choose New Team" << endl;
								getline(cin, menuSelectionstr);
								menuSelection2 = stoi(menuSelectionstr);
								switch(menuSelection)
								{
									case 1:
										break;
									case 2:
										break;
									case 3:
										break;
									case 4:
										break;
								}
							}
							menuSelection2 = 0;
							break;
						case 3:
							break;
					}
				}
				menuSelection = 0;
				break;
			case 3:
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
							while(menuSelection2 != 4)
							{
								cout << "======Main Menu======" << endl;
								cout << "1. Print Roster" << endl;
								cout << "2. Rank Players" << endl;
								cout << "3. Print Team Stats" << endl;
								cout << "4. Choose New Team" << endl;
								getline(cin, menuSelectionstr);
								menuSelection2 = stoi(menuSelectionstr);
								switch(menuSelection)
								{
									case 1:
										break;
									case 2:
										break;
									case 3:
										break;
									case 4:
										break;
								}
							}
							menuSelection2 = 0;
							break;
						case 3:
							break;
					}
				}
				menuSelection = 0;
				break;
			case 4:
			    cout << "Goodbye!" << endl;
				break;
		}
	}

    return 0;
}
