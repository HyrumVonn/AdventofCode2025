#include "batteryBank.hpp"


batteryBank::batteryBank()
{
}

void batteryBank::ParseString(std::string input)
{
    inputSize = input.length();

    //calloc indices to fid num indices to remember
    indices = (int *)calloc(NUM_INDICES, sizeof(int));

    //malloc digitBank to fit all digits
    digitBank = (int *)calloc(inputSize, sizeof(int));

    //Get character from string
    for(int i = 0; i < inputSize; i++)
    {
        //interpret character as 
        digitBank[i] = (int) input[i] - '0';
    }
}

uint64_t batteryBank::MaxJoltage()
{
    uint64_t result = 0;

    //find digits
    FindHighestDigits();

    //parse digits back to int
    result = ParseDigitsToInt();

    return result;
}

//This is the meat of the algorithm
void batteryBank::FindHighestDigits()
{
    //Initialize, assuming that the highest is the first one. 
    
    int highestDigit = 0;
    PromoteToNextDigit(0, highestDigit);

    //loop until end of digit bank
    for(int i = 1; i < inputSize; i++)
    {
        //check whether the highest digit can even fit at current index
        //if not, then look at next highest, until it can
        //(realistically, could be an if, but should be the same)
        if(i + (NUM_INDICES - (highestDigit + 1)) >= inputSize)
        {
            highestDigit++;
        }

        int currentDigit            = digitBank[i];

        int previousHighestIndex    = indices[highestDigit];
        int previousHighest         = digitBank[previousHighestIndex];

        //if the current digit is higher than the furthest digit we can go
        //back, then set that digit to it, and set every following digit 
        //to the right
        if(currentDigit > previousHighest)
        {
            PromoteToNextDigit(i, highestDigit);
        } 
        else
        {
            //check the next highest, and the next, until you
            //pass the current index
            BackCheck(highestDigit, i);
        }
    }
}

void batteryBank::BackCheck(int highestDigit, int currentIndex)
{
    if(indices[highestDigit] > currentIndex)
    {
        return;
    }

    int currentDigit            = digitBank[currentIndex];

    int previousHighestIndex    = indices[highestDigit];
    int previousHighest         = digitBank[previousHighestIndex];

    if(currentDigit > previousHighest)
    {
        PromoteToNextDigit(currentIndex, highestDigit);
        return;
    }

    BackCheck(highestDigit + 1, currentIndex);
}

//Takes in the first "new highest digit". Recursively places each other digit
//immediately to the right of the new highest digit
void batteryBank::PromoteToNextDigit(int currentIndex, int digitNumber)
{
    if((digitNumber >= NUM_INDICES) || (currentIndex > inputSize - 1))
    {
        return;
    }

    indices[digitNumber] = currentIndex;

    currentIndex++;
    digitNumber++;
    PromoteToNextDigit(currentIndex, digitNumber);
}

uint64_t batteryBank::ParseDigitsToInt()
{
    uint64_t result = 0;

    for(int i = 0; i < NUM_INDICES; i++)
    {
        result *= (uint64_t) 10;
        result += (uint64_t) digitBank[indices[i]];
    }

    return result;
}

batteryBank::~batteryBank()
{
    free(indices);
    free(digitBank);
}