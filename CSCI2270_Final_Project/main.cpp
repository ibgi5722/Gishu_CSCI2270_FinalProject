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
                //cout<<parts<<endl;
            }
            //cout<<strLine<<endl;
        }
    }
    string userInput;
    int intUserInput;
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
