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

//Default constructor
Process::Process() {
	PID = 0;
	arrival_time = 0;
	burst = 0;
	priority = 0;
	timeQuantum = 0;
}

//Constructor
Process::Process(int thePID, int theArrivalTime, int theBurst, int thePriority, int theTimeQuantum, int theWaitTime) {
	PID = thePID;
	arrival_time = theArrivalTime;
	burst = theBurst;
	priority = thePriority;
	timeQuantum = theTimeQuantum;
	waitTime = theWaitTime;
}

//Get Function
int Process::getPID() { return PID; }
int Process::getArrival() { return arrival_time; }
int Process::getBurst() { return burst; }
int Process::getPriority() { return priority; }
int Process::getTimeQ() { return timeQuantum; }
int Process::getWaitTime() { return waitTime; }

int Process::newTimeQ(int prio) { //Updated TimeQuantum
	int Tq;
	if (prio < 100) {
		Tq = (140 - prio) * 20;
		return Tq;
	}
	else
	{
		Tq = (140 - prio) * 5;
		return Tq;
	}
}

int Process::priorityUpdate(int waitTime, int currentTime, int arrivalTime, int oldPriority) {
	int totalWait = waitTime;
	int bonus = ceil(10 * totalWait / (currentTime - arrivalTime));
	int newPriority = max(100, min(oldPriority - bonus + 5, 139));
	return newPriority;
}

void Process::sortingFunction(vector <Process> Q) {

	int size = Q.size();
	for (int i = 0; i < size - 1; i++)
		// Last i elements are already in place   
		for (int j = 0; j < size - i - 1; j++) {
			if (Q[j].getPriority() > Q[j + 1].getPriority()) {
				Process temp = Q[j];
				Q[j] = Q[j + 1];
				Q[j + 1] = temp;
			}
		}
}