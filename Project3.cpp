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
#include <mutex>

using namespace std;

int numberOfProcess = 0;
int currentVectorPosition = 0;
std::mutex mtx;

class Process {

private:
	int PID;
	int arrival_time;
	int burst;
	int priority;
	int timeQuantum = 0;
	int waitTime = 0;
	int lastFinish = 0;
	string status = "";

public:
	int granted = 0; //when being granted every two times, change priority

	//Default constructor
	Process() {
		PID = 0;
		arrival_time = 0;
		burst = 0;
		priority = 0;
	}

	//Constructor
	Process(int thePID, int theArrivalTime, int theBurst, int thePriority) {
		PID = thePID;
		arrival_time = theArrivalTime;
		burst = theBurst;
		priority = thePriority;
	}

	//Get Function
	int getPID() { return PID; }
	int getArrival() { return arrival_time; }
	int getBurst() { return burst; }
	int getPriority() { return priority; }
	int getTimeQ() { return timeQuantum; }
	int getWaitTime() { return waitTime; }
	string getStatus() { return status; }

	void newTimeQ(int prio) { //Updating TimeQuantum function
		if (prio < 100)
			timeQuantum = (140 - prio) * 20;
		else
			timeQuantum = (140 - prio) * 5;
	}

	int priorityUpdate(int waitTime, int currentTime, int arrivalTime, int oldPriority) { //update priority function
		int totalWait = waitTime;
		int bonus = ceil(10 * totalWait / (currentTime - arrivalTime));
		int newPriority = max(100, min(oldPriority - bonus + 5, 139));
		return newPriority;
	}

	void start(int currentTime) {
		burst = burst - timeQuantum;
		cout << "Time " << currentTime << ", P" << PID << ", Started, Granted " << timeQuantum << endl;
		currentTime += timeQuantum;
		lastFinish = currentTime;
		granted++;
	}

	void paused(int currentTime) {
		status = "Paused";
		cout << "Time " << currentTime << ", P" << PID << ", Paused" << endl;
	}

	void arrived(int currentTime) {
		cout << "Time " << arrival_time << ", P" << PID << ", Arrived" << endl;
	}

	void resumed(int currentTime) {
		waitTime = currentTime - lastFinish;
		burst = burst - timeQuantum;
		cout << "Time " << currentTime << ", P" << PID << ", Started, Granted " << timeQuantum << endl;
		granted++;
	}

	void updated(int currentTime) {
		cout << "Time " << currentTime << ", P" << PID << ", Priority updated to " << priority << endl;
	}

