#include "batteryBank.hpp"

batteryBank::batteryBank()
{

}

void batteryBank::ParseString(std::string input)
{
    inputSize = input.length();

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
    //initialize tens and ones, such that it will always start
    //with 10s being the first digit, and 1s being the second
    highestTens = -1;
    highestOnes = -1;

    //loop until end of digit bank
    for(int i = 0; i < inputSize; i++)
    {
        //if the current digit is higher than the tens...
        //AND the current digit isn't the last digit...
        if((digitBank[i] > highestTens) && (i < (inputSize - 1)))
        {
            //set the current digit to the tens
            //set the ones to the next digit after the tens
            highestTens = digitBank[i];
            highestOnes = digitBank[i + 1];
        }
        else if(digitBank[i] > highestOnes)
        {
            //If not, then check whether the current digit is higher than
            //the ones: if so, set the ones to that digit
            highestOnes = digitBank[i];
        }
    }
}

int batteryBank::ParseDigitsToInt()
{
    int result = 0;

    result = highestTens * 10 + highestOnes;

    return result;
}

batteryBank::~batteryBank()
{
    free(digitBank);
}