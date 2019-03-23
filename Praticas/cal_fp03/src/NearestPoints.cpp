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
	return nearestPoints_BF(vp);

}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
    for(int i = left; i <= right; i++){
        for(int j = i + 1; j <= right; j++){
            if(abs(vp[j].y - vp[i].y) >= res.dmin)break;
            else{
                if(vp[i].distance(vp[j]) < res.dmin){
                    res.p1 = vp[i];
                    res.p2 = vp[j];
                    res.dmin = vp[i].distance(vp[j]);
                }
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {

    Result r;


    // Only one point; returns something very big (those points will be taken in consideration in the middle strip)
    if(left >= right) {
        r.dmin = MAX_DOUBLE;
        return r;
    }

    //Two points
    else if(right - left ==1)
    {
        r.dmin = vp[left].distance(vp[right]);
        r.p1 = vp[left];
        r.p2 = vp[right];
        return r;
    }

    //Calculates middle distance
    int middle;

    middle = (right + left) /2;

    //Calculates smallest difference in each side

    Result r1 = np_DC(vp, left, middle,1);
    Result r2 = np_DC(vp, middle+1,right,1);

    r = r1.dmin > r2.dmin ? r2 : r1;

    //Handles middle strip
    Point mid = vp[middle];
    int left_strip = middle, right_strip = middle + 1;
    for(; vp[left_strip].distance(mid) < r.dmin && left_strip >= left; left_strip--);
    for(; vp[right_strip].distance(mid) < r.dmin && right_strip <= right; right_strip++);

    // Order points in strip area by Y coordinate
    sortByY(vp, left_strip, right_strip);

    // Calculate nearest points in strip area (using npByY function)
    npByY(vp, left_strip, right_strip, r);

    // Reorder points in strip area back by X coordinate
    sortByX(vp, left_strip, right_strip);

    return r;


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
	return np_DC(vp,0, vp.size()-1,1);

}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
