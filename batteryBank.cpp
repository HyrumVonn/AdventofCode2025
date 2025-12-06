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
    tensIndex = 0;
    onesIndex = 1;

    //loop until end of digit bank
    for(int i = onesIndex; i < inputSize; i++)
    {
        //if the current digit is higher than the tens
        //AND the current digit isn't the last digit (because we must
        //have room for the ones to the right of the tens)
        if((digitBank[i] > digitBank[tensIndex]) && (i < (inputSize - 1)))
        {
            //promote the current digit to the tens digit
            //promote the next digit to the ones digit
            tensIndex = i;
            onesIndex = i + 1;
        }
        else if(digitBank[i] > digitBank[onesIndex])
        {
            //If not, then check whether the current digit is higher than
            //the ones: if so, promote current digit to the ones digit
            onesIndex = i;
        }
    }
}

int batteryBank::ParseDigitsToInt()
{
    int result = 0;

    result = digitBank[tensIndex] * 10 + digitBank[onesIndex];

    return result;
}

batteryBank::~batteryBank()
{
    free(digitBank);
}