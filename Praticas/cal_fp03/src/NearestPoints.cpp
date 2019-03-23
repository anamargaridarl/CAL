/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

using namespace std;

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {

    double min = MAX_DOUBLE;
    double ind1,ind2, distSq;
    ind1  = 0; ind2 = 0; distSq = 0;


	Result res;

	for(int i = 0; i < vp.size()-1; i++)
    {
	    for(int j = i +1; j < vp.size(); j++)
        {
            if (abs(vp.at(i).y - vp.at(j).y) > min)
                continue;

            distSq = vp.at(i).distSquare(vp.at(j));

	        if(distSq < min) {
                min = distSq;
                ind1 = i;
                ind2 = j;
            }

        }
    }

	res.p1 = vp.at(ind1);
	res.p2 = vp.at(ind2);
	res.dmin = vp.at(ind1).distance(vp.at(ind2));

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	// TODO
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
	// TODO
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	// TODO

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	// TODO

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	// TODO

	// Select the best solution from left and right
	// TODO

	// Determine the strip area around middle point
	// TODO

	// Order points in strip area by Y coordinate
	// TODO

	// Calculate nearest points in strip area (using npByY function)
	// TODO

	// Reorder points in strip area back by X coordinate
	//TODO

	//return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {

	sortByX(vp, 0, vp.size() -1);

    if(vp.size() < 2) {
        Result r;
        return r;
    }

    else if(vp.size() == 2)
    {
       return Result(vp.at(0).distance(vp.at(1)) ,vp.at(0), vp.at(1));
    }

    double dist1, dist2,middle;
    vector<Point> vp1;
    vector<Point> vp2;

	dist1 = vp.at(0).x;
	dist2 = vp.at(vp.size()-1).x;

	middle = (dist2 -dist1) /2;

	for(int i =0; i< vp.size(); i++)
    {
	    if(vp.at(i).x <= middle)
	        vp1.push_back(vp.at(i));
	    else
            vp2.push_back(vp.at(i));
    }

    Result r1 = nearestPoints_DC(vp1);
	Result r2 = nearestPoints_DC(vp2);

	double d = min(r1.dmin, r2.dmin);

	vector<Point> brute;

	for(int i = 0; i < vp.size(); i++)
    {
	    if(vp.at(i).x > middle - d && vp.at(i).x < middle + d)
	        brute.push_back(vp.at(i));

    }

    Result r3 = nearestPoints_BF(brute);

	if(r3.dmin < d) {
	    return r3;
    }
	else
    {
	    if(r1.dmin < r2.dmin)
	        return r1;
	    else
	        return r2;
    }


}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
