
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
#include "Project3.cpp"

using namespace std;

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
			p.getPID() = PID;
			p.getArrival() = arrival_time;
			p.getBurst() = burst;
			p.getPriority() = priority;
			processVector.push_back(p);
		}
		file.close();
	}
	else {
		cout << "File is not open" << endl;
	}
}

bool checkActiveOrNot(vector<Process> queue) {
	
	bool flag;

	if (queue.empty())
		flag = false;
	else
		flag = true;

	return flag;
}

