/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
    if (n == 0 || k < 1 || k > n )
        return 0;
    else if(k == 1 || n == k )
       return 1;
    else
        return s_recursive(n-1,k-1) + k*s_recursive(n-1,k) ;
}

int s_dynamic(int n,int k)
{
    vector<int> v(k,1);

	return 1;
}


int b_recursive(int n)
{
    for (int i = 1; i <= n; i++)
	    return s_recursive(n,i);
}

int b_dynamic(int n)
{
	return 0;
}


