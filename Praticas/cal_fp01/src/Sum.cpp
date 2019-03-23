/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include "stdlib.h"
#include <time.h>

using namespace std;

/*
void randS(int *sequence, int size)
{
    srand(time(NULL));

    for(int i =0; i < size; i++)
    {
        sequence[i] = rand()%10* +1;
    }
}

void timeCount()
{
    long long int times[50];
    long long int sum;

    for(int i = 0; i < 50; i++)
    {
        sum = 0;

        for(int j  = 0 ; j < 1000; j++)
        {
            int *sequence = (int*)malloc(sizeof(int)*10*i);
            randS(sequence,10*i);
            auto start=std::chrono::high_resolution_clock::now();
            calcSum(sequence,i*10);
            auto finish=std::chrono::high_resolution_clock::now();
            auto mili=chrono::duration_cast<chrono::milliseconds>(finish - start).count();
            sum += mili;
            free(sequence);
        }

        times[i]  = (float)sum;


    }

    for(int i = 0 ; i < 50;i++)
    {
        cout << i << " "<< times[i] << endl;
    }


}

 */

string calcSum(int *sequence, int size) {
    string m;
    int soma[size];
    int ind[size];

    for (int i = 0; i < size; i++) {

        int value = 0;

        for (int j = i; j < size; j++) {
            value += sequence[j];

            if (i == 0 || value < soma[j - i]) {
                soma[j - i] = value;
                ind[j - i] = i;
            }

        }
    }


    for (int k = 0; k < size; k++) {
        m += to_string(soma[k]) + "," + to_string(ind[k]) + ";";
    }

    return m;
}

