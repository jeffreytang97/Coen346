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
	int PID;
	int arrival_time;
	int burst;
	int priority;
	int timeQuantum;

public:
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
		PID = thePID;
		arrival_time = theArrivalTime;
		burst = theBurst;
		priority = thePriority;
		timeQuantum = theTimeQuantum;
	}

	//get functions
	int getPID() { return PID; }
	int getArrival() { return arrival_time; }
	int getBurst() { return burst; }
	int getPriority() { return priority; }
	int getTimeQ() { return timeQuantum; }

	int newTimeQ(int prio) {
		int Tq;
		if (prio < 100) {
			Tq = (140 - prio) * 20;
			return 
		}
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

