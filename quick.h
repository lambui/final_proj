#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <unistd.h> //for sleep()
#include <ctime>
#include "RectStash.h"

using namespace std;

void initialize(int objCount, vector<float> &lam1)
{
	int i = 0;
	while(i < objCount)
	{
		float input;
		input = (float) (rand()%100)/100 + 0.1;
		lam1.push_back(input);
		i++;
	}

	//quick(lam1, 0, lam1.size()-1);

	i = 0;
	while(i < lam1.size())
	{
		cout << lam1[i] << endl;
		i++;
	}
}

void printVec(vector<Rect*> input)
{
	int i = 0;
	while(i < input.size())
	{
		cout << i << "	" << input[i]->height << endl;
		i++;
	}
}

void wait ( float mseconds )
{
	clock_t endwait;
	endwait = clock () + mseconds/1000 * CLOCKS_PER_SEC ;
	while (clock() < endwait) {}
}