	void terminated(int currentTime, vector<Process> activeQueue) {
		status = "Terminated";
		activeQueue.erase(activeQueue.begin());
		cout << "Time " << currentTime << ", P" << PID << ", Terminated" << endl;
	}

};
	void sortingFunction(vector <Process> Q) { //using bubble sort to sort the queues

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

void addToQueue(vector<Process> processVector, vector <Process> expiredQueue, int currentTime) {

	//processVector is already in order of arrival time. So, it process will be moved to the queues in order.

	if (processVector[currentVectorPosition].getArrival() == currentTime) { // check if arrival time equals currentTime
		expiredQueue.push_back(processVector[currentVectorPosition]); //insert the process in the expired queue
		sortingFunction(expiredQueue); //sort the queue by checking priority everytime a process is inserted
		currentVectorPosition++;
	}
}	

bool activeOrNot(vector <Process> Q1, vector <Process> Q2) {
	bool flag;
	if (Q1.empty()) //if Q1 is empty, flag is false and Q2 is active
		flag = false;
	else if (Q2.empty()) //if Q2 is empty, flag is true and Q1 is active
		flag = true;
	else
		flag = true; //if both are empty, set Q1 to active (doesn't matter which one is active)
	return flag;
}

void scheduler(vector <Process> Q1, vector <Process> Q2, bool flag1, bool flag2, int currentTime, vector <Process> processVector) {

	if (numberOfProcess == 0) {
		return;
	}

	else if (!flag1) { //execute Q2 since Q1 is expired
		for (int i = 0; i < Q2.size - 1; i++)
		{
			if (Q2[i].getStatus == "Started") {

				mtx.lock();
				Q2[i].start(currentTime);
				if (Q2[i].getBurst() == 0) {
					Q2[i].terminated(currentTime, Q2); //delete the object from Q2 vector
					numberOfProcess--;

				}
				else
					Q2[i].paused(currentTime);

				mtx.unlock();
				currentVectorPosition++;
			}
			else if (Q2[i].getStatus == "Arrived") {
				mtx.lock();
				addToQueue(processVector, Q1, currentTime);
				if (Q2[i].getBurst() == 0) {
					Q2[i].terminated(currentTime, Q2); //delete the object from Q2 vector
					numberOfProcess--;
				}
				else
					Q2[i].arrived(currentTime);

				mtx.unlock();
				currentVectorPosition++;
			}
			else if (Q2[i].getStatus == "Resumed") {
				mtx.lock();
				Q2[i].resumed(currentTime);
				if (Q2[i].getBurst() == 0) {
					Q2[i].terminated(currentTime, Q2); //delete the object from Q2 vector
					numberOfProcess--;
					currentVectorPosition++;
				}
				else {
					if (Q2[i].granted == 2) {
						Q2[i].granted = 0; //change granted back to 0
						Q2[i].priorityUpdate(Q2[i].getWaitTime, currentTime, Q2[i].getArrival, Q2[i].getPriority);
					}
					Q2[i].paused(currentTime);
					Q2[i].updated(currentTime);
				}
				mtx.unlock();
				
			}
		}
	}
	else { //execute Q1 if Q2 is expired
		for (int i = 0; i < Q1.size - 1; i++)
		{
			if (Q1[i].getStatus == "Started") {

				mtx.lock();
				Q1[i].start(currentTime);
				if (Q1[i].getBurst() == 0) {
					Q1[i].terminated(currentTime, Q1); //delete the object from Q2 vector
					numberOfProcess--;
				}
				else
					Q1[i].paused(currentTime);

				mtx.unlock();
				currentVectorPosition++;
			}
			else if (Q1[i].getStatus == "Arrived") {
				mtx.lock();
				addToQueue(processVector, Q2, currentTime);
				if (Q1[i].getBurst() == 0) {
					Q1[i].terminated(currentTime, Q1); //delete the object from Q2 vector
					numberOfProcess--;
				}
				else
					Q1[i].arrived(currentTime);

				mtx.unlock();
				currentVectorPosition++;
			}
			else if (Q1[i].getStatus == "Resumed") {
				mtx.lock();
				Q1[i].resumed(currentTime);
				if (Q1[i].getBurst() == 0) {
					Q1[i].terminated(currentTime, Q1); //delete the object from Q2 vector
					numberOfProcess--;
				}
				else {
					if (Q1[i].granted == 2) {
						Q1[i].granted = 0; //change granted back to 0
						Q1[i].priorityUpdate(Q1[i].getWaitTime, currentTime, Q1[i].getArrival, Q1[i].getPriority);
					}
					Q1[i].paused(currentTime);
					Q1[i].updated(currentTime);
				}
				mtx.unlock();
				currentVectorPosition++;
			}
		}
	}
};

void main() {
	ifstream file("pbs_input.txt");

	bool flag1 = true; 
	bool flag2 = false; //to indicate which queue of process is active or expired
	int arrival_time;
	int burst;
	int priority;
	int PID;
	int time = 1000; //start time

	vector <Process> processVector;
	vector <Process> processQ1; //queues for locating processes, both needs to be sorted using the priorities
	vector <Process> processQ2;

	if (file.is_open()) { //If the file is opened
		while (file >> PID >> arrival_time >> burst >> priority) {
			Process p(PID, arrival_time, burst, priority);
			processVector.push_back(p);
			numberOfProcess++;
		}
		file.close();
	}
	else {
		cout << "File is not open" << endl;
	}

	processVector[0].getArrival = time;

	thread prioritycheduler(scheduler, processQ1, processQ2, flag1, flag2, time, processVector);

	while (currentVectorPosition < numberOfProcess && time < 33000) {
		scheduler(processQ1, processQ2, flag1, flag2, time, processVector); //time will be updated in the scheduler function
	}
}