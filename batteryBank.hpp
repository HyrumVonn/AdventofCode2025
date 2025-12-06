#include <string>
#include <stdlib.h>
#include <cstdint>

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
    uint64_t     ParseDigitsToInt();

public:
    batteryBank();
    ~batteryBank();

    void    ParseString(std::string);

    uint64_t     MaxJoltage();
};

#endif