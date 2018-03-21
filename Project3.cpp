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
<<<<<<< HEAD
	//Default constructor
	Process() {
		PID = 0;
		arrival_time = 0;
		burst = 0;
		priority = 0;
		timeQuantum = 0;
	}

	//Constructor
	Process(int thePID, int theArrivalTime, int theBurst, int thePriority, int theTimeQuantum) { 
=======
	Process(int thePID, int theArrivalTime, int theBurst, int thePriority, int theTimeQuantum, int theWaitTime) { //Constructor
>>>>>>> 69e75485bf5fb103f4d417de25405b50b363174a
		PID = thePID;
		arrival_time = theArrivalTime;
		burst = theBurst;
		priority = thePriority;
		timeQuantum = theTimeQuantum;
		waitTime = theWaitTime;
	}

<<<<<<< HEAD
	//get functions
=======
	//Get Function
>>>>>>> 69e75485bf5fb103f4d417de25405b50b363174a
	int getPID() { return PID; }
	int getArrival() { return arrival_time; }
	int getBurst() { return burst; }
	int getPriority() { return priority; }
	int getTimeQ() { return timeQuantum; }
	int getWaitTime() { return waitTime; }

	int newTimeQ(int prio) { //Updated TimeQuantum
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

	int priorityUpdate(int waitTime, int currentTime, int arrivalTime, int oldPriority) {
		int totalWait = waitTime;
		int bonus = ceil(10 * totalWait / (currentTime - arrivalTime));
		int newPriority = max(100, min(oldPriority - bonus + 5, 139));
		return newPriority;
	}

};


void main() {
	ifstream file("pbs_input.txt");

	bool flag1, flag2; //to indicate which queue of process is active or expired
	int arrival_time;
	int burst;
	int priority;
	string PID;
	 
	vector <Process> processVector;
	vector <Process> processQ1; //queues for locating processes, both needs to be sorted using the priorities
	vector <Process> processQ2;

	if (file.is_open()) { //If the file is opened
		while (file >> PID >> arrival_time >> burst >> priority) {
			Process p = Process();
			p.getPID = PID;
			p.getArrival = arrival_time;    
			p.getBurst = burst;
			p.getPriority = priority;
			processVector.push_back(p);
		}  
		file.close();    
	}
	else {
		cout << "File is not open" << endl;
	}
}

void sortingFunction(vector <Process> Q) {

	int size = Q.size();
	for (int i = 0; i < size - 1; i++)
		// Last i elements are already in place   
		for (int j = 0; j < size - i - 1; j++) {
			if (Q[j].getPriority > Q[j + 1].getPriority) {
				Process temp = Q[j];
				Q[j] = Q[j+1];
				Q[j+1] = temp;
			}
		}
}

