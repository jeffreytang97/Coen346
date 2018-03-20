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

using namespace std;

class Process {

private:
	string PID;
	int arrival_time;
	int burst;
	int priority;
	int timeQuantum;

public:
	Process(string thePID, int theArrivalTime, int theBurst, int thePriority, int theTimeQuantum) { //Constructor
		PID = thePID;
		arrival_time = theArrivalTime;
		burst = theBurst;
		priority = thePriority;
		timeQuantum = theTimeQuantum;
	}

	string getPID() { return PID; }

	int getArrival() { return arrival_time; }
	int getBurst() { return burst; }
	int getPriority() { return priority; }
	int getTimeQ() { return timeQuantum; }
};


void main() {
	ifstream file("pbs_input.txt");

	bool flag1, flag2; //to indicate which queue of process is active or expired
	int arrival_time;
	int burst;
	int priority;
	string PID;

	struct process {
		string processID;
		int arriveTime;
		int burstTime;
		int priorityOfProcess;
	};

	process *p = new process[sizeof(process)];
	vector <process> PIDVector;
	vector <process> processQ1; //queues for locating processes, both needs to be sorted using the priorities
	vector <process> processQ2;

	if (file.is_open()) { //If the file is opened
		while (file >> PID >> arrival_time >> burst >> priority) {

			p->processID = PID;
			p->arriveTime = arrival_time;
			p->burstTime = burst;
			p->priorityOfProcess = priority;
			PIDVector.push_back(*p);
		}
		file.close();
	}
	else {
		cout << "File is not open" << endl;
	}
}

