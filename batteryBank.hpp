#include <string>
#include <stdlib.h>

#ifndef __BATTERY_BANK__
#define __BATTERY_BANK__


class batteryBank
{
    int tensIndex;
    int onesIndex;

    int highestTens;
    int highestOnes;

    int inputSize;

    int* digitBank;

    void    FindHighestDigits();
    int     ParseDigitsToInt();

public:
    batteryBank();
    ~batteryBank();

    void    ParseString(std::string);

    int     MaxJoltage();
};

#endif