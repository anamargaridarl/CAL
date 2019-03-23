/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];

    initializeVisited();
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

/*
bool Labirinth::findGoal(int x, int y)
{
    if(labirinth[x][y] == 2)
        return true;
    else
    {
        if(visited[x][y])
            return false;
        else if(labirinth[x][y] == 1) {
            visited[x][y] = true;
            return findGoal(x, y + 1) || findGoal(x + 1, y) || findGoal(x - 1, y) || findGoal(x, y - 1);
        }
        else if(labirinth[x][y] == 0)
            return false;


    }

}
*/

bool Labirinth::findGoal(int x, int y) {
    if (labirinth[x][y] == 2)
        return true;

    if (!visited[x + 1][y]) {
        if (labirinth[x + 1][y] != 0) {
            visited[x][y] = true;
            if (findGoal(x + 1, y))
                return true;
        }
    }

    if (!visited[x - 1][y]) {
        if (labirinth[x - 1][y] != 0) {
            visited[x][y] = true;
            if (findGoal(x - 1, y))
                return true;
        }
    }

    if (!visited[x][y + 1]) {
        if (labirinth[x][y + 1] != 0) {
            visited[x][y] = true;
            if (findGoal(x, y + 1))
                return true;
        }
    }

    if (!visited[x][y - 1]) {
        if (labirinth[x][y - 1] != 0) {
            visited[x][y] = true;
            if (findGoal(x, -1))
                return true;
        }
    }

    return false;


}




