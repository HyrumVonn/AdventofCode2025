#include <string>
#include <stdlib.h>

#ifndef __BATTERY_BANK__
#define __BATTERY_BANK__

#define NUM_INDICES 12


class batteryBank
{
    int inputSize;

    int* indices;

    int* digitBank;

    void    FindHighestDigits();
    void    BackCheck(int, int);
    void    PromoteToNextDigit(int, int);
    int     ParseDigitsToInt();

public:
    batteryBank();
    ~batteryBank();

    void    ParseString(std::string);

    int     MaxJoltage();
};

#endif