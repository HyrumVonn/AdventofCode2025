#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdio>
#include <vector>

#include "batteryBank.hpp"

using namespace std;

int main()
{

    ifstream iFile;
    string iFileName = "";

    do
    {
        cout << "Input Valid File Name:" << endl;

        cin >> iFileName; 

        iFile.open(iFileName, ios::in );
    } while (iFile.is_open() == false);


    //get each line of input
    //while (input = true)
    string input = "";

    uint64_t maxJoltage = 0;

    while (iFile >> input)
    {        
        batteryBank bank;

        bank.ParseString(input);

        maxJoltage += bank.MaxJoltage();
    }

    cout << "Largest Joltage: " << maxJoltage << endl;


    return 0;
}