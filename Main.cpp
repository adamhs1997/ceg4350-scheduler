/*
Adam Horvath-Smith
CEG 4350-01
Dr. Yong Pei
Project 1
*/

//Driver program for the scheduler simulation

#include "FileHandler.h"

int main(int argc, char** argv){
	FileHandler mfh;
	int* arr = mfh.parseData("processes.txt");
        cout << "# processes " << mfh.getNumberProcesses() << "\n";
	for (int i = 0; i < mfh.getNumberProcesses() * 3; i++) {
		cout << arr[i] << " ";
	}
	
	return 0;
}
