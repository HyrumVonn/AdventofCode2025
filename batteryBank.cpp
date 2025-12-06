#include "batteryBank.hpp"

#include <iostream>
#include <ostream>

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

int batteryBank::MaxJoltage()
{
    int result = 0;

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

        std::cout << "Comparing " << currentDigit << " (" << i;
        std::cout << ") against " <<previousHighest  << " (";
        std::cout << previousHighestIndex << ") at [" << highestDigit << "]" <<std::endl;
        //if the current digit is higher than the furthest digit we can go
        //back, then set that digit to it, and set every following digit 
        //to the right
        if(currentDigit > previousHighest)
        {
            std::cout << " Yes!Begin Promotion:" << std::endl;
            PromoteToNextDigit(i, highestDigit);
        } 
        else
        {
            //check the next highest... and the next...
        }
    }
}

//Takes in the first "new highest digit". Recursively places each other digit
//immediately to the right of the new highest digit
void batteryBank::PromoteToNextDigit(int currentIndex, int digitNumber)
{
    std::cout << "\tPromoting " << digitBank[currentIndex] << " (" << currentIndex;
    std::cout << ") to digit number " <<digitNumber  << " (previously ";
    std::cout << digitBank[indices[digitNumber]] << ")" << std::endl;
    if((digitNumber >= NUM_INDICES) || (currentIndex > inputSize - 1))
    {
        std::cout << "ERRR! Promotion rejected" << std::endl;
        return;
    }

    indices[digitNumber] = currentIndex;

    currentIndex++;
    digitNumber++;
    PromoteToNextDigit(currentIndex, digitNumber);
}

int batteryBank::ParseDigitsToInt()
{
    int result = 0;

    std::cout << "Current indices of digits:" << std::endl;

    for(int i = 0; i < NUM_INDICES; i++)
    {
        std::cout << indices[i] << " ";
        result *= 10;
        result += indices[i];
    }

    std::cout << std::endl;


    std::cout << "And associated Digits:" << std::endl;

    for(int i = 0; i < NUM_INDICES; i++)
    {
        std::cout << digitBank[indices[i]];
        //result *= 10;
        //result += indices[i];
    }

    std::cout << std::endl;

    return result;
}

batteryBank::~batteryBank()
{
    free(indices);
    free(digitBank);
}