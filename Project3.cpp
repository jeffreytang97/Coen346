#include <iostream>
#include <fstream>
//ofstream --> Stream class to write file
//ifstream --> Stream class to read from file
//fstream --> Stream class to both read and write from/to file
#include <pthread.h>
#include <string>
#include <vector>

using namespace std;

void main (){
	ifstream file ("pbs_input.txt");
	
	bool flag1, flag2; //to indicate which queue of process is active or expired

	vector <int> processQ1; //queues for locating processes
	vector <int> processQ2;
	vector <string> PIDVector;

	struct parameters {
		string PID;
		int arrival_time;
		int burst;
		int priority;
	};

	parameters process;

	//vector <int> arriveVector;
	//vector <int> burstVector;
	//vector <int> priorityVector;
	
	if(file.is_open()){ //If the file is opened
		while (file >> PID >> arrival_time >> burst >> priority){
			PIDVector.push_back(PID);

			//arriveVector.push_back(arrival_time);
			//burstVector.push_back(burst);
			//priorityVector.push_back(priority);
			
			/*Chaque index des vectors represente infos d'un Process*/
		}
		file.close();
	}
	else{
		cout << "File is not open" << endl;
	}
}
