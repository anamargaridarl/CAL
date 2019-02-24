/*
 * Change.cpp
 */

#include "Change.h"

int lastCoin(int i, int k, int *coinValues)
{
    for(unsigned int j = i-1; j >= 0; j--)
    {
        return coinValues[j];
    }
    return 0;
}

int minCoin(int i, int k, int *coinValue)
{
    if(k == 0|| i == 0)
        return 0;
    else
        return minCoin(i,k-lastCoin())
}
string calcChange(int m, int numCoins, int *coinValues)
{

    return "";
}


