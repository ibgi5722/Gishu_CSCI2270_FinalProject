 # Gishu_CSCI2270_FinalProject

Project Summary:
The goal of this project is to store the statistics of every player in the MLS and NBA from the 2014/2015 regular season. The statistics will be a select chosen few, including goals, assists, save percentage, field goal percentage, minutes played, and more. Users will be able to choose from a variety of menu options that allow them to manipulate the data. Some of these options will include sorting the players on a team by a specific stat, listing a teams roster alphabetically, printing team totals and averages, and listing the teams in a league alphabetically. The three leagues will be stored in a vector, while a red/black tree will be built of all the teams in that league, and a hash table will store the roster for every team. 

How to Run:
1. In order to run this program a user must pass in the two separate text files with the data from each of the leagues. The first command line argument must be the NBA data from the file called "NBA.txt". The second command line argument will be the MLS data from the file called "MLSData.txt".

2. After you run the program with the correct data then it will display a menu prompting the user to select a league. Enter 1 or 2 to select the corresponding league.

3. This will led you into a series of sub-menu's where a user can manipulate the file data to receive specific infomation about his/her favorite teams and sports.

Dependencies:
No dependencies

System Requirements:
This program will run through the Code-block IDE

Group Members:
Ibsa Gishu (github:ibgi5722)
Kurt Boenning (github: kboenning)

Contributors:

Open issues/bugs:
There is one issue with CodeBlocks IDE being unable to find the header files. If the error "fatal error: (headername).h: No such file or directory" occurs, try typing "include/(headername).h" at the top of the file instead of just "(headername).h". If the error still occurs, try typing "../include/(headername).h". One of those two should allow CodeBlocks to find the header file.
