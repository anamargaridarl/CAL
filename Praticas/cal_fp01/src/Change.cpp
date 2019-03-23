/*
 * Change.cpp
 */

#include "Change.h"
#include <cstring>
#include <iostream>

using namespace std;


string calcChange(int m, int numCoins, int *coinValues)
{
    int minCoins[m+1];
    int lastCoin[m+1];

    minCoins[0] =0;

    for(int i = 1; i < m +1;i++)
    {
        minCoins[i] = 2000;
        lastCoin[i]=0;
    }

    if(m == 0)
        return "";
    if(m < coinValues[0])
        return "-";

    for(int i = 0; i < numCoins; i++) {
        for (int k = coinValues[i]; k <= m; k++) {
            if (1 + minCoins[k - coinValues[i]] < minCoins[k]) {
                minCoins[k] = 1 + minCoins[k - coinValues[i]];
                lastCoin[k] = i;
            }
        }
    }

    string change = "";

    for(int k = m; k > 0; k -= coinValues[lastCoin[k]])
    {
        change = change + to_string(coinValues[lastCoin[k]]) + ";";
    }

    return change;


}


