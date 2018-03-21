#ifndef Process_hpp
#define Process_hpp

#include <iostream>
#include <fstream>
//ofstream --> Stream class to write file
//ifstream --> Stream class to read from file
//fstream --> Stream class to both read and write from/to file
#include <thread>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Project3.h"

using namespace std;

class Process {

private:
	int PID;
	int arrival_time;
	int burst;
	int priority;
	int timeQuantum;
	int waitTime;

public:
	Process();
	Process(int, int, int, int, int, int);
	int getPID();
	int getArrival();
	int getBurst();
	int getPriority();
	int getTimeQ();
	int getWaitTime();
	int newTimeQ(int);
	int priorityUpdate(int, int, int, int);
	void sortingFunction(vector<Process>);
};

#endif /*Process_hpp*/