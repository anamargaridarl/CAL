/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if(n <= 1)
	    return 1;
	else
		return n * factorialRecurs(n-1);

}

int factorialDinam(int n)
{
    int result = 1;

    for(int i = n; i > 0; i--)
    {
        result *= i;
    }
	return result;
}
