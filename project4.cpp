#include <iostream>
#include <fstream>
//ofstream --> Stream class to write file
//ifstream --> Stream class to read from file
//fstream --> Stream class to both read and write from/to file
#include <string>
#include <vector>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <mutex>
#include <sstream>

using namespace std;

struct TLB { //define an object for the TLB which contains 16 entries
	int pageNumber = 0;
	int frameNumber = 0;
};

int bitMaskingOffset(int logicalAddress) { //function to get the offset
	unsigned n = logicalAddress;
	unsigned offset = n & 0xFF; //lower 8 bits for the offset
	return offset;
}

int bitMaskingPageNum(int logicalAddress) {//function to get the page number
	unsigned x = logicalAddress & 0xFF00;  //masking
	unsigned pageNumber = x >> 8; //bit-shifting by 8
	return pageNumber;
}

int concatenate(int frameNumber, int offset) {

	//convert frame number and offset to string so we can concatenate it.
	ostringstream convert;
	convert << frameNumber;
	string frame = convert.str();

	ostringstream c;
	c << offset;
	string off = c.str(); 

	//Concatenate frame number + offset (16 bits now)
	string concat = frame + off;

	//Now, convert back string to int.
	stringstream conversion(concat);
	int physicalAddress = 0;
	conversion >> physicalAddress;

	return physicalAddress; //physical memory is now available!
}

void translation(int listOfLogicalAddress[], int pageTable[], int offset, int pageNumber, int frameNumber, TLB tlb[], int physicalAddress, int tlb_hit, int pageFault) {
	
	bool found;
	
	for (int i = 0; i < sizeof(listOfLogicalAddress); i++)
	{
		offset = bitMaskingOffset(listOfLogicalAddress[i]);
		pageNumber = bitMaskingPageNum(listOfLogicalAddress[i]);

		//search in TLB for a frame associated to the page number
		for (int i = 0; i < 16; i++)
		{
			if ((pageNumber == tlb[i].pageNumber)) {
				physicalAddress = concatenate(tlb[i].frameNumber, offset);
				tlb_hit++;
				found = true;
				break;
			}
			else
				found = false; 
		}

		//If cannot find, go to the page table. (tlb miss)
		if (!found) {
			frameNumber = pageTable[pageNumber]; //corresponding frame number at a certain page number location
			physicalAddress = concatenate(frameNumber, offset);
			found = true; 
			
			//Insert the frame number and page number in TBL
			//Shift every value to the right first
			for (int i = 15; i > 0; i--)
			{
				tlb[i].pageNumber = tlb[i - 1].pageNumber;
				tlb[i].frameNumber = tlb[i - 1].frameNumber;
			}

			//Then, insert the frame number + page number in TBL from the pageTable
			tlb[0].pageNumber = pageNumber;
			tlb[1].frameNumber = frameNumber;
		}

		//If still not found, then there is a page fault.
		if (!found) {
			//Go and read through the backing_store bin file to locate the corresponding page
			//Associate the frame number with the correct page number in the page table
			//Also insert it in the TLB
			pageFault++;
		}
	}
}

int main() {
	
	ifstream myfile("addresses.txt");
	string logicalAddress;
	int listOfLogicalAddress[1000];
	TLB tlb[16]; //the TLB has 16 entries
	int pageTable[256]; //page table with 256 entries 
	int offset = 0;
	int pageNumber = 0;
	int frameNumber = 0;
	int physicalAddress = 0;
	int tlb_hit = 0;
	int pageFault = 0;         

	//Initialise every value of TLB to 0
	for (int i = 0; i < 16; i++)
	{
		tlb[i].pageNumber = 0;
		tlb[i].frameNumber = 0;
	}

	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, logicalAddress))
		{ 
			int logical = stoi(logicalAddress);
			listOfLogicalAddress[i] = logical;
			i++;
		}
		myfile.close();
	}
	else {                                                                
		cout << "Unable to open file";
	}                   

	//translation();

	for (int i = 0; i < 50; i++) //Just a test function to test the functionality of the input read file
	{
		cout << listOfLogicalAddress[i] << " " << bitMaskingOffset(listOfLogicalAddress[i]) << " " << bitMaskingPageNum(listOfLogicalAddress[i]) << endl;
	}

	cin.get();
	return 0;
}