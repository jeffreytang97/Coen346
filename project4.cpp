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
#include <cstddef> // for null

using namespace std;

int listOfLogicalAddress[1000];
int pageTable[256]; //page table with 256 entries 
int physicalMemory[256];

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

int getDataFromBackingStore(int pageNumber) {
	FILE *f;
	int *storage;

	//open file in read mode
	f = fopen("BACKING_STORE.bin", "r");

	//a size of page is 256 bytes, so if we multiply by page number, we will get to the right page.
	int locationOfPage = 256 * pageNumber;

	//Looking for the location of the page
	fseek(f, locationOfPage, SEEK_SET);

	//Store data in temporary storage in memory
	fread(storage, 1, 256, f);

	int free_frame = getNextFreeFrame();
	physicalMemory[free_frame] = *storage;

	return free_frame;
}

int getNextFreeFrame() {
	
	for (int index = 0; index < 256; index++)
	{
		if (physicalMemory[index] == NULL) {
			return index;
		}
	}
}

int pageFaultRate() {
	return;
}

int tlbHitRate() {
	return;
}

int main() {
	
	string logicalAddress;
	TLB tlb[16]; //the TLB has 16 entries
	int offset = 0;
	int pageNumber = 0;
	int frameNumber = 0;
	int physicalAddress = 0;
	int tlb_hit = 0;
	int pageFault = 0;  
	bool found;
	bool valid = false;

	//Initialise every value of TLB to 0
	for (int i = 0; i < 16; i++)
	{
		tlb[i].pageNumber = 0;
		tlb[i].frameNumber = 0;
	}

	ifstream myfile("addresses.txt"); //Opening file
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

	//Translation execution
	for (int i = 0; i < sizeof(listOfLogicalAddress); i++)
	{
		//Bit masking
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

		//If not found in TLB
		if (!found) { 
			do {
				if (pageTable[pageNumber] < 0) { // If not found in the pageTable, go grab the page in backing_store
					pageFault++;
					frameNumber = getDataFromBackingStore(pageNumber);
					pageTable[pageNumber] = frameNumber;
					//Then, start re-executing the process
				}
				else { //If frame exist at location of page number

					int frameUsed = 0;
					frameUsed = pageTable[pageNumber]; 
					physicalAddress = concatenate(frameUsed, offset);
					found = true;
					valid = true;

					//Insert the frame number and page number in TLB
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
			}while (!valid); 
		}
	} 

	//statistics output to do

	for (int i = 0; i < 50; i++) //Just a test function to test the functionality of the input read file
	{
		cout << listOfLogicalAddress[i] << " " << bitMaskingOffset(listOfLogicalAddress[i]) << " " << bitMaskingPageNum(listOfLogicalAddress[i]) << endl;
	}

	cin.get();
	return 0;
}