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
    if(inFile.fail())
    {
        cout<<"The file was not opened successfully"<<endl;
    }
    else
    {
        int i = 0;
        while(getline(inFile, strLine))
        {
            /*i = 0;
            istringstream ss(strLine);
            while(getline(ss, parts, ','))
            {
                if(i == 0)
                {
                    ranking = std::stoi(parts);
                    i++;
                }
                else if(i == 1)
                {
                    movieName = parts;
                    i++;
                }
                else if(i == 2)
                {
                    year = std::stoi(parts);
                    i++;
                }
                else if(i == 3)
                {
                    stock = std::stoi(parts);
                    i++;
                }
            }*/
            cout<<strLine<<endl;
        }
    }
    return 0;
}
